#ifndef _LED_H
#define _LED_H

// enum (define variation interm of number)
// LED_OFF - 0
// LED_on  - 1
typedef enum {
  LED_OFF = 0,
  LED_ON  = 1
} LedState;

/*

*/
void turnLed(LedState state);
#endif // _LED_H
