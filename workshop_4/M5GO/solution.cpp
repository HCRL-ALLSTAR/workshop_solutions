#include <Arduino.h>
#include "HCRL_EDU.h"

#define AIR_GREEN_ICON_PATH "/AIR/Air_GREEN.png"
#define AIR_GREEN_HOVER_ICON_PATH "/AIR/Air_GREEN_Hover.png"
#define AIR_RED_ICON_PATH "/AIR/Air_RED.png"
#define AIR_RED_HOVER_ICON_PATH "/AIR/Air_RED_Hover.png"
#define FAN_ICON_PATH "/FAN/Fan_BLUE.png"
#define FAN_HOVER_ICON_PATH "/FAN/Fan_BLUE_Hover.png"
#define LIGHT_ICON_PATH "/LIGHT/Li_YELLOW.png"
#define LIGHT_HOVER_ICON_PATH "/LIGHT/Li_YELLOW_Hover.png"

#define FAN_INDEX 0
#define AIR_INDEX 1
#define LIGHT_1_INDEX 2
#define LIGHT_2_INDEX 3
#define LIGHT_3_INDEX 4

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
        begin display render 
    */
    hcrl.Ui.begin();
    hcrl.Ui.node_init(5);
    for (int i = 0; i < 5; i++)
    {
        char buffer[50];
        sprintf(buffer, "Item %d", i);
        hcrl.Ui.node_setTitle(i, (String)buffer, "abcdefghijkl");
        hcrl.Ui.node_setTitlePic(i, AIR_RED_ICON_PATH, AIR_GREEN_HOVER_ICON_PATH);
    }

    /*
        set color of UI 
    */
    hcrl.Ui.node_setAllTitleColor(WHITE, CYAN);

    /*
        set UI index 0 to fan node and fan mode
    */
    hcrl.Ui.node_setType(FAN_INDEX, FAN);
    hcrl.Ui.node_setTitle(FAN_INDEX, "Fan", "Near Door");
    hcrl.Ui.node_setTitlePic(FAN_INDEX, FAN_ICON_PATH, FAN_HOVER_ICON_PATH);

    /*
        set UI index 1 to light node and air mode
    */
    hcrl.Ui.node_setType(AIR_INDEX, AIR);
    hcrl.Ui.node_setTitle(AIR_INDEX, "Air", " ");
    hcrl.Ui.node_setTitlePic(AIR_INDEX, AIR_RED_ICON_PATH, AIR_RED_HOVER_ICON_PATH);

    /*
        set UI index 2 to light node and light mode
    */
    hcrl.Ui.node_setType(LIGHT_1_INDEX, LIGHT);
    hcrl.Ui.node_setTitle(LIGHT_1_INDEX, "LIGHT", "1");
    hcrl.Ui.node_setTitlePic(LIGHT_1_INDEX, LIGHT_ICON_PATH, LIGHT_HOVER_ICON_PATH);

    /*
        set UI index 3 to light node and light mode
    */
    hcrl.Ui.node_setType(LIGHT_2_INDEX, LIGHT);
    hcrl.Ui.node_setTitle(LIGHT_2_INDEX, "LIGHT", "2");
    hcrl.Ui.node_setTitlePic(LIGHT_2_INDEX, LIGHT_ICON_PATH, LIGHT_HOVER_ICON_PATH);

    /*
        set UI index 4 to light node and light mode
    */
    hcrl.Ui.node_setType(LIGHT_3_INDEX, LIGHT);
    hcrl.Ui.node_setTitle(LIGHT_3_INDEX, "LIGHT", "3");
    hcrl.Ui.node_setTitlePic(LIGHT_3_INDEX, LIGHT_ICON_PATH, LIGHT_HOVER_ICON_PATH);

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

    /*
        get current data from ui node use index of each item to access data
    */
    light_1Status = hcrl.Ui.get_node_data(LIGHT_1_INDEX);
    light_2Status = hcrl.Ui.get_node_data(LIGHT_2_INDEX);
    light_3Status = hcrl.Ui.get_node_data(LIGHT_3_INDEX);

    hcrl.LED.set_RGB(0, light_1RGB[0], light_1RGB[1], light_1RGB[2]);
    hcrl.LED.set_RGB(1, light_2RGB[0], light_2RGB[1], light_2RGB[2]);
    hcrl.LED.set_RGB(2, light_3RGB[0], light_3RGB[1], light_3RGB[2]);
    hcrl.LED.set_status(0, light_1Status);
    hcrl.LED.set_status(1, light_2Status);
    hcrl.LED.set_status(2, light_3Status);

    hcrl.update();
}
