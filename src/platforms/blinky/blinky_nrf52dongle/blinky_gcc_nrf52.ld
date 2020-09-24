/* Linker script to configure memory regions. */

SEARCH_DIR(.)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x1000, LENGTH = 0xff000
  RAM (rwx) :  ORIGIN = 0x20000008, LENGTH = 0x3fff8
}

INCLUDE "gcc_arm_common.ld"
