#include "gba_memory.h"

// will be wise to eventually make these more efficent
// also, some of these will need to be updated because not all
// memory takes the same amount of time to access

// format
// function - # of clock cycles to access
// TODO check if this is important in pipelining

char readMemory8bits(int addr, gba_memory* memory)
{
  char returnValue;
  // read bios area - 1 clock
  if (addr <= SYSTEMROM_MAX)
  {
    //TODO this is a weird circumstance, check unusual circumestances
    // if program counter is inside bios area, function normally
    // else return most recently successful fetched bios opcode 
    return memory->lastBiosOpcode;
  }
  // read internal fast work ram - 1 clock
  else if (INTERNAL_WORKRAM_MIN <= addr <= INTERNAL_WORKRAM_MAX)
  {
    returnValue = memory->internalWorkRAM[addr - INTERNAL_WORKRAM_MIN];
  }
  // read external fast work ram - 3 clock
  else if (EXTERNAL_WORKRAM_MIN <= addr <= EXTERNAL_WORKRAM_MAX)
  {
    returnValue = memory->externalWorkRAM[addr - EXTERNAL_WORKRAM_MIN];
  }
  // read io registers - 1 clock
  else if (IO_REGISTERS_MIN <= addr <= IO_REGISTERS_MAX)
  {
    returnValue = memory->IORegisters[addr - IO_REGISTERS_MIN];
  }
  // read pallete ram - 1 clock
  else if (PALETTE_RAM_MIN <= addr <= PALETTE_RAM_MAX)
  {
    returnValue = memory->PalleteRAM[addr - PALETTE_RAM_MIN];
  }
  // read VRAM - 1 clock
  else if (VRAM_MIN <= addr <= VRAM_MAX)
  {
    returnValue = memory->VRAM[addr - VRAM_MIN];
  }
  // read OAM - 1 clock
  else if (OAM_MIN <= addr <= OAM_MAX)
  {
    returnValue = memory->OAM[addr - OAM_MIN];
  }
  // TODO handle ROM access and out of bounds memory handling
}

short readMemory16bits(int addr)
{
}

int readMemory32bits(int addr)
{
}
