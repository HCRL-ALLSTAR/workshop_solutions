#include <Arduino.h>
#include "HCRL_EDU.h"

uint8_t motionStatus;
void setup()
{
    Serial.begin(115200);

    /*
        begin motion sensor
    */
    hcrl.MOTION.begin();
}
void loop()
{
    motionStatus = hcrl.MOTION.getValue();
    
    hcrl.update();
}
