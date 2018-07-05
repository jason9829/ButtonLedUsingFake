#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"    // mock_ tell ceedling to mock
#include "mock_Led.h"       // mock_ will be removed when compile

int turnLedCallNumbers = 0;
int getButtonStateMaxCalls = 0;
int exptectedTurnLedMaxCalls = 0;
ButtonState *exptectedButtonStates = NULL;
LedState *exptectedLedStates = NULL;

void setUp(void){}
void tearDown(void){}


void fake_turnLed(LedState state,int NumCalls){
  turnLedCallNumbers++;
  if(NumCalls < exptectedTurnLedMaxCalls){
      if(state != exptectedLedStates[NumCalls]){
        TEST_FAIL_MESSAGE("turnLed() was called with ???, but expect ???");
      }
    }
    else
    TEST_FAIL_MESSAGE("turnLed() was called with ???, but expect ???");
  }


ButtonState fake_getButtonState(int NumCalls){
  if(NumCalls < getButtonStateMaxCalls){
    return exptectedButtonStates[NumCalls];
  }
  else
  TEST_FAIL_MESSAGE("Received extra getButtonState() calls.");
}

void setupFake(LedState expLedStates[], int LedMaxCalls,ButtonState buttStates[], int buttonMaxCalls){
    turnLedCallNumbers = 0;

    turnLed_StubWithCallback(fake_turnLed);
    exptectedLedStates= expLedStates;
    exptectedTurnLedMaxCalls - LedMaxCalls;

    getButtonState_StubWithCallback(fake_getButtonState);
    exptectedButtonStates = buttStates;
    getButtonStateMaxCalls = buttonMaxCalls;
}

void verifyTurnLedCalls(int numCalls ){
  if (turnLedCallNumbers != numCalls){
      TEST_FAIL_MESSAGE("turnLed() was not call at all. But 1 call is expected");
  }
}

  // TURN ON (RELEASED - PRESS - RELEASED),1
void test_doTapTurnOnTapTurnOffLed_given_led_is_off_button_is_pressed_and_released_expect_led_is_turned_on(void){

    LedButtonInfo Info = {LED_OFF, BUTTON_RELEASED,TURN_ON, FIRST_CYCLE};
    LedState exptectedLedStates[] = {LED_ON};
    ButtonState exptectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
    setupFake(exptectedLedStates,1,exptectedButtonStates,3);
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
    LedState exptectedLedStates[] = {LED_OFF};
    ButtonState exptectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
    setupFake(exptectedLedStates,1,exptectedButtonStates,3);


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
