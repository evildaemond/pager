// https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
// https://educ8s.tv/arduino-20x4-character-lcd/
// https://www.youtube.com/watch?v=COssWn4Pcm4
// https://robojax.com/learn/arduino/?vid=robojax_ESP32_LCD
// Custom Charicters and charicter maker: https://lastminuteengineers.com/i2c-lcd-arduino-tutorial/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD I2C address

// Replace with your network credentials
const char* ssid     = "insecure";
const char* password = "J8$c7ggbJEjbdfBG";

byte stupid2[8] ={
0b11110,
0b00001,
0b00010,
0b11100,
0b11111,
0b11111,
0b00000,
0b00000
};

byte letterD[8] ={
0b11110,
0b10001,
0b10001,
0b10001,
0b11110,
0b00000,
0b00000,
0b00000
};

byte thiccT[8] ={
0b11111,
0b11111,
0b01110,
0b01110,
0b01110,
0b00000,
0b00000,
0b00000,
};

byte reception[8] = {
0b11111,
0b10001,
0b10001,
0b10001,
0b11111,
0b00000,
0b00000,
0b00000
};

byte lettern[8] ={
0b11001,
0b11101,
0b10111,
0b10011,
0b10001,
0b00000,
0b00000,
0b00000
};


void setup() {
  lcd.begin();
  // create a new characters
  lcd.createChar(0, stupid2);
  lcd.createChar(1, letterD);
  lcd.createChar(5, thiccT);
  lcd.createChar(3, lettern);
  lcd.createChar(4, reception);
  // SetCursor allows you to change where the cursor starts for the next line, or else it will loop
  // It works by column,row
  // There are 20 columns and 4 rows
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("Connecting to SSID");
    lcd.setCursor(0,1);
    lcd.print(ssid);
  }
  lcd.setCursor(0,2);
  lcd.print("Connected to ");
  lcd.setCursor(0,3);
  lcd.print(ssid);
  delay(2000);
  lcd.clear();
  lcd.print("Intialising...");
  delay(5000);
}


void loop() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(0);
  lcd.setCursor(4,0);
  lcd.write(1);
  lcd.setCursor(13,0);
  lcd.write(5);
  lcd.write(3);
  lcd.setCursor(16,0);
  lcd.write(4);
  lcd.write(4);
  lcd.write(4);  
  lcd.write(4);

  HTTPClient http;
 
  http.begin("http://evil.id.au/grand.txt"); 
  int httpCode = http.GET();
 
  if (httpCode > 0) 
  {
      String payload = http.getString();
      lcd.setCursor(0,1);
      lcd.print(payload);
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("Error on HTTP request");
  }
    
  http.end(); //Free the resources
  delay(600000);
  
  //lcd.setCursor(3,1);
  //lcd.print("Grand Central");
  //lcd.setCursor(2,2);
  //lcd.print("Hack The Planet");

}
