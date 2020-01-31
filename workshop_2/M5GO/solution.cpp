#include <Arduino.h>
#include "HCRL_EDU.h"

float temp;
float humi;
float pressure;
uint8_t motionStatus;

HCRL_EDU hcrl;
void setup()
{
    Serial.begin(115200);

    /*
        begin motion sensor
    */
    hcrl.MOTION.begin();
    /*
        begin env sensor
    */

    hcrl.ENV.begin();
}
void loop()
{
    /*
        get current temperature and store in variable 
    */
    temp = hcrl.ENV.getTemp();

    /*
        get current humidity and store in variable 
    */
    humi = hcrl.ENV.getHumi();

    /*
        get current pressure and store in variable 
    */
    pressure = hcrl.ENV.getPressure();
    /*
        get current motion value  and store in variable 
    */
    motionStatus = hcrl.MOTION.getValue();

    hcrl.update();
}
