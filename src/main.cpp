#include <M5StickC.h>


// config
#define INACTIVITY_SLEEPMS 10000

// global
int menuCounter = 0;
int ms10Counter = 0;
unsigned long lastButtonTime = 0;
// ms macros
#define MS100(msCounter) (msCounter % 10 == 0)
#define MS500(msCounter) (msCounter % 50 == 0)
#define MS1000(msCounter) (msCounter % 100 == 0)
#define MS2000(msCounter) (msCounter % 200 == 0)
// menu macros
#define MENU_LEN 3
#define MENU_TIME(menuCounter) (menuCounter % MENU_LEN == 0)
#define MENU_POWER(menuCounter) (menuCounter % MENU_LEN == 1)
#define MENU_IMU(menuCounter) (menuCounter % MENU_LEN == 2)

// RTC show
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
void setupTime()
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(40, 0, 2);
}
void loopTime()
{
    // put your main code here, to run repeatedly:
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    M5.Lcd.setCursor(0, 15);
    M5.Lcd.printf("Data: %04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.printf("Week: %d\n", RTC_DateStruct.WeekDay);
    M5.Lcd.printf("Time: %02d : %02d : %02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
}
// Power monitor
double vbat = 0.0;
int discharge, charge;
double temp = 0.0;
double bat_p = 0.0;

void setupPower()
{
    M5.Lcd.fillScreen(BLACK);
}

void loopPower()
{

    vbat = M5.Axp.GetVbatData() * 1.1 / 1000;
    charge = M5.Axp.GetIchargeData() / 2;
    discharge = M5.Axp.GetIdischargeData() / 2;
    temp = -144.7 + M5.Axp.GetTempData() * 0.1;
    bat_p = M5.Axp.GetPowerbatData() * 1.1 * 0.5 / 1000;

    M5.Lcd.setCursor(0, 0, 1);
    M5.Lcd.printf("vbat:%.3fV\r\n", vbat);
    M5.Lcd.printf("icharge:%dmA\r\n", charge);
    M5.Lcd.printf("idischg:%dmA\r\n", discharge);
    M5.Lcd.printf("temp:%.1fC\r\n", temp);
    M5.Lcd.printf("pbat:%.3fmW\r\n", bat_p);
    M5.Lcd.printf("CoIn :%d\r\n", M5.Axp.GetCoulombchargeData());
    M5.Lcd.printf("CoOut:%d\r\n", M5.Axp.GetCoulombdischargeData());
    M5.Lcd.printf("CoD:%.2fmAh\r\n", M5.Axp.GetCoulombData());
    M5.Lcd.printf("Vin:%.3fmV\r\n", M5.Axp.GetVinData() * 1.7);
    M5.Lcd.printf("Iin:%.3fmA\r\n", M5.Axp.GetIinData() * 0.625);
    M5.Lcd.printf("Vuin:%.3fmV\r\n", M5.Axp.GetVusbinData() * 1.7);
    M5.Lcd.printf("Iuin:%.3fmA\r\n", M5.Axp.GetIusbinData() * 0.375);
    // // 0x01 long press(1s), 0x02 press
    // if (M5.Axp.GetBtnPress() == 0x02)
    // {
    //     esp_restart();
    // }
}
// IMU
int16_t accX = 0;
int16_t accY = 0;
int16_t accZ = 0;
int16_t gyroX = 0;
int16_t gyroY = 0;
int16_t gyroZ = 0;
int16_t tempImu = 0;

void setupIMU()
{
    M5.Lcd.fillScreen(BLACK);
    M5.IMU.Init();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(40, 0);
    M5.Lcd.println("SH200I TEST");
    M5.Lcd.setCursor(0, 15);
    M5.Lcd.println("  X       Y       Z");
}

void loopIMU()
{
    M5.IMU.getGyroAdc(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAccelAdc(&accX, &accY, &accZ);
    M5.IMU.getTempAdc(&tempImu);

    M5.Lcd.setCursor(0, 30);
    M5.Lcd.printf("%.2f   %.2f   %.2f      ", ((float)gyroX) * M5.IMU.gRes, ((float)gyroY) * M5.IMU.gRes, ((float)gyroZ) * M5.IMU.gRes);
    M5.Lcd.setCursor(140, 30);
    M5.Lcd.print("mg");
    M5.Lcd.setCursor(0, 45);
    M5.Lcd.printf("%.2f   %.2f   %.2f      ", ((float)accX) * M5.IMU.aRes, ((float)accY) * M5.IMU.aRes, ((float)accZ) * M5.IMU.aRes);
    M5.Lcd.setCursor(140, 45);
    M5.Lcd.print("o/s");
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.printf("Temperature : %.2f C", ((float)tempImu) / 333.87 + 21.0);
}

void loopMenu()
{
    // buttons
    if (digitalRead(M5_BUTTON_HOME) == LOW)
    {
        lastButtonTime = millis();
        menuCounter++;
        if (MENU_TIME(menuCounter))
        {
            setupTime();
            loopTime();
        }
        else if (MENU_POWER(menuCounter))
        {
            setupPower();
            loopPower();
        }
        else if (MENU_IMU(menuCounter))
        {
            setupIMU();
            loopIMU();
        }
        delay(200); // debounce
    }
    else if (digitalRead(BUTTON_B_PIN) == LOW)
    {
        M5.Lcd.fillScreen(BLACK);
        M5.Axp.DeepSleep(SLEEP_SEC(30));
        delay(200); // debounce
    }
    //sleep
    if ( millis() - lastButtonTime > INACTIVITY_SLEEPMS ) {
        M5.Axp.DeepSleep(SLEEP_SEC(30));
        //M5.Axp.DeepSleep(30);
    }
}

void setTime()
{
    // RTC_TimeTypeDef TimeStruct;
    // TimeStruct.Hours   = 15;
    // TimeStruct.Minutes = 50;
    // TimeStruct.Seconds = 00;
    // M5.Rtc.SetTime(&TimeStruct);
    // RTC_DateTypeDef DateStruct;
    // DateStruct.WeekDay = 7;
    // DateStruct.Month = 7;
    // DateStruct.Date = 27;
    // DateStruct.Year = 2019;
    // M5.Rtc.SetData(&DateStruct);
}

void setup()
{
    //pin
    pinMode(M5_BUTTON_HOME, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    // screen
    M5.begin();
    M5.Lcd.setRotation(3);
    setupTime();
    //power
    M5.Axp.EnableCoulombcounter();
}

void loop()
{
    // loop
    if (MENU_TIME(menuCounter) && MS1000(ms10Counter))
    {
        loopTime();
    }
    else if (MENU_POWER(menuCounter) && MS500(ms10Counter))
    {
        loopPower();
    }
    else if (MENU_IMU(menuCounter) && MS100(ms10Counter))
    {
        loopIMU();
    }
    // handle menu
    loopMenu();
    delay(10);
    ms10Counter++;
}
