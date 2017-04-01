#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


#define trigIN 13
#define echoIN 12
#define trigOUT 8
#define echoOUT 5

long durationIN,durationOUT, distanceIN,distanceOUT,total = 100;

void setup()
{
  Serial.begin (9600);
  pinMode(trigIN, OUTPUT);
  pinMode(echoIN, INPUT);
  pinMode(trigOUT, OUTPUT);
  pinMode(echoOUT, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  displayO(100);

}
long readOUT()
{
  digitalWrite(trigOUT, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigOUT, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigOUT, LOW);
   
  durationOUT = pulseIn(echoOUT, HIGH);
  distanceOUT = (durationOUT/2) / 29.1;

  Serial.print("Distanta OUT: ");
  Serial.println(distanceOUT);
  return distanceOUT;
}

long readIN()
{
  digitalWrite(trigIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigIN, LOW);
   
  durationIN = pulseIn(echoIN, HIGH);
  distanceIN = (durationIN/2) / 29.1;

  Serial.print("Distanta IN: ");
  Serial.println(distanceIN);
  return distanceIN;
}

void displayO(int x)
{
display.clearDisplay(); 
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);

display.println("     Locuri libere");
display.print("         ");
display.setTextSize(3);
display.println(x);
display.display();
}

void loop() 
{
  int x;
  long distIN,distOUT;

  distIN = readIN();
  distOUT = readOUT();
  x = distIN - distOUT;
 
  if(x < -20 && total >=1)
  {
    displayO(--total);
    delay(3000);
  }
  else
  if(x > 20 && total<=99)
  {
    displayO(++total);
    delay(3000);
  }
  else
  {
    display.clearDisplay(); 
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Parcare indisponibila");
  }
}
