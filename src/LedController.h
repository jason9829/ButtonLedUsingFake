#ifndef _LEDCONTROLLER_H
#define _LEDCONTROLLER_H

#include "Led.h"
#include "Button.h"

typedef struct LedButtonInfo LedButtonInfo;
struct LedButtonInfo{

  LedState CurrentLedState;
  ButtonState previousButtonState;
  Operation OnOrOff;
  cyclesState Cycles;
};


void turnOnLedIfButtonIsPressed(void);
//void turnOffLedIfButtonIsPressed(void);
void doTapTurnOnTapTurnOffLed(LedButtonInfo *Info);

#endif // _LEDCONTROLLER_H
