#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

char strValue[21];
int index = 0;
int newTemp = 0;
int temp = 0;
int light = 0;
uint32_t color;

void setup() {
  strip.begin();
  //strip.show();
  Serial.begin(9600);
  temp = 30;
}

void loop() {

}

void serialEvent(){
  while(Serial.available()){
    char ch = Serial.read();
    delay(5);
    Serial.println(ch);

    if(ch =='c'){
      for(int i=0; i <light;i++){
        strip.setPixelColor(i, strip.Color(0,0,0));
      }
      light = -1;
    }
    //Serial.write(ch);

    if(ch == 'f'){
      strip.show();
    }

    if(index< 20 && isDigit(ch)){
      strValue[index++] = ch;
    }
    else{
      strValue[index] = 0;
      newTemp = atoi(strValue);
      //Serial.print(newTemp);

      if(newTemp <= 33 && newTemp !=0){
        strip.setPixelColor(light, strip.Color(0,150,0));
      }
      else if(newTemp <=66){
        strip.setPixelColor(light, strip.Color(150,150,50));
      }
      else if(newTemp <= 85){
        strip.setPixelColor(light, strip.Color(100,100,100));
      }
      else if(newTemp > 85){
        strip.setPixelColor(light, strip.Color(150,0,0));
      }
      else{

      }
      strValue;
      index = 0;
      temp - newTemp;
      light++;
    }
  }
}

