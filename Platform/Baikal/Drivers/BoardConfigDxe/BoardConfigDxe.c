#include <Protocol/FdtClient.h>
#include "BoardConfigDxe.h"
// Begin code
//HII support
EFI_GUID   mBoardConfigFormSetGuid = BOARD_CONFIG_FORMSET_GUID;

CHAR16     mIfrVariableName[] = L"BoardConfig";
EFI_HANDLE                    mDriverHandle = NULL;
BOARD_CONFIG_DEV         *PrivateData = NULL;

// HII support for Device Path
HII_VENDOR_DEVICE_PATH  mHiiVendorDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    BOARD_CONFIG_FORMSET_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};
// end code
EFI_GUID   mBoardConfigVarGuid = BOARD_CONFIG_VAR_GUID;

///
/// Driver Support EFI Version Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED 
EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL gBoardConfigDriverSupportedEfiVersion = {
  sizeof (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL),
  0x0002003c
};

EFI_STATUS
EFIAPI
BoardConfigDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BoardConfigDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BoardConfigDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
	return EFI_SUCCESS;
}

EFI_DRIVER_BINDING_PROTOCOL gBoardConfigDriverBinding = {
  BoardConfigDriverBindingSupported,
  BoardConfigDriverBindingStart,
  BoardConfigDriverBindingStop,
  BOARD_CONFIG_DRIVER_VERSION,
  NULL,
  NULL
};

EFI_STATUS
EFIAPI
BoardConfigUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
   return EFI_SUCCESS;
}

EFI_STATUS FdtNodeSetStatus(
  IN FDT_CLIENT_PROTOCOL  *FdtClient,
  IN CHAR8                *NodeAlias,
  IN UINT8                 Value)
{
  INT32                Node = 0;
  EFI_STATUS            Status;
  CONST CHAR8          *StatusValue;

  DEBUG ((EFI_D_INFO, "BoardConfig: %a: \n", __FUNCTION__));

  StatusValue = Value ? "okay" : "disabled";
  Status = FdtClient->FindNodeByAlias (FdtClient, NodeAlias, &Node);
  DEBUG ((EFI_D_INFO, "BoardConfig: %a: FindNodeByAlias, Status: %r\n", __FUNCTION__, Status));
  if (!EFI_ERROR (Status))
  {
     Status = FdtClient->SetNodeProperty (FdtClient, Node, "status", StatusValue, AsciiStrLen(StatusValue) + 1);
     DEBUG ((EFI_D_INFO, "BoardConfig: %a: SetNodeProperty, Status: %r\n", __FUNCTION__, Status));
     if (EFI_ERROR (Status))
     {
       DEBUG ((EFI_D_ERROR, "BoardConfig: %a: unable to set status in FDT node property, Status: %r\n", __FUNCTION__, Status));
     }
  }
  return Status;
}

EFI_STATUS FdtNodeGetStatus(
  IN  FDT_CLIENT_PROTOCOL  *FdtClient,
  IN  CHAR8                *NodeAlias,
  OUT UINT8                *Value)
{
  INT32                Node = 0;
  UINT32               Sz = 0;
  CONST CHAR8         *Property;
  EFI_STATUS           Status;

  Status = FdtClient->FindNodeByAlias (FdtClient, NodeAlias, &Node);
  if (!EFI_ERROR (Status))
  {
    Status = FdtClient->GetNodeProperty (FdtClient, Node, "status", (CONST VOID **)&Property, &Sz);
    if (EFI_ERROR (Status)) {
      *Value = 1;
      Status = EFI_SUCCESS;
    }
    else
    {
      if (AsciiStrCmp((CONST CHAR8 *)Property, "disabled") == 0)
      {
        *Value = 0;
      }
      else
      {
        *Value = 1;
      }
    }
  }

  return Status;
}

