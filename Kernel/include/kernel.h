#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <string.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <defs.h>
#include <interruptions/lib.h>
#include <interruptions/idtLoader.h>
#include <drivers/videoDriver.h>
#include <drivers/keyboardDriver.h>
#include <syscalls/syscalls.h>

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

#endif // KERNEL_H