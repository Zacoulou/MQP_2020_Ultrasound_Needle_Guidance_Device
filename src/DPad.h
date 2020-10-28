#ifndef _DPAD_H_
#define _DPAD_H_

#include <arduino.h>

//Button Pinout
extern const int switch_A;  // UP        
extern const int switch_B;  // LEFT     
extern const int switch_C;  // DOWN     
extern const int switch_D;  // RIGHT     
extern const int switch_E;  // PRESSED   

extern int pos_A , pos_B, pos_C, pos_D, pos_E;
extern String currentPress;

//Function Prototypes
String readSwitch();

#endif /* _DPAD_H_ */
