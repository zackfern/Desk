#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN       6
#define NUMPIXELS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String inData;

void setup() {
  Serial.begin(9600);
  
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(8); // 32
  
  startupScreen();
  
  pixels.show();
}

void startupScreen() {
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  
  pixels.setPixelColor(1, pixels.Color(150, 0, 0));
  pixels.setPixelColor(2, pixels.Color(150, 0, 0));
  
  pixels.setPixelColor(3, pixels.Color(0, 150, 0));
  pixels.setPixelColor(4, pixels.Color(0, 150, 0));
  
  pixels.setPixelColor(5, pixels.Color(0, 0, 150));
  pixels.setPixelColor(6, pixels.Color(0, 0, 150));

  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
}

void loop() {
  while(Serial.available() > 0) {
    String Cmd = Serial.readStringUntil(';');
    int    Pos = Serial.readStringUntil(';').toInt();
    int    Red = Serial.readStringUntil(';').toInt();
    int  Green = Serial.readStringUntil(';').toInt();
    int   Blue = Serial.readStringUntil(';').toInt();
    
    Serial.print("Cmd = ");
    Serial.println(Cmd);
    
    Serial.print("Pos = ");
    Serial.println(Pos);
    
    Serial.print("Red = ");
    Serial.println(Red);
    
    Serial.print("Green = ");
    Serial.println(Green);
    
    Serial.print("Blue = ");
    Serial.println(Blue);
    
    processCommand(Cmd, Pos, Red, Green, Blue);
  }
}

void processCommand(String cmd, int pos, int red, int green, int blue) {
  if(cmd == "BRI") {
    pixels.setBrightness(pos);
  }
  
  if(cmd == "SET") {
    pixels.setPixelColor(pos, pixels.Color(red, green, blue));
  }
  
  if(cmd == "ALL") {
    for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      delay(100);
    }
  }
  
  if(cmd == "START") {
    startupScreen();
  }
  
  pixels.show();
}
