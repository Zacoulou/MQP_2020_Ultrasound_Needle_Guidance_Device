#include "DPad.h"

String readSwitch()
{
    pos_A = digitalRead(switch_A);
    pos_B = digitalRead(switch_B);
    pos_C = digitalRead(switch_C);
    pos_D = digitalRead(switch_D);
    pos_E = digitalRead(switch_E);

    currentPress = "Neutral";

    if (pos_A == HIGH){currentPress = "Up";}
    if (pos_B == HIGH){currentPress = "Left";}
    if (pos_C == HIGH){currentPress = "Down";}
    if (pos_D == HIGH){currentPress = "Right";}
    if (pos_E == HIGH){currentPress = "Middle";}

    return currentPress;
}