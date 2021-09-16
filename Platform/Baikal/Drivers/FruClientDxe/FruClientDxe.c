/** @file
  Copyright (c) 2021, Baikal Electronics, JSC. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <Library/BaikalI2cLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/TimeBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/I2cIo.h>
#include <Protocol/FruClient.h>
#include "FruInternals.h"

#define EEPROM_I2C_BUS   0
#define EEPROM_SIZE      4096

#define MULTIRECORD_TYPEID_MAC0  0xC0
#define MULTIRECORD_TYPEID_MAC1  0xC6
#define MULTIRECORD_TYPEID_MAC2  0xC7
#define MULTIRECORD_TYPEID_MACN  0xC8

STATIC
UINTN
EFIAPI
FruClientGetBoardMfgDateTime (
  VOID
  );

STATIC
UINTN
EFIAPI
FruClientReadBoardManufacturer (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadBoardName (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadBoardSerialNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadBoardPartNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadBoardFileId (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductManufacturer (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductName (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductPartNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductVersion (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductSerialNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductAssetTag (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
EFIAPI
FruClientReadProductFileId (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
EFI_STATUS
EFIAPI
FruClientGetMultirecordMacAddr (
  IN   CONST UINTN             MacAddrIdx,
  OUT  EFI_MAC_ADDRESS *CONST  MacAddr
  );

STATIC
UINTN
FruReadTypLenEncBoardData (
  IN   CONST UINTN   FieldIdx,
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC
UINTN
FruReadTypLenEncProductData (
  IN   CONST UINTN   FieldIdx,
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  );

STATIC UINT8  *mFruBuf;
STATIC UINTN   mFruBufSize;

typedef struct {
  UINTN                           OperationCount;
  EFI_I2C_OPERATION               Address;
  EFI_I2C_OPERATION               Data;
} EEPROM_I2C_READ_REQUEST;

STATIC
EFI_STATUS
LocateI2cEepromDevice (
  OUT EFI_I2C_IO_PROTOCOL     **Instance
)
{
  EFI_I2C_IO_PROTOCOL *Dev;
  EFI_STATUS          Status;
  EFI_HANDLE          *HandleBuffer;
  UINTN               HandleCount;
  UINTN               Index;
  BOOLEAN             Found;

  if (Instance == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Retrieve all I2C device I/O handles in the handle database
  //
  Status = gBS->LocateHandleBuffer (ByProtocol,
                                    &gEfiI2cIoProtocolGuid,
                                    NULL,
                                    &HandleCount,
                                    &HandleBuffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Locate protocol instance matching specific device
  //
  Found = FALSE;
  for (Index = 0; (Index < HandleCount) && !Found; Index++) {
    Status = gBS->OpenProtocol (
                    HandleBuffer[Index],
                    &gEfiI2cIoProtocolGuid,
                    (VOID **) &Dev,
                    gImageHandle,
                    HandleBuffer[Index],
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (!EFI_ERROR (Status) &&
        CompareGuid (Dev->DeviceGuid, &gEepromI2cDeviceGuid)) {
      Found = TRUE;
      *Instance = Dev;
    }
  }

  //
  // Free the handle array
  //
  gBS->FreePool (HandleBuffer);

  return Found ? EFI_SUCCESS : EFI_NOT_FOUND;
}

/**
  Read FRU data.

  @param  Address               Memory address.
  @param  Size                  Number of bytes to read.
  @param  Data                  Pointer to the buffer to store the data in.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_DEVICE_ERROR      The data could not be retrieved from memory
                                due to hardware error.
**/
STATIC
EFI_STATUS
I2cReadFruData (
  IN  UINT16                      Address,
  IN  UINT16                      Size,
  OUT UINT8                       *Data
  )
{
  EFI_I2C_IO_PROTOCOL     *I2cIo;
  EEPROM_I2C_READ_REQUEST  Request;
  EFI_STATUS               Status;
  UINT8                    AddressBuffer[2];

  Status = LocateI2cEepromDevice (&I2cIo);
  if (!EFI_ERROR (Status)) {
    AddressBuffer[0] = (Address >> 8) & 0xFF;
    AddressBuffer[1] = Address & 0xFF;

    Request.OperationCount = 2;
    Request.Address.Flags = 0;
    Request.Address.LengthInBytes = sizeof (AddressBuffer);
    Request.Address.Buffer = AddressBuffer;
    Request.Data.Flags = I2C_FLAG_READ;
    Request.Data.LengthInBytes = Size;
    Request.Data.Buffer = Data;
    Status = I2cIo->QueueRequest (I2cIo, 0,
                                  NULL,
                                  (EFI_I2C_REQUEST_PACKET *)&Request,
                                  NULL);
    if (EFI_ERROR (Status)) {
      if (Status != EFI_TIMEOUT) {
        DEBUG ((EFI_D_ERROR, "I2cEeprom: read @%04X failed: %r\r\n",
                Address, Status));
      }
      Status = EFI_DEVICE_ERROR;
    }
  } else {
    DEBUG ((EFI_D_ERROR, "%a: unable to locate FRU EEPROM device, Status: %r\n", __FUNCTION__, Status));
  }
  return Status;
}

