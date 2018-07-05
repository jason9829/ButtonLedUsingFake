#ifndef _BUTTON_H
#define _BUTTON_H

/*
  Return non-zero if button is pressed; Otherwise, return 0
*/
typedef enum{
  BUTTON_RELEASED = 0,
  BUTTON_PRESSED     = 1,
} ButtonState;

/*
  To diffentiate the if else statement for turn ON led or OFF
*/
typedef enum{
  TURN_OFF = 0 ,
  TURN_ON  = 1 ,
  STAY_OFF =2,
  STAY_ON =3,
} Operation;

/*
  Three cycles based on test
  When at THIRD_CYCLE cyclesState set back to FIRST_CYCLE
*/
typedef enum{
  FIRST_CYCLE  = 1,
  SECOND_CYCLE = 2,
  THIRD_CYCLE  = 3,
} cyclesState;

ButtonState getButtonState(void);

#endif // _BUTTON_H
