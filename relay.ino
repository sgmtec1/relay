// Open Source
// Trabalhando com Display LCD com I2C

#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

#include <math.h>

int pinOut = 10;

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 Temp = (Temp * 9.0)/ 5.0 + 32.0; 
 return Temp;
}

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)  
}

void loop() {             
  int val;                
  double temp;            
  val=analogRead(0);      
  temp=Thermistor(val);
  lcd.clear();
  Serial.print("TEMPERATURA = ");
  Serial.print(temp);   
  Serial.println(" F");
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("TEMP "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(temp); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(" F"); //IMPRIME O TEXTO NO DISPLAY LCD
  
  if (temp >= 150){
    digitalWrite(pinOut, LOW);
    lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
    lcd.print("LUZ DESLIGADA"); //IMPRIME O TEXTO NO DISPLAY LCD
  }
  else {
    digitalWrite(pinOut, HIGH);
    lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
    lcd.print("LUZ LIGADA"); //IMPRIME O TEXTO NO DISPLAY LCD
  }
  delay(500);            
}
