/** @file
  Copyright (c) 2020, Baikal Electronics, JSC. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef BM1000_PLATFORM_PCIE_H
#define BM1000_PLATFORM_PCIE_H

enum {
  BM1000_PCIE_X4_0_IDX = 0,
  BM1000_PCIE_X4_1_IDX,
  BM1000_PCIE_X8_IDX
};

#define BM1000_PCIE_X4_0_CDM_BASE     0x02200000
#define BM1000_PCIE_X4_0_CDM_SIZE     0x10000
#define BM1000_PCIE_X4_0_DYNIO0_BASE  0x40100000
#define BM1000_PCIE_X4_0_DYNIO0_SIZE  0xFF00000
#define BM1000_PCIE_X4_0_DYNIO1_BASE  0x400000000
#define BM1000_PCIE_X4_0_DYNIO1_SIZE  0x100000000
#define BM1000_PCIE_X4_0_DYNIO2_BASE  0x4000000000
#define BM1000_PCIE_X4_0_DYNIO2_SIZE  0x1000000000
#define BM1000_PCIE_X4_0_MMIO32_BASE  (BM1000_PCIE_X4_0_DYNIO0_BASE)
#define BM1000_PCIE_X4_0_MMIO32_SIZE  (BM1000_PCIE_X4_0_DYNIO0_SIZE - BM1000_PCIE_X4_0_CFG_SIZE - BM1000_PCIE_X4_0_PORTIO_SIZE)
#define BM1000_PCIE_X4_0_CFG_BASE     (BM1000_PCIE_X4_0_DYNIO0_BASE + BM1000_PCIE_X4_0_DYNIO0_SIZE - BM1000_PCIE_X4_0_CFG_SIZE)
#define BM1000_PCIE_X4_0_CFG_SIZE     0x10000
#define BM1000_PCIE_X4_0_PORTIO_BASE  (BM1000_PCIE_X4_0_DYNIO0_BASE + BM1000_PCIE_X4_0_DYNIO0_SIZE - BM1000_PCIE_X4_0_CFG_SIZE - BM1000_PCIE_X4_0_PORTIO_SIZE)
#define BM1000_PCIE_X4_0_PORTIO_SIZE  0x100000
#define BM1000_PCIE_X4_0_MMIO64_BASE  (BM1000_PCIE_X4_0_DYNIO1_BASE)
#define BM1000_PCIE_X4_0_MMIO64_SIZE  (BM1000_PCIE_X4_0_DYNIO1_SIZE)

#define BM1000_PCIE_X4_1_CDM_BASE     0x02210000
#define BM1000_PCIE_X4_1_CDM_SIZE     0x10000
#define BM1000_PCIE_X4_1_DYNIO0_BASE  0x50000000
#define BM1000_PCIE_X4_1_DYNIO0_SIZE  0x10000000
#define BM1000_PCIE_X4_1_DYNIO1_BASE  0x500000000
#define BM1000_PCIE_X4_1_DYNIO1_SIZE  0x100000000
#define BM1000_PCIE_X4_1_DYNIO2_BASE  0x5000000000
#define BM1000_PCIE_X4_1_DYNIO2_SIZE  0x1000000000
#define BM1000_PCIE_X4_1_MMIO32_BASE  (BM1000_PCIE_X4_1_DYNIO0_BASE)
#define BM1000_PCIE_X4_1_MMIO32_SIZE  (BM1000_PCIE_X4_1_DYNIO0_SIZE - BM1000_PCIE_X4_1_CFG_SIZE - BM1000_PCIE_X4_1_PORTIO_SIZE)
#define BM1000_PCIE_X4_1_CFG_BASE     (BM1000_PCIE_X4_1_DYNIO0_BASE + BM1000_PCIE_X4_1_DYNIO0_SIZE - BM1000_PCIE_X4_1_CFG_SIZE)
#define BM1000_PCIE_X4_1_CFG_SIZE     0x10000
#define BM1000_PCIE_X4_1_PORTIO_BASE  (BM1000_PCIE_X4_1_DYNIO0_BASE + BM1000_PCIE_X4_1_DYNIO0_SIZE - BM1000_PCIE_X4_1_CFG_SIZE - BM1000_PCIE_X4_1_PORTIO_SIZE)
#define BM1000_PCIE_X4_1_PORTIO_SIZE  0x100000
#define BM1000_PCIE_X4_1_MMIO64_BASE  (BM1000_PCIE_X4_1_DYNIO1_BASE)
#define BM1000_PCIE_X4_1_MMIO64_SIZE  (BM1000_PCIE_X4_1_DYNIO1_SIZE)

#define BM1000_PCIE_X8_CDM_BASE       0x02220000
#define BM1000_PCIE_X8_CDM_SIZE       0x10000
#define BM1000_PCIE_X8_DYNIO0_BASE    0x60000000U
#define BM1000_PCIE_X8_DYNIO0_SIZE    0x20000000
#define BM1000_PCIE_X8_DYNIO1_BASE    0x600000000
#define BM1000_PCIE_X8_DYNIO1_SIZE    0x200000000
#define BM1000_PCIE_X8_DYNIO2_BASE    0x6000000000
#define BM1000_PCIE_X8_DYNIO2_SIZE    0x2000000000
#define BM1000_PCIE_X8_MMIO32_BASE    (BM1000_PCIE_X8_DYNIO0_BASE)
#define BM1000_PCIE_X8_MMIO32_SIZE    (BM1000_PCIE_X8_DYNIO0_SIZE - BM1000_PCIE_X8_CFG_SIZE - BM1000_PCIE_X8_PORTIO_SIZE)
#define BM1000_PCIE_X8_CFG_BASE       (BM1000_PCIE_X8_DYNIO0_BASE + BM1000_PCIE_X8_DYNIO0_SIZE - BM1000_PCIE_X8_CFG_SIZE)
#define BM1000_PCIE_X8_CFG_SIZE       0x10000
#define BM1000_PCIE_X8_PORTIO_BASE    (BM1000_PCIE_X8_DYNIO0_BASE + BM1000_PCIE_X8_DYNIO0_SIZE - BM1000_PCIE_X8_CFG_SIZE - BM1000_PCIE_X8_PORTIO_SIZE)
#define BM1000_PCIE_X8_PORTIO_SIZE    0x100000
#define BM1000_PCIE_X8_MMIO64_BASE    (BM1000_PCIE_X8_DYNIO1_BASE)
#define BM1000_PCIE_X8_MMIO64_SIZE    (BM1000_PCIE_X8_DYNIO1_SIZE)

#define BM1000_PCIE_BUS_MINS { \
  0,                           \
  0,                           \
  0                            \
}

#define BM1000_PCIE_BUS_MAXS { \
  0xFF,                        \
  0xFF,                        \
  0xFF                         \
}

#define BM1000_PCIE_CDM_BASES { \
  BM1000_PCIE_X4_0_CDM_BASE,    \
  BM1000_PCIE_X4_1_CDM_BASE,    \
  BM1000_PCIE_X8_CDM_BASE       \
}

#define BM1000_PCIE_CFG_BASES { \
  BM1000_PCIE_X4_0_CFG_BASE,    \
  BM1000_PCIE_X4_1_CFG_BASE,    \
  BM1000_PCIE_X8_CFG_BASE       \
}

#define BM1000_PCIE_MMIO32_BASES { \
  BM1000_PCIE_X4_0_MMIO32_BASE,    \
  BM1000_PCIE_X4_1_MMIO32_BASE,    \
  BM1000_PCIE_X8_MMIO32_BASE       \
}

#define BM1000_PCIE_MMIO32_SIZES { \
  BM1000_PCIE_X4_0_MMIO32_SIZE,    \
  BM1000_PCIE_X4_0_MMIO32_SIZE,    \
  BM1000_PCIE_X8_MMIO32_SIZE       \
}

#define BM1000_PCIE_MMIO64_BASES { \
  BM1000_PCIE_X4_0_MMIO64_BASE,    \
  BM1000_PCIE_X4_1_MMIO64_BASE,    \
  BM1000_PCIE_X8_MMIO64_BASE       \
}

#define BM1000_PCIE_MMIO64_SIZES { \
  BM1000_PCIE_X4_0_MMIO64_SIZE,    \
  BM1000_PCIE_X4_0_MMIO64_SIZE,    \
  BM1000_PCIE_X8_MMIO64_SIZE       \
}

#define BM1000_PCIE_PORTIO_BASES { \
  BM1000_PCIE_X4_0_PORTIO_BASE,    \
  BM1000_PCIE_X4_1_PORTIO_BASE,    \
  BM1000_PCIE_X8_PORTIO_BASE       \
}

#define BM1000_PCIE_PORTIO_SIZES { \
  BM1000_PCIE_X4_0_PORTIO_SIZE,    \
  BM1000_PCIE_X4_1_PORTIO_SIZE,    \
  BM1000_PCIE_X8_PORTIO_SIZE       \
}

#define BM1000_PCIE_PORTIO_MINS { \
  0,                              \
  0x100000,                       \
  0x200000                        \
}

#define BM1000_PCIE_PORTIO_MAXS {                 \
  (0 << 20) | (BM1000_PCIE_X4_0_PORTIO_SIZE - 1), \
  (1 << 20) | (BM1000_PCIE_X4_1_PORTIO_SIZE - 1), \
  (2 << 20) | (BM1000_PCIE_X8_PORTIO_SIZE   - 1)  \
}

#endif // BM1000_PLATFORM_PCIE_H
