#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <LiquidCrystal.h>
//0
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
//1
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
//2
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
//3
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
//4
uint8_t lev2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
//5
uint8_t lev3[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
//6 "("
uint8_t lev4[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
//7
uint8_t empty[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void init_symbols(LiquidCrystal &lcd) {
  lcd.createChar(0, kvadrokopter);
  lcd.createChar(1, battary);
  lcd.createChar(2, pult);
  lcd.createChar(3, connection);
  lcd.createChar(4, lev2);
  lcd.createChar(5, lev3);
  lcd.createChar(6, lev4);
  lcd.createChar(7, empty);//empty
}
#endif
