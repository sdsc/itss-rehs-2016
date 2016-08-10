#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
const int MaxChars = 20;
char strValue[MaxChars+1];
int index = 0;
int light = 0;
int color = 0;
double jobs = 0;
int newColor = 0;
int numLights = 0;
bool first = true;

void setup() {
  strip.begin();
  //strip.show();
  Serial.begin(9600);
  //strip.setPixelColor(0, strip.Color(255,255,255));

}

void loop() {

}

void serialEvent(){
  while(Serial.available()){
    char ch = Serial.read();
    delay(5);
    if(ch =='c'){
      for(int i=0; i <light;i++){
        strip.setPixelColor(i, strip.Color(0,0,0));
      }
      light = -1;
      color = -1;
      jobs = 0;
      first = true;
    }

    //Serial.write(ch);
    if(index< MaxChars && isDigit(ch)){
      strValue[index++] = ch;
    }
    else{
      strValue[index] = 0;
      newColor = atoi(strValue);
      //Serial.println(newColor);
      if(first){
            jobs = newColor*1.0;
            //Serial.print(jobs);
            first = false;
      }
      else{
        if(newColor == 0){
         numLights = 0;
         //Serial.println(numLights);
        }
        else{
          numLights = (newColor/jobs)*144;
          Serial.println(numLights);
        }
      }
      //Serial.print(first);

      for(int i = 0; i<numLights; i++){
        if(color == 3){
          strip.setPixelColor(light, strip.Color(150,150,150));
          while(light<144){
            strip.setPixelColor(light, strip.Color(150,150,150));
            light++;
        }
        }
        else if(color == 2){
          strip.setPixelColor(light, strip.Color(0,0,150));
        }
        else if(color == 1){
          strip.setPixelColor(light, strip.Color(150,0,150));
        }

        light++;
      }
      color++;
      strip.show();
      strValue;
      index = 0;

    }
  }
}
