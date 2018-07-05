#include "LedController.h"
#include "Led.h"
#include "Button.h"

/*void turnOnLedIfButtonIsPressed(void){
  if(getButtonState() != 0){
      turnLed(LED_OFF);
  }
}

void turnOffLedIfButtonIsPressed(void){
  if(getButtonState() == 0){
      turnLed(LED_ON);
  }
}
*/

// combine both

void turnOnLedIfButtonIsPressed(void){
    int button_state = getButtonState();
  if(button_state != 0){
      turnLed(LED_ON);
    }
  else if(button_state == 0){
      turnLed(LED_OFF);
    }
  }

/*void checkButtonAndDoLedForever(void){
  while(1){
      turnOnLedIfButtonIsPressed()
          }
}*/

//*******************Specification of the LED*********************
//1. To turn on
//  Release -> Press -> [ON]
//2. To turn off
//  Release -> Press -> Release -> [OFF]
//3. Remain Led state
//   Release -> Release -> Release -> [ON/OFF]

void doTapTurnOnTapTurnOffLed(LedButtonInfo *Info){

    int currentButtonState = getButtonState();

        // TURN ON (RELEASED - PRESS - RELEASED),1
        if(Info->CurrentLedState == LED_OFF  && Info->OnOrOff== TURN_ON){       // check LED state


              if(currentButtonState == BUTTON_RELEASED && Info->Cycles == FIRST_CYCLE){     // first button
                Info->Cycles = SECOND_CYCLE;
              }
              if (currentButtonState == BUTTON_PRESSED  && Info->Cycles == SECOND_CYCLE){
                Info->Cycles = THIRD_CYCLE;
                Info->previousButtonState = BUTTON_PRESSED;
                Info->CurrentLedState = LED_ON;
                turnLed(LED_ON);
              }
              if (Info->Cycles == THIRD_CYCLE){

                Info->Cycles = FIRST_CYCLE;
              }

            }
			    // STAY ON (PRESS - PRESS -PRESS),5
          else if (Info->CurrentLedState == LED_ON  && Info->OnOrOff== TURN_ON){
            if(currentButtonState == BUTTON_PRESSED && Info->Cycles == FIRST_CYCLE){
              Info->Cycles = SECOND_CYCLE;
            }
            if(currentButtonState == BUTTON_PRESSED  && Info->Cycles == SECOND_CYCLE){
              Info->Cycles = THIRD_CYCLE;
            }
              if(currentButtonState == BUTTON_PRESSED && Info->Cycles == THIRD_CYCLE){
                Info->previousButtonState = BUTTON_PRESSED;
                Info->CurrentLedState = LED_ON;
                Info->Cycles= FIRST_CYCLE;
                turnLed(LED_ON);
              }
          }
          // STAY OFF (PRESS - PRESS -PRESS),6
          else if (Info->CurrentLedState == LED_OFF  && Info->OnOrOff== STAY_OFF){
            if(currentButtonState == BUTTON_PRESSED && Info->Cycles == FIRST_CYCLE){
              Info->Cycles = SECOND_CYCLE;
              }
            if(currentButtonState == BUTTON_PRESSED  && Info->Cycles == SECOND_CYCLE){
              Info->previousButtonState = BUTTON_PRESSED;
              Info->Cycles = THIRD_CYCLE;
            }
              if(currentButtonState == BUTTON_PRESSED  && Info->Cycles == THIRD_CYCLE){
                Info->previousButtonState = BUTTON_PRESSED;
                Info->CurrentLedState = LED_OFF;
                Info->Cycles= FIRST_CYCLE;
                turnLed(LED_OFF);
              }
          }

        // TURN OFF (RELEASED - PRESS - RELEASED),2
          else if (Info->CurrentLedState == LED_ON && Info->OnOrOff== TURN_OFF){
              if(currentButtonState == BUTTON_RELEASED && Info->Cycles == FIRST_CYCLE){
                Info->Cycles = SECOND_CYCLE;
              }

              if (currentButtonState == BUTTON_PRESSED && Info->Cycles == SECOND_CYCLE ){
                Info->previousButtonState = BUTTON_PRESSED;
                Info->Cycles = THIRD_CYCLE;
              }
              if(Info->previousButtonState == BUTTON_PRESSED && currentButtonState == BUTTON_RELEASED && Info->Cycles == THIRD_CYCLE){
                Info->previousButtonState = BUTTON_RELEASED;
                Info->CurrentLedState = LED_OFF;
                Info->Cycles= FIRST_CYCLE;
                turnLed(LED_OFF);
            }
          }
          // STAY OFF (RELEASED - RELEASED - RELEASED),4
            else if (Info->CurrentLedState == LED_OFF && Info->OnOrOff== TURN_OFF){
              if(currentButtonState == BUTTON_RELEASED  && Info->Cycles == FIRST_CYCLE){

                Info->CurrentLedState = LED_OFF;
                Info->Cycles = SECOND_CYCLE;
              }
              if(currentButtonState == BUTTON_RELEASED  && Info->Cycles == SECOND_CYCLE){

                Info->CurrentLedState = LED_OFF;
                Info->Cycles = THIRD_CYCLE;
              }
              if(currentButtonState == BUTTON_RELEASED && Info->Cycles == THIRD_CYCLE){
                Info->previousButtonState = BUTTON_RELEASED;
                Info->CurrentLedState = LED_OFF;
                Info->Cycles= FIRST_CYCLE;
                turnLed(LED_OFF);
              }
          }
           // STAY ON (RELEASED - RELEASED - RELEASED),3
          else if (Info->CurrentLedState == LED_ON && Info->OnOrOff== STAY_ON){
            if(currentButtonState == BUTTON_RELEASED  && Info->Cycles == FIRST_CYCLE){

              Info->CurrentLedState = LED_ON;
              Info->Cycles = SECOND_CYCLE;
            }
            if(currentButtonState == BUTTON_RELEASED  && Info->Cycles == SECOND_CYCLE){

              Info->CurrentLedState = LED_ON;
                Info->Cycles = THIRD_CYCLE;
            }
            if(currentButtonState == BUTTON_RELEASED  && Info->Cycles == THIRD_CYCLE){
              Info->previousButtonState = BUTTON_RELEASED;
              Info->CurrentLedState = LED_ON;
              Info->Cycles = FIRST_CYCLE;
              turnLed(LED_ON);
            }
        }
  }

/*void doTapTapLedController(void){
  LedState CurrentLedState
  while(1){

  }
}*/
