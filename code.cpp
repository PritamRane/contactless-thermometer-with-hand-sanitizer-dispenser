// coded in arduino r3 //tinkercad

#include <LiquidCrystal.h>
#include<Servo.h>
Servo myservo; 
const int trigpin=10;
const int echopin=9;
long duration,cm;

    
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define pinTemp A0


void setup() {
  Serial.begin( 9600 );
  pinMode( pinTemp,INPUT );
  
  lcd.begin(16, 2);
  lcd.print("Temperature:");
  
  myservo.attach(13);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin,INPUT);
  myservo.write(0);
}

void loop() {
  //getting the voltage reading from the temperature sensor
  // converting that reading to voltage
  //converting from 10 mv per degree wit 500 mV offset
  //This formula converts the number 0-1023 from the ADC into 0-5000mV (= 5V)
  float temp = ((analogRead(pinTemp) * (5.0/1024))-0.5 )*100;
  
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(10); 
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration=pulseIn(echopin,HIGH);
  cm=duration*0.034/2;
  Serial.println(cm);
  if(cm<30){
   	myservo.write(90); 
   	delay(100); 
   	myservo.write(180); 
   	delay(1000);
    myservo.write(0); 
   	delay(1000);
    
    lcd.print( temp );
  	Serial.println( temp );
  	delay( 5000 );
  }

}
