// -*- C++ -*-
// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 1999-2003 Forgotten
// Copyright (C) 2005 Forgotten and the VBA development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#ifndef VBA_GBA_H
#define VBA_GBA_H

#include "System.h"
#include "ichflysettings.h"

#define SAVE_GAME_VERSION_1 1
#define SAVE_GAME_VERSION_2 2
#define SAVE_GAME_VERSION_3 3
#define SAVE_GAME_VERSION_4 4
#define SAVE_GAME_VERSION_5 5
#define SAVE_GAME_VERSION_6 6
#define SAVE_GAME_VERSION_7 7
#define SAVE_GAME_VERSION_8 8
#define SAVE_GAME_VERSION_9 9
#define SAVE_GAME_VERSION  SAVE_GAME_VERSION_9

typedef struct {
  u8 *address;
  u32 mask;
} memoryMap;

typedef union {
  struct {
#ifdef WORDS_BIGENDIAN
    u8 B3;
    u8 B2;
    u8 B1;
    u8 B0;
#else
    u8 B0;
    u8 B1;
    u8 B2;
    u8 B3;
#endif
  } B;
  struct {
#ifdef WORDS_BIGENDIAN
    u16 W1;
    u16 W0;
#else
    u16 W0;
    u16 W1;
#endif
  } W;
#ifdef WORDS_BIGENDIAN
  volatile u32 I;
#else
	u32 I;
#endif
} reg_pair;

#ifndef NO_GBA_MAP
extern memoryMap map[256];
#endif

extern reg_pair reg[45];
extern u8 biosProtected[4];

extern bool N_FLAG;
extern bool Z_FLAG;
extern bool C_FLAG;
extern bool V_FLAG;
extern bool armIrqEnable;
extern bool armState;
extern int armMode;
extern void (*cpuSaveGameFunc)(u32,u8);

//#ifdef BKPT_SUPPORT //ichfly
extern u8 freezeWorkRAM[0x40000];
extern u8 freezeInternalRAM[0x8000];
extern u8 freezeVRAM[0x18000];
extern u8 freezeOAM[0x400];
extern u8 freezePRAM[0x400];
extern bool debugger_last;
extern int  oldreg[17];
extern char oldbuffer[10];
//#endif

//ichfly
extern "C" void ichfly_readfrom(FILE* fd, int pos,char *ptr, size_t len);

#ifdef usebuffedVcout
extern u8 VCountgbatods[0x100]; //(LY)      (0..227) + check overflow
extern u8 VCountdstogba[263]; //(LY)      (0..262)
extern u8 VCountdoit[263]; //jump in or out
#endif

extern bool CPUReadGSASnapshot(const char *);
extern bool CPUWriteGSASnapshot(const char *, const char *, const char *, const char *);
extern bool CPUWriteBatteryFile(const char *);
extern bool CPUReadBatteryFile(const char *);
extern bool CPUExportEepromFile(const char *);
extern bool CPUImportEepromFile(const char *);
extern bool CPUWritePNGFile(const char *);
extern bool CPUWriteBMPFile(const char *);
extern void CPUCleanUp();
extern void CPUUpdateRender();
extern bool CPUReadMemState(char *, int);
extern bool CPUReadState(const char *);
extern bool CPUWriteMemState(char *, int);
extern bool CPUWriteState(const char *);
extern int CPULoadRom(const char *,bool);
extern void doMirroring(bool);
extern void CPUUpdateRegister(u32, u16);
extern void applyTimer ();
//extern void CPUWriteHalfWord(u32, u16);
//extern void CPUWriteByte(u32, u8);
extern void CPUInit(const char *,bool,bool);
extern void CPUReset();
extern void CPULoop(int);
extern void CPUCheckDMA(int,int);
extern bool CPUIsGBAImage(const char *);
extern bool CPUIsZipFile(const char *);
#ifdef PROFILING
#include "prof/prof.h"
extern void cpuProfil(profile_segment *seg);
extern void cpuEnableProfiling(int hz);
#endif

//extern struct EmulatedSystem GBASystem;

#define R13_IRQ  18
#define R14_IRQ  19
#define SPSR_IRQ 20
#define R13_USR  26
#define R14_USR  27
#define R13_SVC  28
#define R14_SVC  29
#define SPSR_SVC 30
#define R13_ABT  31
#define R14_ABT  32
#define SPSR_ABT 33
#define R13_UND  34
#define R14_UND  35
#define SPSR_UND 36
#define R8_FIQ   37
#define R9_FIQ   38
#define R10_FIQ  39
#define R11_FIQ  40
#define R12_FIQ  41
#define R13_FIQ  42
#define R14_FIQ  43
#define SPSR_FIQ 44

#include "Cheats.h"
#include "Globals.h"
#include "EEprom.h"
#include "Flash.h"

#endif //VBA_GBA_H
