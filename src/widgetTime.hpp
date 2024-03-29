
#include <M5StickC.h>


// first time setup
void setTime()
{
    // RTC_TimeTypeDef TimeStruct;
    // TimeStruct.Hours   = 1;
    // TimeStruct.Minutes = 04;
    // TimeStruct.Seconds = 00;
    // M5.Rtc.SetTime(&TimeStruct);
    // RTC_DateTypeDef DateStruct;
    // DateStruct.WeekDay = 1;
    // DateStruct.Month = 11;
    // DateStruct.Date = 17;
    // DateStruct.Year = 2019;
    // M5.Rtc.SetData(&DateStruct);
}

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
    M5.Lcd.printf("Date: %04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.printf("Week: %d\n", RTC_DateStruct.WeekDay);
    M5.Lcd.printf("Time: %02d : %02d : %02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
}