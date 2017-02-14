
#define SYSTEMROM_MIN 0x00000000
#define SYSTEMROM_MAX 0x00003fff
#define EXTERNAL_WORKRAM_MIN 0x02000000
#define EXTERNAL_WORKRAM_MAX 0x0203ffff
#define INTERNAL_WORKRAM_MIN 0x03000000
#define INTERNAL_WORKRAM_MAX 0x03007fff
#define IO_REGISTERS_MIN 0x04000000
#define IO_REGISTERS_MAX 0x04ffffff
#define PALETTE_RAM_MIN 0x05000000
#define PALETTE_RAM_MAX 0x050003ff
#define VRAM_MIN 0x06000000
#define VRAM_MAX 0x06017fff
#define OAM_MIN 0x07000000
#define OAM_MAX 0x070003ff
// the maxes will be defined by each game pack
// may be wise to find the maxes and the location of flash memory on
// load of rom
#define GAMEPAK_WAIT0_ROM_MIN 0x08000000

#define GAMEPAK_WAIT1_ROM_MIN 0x0a000000

#define GAMEPAK_WAIT2_ROM_MIN 0x0c000000

#define GAMEPAK_RAM_MIN 0x0e000000

#define ADDRESS_SPACE_MAX 0x0e010000


#define ROM_MASK 0x0
#define EXTERNAL_WORKRAM_MASK 0x02
#define INTERNAL_WORKRAM_MASK 0x03
#define IO_REGISTERS_MASK 0x04
#define PALETTE_MASK 0x05
#define VRAM_MASK 0x06
#define OAM_MASK 0x07
#define WAIT_0_MASK 0x08
#define WAIT_1_MASK 0x0a
#define WAIT_2_MASK 0x0c
#define GAMEPAK_SRAM 0x0e



struct memory_queue_object
{
  char clocksToWait;
  int value;
  int sizeOfValue;
};


class MemoryHeap
{

  MemoryHeap(int size);
  ~MemoryHeap();

  memory_queue_object pop();
  memory_queue_object peak();
  void insert(memory_queue_object newMemoryObject);
  void decrement();

  bool isEmpty();

private:

  memory_queue_object* heap;
  int heapSize;
  int arraySize;


  int getLeftChildIndex(int nodeIndex);
  int getRightChildIndex(int nodeIndex);
  int getParentIndex(int nodeIndex);

  void siftUp(int nodeIndex);
  void siftDown(int nodeIndex);

  void resize(int size);
};


class memory_structure
{
  public:
    memory_structure();

    void loadMemory(int sourceAddr, int destAddr, char size);
    void writeMemory(int value, int destAddr, char size);
//    DMALoadMemory();
    void memoryCycleUpdate();
  private:
    // addresses must be cleaned for corner cases before they get here
    // these ACTUALLY will do the action, immediately, with no wait
    int load32(char* sourceAddr);
    short load16(char* sourceAddr);
    char load8(char* sourceAddr);
    void write32(int x, char* destAddr);
    void write16(short x, char* destAddr);
    void write8(char x, char* destAddr);
    int returnOpCode(int opCode);

    MemoryHeap* memoryQueue;

    char* biosROM;
    char* internalWorkRAM;
    char* externalWorkRAM;
    char* IORegisters;
    char* VRAM;
    char* OAM;
    char* PalleteRAM;
    char* gamePakROM;
};
