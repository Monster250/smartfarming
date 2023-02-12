    //https://api.thingspeak.com/update?api_key=3E29S2HHNWTSMAOA&field1=26
 #include <DHT.h>
#include <SoftwareSerial.h>
String apiKey = "6VL4PY1SJG6OFO5E";
SoftwareSerial ser(A0, A1); //WIFI MODULE  TX CONNECT AURDINO 2 PIN AND RX CONNECTED AURDINO 3 RX, TX
 
#define DHTTYPE DHT11   // DHT 11 
#define DHTPIN A3     // what pin we're connected to
DHT dht(DHTPIN, DHTTYPE);
 
#define RELAY A5
int sensor =A2;
  #include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
int humi,temp;
void setup(){
  ser.begin(115200);
    Serial.begin(9600); 
    dht.begin();
    pinMode(RELAY, OUTPUT);
  
    pinMode (sensor, INPUT);
 
   digitalWrite(RELAY,LOW);
    lcd.begin(16,2);
  lcd.print("SMART AGRICULTURE");
  lcd.setCursor(0,1);
  lcd.print("SYSTEM IOT"); 
  delay(2000);
  lcd.clear();
    unsigned char check_connection=0;
    unsigned char times_check=0;
    Serial.println("Connecting to Wifi");
  while(check_connection==0)
  {
   Serial.print("..");
   ser.print("AT+CWJAP=\"test1234\",\"TEST1234\"\r\n");
   ser.setTimeout(5000);
   if(ser.find("WIFI CONNECTED\r\n")==1 )
   {
   Serial.println("WIFI CONNECTED");
   break;
   }
 
    
  }
  delay(5000);
  
}
void loop()
{
 int statusSensor = digitalRead(sensor);
    Serial.println(statusSensor );
   lcd.setCursor(0,0);
            lcd.print("SOIL:");
  humi= dht.readHumidity();
  temp= dht.readTemperature();
  lcd.setCursor(0,1);
    lcd.print("T:");
      lcd.setCursor(2,1);
    lcd.print(temp);
     lcd.setCursor(8,1);
    lcd.print("H:");
    lcd.setCursor(12,1);
    lcd.print(humi);
  Serial.print("H:");
  Serial.print(humi);
  Serial.println("%");
  Serial.print("T:");
  Serial.print(temp);
  Serial.println("C");
   if (statusSensor ==HIGH) {
           lcd.setCursor(6,0);
    lcd.print("DRY     ");
           digitalWrite(RELAY,HIGH);       
            
                 
           
    }
     else if(statusSensor==LOW) {
          lcd.setCursor(6,0);
            lcd.print("WET      ");
           digitalWrite(RELAY,LOW);      // If just LEDON turn on Pin 13
            
            
                 
           
    }
       
      
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  ser.println(cmd);
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(temp);
  getStr +="&field2=";
  getStr += String(humi);
   getStr +="&field3=";
  getStr += String(statusSensor);
  getStr += "\r\n\r\n\r\n";
 
  // thingspeak needs 15 sec delay between updates
 delay(15000); 
 
}
