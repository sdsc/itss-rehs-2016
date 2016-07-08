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

      if(newTemp <= 45 && newTemp !=0){
        strip.setPixelColor(light, strip.Color(0,0,255));
      }
      else if(newTemp <=85){
        strip.setPixelColor(light, strip.Color(100,100,100));
      }
      else if(newTemp > 85){
        strip.setPixelColor(light, strip.Color(255,0,0));
      }
//      else if(newTemp <= 33){
//        strip.setPixelColor(light, strip.Color(13,13,255));
//      }
//      else if(newTemp <= 36){
//        strip.setPixelColor(light, strip.Color(26,26,255));
//      }
//      else if(newTemp <= 39){
//        strip.setPixelColor(light, strip.Color(39,39,255));
//      }
//      else if(newTemp <= 42){
//        strip.setPixelColor(light, strip.Color(52,52,255));
//      }
//      else if(newTemp <= 45){
//        strip.setPixelColor(light, strip.Color(65,65,255));
//      }
//      else if(newTemp <= 48){
//        strip.setPixelColor(light, strip.Color(78,78,255));
//      }
//      else if(newTemp <= 51){
//        strip.setPixelColor(light, strip.Color(91,91,255));
//      }
//      else if(newTemp <= 54){
//        strip.setPixelColor(light, strip.Color(104,104,255));
//      }
//      else if(newTemp <= 57){
//        strip.setPixelColor(light, strip.Color(117,117,255));
//      }
//      else if(newTemp <= 60){
//        strip.setPixelColor(light, strip.Color(130,130,255));
//      }
//      else if(newTemp <= 63){
//        strip.setPixelColor(light, strip.Color(143,143,255));
//      }
//      else if(newTemp <= 66){
//        strip.setPixelColor(light, strip.Color(156,156,255));
//      }
//      else if(newTemp <= 69){
//        strip.setPixelColor(light, strip.Color(169,169,255));
//      }
//      else if(newTemp <= 72){
//        strip.setPixelColor(light, strip.Color(182,182,255));
//      }
//      else if(newTemp <= 75){
//        strip.setPixelColor(light, strip.Color(200,200,255));
//      }
//      else if(newTemp <= 80){
//        strip.setPixelColor(light, strip.Color(213,213,255));
//      }
//      else if(newTemp <= 85){
//        strip.setPixelColor(light, strip.Color(226,226,255));
//      }
//      else if(newTemp <= 90){
//        strip.setPixelColor(light, strip.Color(239,239,255));
//      }
//      else if(newTemp > 90){
//        strip.setPixelColor(light, strip.Color(255,255,255));
//      }
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
