#include "unity.h"
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "LedController.h"
#include "mock_Button.h"    // mock_ tell ceedling to mock
#include "mock_Led.h"       // mock_ will be removed when compile

int turnLedCallNumbers = 0;
int getButtonStateMaxCalls = 0;
int expectedTurnLedMaxCalls = 0;
ButtonState *expectedButtonStates = NULL;
LedState *expectedLedStates = NULL;

void setUp(void){}
void tearDown(void){}

char *createMsg(char *format,...){
  va_list valist;
  int neededSize = 0;
  char *buffer;          // store data


  va_start(valist,format);
  neededSize = vsnprintf(buffer, 0, format, valist) + 1; // since 0 it will return bytes required due to ISO99_source
  buffer = malloc(neededSize);
  vsnprintf(buffer, neededSize, format, valist);
  va_end(valist);

  return buffer;
}

void freeError(char *msg){
  if(msg) {
    free(msg);
  }
}
char *getLedStateName(LedState state){
  switch(state){
    case LED_ON:
     return "LED_ON";
    case LED_OFF:
     return "LED_OFF";
    default:
      return "(unknown LED state)";
  }
}
void fake_turnLed(LedState state,int NumCalls){
  char *msg;
  turnLedCallNumbers++;
  if(NumCalls < expectedTurnLedMaxCalls){
    LedState expectedState = expectedLedStates[NumCalls];

  if(state != expectedLedStates){
      msg = createMsg("turnLed() was called with %s, but expect %s"), \
                getLedStateName(state), getLedStateName(expectedState);
    TEST_FAIL_MESSAGE(msg);

  }
    else
      msg = createMsg("turnLed() was called with %s, but expect %s"), \
                getLedStateName(state), getLedStateName(expectedState);
    TEST_FAIL_MESSAGE(msg);
  }

}
ButtonState fake_getButtonState(int NumCalls){
  if(NumCalls < getButtonStateMaxCalls){
    return expectedButtonStates[NumCalls];
  }
  else
  TEST_FAIL_MESSAGE("Received extra getButtonState() calls.");
}

void setupFake(LedState expLedStates[], int LedMaxCalls,ButtonState buttStates[], int buttonMaxCalls){
    turnLedCallNumbers = 0;

    turnLed_StubWithCallback(fake_turnLed);
    expectedLedStates= expLedStates;
    expectedTurnLedMaxCalls - LedMaxCalls;

    getButtonState_StubWithCallback(fake_getButtonState);
    expectedButtonStates = buttStates;
    getButtonStateMaxCalls = buttonMaxCalls;
}

void verifyTurnLedCalls(int numCalls ){
  if (turnLedCallNumbers != numCalls){
      TEST_FAIL_MESSAGE("turnLed() was not call at all. But 1 call is expected");
  }
}

// TURN ON (RELEASED - PRESS - RELEASED),1
void test_XXXXXX(void){

  LedButtonInfo Info = {LED_OFF, BUTTON_RELEASED,TURN_ON, FIRST_CYCLE};
  LedState expectedLedStates[] = {LED_ON};
  ButtonState expectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
  setupFake(expectedLedStates,1,expectedButtonStates,3);

 getButtonState();
 getButtonState();
 turnLed(LED_ON);
 getButtonState();
  verifyTurnLedCalls(1);

}

  // TURN ON (RELEASED - PRESS - RELEASED),1
void test_doTapTurnOnTapTurnOffLed_given_led_is_off_button_is_pressed_and_released_expect_led_is_turned_on(void){

    LedButtonInfo Info = {LED_OFF, BUTTON_RELEASED,TURN_ON, FIRST_CYCLE};
    LedState expectedLedStates[] = {LED_ON};
    ButtonState expectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
    setupFake(expectedLedStates,1,expectedButtonStates,3);
    //turnLedCallNumbers = 0;

    //getButtonState_StubWithCallback(fake_getButtonStateReleasedPressedReleased);

    doTapTurnOnTapTurnOffLed(&Info);
    doTapTurnOnTapTurnOffLed(&Info);
    doTapTurnOnTapTurnOffLed(&Info);

    verifyTurnLedCalls(1);
    TEST_ASSERT_EQUAL(LED_ON, Info.CurrentLedState);
}

// TURN OFF (RELEASED - PRESS - RELEASED),2
void test_doTapTurnOnTapTurnOffLed_given_led_is_on_button_is_pressed_and_released_expect_led_is_turned_off(void){
//                      currentLed , previousbut ,2 statesbeforebut

    LedButtonInfo Info = {LED_ON, BUTTON_RELEASED,TURN_OFF, FIRST_CYCLE};
    LedState expectedLedStates[] = {LED_OFF};
    ButtonState extectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
    setupFake(expectedLedStates,1,expectedButtonStates,3);


    doTapTurnOnTapTurnOffLed(&Info);
    doTapTurnOnTapTurnOffLed(&Info);
    doTapTurnOnTapTurnOffLed(&Info);

    verifyTurnLedCalls(1);
    TEST_ASSERT_EQUAL(LED_OFF, Info.CurrentLedState);
}


/*
// STAY ON (RELEASED - RELEASED - RELEASED),3
void test_doTapTurnOnTapTurnOffLed_given_led_is_on_button_is_released_and_released_expect_led_is_turned_on(void){

    LedButtonInfo Info = {LED_ON, BUTTON_RELEASED,STAY_ON,FIRST_CYCLE};

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    doTapTurnOnTapTurnOffLed(&Info);

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    doTapTurnOnTapTurnOffLed(&Info);

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    turnLed_Expect(LED_ON);
    doTapTurnOnTapTurnOffLed(&Info);


    TEST_ASSERT_EQUAL(LED_ON, Info.CurrentLedState);
}

// STAY OFF (RELEASED - RELEASED - RELEASED),4
void test_doTapTurnOnTapTurnOffLed_given_led_is_off_button_is_released_and_released_expect_led_is_turned_off(void){

    LedButtonInfo Info = {LED_OFF, BUTTON_RELEASED,TURN_OFF};

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    doTapTurnOnTapTurnOffLed(&Info);

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    doTapTurnOnTapTurnOffLed(&Info);

    getButtonState_ExpectAndReturn(BUTTON_RELEASED);

    turnLed_Expect(LED_OFF);
    doTapTurnOnTapTurnOffLed(&Info);


    TEST_ASSERT_EQUAL(LED_OFF, Info.CurrentLedState);
}

// STAY ON (PRESS - PRESS -PRESS),5
void test_doTapTurnOnTapTurnOffLed_given_led_is_on_button_is_pressed_and_pressed_expect_led_is_turned_on(void){

  LedButtonInfo Info = {LED_ON, BUTTON_PRESSED,TURN_ON};

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);

  doTapTurnOnTapTurnOffLed(&Info);

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);


  doTapTurnOnTapTurnOffLed(&Info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  doTapTurnOnTapTurnOffLed(&Info);


  TEST_ASSERT_EQUAL(LED_ON, Info.CurrentLedState);
}

// STAY OFF (PRESS - PRESS -PRESS),6
void test_doTapTurnOnTapTurnOffLed_given_led_is_off_button_is_pressed_and_pressed_expect_led_is_turned_off(void){

  LedButtonInfo Info = {LED_OFF, BUTTON_PRESSED ,STAY_OFF};

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);

  doTapTurnOnTapTurnOffLed(&Info);

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);


  doTapTurnOnTapTurnOffLed(&Info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);

  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&Info);


  TEST_ASSERT_EQUAL(LED_OFF, Info.CurrentLedState);
}
*/
