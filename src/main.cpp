#include <M5StickC.h>
#include <WiFi.h>
#include <esp_wifi.h>
// widgets
#include "widgetTime.hpp"
#include "widgetPower.hpp"
#include "widgetIMU.hpp"
#include "menu.hpp"
#include "led.hpp"

// config
#define INACTIVITY_SLEEPMS 20000
const char *ssid = "xxxx";
const char *password = "xxxx";

// global
int menuCounter = 0;
int ms10Counter = 0;
int hue = 0;
int brig = 50;
unsigned long lastButtonTime = 0;
unsigned long lastPushTime = 0;
unsigned long lastReleaseTime = 0;
RTC_DATA_ATTR int bootCount = 0;



void sleep();
void cleanScreen();
void IRAM_ATTR released();
void IRAM_ATTR pushed();


void buttonClick()
{
    if (menuCounter % 2 == 0)
    {
        hue += 25;
        cleanScreen();
        M5.Lcd.printf("Hue Updated: %d", hue%251);
    }
    else 
    {
        brig += 50;
        cleanScreen();
        M5.Lcd.printf("Brig Updated: %d", brig%251);

    }
}

void buttonLongClick()
{
    cleanScreen();
    M5.Lcd.printf("Mode Changed");
    menuCounter++;
}

void IRAM_ATTR pushed() {
    lastPushTime = millis();
    attachInterrupt(M5_BUTTON_HOME, released, RISING);
    cleanScreen();
    M5.Lcd.printf("pushed");
}

void IRAM_ATTR released() {
    lastReleaseTime = millis();
    attachInterrupt(M5_BUTTON_HOME, pushed, FALLING);
    cleanScreen();
    M5.Lcd.printf("released");
    if ( lastReleaseTime - lastPushTime > 1000 )
    {
        buttonLongClick();
    }
    else
    {
        buttonClick();
    }
}

void setup()
{
    ++bootCount;
    //pin
    pinMode(M5_BUTTON_HOME, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    attachInterrupt(M5_BUTTON_HOME, pushed, FALLING);
    // attachInterrupt(M5_BUTTON_HOME, released, RISING);
    // screen
    M5.begin();
    M5.Lcd.setRotation(3);
    //led
    setupLeds();
    
    // wifi
    // WiFi.begin(ssid, password);             // Connect to the network
    cleanScreen();
    M5.Lcd.printf("Reboot...");
    // M5.Lcd.printf(ssid);

    // while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    //     delay(500);
    //     M5.Lcd.printf(".");
    // }
    // M5.Lcd.println('\n');
    // M5.Lcd.println("Connection established!");
    // M5.Lcd.print("IP address:\t");
    // M5.Lcd.println(WiFi.localIP());
    //esp_wifi_stop();
}

void loop()
{
    
    // loop
    if (digitalRead(M5_BUTTON_HOME) == LOW)
    {

    }
    fire(hue%251, brig%251);
    // handle menu
    ms10Counter++;
}

void cleanScreen()
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(40, 0, 2);
}

void sleep()
{
    lastButtonTime = millis();
    // fill screen with black
    M5.Lcd.fillScreen(BLACK);
    M5.Axp.ScreenBreath(7);
    //Configure GPIO37 as ext0 wake up source for LOW logic level
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0);
    //Go to sleep now
    M5.Axp.DeepSleep(0);
}