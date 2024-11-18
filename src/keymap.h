#ifndef KEYMAP_H
#define KEYMAP_H

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

#define ROWS 5
#define COLS 12
#define FN 0x73

uint8_t keymap[ROWS][COLS] = {
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D},
    {0x35, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2E},
    {0x2B, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x2F},
    {0xE1, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0x30},
    {0xE0, 0x73, 0xE3, 0xE2, 0x2A, 0x2C, 0x2C, 0x28, 0x4C, 0x00, 0x34, 0x31}
};

uint8_t fn_keymap[ROWS][COLS] = {
    {0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45},
    {0},
    {0},
    {0},
    {0}
};

#endif