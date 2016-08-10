#include <Adafruit_NeoPixel.h>


#define PIN 6
#if defined(ARDUINO_ARCH_SAMD) || defined(__SAM3X8E__)
  // use pin 18 with Due, pin 1 with Zero or M0 Pro
  #define lcd Serial1
#else
  #include <SoftwareSerial.h>
  // Create a software serial port!
  SoftwareSerial lcd = SoftwareSerial(0,2);
#endif

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
  lcd.begin(9600);

//sets size of display
  lcd.write(0xFE);
  lcd.write(0xD1);
  lcd.write(16);
  lcd.write(2);
  delay(10);

//sets contrast
  lcd.write(0xFE);
  lcd.write(0x50);
  lcd.write(200);
  delay(10);

//sets brightness
  lcd.write(0xFE);
  lcd.write(0x99);
  lcd.write(255);
  delay(10);

//turns off cursors
  lcd.write(0xFE);
  lcd.write(0x4B);
  lcd.write(0xFE);
  lcd.write(0x54);

  //strip.show();
  Serial.begin(9600);
  //strip.setPixelColor(0, strip.Color(255,255,255));
}

void loop() {

}

void tempTest(){
      lcd.write(0xFE);
      lcd.write(0x58);
      delay(10);

      lcd.write(0xFE);
      lcd.write(0x48);
      delay(10);

      lcd.println("Temperatures for");
      lcd.print("Rack 16 Systems");

      if(newColor <= 33 && newColor !=0){
        strip.setPixelColor(light, strip.Color(0,150,0));
      }
      else if(newColor <=66){
        strip.setPixelColor(light, strip.Color(150,150,50));
      }
      else if(newColor <= 85){
        strip.setPixelColor(light, strip.Color(100,100,100));
      }
      else if(newColor> 85){
        strip.setPixelColor(light, strip.Color(150,0,0));
      }
      else{

      }
      strValue;
      index = 0;
      light++;
}

void power(){
      lcd.write(0xFE);
      lcd.write(0x58);
      delay(10);

      lcd.write(0xFE);
      lcd.write(0x48);
      delay(10);

      lcd.println("Power Usage");
      lcd.print("low-high");

      Serial.print(light);
      if(newColor< 0){
        strip.setPixelColor(light, strip.Color(lastColor+(newColor*20),0,150));
        lastColor=lastColor+(newColor*20);
      }
      else{
        strip.setPixelColor(light, strip.Color(lastColor+(newColor*20),0,150));
        lastColor=lastColor+(newColor*20);
      }
      strValue;
      index = 0;
      light++;
   }

void totalJobs(){
      lcd.write(0xFE);
      lcd.write(0x58);
      delay(10);

      lcd.write(0xFE);
      lcd.write(0x48);
      delay(10);

      lcd.write(0xFE);
      lcd.write(0x51);
      delay(10);

      lcd.println("Total Jobs");
      lcd.println("Pending, purple");
      lcd.println("Running, blue");
      lcd.println("Completed, white");

      lcd.write(0xFE);
      lcd.write(0x52);
      delay(10);

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
