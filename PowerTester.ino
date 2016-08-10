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
  Serial.begin(9600);
}

void loop() {

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
    if(ch == 'f'){
        strip.show();
        dataSet++;
        light = 0;
     }
    Serial.print(light);
    if(index< 20 && isDigit(ch)){
      strValue[index++] = ch;
    }
    else{
      strValue[index] = 0;
      newColor = atoi(strValue);
    }
      strip.setPixelColor(light, strip.Color(lastColor+newColor,0,150));
      lastColor=lastColor+newColor;
    }
    strValue;
    index = 0;
    light++;

}
