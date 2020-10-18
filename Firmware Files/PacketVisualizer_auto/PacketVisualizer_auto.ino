// Chandler McCowan
// Network Traffic Indicator using ESP8266 and 8 LEDs
// Advanced Firmware Version
// This firmware is intended for the Stasis Electronics 8 Bit WiFi Visualizer board

// Use this firmware if you want more advanced features such as:
//  - Auto scan available networks to select channel with strongest network
//  - Auto range the packets per second to automatically configure the max rate
//  - Change LED brightness to match packet rate intensity
//  - Low Pass Filter for smoother LED changes
//  - Change AP Channel with user button

// AP Channel: This is the network channel that the visualizer listens to, it only looks at one channel at a time.
//             This firmware will automatically look for the channel with the strongest wifi network

  int ap_channel = 1; // This will be changed automatically on setup
  
// Max Rate: This is the maximum rate of packets per seconds that will be displayed, and will then be divided by 8 to determine
//           This firmware will automatically adjust this value as it runs

  double max_rate = 0; // packets per second // This will be changed automatically as the device runs

// Refresh Rate: This is how often the display is updated, and is used in calculating the packets per second.

  int refresh_rate = 100; // ms // Feel free to change!

// LED Brightness: You can use the PWM functionality on the Output Enable pin to set a brightness for the LEDs.
//                 Use a value between 0 and 1023, where 1023 is "off", and 950 is "dim" and 0 is fully "on"
//                 This firmware allows you to specify a brightness for every displayed value, growing in brightness as
//                 packet rate intensifies. Array begins with value 1, and goes to value 8

  int led_brightness[8] = {1020, 1010, 1000, 950, 900, 500, 300, 0};

// Header files to include
#include <ESP8266WiFi.h>
#include <EEPROM.h>

// GPIO Pin Definitions
// Changing these will affect the board's functionality, do so at your own risk!
#define LATCH 5 
#define CLOCK 4  
#define DATA 16   
#define SWITCH 14
#define CLEAR 12
#define OUTPUTENABLE 13

// variable that is incremented everytime a packet is sniffed
unsigned volatile long pkts = 0;

// Call Back function to capture packets and increment variable
void counter() {
  pkts++;
}


void setup() {
  Serial.begin(115200);                // begin Serial port and set the baud rate to 115200, feel free to change this if you want
  Serial.print("\n\n\n");              // helps to clear the application dialogue and the ESP8266's boot dialogue
  if(ap_channel<1||ap_channel>14){
    ap_channel=1;
    Serial.println("AP Channel out of bounds, set ap_channel to something between 1 and 14");
  }
  
  // Networking Setup, sets ESP8266 into Promiscuous mode and adds the packet counter function to the call back
  Serial.print("Initializing Network Settings on Channel ");Serial.println(ap_channel);
  wifi_set_opmode(STATION_MODE);                                // Promiscuous works only with station mode
  wifi_set_channel(ap_channel);                                 // Set which channel we are listening to
  wifi_promiscuous_enable(0);                                   // make sure promiscuous mode is disabled so we can add our call back function
  wifi_set_promiscuous_rx_cb((wifi_promiscuous_cb_t)counter);   // Set up promiscuous callback. Typecasted to match expected pointer type
  wifi_promiscuous_enable(1);                                   // enable promisuous mode with our new call back function
  Serial.println("Network Settings Configured");
  
  // GPIO Port Configuration
  Serial.println("Initializing Pins");
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLEAR, OUTPUT);
  pinMode(OUTPUTENABLE, OUTPUT);
  pinMode(SWITCH, INPUT);               // Not used in this firmware, but feel free to add your own button functionality
  
  // Set initial pin conditions
  digitalWrite(CLEAR, HIGH);                      // Active Low
  analogWrite(OUTPUTENABLE, led_brightness);      // Set LED Brightness
  
  Serial.println("Finished Setup, Starting loop");
}

void loop() {
  static unsigned long prevTime = 0;      // timer variable to use to see if enough time has passed since last display update
                                          // "static" means the compiler won't re-initialize the variable every loop
  static byte previous_value = 0;         // value used to make sure we only update the display as needed

  ESP.wdtFeed();  // Feed watchdog timer just in case, since we are doing nothing
  
  if(millis() - prevTime >= refresh_rate) // check if it is time to update the display
  {
    prevTime = millis();                  // update timer variable for next display update

    double packets_per_second = (pkts*(1000/refresh_rate)); // calculate how many packets per second have occured since last display
                                                         // 1000 is used to convert milliseconds to seconds
    
    pkts = 0;                             // reset packets counter variable for next calculation
    
    byte led_value = pow(2,ceil((packets_per_second/max_rate)*8.0)) - 1;
    
    if(previous_value!=led_value){
      // Display Value
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, MSBFIRST, led_value);
      digitalWrite(LATCH, HIGH);
      previous_value=led_value;
    }
    
    // Print to terminal, if refresh rate is too fast, you might find some errors in writing out to serial
    // Serial.print("Packet Rate: "); Serial.print(packets_per_second); Serial.println(" packets per second");
  }
}
