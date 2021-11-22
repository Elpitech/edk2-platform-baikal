#ifndef __BOARD_CONFIG_DXE_H__
#define __BOARD_CONFIG_DXE_H__

#include <Uefi.h>

//
// Libraries
//
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//
// UEFI Driver Model Protocols
//
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiPackageList.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/ComponentName.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/FdtClient.h>
// Added for HII
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiString.h>
#include <Library/DevicePathLib.h>
#include "BoardConfigDxeDataStruc.h"
//
// Driver Version
//
#define BOARD_CONFIG_DRIVER_VERSION  0x00000099

//
// Protocol instances
//
extern EFI_DRIVER_BINDING_PROTOCOL  gBoardConfigDriverBinding;
extern EFI_COMPONENT_NAME2_PROTOCOL  gBoardConfigComponentName2;
extern EFI_COMPONENT_NAME_PROTOCOL  gBoardConfigComponentName;
extern EFI_HII_CONFIG_ACCESS_PROTOCOL  gBoardConfigHiiConfigAccess;
extern EFI_STATUS FdtNodeSetStatus(FDT_CLIENT_PROTOCOL *FdtClient, CHAR8 *NodeAlias, UINT8 Value);

#define BOARD_CONFIG_DEV_SIGNATURE SIGNATURE_32 ('m', 'w', 'd', 'r')

// Need a Data structure for HII routing and accessing
typedef struct {
  UINT32                           Signature;

  EFI_HANDLE                       Handle;
  BOARD_CONFIG_DATA                Configuration;
  EFI_HANDLE                       DriverHandle;
  EFI_HII_HANDLE                   HiiHandle;
  //
  // Consumed protocol
  //
  EFI_HII_DATABASE_PROTOCOL        *HiiDatabase;
  EFI_HII_STRING_PROTOCOL          *HiiString;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;
  EFI_FORM_BROWSER2_PROTOCOL       *FormBrowser2;
  FDT_CLIENT_PROTOCOL  			   *FdtClient;

  //
  // Produced protocol
  //
  EFI_HII_CONFIG_ACCESS_PROTOCOL   ConfigAccess;

} BOARD_CONFIG_DEV;

  #define BOARD_CONFIG_DEV_FROM_THIS(a)  CR (a, BOARD_CONFIG_DEV, ConfigAccess, BOARD_CONFIG_DEV_SIGNATURE)

  #pragma pack(1)
///
/// HII specific Vendor Device Path definition.
///
typedef struct {
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} HII_VENDOR_DEVICE_PATH;

  #pragma pack()
//
// Include files with function prototypes
//
#include "ComponentName.h"
#include "HiiConfigAccess.h"

#endif
