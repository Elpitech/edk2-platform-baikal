#ifndef _BOARDCONFIGDXEDATASTRUC_H_
#define _BOARDCONFIGDXEDATASTRUC_H_
#include <Guid/HiiPlatformSetupFormset.h>
#include <Guid/HiiFormMapMethodGuid.h>

#define BOARD_CONFIG_VAR_GUID   { 0x363729f9, 0x35fc, 0x40a6,{ 0xaf, 0xc8, 0xe8, 0xf5, 0x49, 0x11, 0xf1, 0xd6} }
#define BOARD_CONFIG_FORMSET_GUID { 0x5481db09, 0xe5f7, 0x4158, { 0xa5, 0xc5, 0x2d, 0xbe, 0xa4, 0x95, 0x34, 0xff} }
#define CONFIGURATION_VARSTORE_ID    0x1234

#pragma pack(1)
typedef struct {
    UINT8  LvdsEnable;
    UINT8  MmcEnable;
    UINT8  EspiEnable;
    UINT8  VdecEnable;
    UINT8  resv0;
    UINT8  resv1;
    UINT8  resv2;
    UINT8  resv3;
} BOARD_CONFIG_DATA;
#pragma pack()

#endif
