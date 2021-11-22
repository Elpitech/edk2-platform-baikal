#include "BoardConfigDxe.h"

extern EFI_GUID   mBoardConfigFormSetGuid;
extern CHAR16     mIfrVariableName[];

///
/// HII Config Access Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED 
EFI_HII_CONFIG_ACCESS_PROTOCOL gBoardConfigHiiConfigAccess = {
  BoardConfigHiiConfigAccessExtractConfig,
  BoardConfigHiiConfigAccessRouteConfig,
  BoardConfigHiiConfigAccessCallback
};

EFI_STATUS
EFIAPI
BoardConfigHiiConfigAccessExtractConfig (
  IN CONST  EFI_HII_CONFIG_ACCESS_PROTOCOL  *This,
  IN CONST  EFI_STRING                      Request,
  OUT       EFI_STRING                      *Progress,
  OUT       EFI_STRING                      *Results
  )
{
  //Begin code
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  BOARD_CONFIG_DEV            *PrivateData;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;
  EFI_STRING                       ConfigRequest;
  BOOLEAN                          AllocatedRequest;
  if (Progress == NULL || Results == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Initialize the local variables.
  //
  ConfigRequest     = NULL;
  *Progress         = Request;
  AllocatedRequest  = FALSE;
  PrivateData = BOARD_CONFIG_DEV_FROM_THIS (This);
  HiiConfigRouting = PrivateData->HiiConfigRouting;
  //
  // Get Buffer Storage data from EFI variable.
  // Try to get the current setting from variable.
  //
  BufferSize = sizeof (BOARD_CONFIG_DATA);
  Status = gRT->GetVariable (
            mIfrVariableName,
            &mBoardConfigFormSetGuid,
            NULL,
            &BufferSize,
            &PrivateData->Configuration
            );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }
  if (Request == NULL) {
    DEBUG ((DEBUG_INFO, "\n:: Inside of Extract Config and Request == Null "));
  } else {
    ConfigRequest = Request;
  }
  //
  // Convert buffer data to <ConfigResp> by helper function BlockToConfig()
  //
  Status = HiiConfigRouting->BlockToConfig (
                                  HiiConfigRouting,
                                  ConfigRequest,
                                  (UINT8 *) &PrivateData->Configuration,
                                  BufferSize,
                                  Results,
                                  Progress
                                  );
  //
  // Free the allocated config request string.
  //
  if (AllocatedRequest) {
    FreePool (ConfigRequest);
  }
  //
  // Set Progress string to the original request string.
  //
  if (Request == NULL) {
    *Progress = NULL;
  } else if (StrStr (Request, L"OFFSET") == NULL) {
    *Progress = Request + StrLen (Request);
  }
  return Status;
// End code
}

EFI_STATUS
EFIAPI
BoardConfigHiiConfigAccessRouteConfig (
  IN CONST  EFI_HII_CONFIG_ACCESS_PROTOCOL  *This,
  IN CONST  EFI_STRING                      Configuration,
  OUT       EFI_STRING                      *Progress
  )
{
  //Begin code
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  BOARD_CONFIG_DEV            *PrivateData;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;

  if (Configuration == NULL || Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  PrivateData = BOARD_CONFIG_DEV_FROM_THIS (This);
  HiiConfigRouting = PrivateData->HiiConfigRouting;
  *Progress = Configuration;

  //
  // Get Buffer Storage data from EFI variable
  //
  BufferSize = sizeof (BOARD_CONFIG_DATA);
  Status = gRT->GetVariable (
            mIfrVariableName,
            &mBoardConfigFormSetGuid,
            NULL,
            &BufferSize,
            &PrivateData->Configuration
            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Convert <ConfigResp> to buffer data by helper function ConfigToBlock()
  //
  BufferSize = sizeof (BOARD_CONFIG_DATA);
  Status = HiiConfigRouting->ConfigToBlock (
                               HiiConfigRouting,
                               Configuration,
                               (UINT8 *) &PrivateData->Configuration,
                               &BufferSize,
                               Progress
                               );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Store Buffer Storage back to EFI variable
  //
  Status = gRT->SetVariable(
                  mIfrVariableName,
                  &mBoardConfigFormSetGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof (BOARD_CONFIG_DATA),
                  &PrivateData->Configuration
                  );

  Status = FdtNodeSetStatus(PrivateData->FdtClient, "vdu-lvds", PrivateData->Configuration.LvdsEnable);
  Status = FdtNodeSetStatus(PrivateData->FdtClient, "mmc0", PrivateData->Configuration.MmcEnable);

  return Status;
}  

EFI_STATUS
EFIAPI
BoardConfigHiiConfigAccessCallback (
  IN     CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN     EFI_BROWSER_ACTION                     Action,
  IN     EFI_QUESTION_ID                        QuestionId,
  IN     UINT8                                  Type,
  IN OUT EFI_IFR_TYPE_VALUE                     *Value,
  OUT    EFI_BROWSER_ACTION_REQUEST             *ActionRequest
  )
{
  return EFI_SUCCESS;
}
