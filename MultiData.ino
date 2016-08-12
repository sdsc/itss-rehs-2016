#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
const int MaxChars = 20;
char strValue[MaxChars+1];
int index = 0;
double newColor = 0;
int numLights = 0;
int light = 0;
int color = 0;
int lastColor = 150;

int dataSet = 0;
int totalJobCount = 0;

double jobs=0;
char ch;
bool first = true;


void setup() {
  strip.begin();
  //strip.show();
  Serial.begin(9600);
  //strip.setPixelColor(0, strip.Color(255,255,255));
}

void loop() {

}

void tempTest(){

      //lcd.println("Temperatures for");
      //lcd.print("Rack 16 Systems");

      if(newColor <= 40 && newColor !=0){
        strip.setPixelColor(light, strip.Color(0,0,150));
      }
      else if(newColor <=65){
        strip.setPixelColor(light, strip.Color(0,150,100));
      }
      else if(newColor <= 80){
        strip.setPixelColor(light, strip.Color(100,100,100));
      }
      else if(newColor> 80){
        strip.setPixelColor(light, strip.Color(150,100,50));
      }
      else{

      }
      strValue;
      index = 0;
      light++;
}

void power(){
      //lcd.println("Power Usage");
      //lcd.print("low-high");

      Serial.print(light);
      strip.setPixelColor(light, strip.Color(lastColor+newColor,0,150));
      lastColor=lastColor+newColor;

      strValue;
      index = 0;
      light++;
   }

void totalJobs(){

      //lcd.println("Total Jobs");
      //lcd.println("Pending, purple");
      //lcd.println("Running, blue");
      //lcd.println("Completed, white");

      Serial.print(light);
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
          //Serial.println(numLights);
        }

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
      }
      //Serial.print(first);
      color++;
      strValue;
      index = 0;
      totalJobCount++;
      if(totalJobCount==4){
        strip.show();
        totalJobCount = 0;
        first=true;
        dataSet=0;
        color=0;
        light=0;
      }
}

void serialEvent(){
  while(Serial.available()){
    ch = Serial.read();
    delay(5);
    if(ch =='c'){
      //for(int i=0; i <light;i++){
        //strip.setPixelColor(i, strip.Color(0,0,0));
      //}
      first = true;
      light = -1;
      color = -1;
      dataSet = -1;
    }
    if(index< 20 && isDigit(ch)){
      strValue[index++] = ch;
    }
    else{
      strValue[index] = 0;
      newColor = atoi(strValue);
      if(dataSet==0){
        tempTest();
        Serial.print("tempTest");
        Serial.print(light);
      }
      if(ch == 'f'){
        strip.show();
        dataSet++;
        light = 0;
      }
      else if(dataSet==1){
        power();
        Serial.print("power");
        Serial.print(light);
      }
      else if(dataSet==2){
        totalJobs();
        Serial.print("total jobs");
        Serial.print(light);
      }
    }
  }
}
