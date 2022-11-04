#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27,16,2);
#include <OneWire.h>

#define analogPin 0          
#define chargePin 13         
#define dischargePin 11        
#define resistorValue 10000.0F   

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                
float nanoFarads;

void setup(){
     lcd.init();
 lcd.backlight();
 
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
  Serial.begin(9600); 
           
}

void loop(){
    lcd.setCursor(0,0);
  lcd.print("Cap. Meter"); 
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPin) < 648){       
  }

  

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       
  Serial.print(" mS    ");         

  if (microFarads > 1){
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");  

               lcd.setCursor(0, 1);
                lcd.print("Cap=");
     lcd.print((long)microFarads);
          lcd.print("uF");  
  }

  else{
    nanoFarads = microFarads * 1000.0;     
    Serial.print((long)nanoFarads);         
    Serial.println(" nanoFarads"); 
    
    lcd.setCursor(0, 1);
     lcd.print("Cap=");
     lcd.print((long)nanoFarads);
          lcd.print("nF");    
    delay(500);
    lcd.clear();
    
    
  }

  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while(analogRead(analogPin) > 0){         
  }

  pinMode(dischargePin, INPUT);            
}