/** @file
  Copyright (c) 2021 - 2023, Baikal Electronics, JSC. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef BM1000_H_
#define BM1000_H_

#define BM1000_PCIE_GPR_BASE            0x02050000
#define BM1000_PCIE_GPR_SIZE            SIZE_4KB

#define BM1000_PCIE0_IDX  0 // PCIe0 (x4 #0)
#define BM1000_PCIE1_IDX  1 // PCIe1 (x4 #1)
#define BM1000_PCIE2_IDX  2 // PCIe2 (x8)

#define BM1000_PCIE_GPR_STS(PcieIdx)          (BM1000_PCIE_GPR_BASE + (PcieIdx) * 0x20 + 0x04)
#define BM1000_PCIE_GPR_STS_LTSSM_STATE_L0    0x11
#define BM1000_PCIE_GPR_STS_LTSSM_STATE_MASK  0x3F
#define BM1000_PCIE_GPR_STS_SMLH_LINKUP       BIT6
#define BM1000_PCIE_GPR_STS_RDLH_LINKUP       BIT7

#define BM1000_PCIE0_DBI_BASE           0x02200000
#define BM1000_PCIE0_DBI_SIZE           SIZE_4KB

#define BM1000_PCIE1_DBI_BASE           0x02210000
#define BM1000_PCIE1_DBI_SIZE           SIZE_4KB

#define BM1000_PCIE2_DBI_BASE           0x02220000
#define BM1000_PCIE2_DBI_SIZE           SIZE_4KB

#define BM1000_GPIO32_BASE              0x20200000
#define BM1000_GPIO32_SIZE              SIZE_4KB

#define BM1000_SPI_BASE                 0x20210000
#define BM1000_SPI_SIZE                 SIZE_4KB

#define BM1000_I2S_BASE                 0x20220000
#define BM1000_I2S_SIZE                 SIZE_4KB

#define BM1000_UART1_BASE               0x20230000
#define BM1000_UART1_SIZE               SIZE_4KB

#define BM1000_UART2_BASE               0x20240000
#define BM1000_UART2_SIZE               SIZE_4KB

#define BM1000_I2C1_BASE                0x20250000
#define BM1000_I2C1_SIZE                SIZE_4KB

#define BM1000_I2C2_BASE                0x20260000
#define BM1000_I2C2_SIZE                SIZE_4KB

#define BM1000_SMBUS1_BASE              0x20270000
#define BM1000_SMBUS1_SIZE              SIZE_4KB

#define BM1000_SMBUS2_BASE              0x20280000
#define BM1000_SMBUS2_SIZE              SIZE_4KB

#define BM1000_ESPI_BASE                0x202A0000
#define BM1000_ESPI_SIZE                SIZE_4KB

#define BM1000_HDA_BASE                 0x202C0000
#define BM1000_HDA_SIZE                 SIZE_4KB

#define BM1000_LVDS_VDU_BASE            0x202D0000
#define BM1000_LVDS_VDU_SIZE            SIZE_4KB

#define BM1000_MMC_BASE                 0x202E0000
#define BM1000_MMC_SIZE                 SIZE_4KB

#define BM1000_USB2_BASE                0x2C400000
#define BM1000_USB2_SIZE                SIZE_64KB

#define BM1000_USB3_BASE                0x2C500000
#define BM1000_USB3_SIZE                SIZE_64KB

#define BM1000_SATA0_BASE               0x2C600000
#define BM1000_SATA0_SIZE               SIZE_4KB

#define BM1000_SATA1_BASE               0x2C610000
#define BM1000_SATA1_SIZE               SIZE_4KB

#define BM1000_GIC_BASE                 0x2D000000
#define BM1000_GIC_SIZE                 SIZE_2MB

#define BM1000_XGMAC0_BASE              0x30200000
#define BM1000_XGMAC0_SIZE              SIZE_128KB

#define BM1000_XGMAC1_BASE              0x30220000
#define BM1000_XGMAC1_SIZE              SIZE_128KB

#define BM1000_GMAC0_BASE               0x30240000
#define BM1000_GMAC0_SIZE               SIZE_8KB

#define BM1000_GMAC1_BASE               0x30250000
#define BM1000_GMAC1_SIZE               SIZE_8KB

#define BM1000_HDMI_VDU_BASE            0x30260000
#define BM1000_HDMI_VDU_SIZE            SIZE_4KB

#define BM1000_HDMI_CTRLR_BASE          0x30280000
#define BM1000_HDMI_CTRLR_SIZE          SIZE_128KB

#define BM1000_PCIE0_DYNIO0_BASE        0x40100000
#define BM1000_PCIE0_DYNIO0_SIZE        (SIZE_256MB - SIZE_1MB)

#define BM1000_PCIE1_DYNIO0_BASE        0x50000000
#define BM1000_PCIE1_DYNIO0_SIZE        SIZE_256MB

#define BM1000_PCIE2_DYNIO0_BASE        0x60000000U
#define BM1000_PCIE2_DYNIO0_SIZE        SIZE_512MB

#define BM1000_PCIE0_DYNIO1_BASE        0x400000000
#define BM1000_PCIE0_DYNIO1_SIZE        SIZE_4GB

#define BM1000_PCIE1_DYNIO1_BASE        0x500000000
#define BM1000_PCIE1_DYNIO1_SIZE        SIZE_4GB

#define BM1000_PCIE2_DYNIO1_BASE        0x600000000
#define BM1000_PCIE2_DYNIO1_SIZE        SIZE_8GB

#define BM1000_PCIE0_DYNIO2_BASE        0x4000000000
#define BM1000_PCIE0_DYNIO2_SIZE        SIZE_64GB

#define BM1000_PCIE1_DYNIO2_BASE        0x5000000000
#define BM1000_PCIE1_DYNIO2_SIZE        SIZE_64GB

#define BM1000_PCIE2_DYNIO2_BASE        0x6000000000
#define BM1000_PCIE2_DYNIO2_SIZE        SIZE_128GB

#endif // BM1000_H_
