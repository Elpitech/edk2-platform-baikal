/** @file
  Copyright (c) 2019 - 2021, Baikal Electronics, JSC. All rights reserved.<BR>
  Author: Pavel Parkhomenko <Pavel.Parkhomenko@baikalelectronics.ru>

  Parts of this file were based on sources as follows:

  Copyright (c) 2011, ARM Ltd. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef BAIKAL_VDU_H_
#define BAIKAL_VDU_H_

#define LCRU_LVDS     0x20010000
#define LCRU_HDMI     0x30010000
#define VDU_LVDS      0x202D0000
#define VDU_HDMI      0x30260000

// Controller Register Offsets
#define BAIKAL_VDU_REG_CR1(x)           ((UINTN) (x) + 0x000)
#define BAIKAL_VDU_REG_HTR(x)           ((UINTN) (x) + 0x008)
#define BAIKAL_VDU_REG_VTR1(x)          ((UINTN) (x) + 0x00C)
#define BAIKAL_VDU_REG_VTR2(x)          ((UINTN) (x) + 0x010)
#define BAIKAL_VDU_REG_PCTR(x)          ((UINTN) (x) + 0x014)
#define BAIKAL_VDU_REG_IMR(x)           ((UINTN) (x) + 0x01C)
#define BAIKAL_VDU_REG_DBAR(x)          ((UINTN) (x) + 0x028)
#define BAIKAL_VDU_REG_DEAR(x)          ((UINTN) (x) + 0x030)
#define BAIKAL_VDU_REG_HVTER(x)         ((UINTN) (x) + 0x044)
#define BAIKAL_VDU_REG_HPPLOR(x)        ((UINTN) (x) + 0x048)
#define BAIKAL_VDU_REG_GPIOR(x)         ((UINTN) (x) + 0x1F8)
#define BAIKAL_VDU_REG_CIR(x)           ((UINTN) (x) + 0x1FC)
#define BAIKAL_VDU_REG_MRR(x)           ((UINTN) (x) + 0xFFC)

/**********************************************************************/

// Register components (register bits)

// This should make life easier to program specific settings in the different registers
// by simplifying the setting up of the individual bits of each register
// and then assembling the final register value.

/**********************************************************************/

// Register: HTR
#define HOR_AXIS_PANEL(hbp,hfp,hsw,hor_res) (UINT32) ((((UINT32)(hsw) - 1) << 24) | (UINT32)((hbp) << 16) | ((UINT32)((hor_res) / 16) << 8) | ((UINT32)(hfp) << 0))

// Register: VTR1
#define VER_AXIS_PANEL(vbp,vfp,vsw) (UINT32)(((UINT32)(vbp) << 16) | ((UINT32)(vfp) << 8) | ((UINT32)(vsw) << 0))

// Register: HVTER
#define TIMINGS_EXT(hbp,hfp,hsw,vbp,vfp,vsw) (UINT32)(((UINT32)(vsw / 256) << 24) | ((UINT32)(hsw / 256) << 16) | ((UINT32)(vbp / 256) << 12) | ((UINT32)(vfp / 256) << 8) | ((UINT32)(hbp / 256) << 4) | ((UINT32)(hfp / 256) << 4))

#define BAIKAL_VDU_CR1_FDW_4_WORDS        (0 << 16)
#define BAIKAL_VDU_CR1_FDW_8_WORDS        (1 << 16)
#define BAIKAL_VDU_CR1_FDW_16_WORDS       (2 << 16)
#define BAIKAL_VDU_CR1_OPS_LCD24          (1 << 13)
#define BAIKAL_VDU_CR1_OPS_LCD18          (0 << 13)
#define BAIKAL_VDU_CR1_OPS_555            (1 << 12)
#define BAIKAL_VDU_CR1_VSP                (1 << 11)
#define BAIKAL_VDU_CR1_HSP                (1 << 10)
#define BAIKAL_VDU_CR1_DEP                (1 << 8)
#define BAIKAL_VDU_CR1_BGR                (1 << 5)
#define BAIKAL_VDU_CR1_BPP1               (0 << 2)
#define BAIKAL_VDU_CR1_BPP2               (1 << 2)
#define BAIKAL_VDU_CR1_BPP4               (2 << 2)
#define BAIKAL_VDU_CR1_BPP8               (3 << 2)
#define BAIKAL_VDU_CR1_BPP16              (4 << 2)
#define BAIKAL_VDU_CR1_BPP18              (5 << 2)
#define BAIKAL_VDU_CR1_BPP24              (6 << 2)
#define BAIKAL_VDU_CR1_LCE                (1 << 0)

#define BAIKAL_VDU_HPPLOR_HPOE            (1 << 31)

#define BAIKAL_VDU_PCTR_PCR               (1 << 10)
#define BAIKAL_VDU_PCTR_PCI               (1 << 9)

#define BAIKAL_VDU_MRR_DEAR_MRR_MASK      (0xFFFFFFF8)
#define BAIKAL_VDU_MRR_OUTSTND_RQ(x)      ((x >> 1) << 0)

#define BAIKAL_VDU_GPIOR_UHD_SNGL_PORT    (0 << 18)
#define BAIKAL_VDU_GPIOR_UHD_DUAL_PORT    (1 << 18)
#define BAIKAL_VDU_GPIOR_UHD_QUAD_PORT    (2 << 18)
#define BAIKAL_VDU_GPIOR_UHD_ENB          (1 << 17)

#define BAIKAL_VDU_PERIPH_ID              0x0090550F

EFI_STATUS
BaikalSetVduFrequency(
  UINT32 LcruId,
  UINT32 RefFreq,
  UINT32 OscFreq
  );

BOOLEAN LvdsEnabled(
  VOID
  );
#endif /* BAIKAL_VDU_H_ */
