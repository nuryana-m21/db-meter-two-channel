#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
const int sampleWindow = 50;   // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(115200);                                 // Serial comms for debugging
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);           // OLED display start
   display.clearDisplay();                              // Clear buffer
   display.setTextSize(2);                              // Set text size to 2
   display.setTextColor(WHITE);                         // Set text color to WHITE
   display.setCursor(0, 0);                             // Cursor to upper left corner
   display.println("[dB] METER");                       // Write title
   display.display();                                   // Show title
   delay(3000);                                         // Wait 3 seconds
   display.clearDisplay();                              // Clear the display
}
 
void loop() 
{
   // Read and display dB for Channel 1 (A0)
   float db1 = readDb(0);
   display.setCursor(3, 0);                              // Top of the screen
   display.setTextSize(1);                               // Text size 1
   display.print("CH1: ");                               // Label for channel 1
   display.print(db1);                                   // Write calibrated deciBels
   display.print(" dB");                                 // Units

   // Draw bar graph for Channel 1
   display.drawRoundRect(0, 15, 127, 10, 3, WHITE);      // Outline for bar graph
   int barWidth1 = map(db1, 2, 120, 1, 120);             // Map dB to graph width
   display.fillRoundRect(1, 16, barWidth1, 8, 3, WHITE); // Fill bar graph

   // Read and display dB for Channel 2 (A1)
   float db2 = readDb(1);
   display.setCursor(3, 32);                             // Lower part of the screen
   display.print("CH2: ");                               // Label for channel 2
   display.print(db2);                                   // Write calibrated deciBels
   display.print(" dB");                                 // Units

   // Draw bar graph for Channel 2
   display.drawRoundRect(0, 47, 127, 10, 3, WHITE);      // Outline for bar graph
   int barWidth2 = map(db2, 2, 120, 1, 120);             // Map dB to graph width
   display.fillRoundRect(1, 48, barWidth2, 8, 3, WHITE); // Fill bar graph

   display.display();                                    // Show updated display
   delay(500);                                           // Add delay for stability
   display.clearDisplay();                               // Clear the display
}

// Function to read and calculate dB from analog input
float readDb(int pin)
{
   unsigned long startMillis = millis();                 // Start of sample window
   unsigned int signalMax = 0;                           // Minimum value
   unsigned int signalMin = 1024;                        // Maximum value

   // Collect data for the sample window
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(pin);                          // Read analog input
      if (sample < 1024)                                 // Toss out spurious readings
      {
         if (sample > signalMax)
            signalMax = sample;                          // Save max levels
         else if (sample < signalMin)
            signalMin = sample;                          // Save min levels
      }
   }

   float peakToPeak = signalMax - signalMin;             // Max - min = peak-peak amplitude
   float db = map(peakToPeak, 1, 270, 1.5, 100);         // Calibrate for deciBels
   return db;
}
