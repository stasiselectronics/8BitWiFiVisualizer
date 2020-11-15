// Header files to include
#include <ESP8266WiFi.h>

// GPIO Pin Definitions
// Changing these will affect the board's functionality, do so at your own risk!
#define LATCH 5 
#define CLOCK 4  
#define DATA 16   
#define SWITCH 14
#define CLEAR 12
#define OUTPUTENABLE 13


void setup() {
  Serial.begin(115200);                // begin Serial port and set the baud rate to 115200, feel free to change this if you want
  Serial.print("\n\n\n");              // helps to clear the application dialogue and the ESP8266's boot dialogue
  
  // GPIO Port Configuration
  Serial.println("Initializing Pins");
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLEAR, OUTPUT);
  pinMode(OUTPUTENABLE, OUTPUT);
  pinMode(SWITCH, INPUT);
  
  // Set initial pin conditions
  digitalWrite(CLEAR, HIGH);  // Active Low
  digitalWrite(OUTPUTENABLE, LOW);  // Active Low
  
  Serial.println("Finished Setup, Starting loop");
}

void loop() {
  ESP.wdtFeed();  // Feed watchdog timer just in case, since we are doing nothing

  // Example of how to write data to the LEDs
  //digitalWrite(LATCH, LOW);
  //shiftOut(DATA, CLOCK, MSBFIRST, led_value);
  //digitalWrite(LATCH, HIGH);
}
