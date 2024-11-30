#include "user_key.h"


extern uint8_t refresh;

void Key_Event_CW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","157AAAAAAAA9876543210",2,1,0,1);
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_CCW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W2","157AAAAAAAA9876543210",2,1,0,1);
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_PUSH(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","00000000000123456789A987654321000000000000000",2,1,0,1);
      hxzp_Led_piece("W1","123456789A98765432100000000000000000000000000",2,1,0,1);
      hxzp_Led_piece("W2","00000000000123456789A987654321000000000000000",2,1,0,1);
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_KEY1(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","0000000000000000000000123456789A9876543210000",2,1,0,1);
      hxzp_Led_piece("W1","00000000000123456789A987654321000000000000000",2,1,0,1);
      hxzp_Led_piece("W2","123456789A98765432100000000000000000000000000",2,1,0,1);
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_KEY2(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","123456789A98765432100000000000000000000000000",2,1,0,1);
      hxzp_Led_piece("W1","00000000000123456789A987654321000000000000000",2,1,0,1);
      hxzp_Led_piece("W2","0000000000000000000000123456789A9876543210000",2,1,0,1);    
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void User_Key_Init(void)
{
  hxzp_Key_eventReg("CW",Key_Event_CW);
  hxzp_Key_eventReg("CCW",Key_Event_CCW);
  hxzp_Key_eventReg("PUSH",Key_Event_PUSH);
  hxzp_Key_eventReg("KEY1",Key_Event_KEY1);
  hxzp_Key_eventReg("KEY2",Key_Event_KEY2);  
}












