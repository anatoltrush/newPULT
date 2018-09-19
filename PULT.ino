#include <LiquidCrystal.h>
#include "INIT_PULT.h"
#include "SYMBOLS.h"
#include "D:\OTHER\BoEvgeshka\COMMON\VOLTAGE.h"
#include "D:\OTHER\BoEvgeshka\COMMON\FLASH.h"
#include "JOYSTICK.h"
//WI-FI
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define TIME_READ_JOYSTICK 20//must be 20...40
#define TIME_READ_VOLTAGE 3000
#define MIN_VOLTAGE 6.6//min voltage
#define MAX_VOLTAGE 8.4//max voltage

#define VOLTAGE_PIN A2

#define JOY_LEFT_X A0
#define JOY_LEFT_Y A1
#define JOY_LEFT_CLICK A5

#define JOY_RIGHT_X A3
#define JOY_RIGHT_Y A4
#define JOY_RIGHT_CLICK A6

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Voltage volt(VOLTAGE_PIN, TIME_READ_VOLTAGE, MIN_VOLTAGE, MAX_VOLTAGE);
Joystick joy_left(JOY_LEFT_X, JOY_LEFT_Y, JOY_LEFT_CLICK, TIME_READ_JOYSTICK, true);
Joystick joy_right(JOY_RIGHT_X, JOY_RIGHT_Y, JOY_RIGHT_CLICK, TIME_READ_JOYSTICK, false);
uint8_t data_upr[SIZE_OF_DATA] = {0, 0, 0, 0, 0, 0};
Flasher led(8, TIME_READ_JOYSTICK, TIME_READ_JOYSTICK);
//WI-FI
RF24 radio(9, 10);				//создать" модуль на пинах 9 и 10
byte address[][6] = { "1Node", "2Node", "3Node", "4Node", "5Node", "6Node" }; //возможные номера труб
float volt_kv;
byte gotByte;
void setup() {
	//more important
	lcd.begin(16, 2);
	lcd_initialization(lcd); //WRITE SYMBOLS
	//WI-FI
	radio.begin();				//активировать модуль
	radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
	radio.setRetries(0, 15);     //время между попыткой достучаться, число попыток
	radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
	radio.setPayloadSize(32);     //размер пакета, в байтах

	radio.openWritingPipe(address[0]);   //мы - труба 0, открываем канал для передачи данных
	radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

	radio.setPALevel(RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
	radio.setDataRate(RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
								   //должна быть одинакова на приёмнике и передатчике!
								   //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
								   //ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!
	radio.powerUp(); //начать работу
	radio.stopListening();  //не слушаем радиоэфир, мы передатчик
#ifdef FOR_DEBUG
	Serial.begin(9600);
	Serial.println("Start PULT!");
#endif //FOR_DEBUG
}
void loop() {
	while (true)
	{
		//more important
		joy_left.update(data_upr[0], data_upr[1], data_upr[4]);
		joy_right.update(data_upr[2], data_upr[3], data_upr[5]);
		//WI-FI
		if (radio.write(&data_upr, sizeof(data_upr))) {
			if (!radio.available()) {                     //если получаем не пустой ответ
#ifdef FOR_DEBUG
				Serial.println("Empty!");
#endif //FOR_DEBUG
			}
			else {
				while (radio.available()) {                      //если в ответе что-то есть
					radio.read(&gotByte, 1);
					volt_kv = gotByte;
					volt_kv /= 10;
					volt.is_conn = true;
          joy_left.on_lcd(lcd, data_upr[0], data_upr[1], data_upr[4]);
          joy_right.on_lcd(lcd, data_upr[2], data_upr[3], data_upr[5]);
#ifdef FOR_DEBUG
					Serial.print("Answer: "); Serial.println(volt_kv);
#endif //FOR_DEBUG
				}
			}
		}
		else {
			volt.is_conn = false;
#ifdef FOR_DEBUG
			//Serial.println("Fail connect");
#endif //FOR_DEBUG
		}
		//less important
		volt.show_all_pult_voltage(lcd);
		volt.show_all_kvadro_voltage(lcd, volt_kv);
		led.update();
	}
}
