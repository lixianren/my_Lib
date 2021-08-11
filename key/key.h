#ifndef __KEY_H
#define __KEY_H

typedef void (*Pfuntion)(void);
typedef enum
{
    KEY_MODE_NOTHING = 0,
    KEY_MODE_SHORT1,
    KEY_MODE_SHORT2,
    KEY_MODE_SHORT3,
    KEY_MODE_LONG,
}KeyModeEnumType;
typedef struct
{
    Pfuntion *KeySta;
    KeyModeEnumType KeyMode;
    uint16_t KeyOnTime;
    uint16_t KeyOffTime;
    uint8_t KeyShortStep;
    uint8_t KeyLongStep;
    uint8_t KeyCnt;
}KeyParaStructType;

typedef struct
{
    KeyParaStructType *KeyPiont[2];
    uint8_t KeyPiontNum;
}KeyPiontStuctType;

void KeyScan(void);
void KeyStatueHandle(void);

#endif
