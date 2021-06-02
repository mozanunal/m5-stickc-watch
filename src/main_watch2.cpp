// #include <M5StickC.h>
// #include <WiFi.h>
// #include <esp_wifi.h>

// // widgets
// #include "widgetTime.hpp"
// #include "widgetPower.hpp"
// #include "widgetIMU.hpp"
// #include "menu.hpp"

// // config
// #define INACTIVITY_SLEEPMS 20000
// const char *ssid = "xxxx";
// const char *password = "xxxx";

// // global
// int menuCounter = 0;
// int ms10Counter = 0;
// unsigned long lastButtonTime = 0;
// RTC_DATA_ATTR int bootCount = 0;

// void loopMenu()
// {
//     // buttons
//     if (digitalRead(M5_BUTTON_HOME) == LOW)
//     {
//         lastButtonTime = millis();
//         menuCounter++;
//         if (MENU_TIME(menuCounter))
//         {
//             setupTime();
//             loopTime();
//         }
//         else if (MENU_POWER(menuCounter))
//         {
//             setupPower();
//             loopPower();
//         }
//         else if (MENU_IMU(menuCounter))
//         {
//             setupIMU();
//             loopIMU();
//         }
//         delay(200); // debounce
//     }
//     else if (digitalRead(BUTTON_B_PIN) == LOW)
//     {
//         M5.Lcd.fillScreen(BLACK);
//         M5.Axp.DeepSleep(SLEEP_SEC(30));
//         delay(200); // debounce
//     }
//     //sleep
//     if (millis() - lastButtonTime > INACTIVITY_SLEEPMS)
//     {
//         lastButtonTime = millis();
//         // fill screen with black
//         M5.Lcd.fillScreen(BLACK);
//         M5.Axp.ScreenBreath(7);
//         //Configure GPIO37 as ext0 wake up source for LOW logic level
//         esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0);
//         //Go to sleep now
//         M5.Axp.DeepSleep(0);
//     }
// }



// void setup()
// {
//     ++bootCount;
//     //pin
//     pinMode(M5_BUTTON_HOME, INPUT_PULLUP);
//     pinMode(BUTTON_B_PIN, INPUT_PULLUP);
//     // screen
//     M5.begin();
//     M5.Lcd.setRotation(3);
//     setupTime();
//     //power
//     M5.Axp.EnableCoulombcounter();
//     setTime();
//     // wifi
//     // WiFi.begin(ssid, password);             // Connect to the network
//     // M5.Lcd.printf("Connecting to ");
//     // M5.Lcd.printf(ssid);

//     // while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
//     //     delay(500);
//     //     M5.Lcd.printf(".");
//     // }
//     // M5.Lcd.println('\n');
//     // M5.Lcd.println("Connection established!");
//     // M5.Lcd.print("IP address:\t");
//     // M5.Lcd.println(WiFi.localIP());
//     //esp_wifi_stop();
// }

// void loop()
// {
//     // loop
//     if (MENU_TIME(menuCounter) && MS1000(ms10Counter))
//     {
//         loopTime();
//     }
//     else if (MENU_POWER(menuCounter) && MS500(ms10Counter))
//     {
//         loopPower();
//     }
//     else if (MENU_IMU(menuCounter) && MS100(ms10Counter))
//     {
//         loopIMU();
//     }
//     // handle menu
//     loopMenu();
//     delay(10);
//     ms10Counter++;
// }
