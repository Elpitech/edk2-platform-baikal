/** @file
  Copyright (c) 2020 - 2022, Baikal Electronics, JSC. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <BM1000.h>

#include "AcpiPlatform.h"

#define BUS_RES WordBusNumber (ResourceProducer, MinFixed, MaxFixed,, 0x0, 0x1, 0xFF, 0x0, 0xFF)

DefinitionBlock (__FILE__, "SSDT", 2, "BAIKAL", "SSDTPCI0", 1)
{
  External (\_SB.CRU0, DeviceObj)
  External (\_SB.GPIO, DeviceObj)
  External (\_SB.GPIO.GPIP, DeviceObj)

  Scope (_SB_)
  {
    // PCIe0 (x4 #0)
    Device (PCI0)
    {
      Name (_HID, EISAID ("PNP0A08"))
      Name (_CID, EISAID ("PNP0A03"))
      Name (_UID, BAIKAL_ACPI_PCIE0_SEGMENT)
      Name (_CCA, Zero)
      Name (_SEG, BAIKAL_ACPI_PCIE0_SEGMENT)
      Name (_BBN, Zero)

      Method (_STA)
      {
        Return (0xF)
      }

      Name (_PRT, Package()
      {
        Package() { 0x0000FFFF, 0, Zero, Zero },
        Package() { 0x0000FFFF, 1, Zero, Zero },
        Package() { 0x0000FFFF, 2, Zero, Zero },
        Package() { 0x0000FFFF, 3, Zero, Zero }
      })

      Method (_CRS, 0, Serialized)
      {
        Store (ResourceTemplate ()
        {
          BUS_RES
          QWordMemory (ResourceProducer,, MinFixed, MaxFixed,,, 0x0,
                       BAIKAL_ACPI_PCIE0_MEM_BASE,
                       BAIKAL_ACPI_PCIE0_MEM_MAX,
                       BAIKAL_ACPI_PCIE0_MEM_OFFSET,
                       BAIKAL_ACPI_PCIE0_MEM_SIZE)
          QWordIO (ResourceProducer, MinFixed, MaxFixed,, EntireRange, 0x0,
                   BAIKAL_ACPI_PCIE_IO_BASE,
                   BAIKAL_ACPI_PCIE_IO_MAX,
                   BAIKAL_ACPI_PCIE0_IO_OFFSET,
                   BAIKAL_ACPI_PCIE_IO_SIZE,,,,
                   TypeTranslation)
        }, Local0)

        Return (Local0)
      }

      Name (NUML, 4)
      Name (NUMV, 4)

      Device (RES0)
      {
        Name (_ADR, Zero)
        Method (_CRS, 0, Serialized)
        {
          Store (ResourceTemplate ()
          {
            QWordMemory (,, MinFixed, MaxFixed,,, 0x0,
                         BAIKAL_ACPI_PCIE0_CFG_BASE,
                         BAIKAL_ACPI_PCIE0_CFG_MAX,
                         BAIKAL_ACPI_PCIE_CFG_OFFSET,
                         BAIKAL_ACPI_PCIE_CFG_SIZE)
            Memory32Fixed (ReadWrite, BM1000_PCIE0_DBI_BASE, BM1000_PCIE0_DBI_SIZE)
            Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 458, 461 }
#if defined(BAIKAL_MBM10) || defined(BAIKAL_MBM20) || defined(ELPITECH)
            GpioIo (Exclusive, PullDefault, , , IoRestrictionNone, "\\_SB.GPIO") { 6 }
#endif
          }, Local0)

          Return (Local0)
        }
      }

      NATIVE_PCIE_OSC
    }

#ifdef BAIKAL_ACPI_PCIE1_SEGMENT
    // PCIe1 (x4 #1)
    Device (PCI1)
    {
      Name (_HID, EISAID ("PNP0A08"))
      Name (_CID, EISAID ("PNP0A03"))
      Name (_UID, BAIKAL_ACPI_PCIE1_SEGMENT)
      Name (_CCA, Zero)
      Name (_SEG, BAIKAL_ACPI_PCIE1_SEGMENT)
      Name (_BBN, Zero)

      Method (_STA)
      {
        Return (0xF)
      }

      Name (_PRT, Package()
      {
        Package() { 0x0000FFFF, 0, Zero, Zero },
        Package() { 0x0000FFFF, 1, Zero, Zero },
        Package() { 0x0000FFFF, 2, Zero, Zero },
        Package() { 0x0000FFFF, 3, Zero, Zero }
      })

      Method (_CRS, 0, Serialized)
      {
        Store (ResourceTemplate ()
        {
          BUS_RES
          QWordMemory (ResourceProducer,, MinFixed, MaxFixed,,, 0x0,
                       BAIKAL_ACPI_PCIE1_MEM_BASE,
                       BAIKAL_ACPI_PCIE1_MEM_MAX,
                       BAIKAL_ACPI_PCIE1_MEM_OFFSET,
                       BAIKAL_ACPI_PCIE1_MEM_SIZE)
          QWordIO (ResourceProducer, MinFixed, MaxFixed,, EntireRange, 0x0,
                   BAIKAL_ACPI_PCIE_IO_BASE,
                   BAIKAL_ACPI_PCIE_IO_MAX,
                   BAIKAL_ACPI_PCIE1_IO_OFFSET,
                   BAIKAL_ACPI_PCIE_IO_SIZE,,,,
                   TypeTranslation)
        }, Local0)

        Return (Local0)
      }

      Name (NUML, 4)
      Name (NUMV, 4)

      Device (RES0)
      {
        Name (_ADR, Zero)
        Method (_CRS, 0, Serialized)
        {
          Store (ResourceTemplate ()
          {
            QWordMemory (,, MinFixed, MaxFixed,,, 0x0,
                         BAIKAL_ACPI_PCIE1_CFG_BASE,
                         BAIKAL_ACPI_PCIE1_CFG_MAX,
                         BAIKAL_ACPI_PCIE_CFG_OFFSET,
                         BAIKAL_ACPI_PCIE_CFG_SIZE)
            Memory32Fixed (ReadWrite, BM1000_PCIE1_DBI_BASE, BM1000_PCIE1_DBI_SIZE)
            Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 434, 437 }
          }, Local0)

          Return (Local0)
        }
      }

      NATIVE_PCIE_OSC
    }
#endif

#ifdef BAIKAL_ACPI_PCIE2_SEGMENT
    // PCIe2 (x8)
    Device (PCI2)
    {
      Name (_HID, EISAID ("PNP0A08"))
      Name (_CID, EISAID ("PNP0A03"))
      Name (_UID, BAIKAL_ACPI_PCIE2_SEGMENT)
      Name (_CCA, Zero)
      Name (_SEG, BAIKAL_ACPI_PCIE2_SEGMENT)
      Name (_BBN, Zero)

      Method (_STA)
      {
        Return (0xF)
      }

      Name (_PRT, Package()
      {
        Package() { 0x0000FFFF, 0, Zero, Zero },
        Package() { 0x0000FFFF, 1, Zero, Zero },
        Package() { 0x0000FFFF, 2, Zero, Zero },
        Package() { 0x0000FFFF, 3, Zero, Zero }
      })

      Method (_CRS, 0, Serialized)
      {
        Store (ResourceTemplate ()
        {
          BUS_RES
          QWordMemory (ResourceProducer,, MinFixed, MaxFixed,,, 0x0,
                       BAIKAL_ACPI_PCIE2_MEM_BASE,
                       BAIKAL_ACPI_PCIE2_MEM_MAX,
                       BAIKAL_ACPI_PCIE2_MEM_OFFSET,
                       BAIKAL_ACPI_PCIE2_MEM_SIZE)
          QWordIO (ResourceProducer, MinFixed, MaxFixed,, EntireRange, 0x0,
                   BAIKAL_ACPI_PCIE_IO_BASE,
                   BAIKAL_ACPI_PCIE_IO_MAX,
                   BAIKAL_ACPI_PCIE2_IO_OFFSET,
                   BAIKAL_ACPI_PCIE_IO_SIZE,,,,
                   TypeTranslation)
        }, Local0)

        Return (Local0)
      }

      Name (NUML, 8)
      Name (NUMV, 16)

      Device (RES0)
      {
        Name (_ADR, Zero)
        Method (_CRS, 0, Serialized)
        {
          Store (ResourceTemplate ()
          {
            QWordMemory (,, MinFixed, MaxFixed,,, 0x0,
                         BAIKAL_ACPI_PCIE2_CFG_BASE,
                         BAIKAL_ACPI_PCIE2_CFG_MAX,
                         BAIKAL_ACPI_PCIE_CFG_OFFSET,
                         BAIKAL_ACPI_PCIE_CFG_SIZE)
            Memory32Fixed (ReadWrite, BM1000_PCIE2_DBI_BASE, BM1000_PCIE2_DBI_SIZE)
            Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 410, 413 }
#if defined(BAIKAL_MBM10) || defined(BAIKAL_MBM20) || defined(ELPITECH)
            GpioIo (Exclusive, PullDefault, , , IoRestrictionNone, "\\_SB.GPIO") { 3 }
#endif
          }, Local0)

          Return (Local0)
        }
      }

      NATIVE_PCIE_OSC
    }
#endif
  }
}
