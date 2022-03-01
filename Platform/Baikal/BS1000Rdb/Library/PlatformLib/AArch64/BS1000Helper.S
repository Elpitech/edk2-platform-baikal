#
#  Copyright (c) 2011-2013, ARM Limited. All rights reserved.
#  Copyright (c) 2016, Linaro Limited. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
#

#include <AsmMacroIoLibV8.h>
#include <Library/ArmLib.h>

// VOID
// ArmPlatformPeiBootAction (
//   VOID   *DeviceTreeBaseAddress,   // passed by loader in x0
//   VOID   *ImageBase                // passed by FDF trampoline in x1
//   );
ASM_FUNC(ArmPlatformPeiBootAction)
  //
  // If we are booting from RAM using the Linux kernel boot protocol, x0 will
  // point to the DTB image in memory. Otherwise, use the default value defined
  // by the platform.
  //
  cbnz  x0, 0f
  ldr   x0, PcdGet64 (PcdDeviceTreeInitialBaseAddress)

0:mov   x29, x30            // preserve LR
  mov   x28, x0             // preserve DTB pointer
  mov   x27, x1             // preserve base of image pointer

  //
  // The base of the runtime image has been preserved in x1. Check whether
  // the expected magic number can be found in the header.
  //
  ldr   w8, .LArm64LinuxMagic
  ldr   w9, [x1, #0x38]
  cmp   w8, w9
  bne   .Lout

  //
  //
  // OK, so far so good. We have confirmed that we likely have a DTB and are
  // booting via the arm64 Linux boot protocol. Update the base-of-image PCD
  // to the actual relocated value, and add the shift of PcdFdBaseAddress to
  // PcdFvBaseAddress as well
  //
  adr   x8, PcdGet64 (PcdFdBaseAddress)
  adr   x9, PcdGet64 (PcdFvBaseAddress)
  ldr   x6, [x8]
  ldr   x7, [x9]
  sub   x7, x7, x6
  add   x7, x7, x1
  str   x1, [x8]
  str   x7, [x9]

  //
  // Discover the memory size and offset from the DTB, and record in the
  // respective PCDs. This will also return false if a corrupt DTB is
  // encountered. Since we are calling a C function, use the window at the
  // beginning of the FD image as a temp stack.
  //
  adr   x1, PcdGet64 (PcdSystemMemoryBase)
  adr   x2, PcdGet64 (PcdSystemMemorySize)
  mov   sp, x7
  bl    FindMemnode
  cbz   x0, .Lout

  //
  // Copy the DTB to the slack space right after the 64 byte arm64/Linux style
  // image header at the base of this image (defined in the FDF), and record the
  // pointer in PcdDeviceTreeInitialBaseAddress.
  //
  adr   x8, PcdGet64 (PcdDeviceTreeInitialBaseAddress)
  add   x27, x27, #0x40
  str   x27, [x8]

  mov   x0, x27
  mov   x1, x28
  bl    CopyFdt

.Lout:
  ret    x29

.LArm64LinuxMagic:
  .byte   0x41, 0x52, 0x4d, 0x64

//UINTN
//ArmPlatformGetPrimaryCoreMpId (
//  VOID
//  );
ASM_FUNC(ArmPlatformGetPrimaryCoreMpId)
  MOV32  (w0, FixedPcdGet32 (PcdArmPrimaryCore))
  ret

//UINTN
//ArmPlatformIsPrimaryCore (
//  IN UINTN MpId
//  );
ASM_FUNC(ArmPlatformIsPrimaryCore)
  MOV32 (w1, FixedPcdGet32(PcdArmPrimaryCoreMask))
  and   x0, x0, x1
  MOV32 (w1, FixedPcdGet32(PcdArmPrimaryCore))
  cmp   w0, w1
  cset  x0, eq
  ret

//UINTN
//ArmPlatformGetCorePosition (
//  IN UINTN MpId
//  );
// With this function: CorePos = (ClusterId * 4) + CoreId
ASM_FUNC(ArmPlatformGetCorePosition)
  ubfx  x1, x0, #8,  #8
  ubfx  x2, x0, #16, #8
  add   x0, x1, x2, LSL #2
  ret

//EFI_PHYSICAL_ADDRESS
//GetPhysAddrTop (
//  VOID
//  );
ASM_FUNC(ArmGetPhysAddrTop)
  mrs   x0, id_aa64mmfr0_el1
  adr   x1, .LPARanges
  and   x0, x0, #7
  ldrb  w1, [x1, x0]
  mov   x0, #1
  lsl   x0, x0, x1
  ret

//
// Bits 0..2 of the AA64MFR0_EL1 system register encode the size of the
// physical address space support on this CPU:
// 0 == 32 bits, 1 == 36 bits, etc etc
// 6 and 7 are reserved
//
.LPARanges:
  .byte 32, 36, 40, 42, 44, 48, -1, -1

ASM_FUNCTION_REMOVE_IF_UNREFERENCED