EFI_STATUS
EFIAPI
FruClientDxeInitialize (
  IN  EFI_HANDLE         ImageHandle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;

  STATIC FRU_CLIENT_PROTOCOL  mFruClientProtocol = {
    FruClientGetBoardMfgDateTime,
    FruClientReadBoardManufacturer,
    FruClientReadBoardName,
    FruClientReadBoardSerialNumber,
    FruClientReadBoardPartNumber,
    FruClientReadBoardFileId,
    FruClientReadProductManufacturer,
    FruClientReadProductName,
    FruClientReadProductPartNumber,
    FruClientReadProductVersion,
    FruClientReadProductSerialNumber,
    FruClientReadProductAssetTag,
    FruClientReadProductFileId,
    FruClientGetMultirecordMacAddr
  };

  Status = gBS->AllocatePool (EfiBootServicesData, EEPROM_SIZE, (VOID **) &mFruBuf);
  if (EFI_ERROR (Status)) {
    DEBUG ((
      EFI_D_ERROR,
      "%a: unable to allocate mFruBuf, Status: %r\n",
      __FUNCTION__,
      Status
      ));
    return Status;
  }

  Status = I2cReadFruData(0, EEPROM_SIZE, (UINT8 *) mFruBuf);
  if (EFI_ERROR(Status)) {
    return Status;
  } else {
    mFruBufSize = EEPROM_SIZE;
  }

  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gFruClientProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mFruClientProtocol
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((
      EFI_D_ERROR,
      "%a: unable to install FruClientProtocol, Status: %r\n",
      __FUNCTION__,
      Status
      ));
    return Status;
  }

