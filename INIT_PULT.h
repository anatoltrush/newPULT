#ifndef INIT_PULT_H
#define INIT_PULT_H

#include <LiquidCrystal.h>
#include "symbols.h"

void lcd_initialization(LiquidCrystal &lcd) {
  init_symbols(lcd);
  
  lcd.setCursor(1, 0);
  lcd.print("REMOTE CONTROL");
  lcd.setCursor(1, 1);
  lcd.print("INITIALIZATION");
  delay(2000);
  for (byte str = 0; str < 2; str++) {
    for (byte stl = 0; stl < 16; stl++) {
      lcd.setCursor(stl, str);
      lcd.print("X");
      delay(60);
    }
  }
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(byte(0));

  lcd.setCursor(1, 0);
  lcd.write(byte(1));

  lcd.setCursor(0, 1);
  lcd.write(byte(2));

  lcd.setCursor(1, 1);
  lcd.write(byte(1));

  lcd.setCursor(11, 0);
  lcd.write(byte(3));

//---------------------
  lcd.setCursor(10, 1);
  lcd.write("Pw");

  lcd.setCursor(12, 1);
  lcd.write("_");

  lcd.setCursor(13, 1);
  lcd.write("_");

  lcd.setCursor(14, 1);
  lcd.write("_");

  lcd.setCursor(15, 01);
  lcd.write("_");
}
#endif // INIT_PULT
