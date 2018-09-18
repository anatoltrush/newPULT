#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <LiquidCrystal.h>
//1
uint8_t kvadrokopter[8] = {
  0b00000,
  0b11011,
  0b11011,
  0b00100,
  0b00100,
  0b11011,
  0b11011,
  0b00000
};
//2
uint8_t battary[8] = {
  0b00010,
  0b00100,
  0b01000,
  0b11111,
  0b00010,
  0b00100,
  0b01000,
  0b00000
};
//3
uint8_t pult[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b10001,
  0b11011,
  0b10001,
  0b11111
};
//4
uint8_t connection[8] = {
  0b11111,
  0b10000,
  0b11110,
  0b10000,
  0b11100,
  0b10000,
  0b11000,
  0b10000
};
//5
uint8_t up[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b00000
};
//6
uint8_t down[8] = {
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
//7 "("
uint8_t left[8] = {
  0b00000,
  0b00100,
  0b01111,
  0b11111,
  0b01111,
  0b00100,
  0b00000,
  0b00000
};
//8 ")"
uint8_t right[8] = {
  0b00000,
  0b00100,
  0b11110,
  0b11111,
  0b11110,
  0b00100,
  0b00000,
  0b00000
};
void init_symbols(LiquidCrystal &lcd) {
  lcd.createChar(0, kvadrokopter);
  lcd.createChar(1, battary);
  lcd.createChar(2, pult);
  lcd.createChar(3, connection);
  lcd.createChar(4, up);
  lcd.createChar(5, down);
  lcd.createChar(6, left);
  lcd.createChar(7, right);
}
#endif
