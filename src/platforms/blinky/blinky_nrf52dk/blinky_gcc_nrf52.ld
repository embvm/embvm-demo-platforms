/* Linker script to configure memory regions. */

SEARCH_DIR(.)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x100000
  RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 0x40000
}

INCLUDE "gcc_arm_common.ld"
