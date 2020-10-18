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

// Low Pass Filter: This software filter helps to smooth out the packets per second data to make a more pleasant
//                  light display. 

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
  Serial.println("Auto Selecting Channel");
  ap_channel = get_channel();
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
  digitalWrite(OUTPUTENABLE, LOW);                // Active Low
  
  Serial.println("Finished Setup, Starting loop");
}

void loop() {
  static unsigned long prevTime = 0;      // timer variable to use to see if enough time has passed since last display update
                                          // "static" means the compiler won't re-initialize the variable every loop
  static byte previous_value = 0;         // value used to make sure we only update the display as needed

  ESP.wdtFeed();  // Feed watchdog timer just in case, since we are doing nothing most of the time
  
  if(millis() - prevTime >= refresh_rate) // check if it is time to update the display
  {
    prevTime = millis();                  // update timer variable for next display update

    double packets_per_second = (pkts*(1000/refresh_rate)); // calculate how many packets per second have occured since last display
                                                         // 1000 is used to convert milliseconds to seconds
    
    pkts = 0;                             // reset packets counter variable for next calculation

    if(packets_per_second>max_rate){
      max_rate = packets_per_second;      // auto adjust max rate
    }
    
    byte led_value = pow(2,ceil((packets_per_second/max_rate)*8.0)) - 1;

    max_rate-= 1;                       // have max rate fall back over time
    
    if(previous_value!=led_value){
      // Display Value
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, MSBFIRST, led_value);
      digitalWrite(LATCH, HIGH);
      previous_value=led_value;
      analogWrite(OUTPUTENABLE, led_brightness[led_value-1]);      // Set LED Brightness
    }
    
    // Print to terminal, if refresh rate is too fast, you might find some errors in writing out to serial
    // Serial.print("Packet Rate: "); Serial.print(packets_per_second); Serial.println(" packets per second");
    Serial.print(packets_per_second);Serial.print(",");Serial.println(max_rate);
  }
}

int get_channel(){
  // function looks at all available networks and returns the channel that has the strongest network present
  int wifi_networks_n = 0;    // Number of wifi networks present, and used to reference details of the networks
  int max_rssi = -1000;       // RSSIs are negative, so initialize to something below any actual network strength
  int strongest_network = 0;  // Number in list of wifi networks, used to print for reference

  WiFi.mode(WIFI_STA);        // Make sure ESP8266 is in station mode
  WiFi.disconnect();          // Make sure we're not connected to any network
  wifi_networks_n = WiFi.scanNetworks();  // Get number of available networks, used to access array of wifi networks

  if(wifi_networks_n == 0){
    Serial.println("No Networks Found, that's not right, who doesn't have a WiFi network around?");
    return 0;
  }
  else{
    for (int i = 0; i < wifi_networks_n; ++i) {
      // look through wifi networks and find strongest network strength and save corresponding network channel
      if(WiFi.RSSI(i)>max_rssi){
        strongest_network = i;
        max_rssi=WiFi.RSSI(i);
      }
    }
    Serial.print("Found strongest network ");Serial.print(WiFi.SSID(strongest_network));
    Serial.print(" with RSSI of "); Serial.print(WiFi.RSSI(strongest_network));
    Serial.print(" on channel ");Serial.println(WiFi.channel(strongest_network));
    return(WiFi.channel(strongest_network));
  }
}
