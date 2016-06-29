#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
const int MaxChars = 4;
char strValue[MaxChars+1];
int index = 0;
int newTemp = 0;
int temp = 0;
int light = 0;

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
  temp = 30;
}

void loop() {
  
}

void serialEvent(){
  while(Serial.available()){
    char ch = Serial.read();
    if(ch =='c'){
      for(int i=0; i <light;i++){
        strip.setPixelColor(i, strip.Color(0,0,0));
      }
      light = -1;
    }
    Serial.write(ch);
    if(index< MaxChars && isDigit(ch)){
      strValue[index++] = ch;
    }
    else{
      strValue[index] = 0;
      newTemp = atoi(strValue);
      Serial.print(newTemp);
      if(newTemp < 50 && newTemp !=0){
        strip.setPixelColor(light, strip.Color(0,0,255)); 
      }
      else if(newTemp > 50){
        strip.setPixelColor(light, strip.Color(255,0,0));
      }
      else{
        
      }
      strip.show();
      strValue;
      index = 0;
      temp - newTemp;
      light++;
    }
  }
}