#if !defined (MDEPKG_NDEBUG)
  if (mFruBufSize == EEPROM_SIZE) {
    UINTN            Idx;
    EFI_MAC_ADDRESS  MacAddr;
    UINTN            RetVal;
    CHAR8            Str[FRU_TYPLENSTR_MAX_SIZE];

    RetVal = mFruClientProtocol.GetBoardMfgDateTime ();
    if (RetVal > 0) {
      EFI_TIME  EfiTime;
      UINT32    EpochSeconds;

      EfiTime.Year   = 1996;
      EfiTime.Month  = 1;
      EfiTime.Day    = 1;
      EfiTime.Hour   = 0;
      EfiTime.Minute = 0;
      EfiTime.Second = 0;

      EpochSeconds = EfiTimeToEpoch (&EfiTime);
      EpochSeconds += RetVal * 60;
      EpochToEfiTime (EpochSeconds, &EfiTime);

      DEBUG ((
        EFI_D_INFO,
        "FRU board mfg.date/time:   %04u-%02u-%02u %02u:%02u\n",
        EfiTime.Year,
        EfiTime.Month,
        EfiTime.Day,
        EfiTime.Hour,
        EfiTime.Minute
        ));
    }

    RetVal = mFruClientProtocol.ReadBoardManufacturer (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU board manufacturer:    %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadBoardName (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU board name:            %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadBoardSerialNumber (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU board serial number:   %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadBoardPartNumber (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU board part number:     %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadBoardFileId (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU board file ID:         %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductManufacturer (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product manufacturer:  %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductName (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product name:          %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductPartNumber (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product part number:   %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductVersion (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product version:       %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductSerialNumber (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product serial number: %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductAssetTag (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product asset tag:     %a\n", Str));
    }

    RetVal = mFruClientProtocol.ReadProductFileId (Str, sizeof (Str));
    if (RetVal > 0) {
      DEBUG ((EFI_D_INFO, "FRU product file ID:       %a\n", Str));
    }

    for (Idx = 0; Idx < 2; ++Idx) {
      gBS->SetMem (&MacAddr, sizeof (MacAddr), 0);
      Status = mFruClientProtocol.GetMultirecordMacAddr (Idx, &MacAddr);
      if (Status == EFI_SUCCESS) {
        DEBUG ((
          EFI_D_INFO,
          "FRU MAC address #%u:        %02x:%02x:%02x:%02x:%02x:%02x\n",
          Idx,
          MacAddr.Addr[0],
          MacAddr.Addr[1],
          MacAddr.Addr[2],
          MacAddr.Addr[3],
          MacAddr.Addr[4],
          MacAddr.Addr[5]
          ));
      }
    }
  }
#endif

  return EFI_SUCCESS;
}

STATIC
UINTN
EFIAPI
FruClientGetBoardMfgDateTime (
  VOID
  )
{
  CONST UINT8  *BoardArea;
  UINTN         BoardAreaSize;
  EFI_STATUS    Status;

  if (mFruBufSize != EEPROM_SIZE) {
    return 0;
  }

  Status = FruInternalsBoardAreaLocate (
             mFruBuf,
             mFruBufSize,
             &BoardArea,
             &BoardAreaSize
             );

  if (EFI_ERROR (Status) || BoardAreaSize < 6) {
    return 0;
  }

  return (BoardArea[3] <<  0) |
         (BoardArea[4] <<  8) |
         (BoardArea[5] << 16);
}

STATIC
UINTN
EFIAPI
FruClientReadBoardManufacturer (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncBoardData (0, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadBoardName (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncBoardData (1, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadBoardSerialNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncBoardData (2, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadBoardPartNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncBoardData (3, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadBoardFileId (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncBoardData (4, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductManufacturer (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (0, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductName (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (1, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductPartNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (2, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductVersion (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (3, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductSerialNumber (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (4, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductAssetTag (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (5, DstBuf, DstBufSize);
}

STATIC
UINTN
EFIAPI
FruClientReadProductFileId (
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  return FruReadTypLenEncProductData (6, DstBuf, DstBufSize);
}

STATIC
EFI_STATUS
EFIAPI
FruClientGetMultirecordMacAddr (
  IN   CONST UINTN             MacAddrIdx,
  OUT  EFI_MAC_ADDRESS *CONST  MacAddr
  )
{
  CONST UINT8         *MrecArea;
  MULTIRECORD_HEADER   MrecHdr;
  UINTN                MrecType;
  EFI_STATUS           Status;

  ASSERT (MacAddr != NULL);

  if (mFruBufSize != EEPROM_SIZE) {
    return EFI_DEVICE_ERROR;
  }

  Status = FruInternalsMultirecordAreaLocate (mFruBuf, mFruBufSize, &MrecArea);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (MacAddrIdx == 0) {
    MrecType = MULTIRECORD_TYPEID_MAC0;
  } else if (MacAddrIdx == 1) {
    MrecType = MULTIRECORD_TYPEID_MAC1;
  } else if (MacAddrIdx == 2) {
    MrecType = MULTIRECORD_TYPEID_MAC2;
  } else {
    MrecType = MULTIRECORD_TYPEID_MACN;
  }

  while (FruInternalsMultirecordParseHeader (
           MrecArea,
           (mFruBuf + mFruBufSize) - MrecArea,
           &MrecHdr
           ) == EFI_SUCCESS) {
    if (MrecHdr.TypeId == MrecType) {
      if (FruInternalsMultirecordCheckData (MrecArea,
                                            (mFruBuf + mFruBufSize) - MrecArea,
                                            &MrecHdr
                                            ) == EFI_SUCCESS) {
        UINTN  Idx;
        CONST UINT8  *MacData = MrecArea + sizeof (MULTIRECORD_HEADER);
        if (((MacAddrIdx <= 2) && (MrecHdr.Length != 6)) ||
            ((MacAddrIdx > 2) && (MrecHdr.Length < (MacAddrIdx - 2) * 6 + 1))) {
          return EFI_INVALID_PARAMETER;
        }
        if (MacAddrIdx > 2) {
          if ((MacAddrIdx - 2) > MacData[0]) {
            return EFI_INVALID_PARAMETER;
          } else {
            MacData = MacData + 1 + 6 * (MacAddrIdx - 3);
          }
        }

        for (Idx = 0; Idx < 6; ++Idx) {
          MacAddr->Addr[Idx] = MacData[Idx];
        }

        return EFI_SUCCESS;
      }
    }

    if (MrecHdr.Format & 0x80) {
      break;
    }

    MrecArea += sizeof (MULTIRECORD_HEADER) + MrecHdr.Length;
  }

  return EFI_INVALID_PARAMETER;
}

STATIC
UINTN
FruReadTypLenEncBoardData (
  IN   CONST UINTN   FieldIdx,
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  CONST UINT8  *BoardArea;
  UINTN         BoardAreaSize;
  UINTN         DstStrLen = DstBufSize;
  CONST UINT8  *EncData;
  UINTN         Idx;
  EFI_STATUS    Status;

  ASSERT (FieldIdx < 5);
  ASSERT (DstBuf != NULL);
  ASSERT (DstBufSize > 0);

  if (mFruBufSize != EEPROM_SIZE) {
    return 0;
  }

  Status = FruInternalsBoardAreaLocate (
             mFruBuf,
             mFruBufSize,
             &BoardArea,
             &BoardAreaSize
             );
  if (EFI_ERROR (Status) || BoardAreaSize <= 6) {
    return 0;
  }

  EncData = BoardArea + 6;
  for (Idx = 0; Idx < FieldIdx; ++Idx) {
    EncData = FruInternalsTypLenEncReadData (EncData, NULL, NULL);
    if (EncData == NULL || EncData >= BoardArea + BoardAreaSize) {
      return 0;
    }
  }

  FruInternalsTypLenEncReadData (EncData, DstBuf, &DstStrLen);
  return DstStrLen;
}

STATIC
UINTN
FruReadTypLenEncProductData (
  IN   CONST UINTN   FieldIdx,
  OUT  CHAR8 *CONST  DstBuf,
  IN   CONST UINTN   DstBufSize
  )
{
  UINTN         DstStrLen = DstBufSize;
  CONST UINT8  *EncData;
  UINTN         Idx;
  CONST UINT8  *ProductArea;
  UINTN         ProductAreaSize;
  EFI_STATUS    Status;

  ASSERT (FieldIdx < 7);
  ASSERT (DstBuf != NULL);
  ASSERT (DstBufSize > 0);

  if (mFruBufSize != EEPROM_SIZE) {
    return 0;
  }

  Status = FruInternalsProductAreaLocate (
             mFruBuf,
             mFruBufSize,
             &ProductArea,
             &ProductAreaSize
             );

  if (EFI_ERROR (Status) || ProductAreaSize <= 3) {
    return 0;
  }

  EncData = ProductArea + 3;
  for (Idx = 0; Idx < FieldIdx; ++Idx) {
    EncData = FruInternalsTypLenEncReadData (EncData, NULL, NULL);
    if (EncData == NULL || EncData >= ProductArea + ProductAreaSize) {
      return 0;
    }
  }

  FruInternalsTypLenEncReadData (EncData, DstBuf, &DstStrLen);
  return DstStrLen;
}
