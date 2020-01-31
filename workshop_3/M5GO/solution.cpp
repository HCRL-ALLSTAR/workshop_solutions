#include <Arduino.h>
#include "HCRL_EDU.h"

float temp;
float humi;
float pressure;
uint8_t motionStatus;

uint8_t light_1Status;
uint8_t light_2Status;
uint8_t light_3Status;

uint16_t light_1RGB[3];
uint16_t light_2RGB[3];
uint16_t light_3RGB[3];

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

    /*
        begin RGB led sensor
    */
    hcrl.LED.begin();

    /*
        set default RGB led brightness
    */
    hcrl.LED.setBrightness(10);
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

    hcrl.LED.set_RGB(0, light_1RGB[0], light_1RGB[1], light_1RGB[2]);
    hcrl.LED.set_RGB(1, light_2RGB[0], light_2RGB[1], light_2RGB[2]);
    hcrl.LED.set_RGB(2, light_3RGB[0], light_3RGB[1], light_3RGB[2]);
    hcrl.LED.set_status(0, light_1Status);
    hcrl.LED.set_status(1, light_2Status);
    hcrl.LED.set_status(2, light_3Status);

    hcrl.update();
}
