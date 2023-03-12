 #include <Wire.h>
#include <LiquidCrystal_I2C.h>

/////this works jst fine

const int IN_D0 = 3;//D5; // digital input


LiquidCrystal_I2C lcd (0x27 , 2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
pinMode (IN_D0, INPUT);
bool value_D0;
value_D0 = digitalRead(IN_D0);
// lcd.begin(16,2);
//  lcd.setCursor(0,0);
//  lcd.print("welcome");
//  delay(1000);
  
  
if(value_D0==0)
{
 lcd.clear();
  //lcd.noBacklight();
  lcd.print("vehicle parked");
  delay(2000);
  lcd.clear();
}
else
{
lcd.begin(16,2);
  lcd.setCursor(0,0);
  //lcd.noBacklight();
  lcd.print("welcome");
delay(1000);


}
}

void loop() {
  // put your main code here, to run repeatedly:
  setup();

}
