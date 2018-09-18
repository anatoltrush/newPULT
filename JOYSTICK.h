#ifndef JOYSTICK_H
#define JOYSTICK_H

#define DEBUG

class Joystick {
	bool is_defined;
	uint8_t differ_x;
	uint8_t differ_y;
	uint8_t x_pin;
	uint8_t y_pin;
  uint8_t cl_pin;
	long period; //period
	unsigned long previousMillis; //last read
public:
	Joystick(uint8_t x_p, uint8_t y_p, uint8_t cl_p, long per):
	is_defined(false),
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
};
#endif // JOYSTICK
