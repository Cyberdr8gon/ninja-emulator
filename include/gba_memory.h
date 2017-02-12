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


struct gba_memory {
  char* biosROM;
  char* internalWorkRAM;
  char* externalWorkRAM;
  char* IORegisters;
  char* VRAM;
  char* OAM;
  char* PalleteRAM;
  char* gamePakROM;
  int lastBiosOpcode;
};

char readMemory8bits(int addr);
short readMemory16bits(int addr);
int readMemory32bits(int addr);