#include "BoardConfigDxe.h"

///
/// Component Name Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED 
EFI_COMPONENT_NAME_PROTOCOL  gBoardConfigComponentName = {
  (EFI_COMPONENT_NAME_GET_DRIVER_NAME)    BoardConfigComponentNameGetDriverName,
  (EFI_COMPONENT_NAME_GET_CONTROLLER_NAME)BoardConfigComponentNameGetControllerName,
  "eng"
};

///
/// Component Name 2 Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED 
EFI_COMPONENT_NAME2_PROTOCOL  gBoardConfigComponentName2 = {
  BoardConfigComponentNameGetDriverName,
  BoardConfigComponentNameGetControllerName,
  "en"
};

///
/// Table of driver names
///
GLOBAL_REMOVE_IF_UNREFERENCED 
EFI_UNICODE_STRING_TABLE mBoardConfigDriverNameTable[] = {
  { "eng;en", (CHAR16 *)L"Board config driver" },
  { NULL, NULL }
};

EFI_STATUS
EFIAPI
BoardConfigComponentNameGetDriverName (
  IN EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
  return LookupUnicodeString2 (
           Language,
           This->SupportedLanguages,
           mBoardConfigDriverNameTable,
           DriverName,
           (BOOLEAN)(This != &gBoardConfigComponentName2)
           );
}

EFI_STATUS
EFIAPI
BoardConfigComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  EFI_HANDLE                    ControllerHandle,
  IN  EFI_HANDLE                    ChildHandle        OPTIONAL,
  IN  CHAR8                         *Language,
  OUT CHAR16                        **ControllerName
  )
{
  EFI_STATUS  Status;
  //
  // ChildHandle must be NULL for a Device Driver
  //
  if (ChildHandle != NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // Make sure this driver is currently managing ControllerHandle
  //
  Status = EfiTestManagedDevice (
             ControllerHandle,
             gBoardConfigDriverBinding.DriverBindingHandle,
             &gEfiPciIoProtocolGuid
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Lookup name of controller specified by ControllerHandle
  //
  Status = EFI_UNSUPPORTED;
  return Status;
}
