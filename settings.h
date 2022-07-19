#ifndef SETTINGS_H

#define DEBUG false
#define SIM false

//ポート割り当て
#ifndef PORT
#define LEFTWHEEL PORT_C
#define RIGHTWHEEL PORT_B
#define COLORSENSOR PORT_1
#define GYROSENSOR PORT_2
#define TOUCHSENSOR PORT_3
#define SONARSENSOR PORT_4
#define PORT
#endif

//シュミレータ環境の値
#define SIM_MIN_BRIGHTNESS 2
#define SIM_MAX_BRIGHTNESS 35
#define SIM_AVG_BRIGHTNESS 18

//動作周期
#define ORDER_T 20
#define BLUETOOTH_T 100

//走行体情報
#define WHEEL 5 //車輪半径(cm)
#define BETWHEENWHEEL 15 //車輪間距離(cm)

#define SETTINGS_H
#endif