#include "gba_memory.h"

// there is a lot of room to improve this heap
MemoryHeap::MemoryHeap(int size)
{
  heap = new memory_queue_object[size];
  arraySize = size;
}

MemoryHeap::~MemoryHeap()
{
  delete[] heap;
}

void MemoryHeap::insert(memory_queue_object newMemoryObject)
{
  if (heapSize == arraySize)
  {
    resize(arraySize * 2);
  }

  heapSize++;

  heap[heapSize - 1] = newMemoryObject;

  siftUp(heapSize - 1);
}



memory_queue_object MemoryHeap::pop()
{
  memory_queue_object temp = heap[0];
  heap[0] = heap[heapSize - 1];
  heapSize--;
  if(heapSize > 0)
  {
    siftDown(0);
  }
}

memory_queue_object MemoryHeap::peak()
{
  return heap[0];
}

void MemoryHeap::siftUp(int nodeIndex)
{
  int parentIndex;
  memory_queue_object temp;

  if(nodeIndex != 0)
  {
    parentIndex = getParentIndex(nodeIndex);
    if (heap[parentIndex].clocksToWait > heap[nodeIndex].clocksToWait)
    {
      temp = heap[parentIndex];
      heap[parentIndex] = heap[nodeIndex];
      heap[nodeIndex] = temp;
      siftUp(parentIndex);
    }
  }
}

void MemoryHeap::siftDown(int nodeIndex)
{
  int leftChildIndex, rightChildIndex, minIndex;
  memory_queue_object temp;

  leftChildIndex = getLeftChildIndex(nodeIndex);
  rightChildIndex = getRightChildIndex(nodeIndex);

  if(rightChildIndex >= heapSize)
  {
    if(leftChildIndex >= heapSize)
    {
      return;
    }
    else
    {
      minIndex = leftChildIndex;
    }
  }
  else
  {
    if(heap[leftChildIndex].clocksToWait <= heap[rightChildIndex].clocksToWait )
    {
      minIndex = leftChildIndex;
    }
    else
    {
      minIndex = rightChildIndex;
    }

  }
  if (heap[nodeIndex].clocksToWait > heap[minIndex].clocksToWait)
  {
    temp = heap[minIndex];
    heap[minIndex] = heap[nodeIndex];
    heap[nodeIndex] = temp;
    siftDown(minIndex);
  }
}



int MemoryHeap::getLeftChildIndex(int nodeIndex)
{
  return 2 * nodeIndex + 1;
}

int MemoryHeap::getRightChildIndex(int nodeIndex)
{
  return 2 * nodeIndex + 2;
}

int MemoryHeap::getParentIndex(int nodeIndex)
{
  return (nodeIndex - 1) / 2;
}

bool MemoryHeap::isEmpty()
{
  return heapSize == 0;
}







// will be wise to eventually make these more efficent
// also, some of these will need to be updated because not all
// memory takes the same amount of time to access

// format
// function - # of clock cycles to access
// TODO check if this is important in pipelining


// this looks horribly copy pasta code but it is more efficent to have one function call and these will be the most used/performant functions in the emulatory

inline short readLittleEndian2Bytes(char* addr)
{
  return ((short)(addr[0]) 
          | ((short)(addr[1]) << 8) );
}

inline int readLittleEndian4Bytes(char* addr)
{
  return ((int)(addr[0]) 
          | ((int)(addr[1]) << 8) 
          | ((int)(addr[2]) << 16) 
          | ((int)(addr[3]) << 24));
}



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
  else if (GAMEPAK_WAIT0_ROM_MIN <= addr <= ADDRESS_SPACE_MAX)
  {
    // todo handle rom access
  }
  else
  {
    // out of bounds
    // returns recently pre-fetched opcode
  }
  // TODO handle ROM access and out of bounds memory handling
}

short readMemory16bits(int addr, gba_memory* memory)
{
  short returnValue;
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
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - INTERNAL_WORKRAM_MIN));
  }
  // read external fast work ram - 3 clock
  else if (EXTERNAL_WORKRAM_MIN <= addr <= EXTERNAL_WORKRAM_MAX)
  {
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - EXTERNAL_WORKRAM_MIN));
  }
  // read io registers - 1 clock
  else if (IO_REGISTERS_MIN <= addr <= IO_REGISTERS_MAX)
  {
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - IO_REGISTERS_MIN));
  }
  // read pallete ram - 1 clock
  else if (PALETTE_RAM_MIN <= addr <= PALETTE_RAM_MAX)
  {
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - PALETTE_RAM_MIN));
  }
  // read VRAM - 1 clock
  else if (VRAM_MIN <= addr <= VRAM_MAX)
  {
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - VRAM_MIN));
  }
  // read OAM - 1 clock
  else if (OAM_MIN <= addr <= OAM_MAX)
  {
    returnValue = readLittleEndian2Bytes(memory->internalWorkRAM 
                                          + (addr - OAM_MIN));
  }
  else if (GAMEPAK_WAIT0_ROM_MIN <= addr <= ADDRESS_SPACE_MAX)
  {
    // todo handle rom access
  }
  else
  {
    // out of bounds
    // returns recently pre-fetched opcode
  }
  // TODO handle ROM access and out of bounds memory handling
}
  

int readMemory32bits(int addr, gba_memory* memory)
{
  int returnValue;
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
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM 
                                          + (addr - INTERNAL_WORKRAM_MIN));
  }
  // read external fast work ram - 6 clock
  else if (EXTERNAL_WORKRAM_MIN <= addr <= EXTERNAL_WORKRAM_MAX)
  {
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM 
                                          + (addr - EXTERNAL_WORKRAM_MIN));
  }
  // read io registers - 1 clock
  else if (IO_REGISTERS_MIN <= addr <= IO_REGISTERS_MAX)
  {
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM 
                                          + (addr - IO_REGISTERS_MIN));
  }
  // read pallete ram - 2 clock
  else if (PALETTE_RAM_MIN <= addr <= PALETTE_RAM_MAX)
  {
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM 
                                          + (addr - PALETTE_RAM_MIN));
  }
  // read VRAM - 2 clock
  else if (VRAM_MIN <= addr <= VRAM_MAX)
  {
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM 
                                          + (addr - VRAM_MIN));
  }
  // read OAM - 1 clock
  else if (OAM_MIN <= addr <= OAM_MAX)
  {
    returnValue = readLittleEndian4Bytes(memory->internalWorkRAM
      + (addr - OAM_MIN));
  }
  else if (GAMEPAK_WAIT0_ROM_MIN <= addr <= ADDRESS_SPACE_MAX)
  {
    // todo handle rom access
  }
  else
  {
    // out of bounds
    // returns recently pre-fetched opcode
  }
  // TODO handle ROM access and out of bounds memory handling
}
