	
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
String apiKey = "14K8UL2QEK8BTHN6"; // Enter your Write API key from ThingSpeak
const char *ssid = "Alexahome";     // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";
const char* server = "api.thingspeak.com";
 
const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
// WiFiClient client;
 
void setup() 
{
   Serial.begin(115200);                                    //Serial comms for debugging
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);              //OLED display start
   display.display();                                     //show buffer
   display.clearDisplay();                                //clear buffer
   display.setTextSize(2);                                //Set text size to 1 (1-6)
   display.setTextColor(WHITE);                           //Set text color to WHITE (no choice lol)
   display.setCursor(0,0);                                //cursor to upper left corner
   display.println("[db] METER");               //write title
   display.display();                                     //show title
   delay(3000);                                           //wait 2 seconds
   
}
 
//--------------------------------------------------------------------------------------------
 //                                         MAIN LOOP
 //--------------------------------------------------------------------------------------------
  
void loop() 
{
   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);                             //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
   
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   float db = map(peakToPeak,1,270,1.5,100);             //calibrate for deciBels
   display.clearDisplay();
   display.setCursor(3,0);                                //cursor to upper left
   display.setTextSize(1);                             //set text size to 2
   display.print(db);                                     //write calibrated deciBels
   display.print(" dB ch 1");     
   display.display();
   display.clearDisplay(); 
   delay();
   
    for(int x =3;x<125;x=x+4){                            //draw scale
   display.drawLine(x, 32, x, 27, WHITE);    }
   display.drawRoundRect(0, 32, 127, 10, 6, WHITE);       //draw outline of bar graph
   int r = map(db,2,120,1,120);                           //set bar graph for width of screen
   display.fillRoundRect(1, 33, r, 8, 6, WHITE);     //draw bar graph with a width of r
   display.display();                                     //show all that we just wrote & drew
   display.clearDisplay();                                //clear the display
 
  
  // }
  //   client.stop();
  delay(0);

{   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(1);                             //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
   
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   float db = map(peakToPeak,1,270,1.5,100);             //calibrate for deciBels
   display.setTextColor(WHITE); 
   display.setCursor(3,10);                                //cursor to upper left
   display.setTextSize(1);                             //set text size to 2
   display.print(db);                                     //write calibrated deciBels
   display.print(" dB ch 2");
   display.display();
   display.clearDisplay(); 

    for(int x =3;x<125;x=x+4){                            //draw scale
   display.drawLine(x, 32, x, 27, WHITE);    }
   display.drawRoundRect(0, 32, 127, 10, 6, WHITE);       //draw outline of bar graph
   int r = map(db,2,120,1,120);                           //set bar graph for width of screen
   display.fillRoundRect(1, 33, r, 8, 6, WHITE);     //draw bar graph with a width of r
   display.display();                                     //show all that we just wrote & drew
   display.clearDisplay();                                //clear the display
 
  
  // }
  //   client.stop();
  delay(0); 
  }


}























