#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <LiquidCrystal.h>

#define LCD_LEFT_POS 9
#define LCD_RIGHT_POS 13

#define DEBUG

class Joystick {
	bool is_defined;
	bool is_left;
	uint8_t differ_x;
	uint8_t differ_y;
	uint8_t x_pin;
	uint8_t y_pin;
  uint8_t cl_pin;
	long period; //period
	unsigned long previousMillis; //last read
public:
	Joystick(uint8_t x_p, uint8_t y_p, uint8_t cl_p, long per, bool is_lft):
	is_defined(false),
	is_left(is_lft),
	differ_x(0),
	differ_y(0),
	x_pin(x_p),
	y_pin(y_p),
	cl_pin(cl_p),
	period(per),
	previousMillis(0)
	{
		pinMode(x_pin, INPUT);
		pinMode(y_pin, INPUT);
    	pinMode(cl_pin, INPUT);
	}
 
	void update(uint8_t &dataX, uint8_t &dataY, uint8_t &dataClick) {
		unsigned long currentMillis = millis(); //current time
		if (currentMillis - previousMillis >= period) {
			if (!is_defined){ //START CORRECTION
				dataX = map(analogRead(x_pin), 0, 1023, 255, 0);
				if (dataX != 127) differ_x = dataX - 127;
				dataY = map(analogRead(y_pin), 0, 1023, 255, 0);
				if (dataY != 127) differ_y = dataY - 127;
#ifdef DEBUG
				Serial.print("differ_x:");
				Serial.print(differ_x);
				Serial.print(" | differ_y:");
				Serial.print(differ_y);
				Serial.println(" DEFINED!");
#endif // DEBUG
				is_defined = true;
			}
			else{
				dataX = map(analogRead(x_pin), 0, 1023, 255, 0);
				if(dataX > (0+differ_x) && dataX < (255-differ_x))
					dataX -= differ_x;
          
				dataY = map(analogRead(y_pin), 0, 1023, 255, 0);
				if(dataY > (0 + differ_y) && dataY < (255 - differ_y))
					dataY -= differ_y;		

		        if(analogRead(cl_pin) > 512) dataClick = 255;
		        else dataClick = 0;
#ifdef DEBUG
				Serial.print("sigX:");
				Serial.print(dataX);
				Serial.print(" | sigY:");
				Serial.print(dataY);
        		Serial.print(" | click:");
        		Serial.print(dataClick);
				Serial.println();
#endif // DEBUG
			}
			previousMillis = currentMillis; //remember time
		}
	}

	void on_lcd(LiquidCrystal &lcd, uint8_t x, uint8_t y, uint8_t cl){
		uint8_t pos = 0;
		if (is_left) pos = LCD_LEFT_POS;
		else pos = LCD_RIGHT_POS;
		//Y
		lcd.setCursor(pos, 1);
		if(y >= 64 && y < 128) lcd.write(byte(4));
		else if(y >= 128 && y < 192) lcd.write(byte(5));
		else if(y >= 192 && y <= 255) lcd.write(byte(6));
		else lcd.write("_");
		//X
		lcd.setCursor(pos+1, 1);
		if(x >= 64 && x < 128) lcd.write(byte(4));
		else if(x >= 128 && x < 192) lcd.write(byte(5));
		else if(x >= 192 && x <= 255) lcd.write(byte(6));
		else lcd.write("_");
		//CLICKED
		lcd.setCursor(pos+2, 1);
		if(cl >= 128) lcd.write(byte(6));
		else lcd.write("_");
	}
};
#endif // JOYSTICK