EFI_STATUS
EFIAPI
BoardConfigDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  // HII Locals
  EFI_HII_PACKAGE_LIST_HEADER     *PackageListHeader;
  EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;
  EFI_HII_HANDLE                   HiiHandle = 0;
  EFI_HII_STRING_PROTOCOL         *HiiString;
  EFI_FORM_BROWSER2_PROTOCOL      *FormBrowser2;
  EFI_HII_CONFIG_ROUTING_PROTOCOL *HiiConfigRouting;
  FDT_CLIENT_PROTOCOL  	          *FdtClient;
  UINTN                            BufferSize;

  Status = EFI_SUCCESS;

    //
    // Install UEFI Driver Model protocol(s).
    //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gBoardConfigDriverBinding,
             ImageHandle,
             &gBoardConfigComponentName,
             &gBoardConfigComponentName2
             );
  ASSERT_EFI_ERROR (Status);

    // Initialize driver private data
  PrivateData = AllocateZeroPool (sizeof (BOARD_CONFIG_DEV));
  if (PrivateData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  PrivateData->Signature = BOARD_CONFIG_DEV_SIGNATURE;

  PrivateData->ConfigAccess.ExtractConfig = BoardConfigHiiConfigAccessExtractConfig;
  PrivateData->ConfigAccess.RouteConfig = BoardConfigHiiConfigAccessRouteConfig;
  PrivateData->ConfigAccess.Callback = BoardConfigHiiConfigAccessCallback;

    //
    // Locate Hii Database protocol
    //
  Status = gBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->HiiDatabase = HiiDatabase;

    //
    // Locate HiiString protocol
    //
  Status = gBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->HiiString = HiiString;

    //
    // Locate Formbrowser2 protocol
    //
  Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &FormBrowser2);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->FormBrowser2 = FormBrowser2;

    //
    // Locate ConfigRouting protocol
    //
  Status = gBS->LocateProtocol (&gEfiHiiConfigRoutingProtocolGuid, NULL, (VOID **) &HiiConfigRouting);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->HiiConfigRouting = HiiConfigRouting;

  Status = gBS->LocateProtocol (&gFdtClientProtocolGuid, NULL, (VOID **) &FdtClient);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PrivateData->FdtClient = FdtClient;
    //
    // Publish sample Fromset and config access
    //
  Status = gBS->InstallMultipleProtocolInterfaces (
                    &mDriverHandle,
                    &gEfiDevicePathProtocolGuid,
                    &mHiiVendorDevicePath,
                    &gEfiHiiConfigAccessProtocolGuid,
                    &PrivateData->ConfigAccess,
                    NULL
                    );
  ASSERT_EFI_ERROR (Status);

  PrivateData->DriverHandle = mDriverHandle;

    //
    // Retrieve HII Package List Header on ImageHandle
    //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiHiiPackageListProtocolGuid,
                  (VOID **)&PackageListHeader,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
      //
      // Register list of HII packages in the HII Database
      //
    Status = HiiDatabase->NewPackageList (
                              HiiDatabase, 
                              PackageListHeader,
                              mDriverHandle,
                              &HiiHandle
                              );
    ASSERT_EFI_ERROR (Status);
  }

  Status = EFI_SUCCESS;

  PrivateData->HiiHandle = HiiHandle;

  BufferSize = sizeof (BOARD_CONFIG_DATA);

  Status = gRT->GetVariable (
             mIfrVariableName,
             &mBoardConfigFormSetGuid,
             NULL,
             &BufferSize,
             &PrivateData->Configuration
             );
  if (EFI_ERROR (Status)) {  // Not definded yet so add it to the NV Variables.
    UINT8       mode = 0;

    Status = FdtNodeGetStatus(PrivateData->FdtClient, "vdu-lvds", &mode);

    if (EFI_ERROR (Status)) {
      DEBUG((EFI_D_ERROR, "Can't get vdu-lvds status (%r)\n", Status));
      return Status;
    };
        // zero out buffer
    ZeroMem (&PrivateData->Configuration, sizeof (BOARD_CONFIG_DATA));
    PrivateData->Configuration.LvdsEnable = mode;

    Status = FdtNodeGetStatus(PrivateData->FdtClient, "mmc0", &mode);

    if (EFI_ERROR (Status)) {
      DEBUG((EFI_D_ERROR, "Can't get mmc0 status (%r)\n", Status));
      return Status;
    };
    PrivateData->Configuration.MmcEnable = mode;

    Status = gRT->SetVariable(
                   mIfrVariableName,
                   &mBoardConfigFormSetGuid,
                   EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                   sizeof (BOARD_CONFIG_DATA),
                   &PrivateData->Configuration
                   );
  } else {
    Status = FdtNodeSetStatus(PrivateData->FdtClient, "vdu-lvds", PrivateData->Configuration.LvdsEnable);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Status = FdtNodeSetStatus(PrivateData->FdtClient, "mmc0", PrivateData->Configuration.MmcEnable);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }
  //
  // Install Driver Supported EFI Version Protocol onto ImageHandle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gBoardConfigDriverSupportedEfiVersion,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

