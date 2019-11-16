#include <M5StickC.h>


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
