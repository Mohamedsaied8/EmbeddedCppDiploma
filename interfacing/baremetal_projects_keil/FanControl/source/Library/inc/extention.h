#ifndef EXTENTION_H
#define EXTENTION_H

#ifndef COMMON_H
#include "common.h"
#endif

#define EXT1			0x40
#define EXT2			0x42
#define EXT3			0x44
#define EXT4			0x46
#define EXT5			0x48
#define EXT6			0x4A
#define EXT7			0x4C
#define EXT8			0x4E

#define IODIRA			0x00
#define IODIRB			0x01

#define IPOLA			0x02
#define IPOLB			0x03

#define GPPUA			0x0C
#define GPPUB			0x0D

#define EGPIOA			0x12
#define EGPIOB			0x13

void extentionWrite(unsigned char adrs, unsigned char reg,unsigned char value);
int extentionRead(unsigned char adrs, unsigned char reg);
#endif
