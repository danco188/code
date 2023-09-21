//YWROBOT 
//Compatible with the Arduino IDE 1.0 
//Library version:1.1 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C  lcd(0x3F,16,2);   // set the LCD address to 0x27 for a 16 chars and 2 line display 
int led= 4;
int senzor = A1;
int tlacitko = 3;
int stav = 1;
const int  AUTOMAT = 1;
const int  SVITI = 2;
const int  ZHASNUTO = 3;
void PrintDisplay (int radek, int sloupec, bool clear, String text){
  if (clear){lcd.clear();}
  lcd.setCursor(sloupec,radek);
  lcd.print (text);
}

 

void setup() {

pinMode(led, OUTPUT);
pinMode(tlacitko, INPUT);
pinMode(A1,INPUT);  
lcd.init();
lcd.backlight();

 

}

 

void loop() {

  /*PrintDisplay(1,0,true,"text");
  delay (1000);*/
  if(digitalRead(tlacitko)==HIGH){
    lcd.clear ();
    if(stav==AUTOMAT){
      stav=SVITI;
    }
    else if (stav==SVITI){
      stav=ZHASNUTO;
    }
    else if(stav==ZHASNUTO){
      stav=AUTOMAT;
    }
    delay(100);
    /*if(stav==4){
      stav=1;
    }
    delay(100);*/
  }
  if (stav==ZHASNUTO){
    digitalWrite(led,LOW);
    PrintDisplay(1,0,false,"nesviti");   
  }else if(stav==SVITI){
    digitalWrite(led,HIGH);
    PrintDisplay(1,1,false,"sviti");
  }else if(stav==AUTOMAT){

    float svetlo = analogRead(A1);
    lcd.setCursor(10,1);
    lcd.print(svetlo);

    if(svetlo>60){
      int raw_light = analogRead(A1);
      int svetlo = map(raw_light, 0, 1023, 0,100);
      digitalWrite(led, LOW);
      PrintDisplay(0,0,false,"automat");
    }else if (svetlo<60) {
      digitalWrite(led, HIGH);
      PrintDisplay(0,0,false,"automat");
    }
  }
}
