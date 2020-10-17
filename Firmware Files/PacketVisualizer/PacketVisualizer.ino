// Chandler McCowan
// Network Traffic Indicator using ESP8266 and 8 LEDs

// TODOs
// clean up styling of code
// add ability to switch channels using the button

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <EEPROM.h>

// Shift Register GPIO Pin Definitions
#define LATCH 5 
#define CLOCK 4  
#define DATA 16   
#define SWITCH 14
#define CLEAR 12
#define OUTPUTENABLE 13

#define disable 0
#define enable  1

#define CHANNEL_ADDR 60

// Mathematic variables to count time and packet change
unsigned long prevTime    = 0;
unsigned long curTime     = 0;
unsigned long pkts        = 0;
unsigned long oldpkts     = 0;
double        derrivative = 0;
double        filter_current_output = 0;
double        filter_previous_output = 0;
double        filter_alpha = 0.250;
double        max_derrivative = 0;

// Display Value
byte value = 1;

// Button ISR variables
volatile unsigned long buttonPrevTime  = 0;
unsigned long button_long_timer  = 0;
byte          button_flag   = 0;
bool          button_state  = false;
bool          button_long_started = false;
byte          button_short  = 0;
byte          button_long   = 0;

void ICACHE_RAM_ATTR button_ISR();

unsigned int ap_channel = 1;

// Capture packets and increment variable
void counter() {
  pkts++;
}


void setup() {
  
  EEPROM.begin(512);        //Initialize EEPROM
  Serial.begin(115200);
  Serial.print("\n\n\n");
  ap_channel=EEPROM.read(CHANNEL_ADDR);
  if(ap_channel<1||ap_channel>14){
    ap_channel=1;
  }

  find_strongest_channel();
  
  // Networking Setup, sets ESP8266 into Promiscuous mode and adds the packet counter function to the call back
  Serial.print("Initializing Network Settings on Channel ");Serial.println(ap_channel);
  wifi_set_opmode(STATION_MODE);                                // Promiscuous works only with station mode
  wifi_set_channel(ap_channel);
  wifi_promiscuous_enable(disable);
  wifi_set_promiscuous_rx_cb((wifi_promiscuous_cb_t)counter);   // Set up promiscuous callback. Typecasted to match expected pointer type
  wifi_promiscuous_enable(enable);
  Serial.println("Network Settings Configured");
  
  // Shift Register and Port Configuration
  Serial.println("Initializing Display");
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, 0);
  digitalWrite(LATCH, HIGH);
  pinMode(CLEAR, OUTPUT);
  pinMode(OUTPUTENABLE, OUTPUT);
  digitalWrite(CLEAR, HIGH);
  digitalWrite(CLEAR, LOW);
  digitalWrite(CLEAR, HIGH);
  pinMode(SWITCH, INPUT);
  attachInterrupt(digitalPinToInterrupt(SWITCH), button_ISR, CHANGE);
  
  Serial.println("Starting Packet Counting");
}

void loop() {
  // Every 100ms calculate the change in packets (Packets/Second) and display on the 8 LEDs
  static byte oldvalue = 0;
  static int s_counter = 0;
  curTime = millis();
  if(curTime - prevTime >= 100)
  {
    s_counter++;
    prevTime = curTime;
    derrivative = pkts-oldpkts;
    derrivative = derrivative * 10;
    oldpkts = pkts;
    //Serial.print(derrivative);
    filter_current_output  = filter_alpha*derrivative + (1-filter_alpha)*filter_previous_output;
    filter_previous_output = filter_current_output;
    //Serial.print(",");Serial.println(filter_current_output);
    derrivative = filter_current_output;
    
    if(derrivative < max_derrivative * 0.125)
    {
      value = 1; //  |-------
      analogWrite(OUTPUTENABLE, 1020);
    }
    else if (derrivative < max_derrivative * 0.25)
    {
      value = 3; //  ||------
      analogWrite(OUTPUTENABLE, 1010);
    }
    else if (derrivative < max_derrivative * 0.375)
    {
      value = 7; //  |||-----
      analogWrite(OUTPUTENABLE, 1000);
    }
    else if (derrivative < max_derrivative * 0.5)
    {
      value = 15; // ||||----
      analogWrite(OUTPUTENABLE, 950);
    }
    else if (derrivative < max_derrivative * 0.625)
    {
      value = 31; // |||||---
      analogWrite(OUTPUTENABLE, 900);
    }
    else if (derrivative < max_derrivative * 0.75)
    {
      value = 63; // ||||||--
      analogWrite(OUTPUTENABLE, 500);
    }
    else if (derrivative < max_derrivative * 0.875)
    {
      value = 127; // |||||||-
      analogWrite(OUTPUTENABLE, 300);
    }
    else if (derrivative >= max_derrivative * 0.875)
    {
      value = 255; // ||||||||
      analogWrite(OUTPUTENABLE, 0);
    }
    if(oldvalue!=value){
      // Display Value
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, MSBFIRST, value);
      delay(1);
      digitalWrite(LATCH, HIGH);
    }
    oldvalue = value;
    
    // Reset auto ranging every hour
    if(s_counter>36000){
      max_derrivative = 0;
      s_counter = 0;
    }
    
    if(derrivative>max_derrivative){
      max_derrivative = derrivative;
      //Serial.print("new max derrivative:");Serial.println(max_derrivative);
    }
  }
  if(!digitalRead(SWITCH)){
    if(button_long_started == false){
      button_long_started = true;
      button_long_timer = millis();
    }
    if(millis()-button_long_timer>1500){
      button_long_timer = 0;
      button_long_started = false;
      change_channel();
    }
  }
  else{
    button_long_started = false;
  }
  
}

void button_ISR()
{
  //Serial.println("Entered Button ISR");
  if(!digitalRead(SWITCH)){
    buttonPrevTime = millis();
  }
  else{
    unsigned long time_difference = millis() - buttonPrevTime;
    if(time_difference > 100){
      button_short = true;
    }
  }
}

void change_channel(){
  Serial.println("Changing Channel");
  bool done_flag = false;
  int current_channel = 1;
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, current_channel);
  digitalWrite(LATCH, HIGH);
  while(!done_flag){
    ESP.wdtFeed();
    curTime = millis();
    if(curTime - prevTime >= 500){
      prevTime = curTime;
      //toggle LEDs
      digitalWrite(OUTPUTENABLE, !digitalRead(OUTPUTENABLE));
    }
    if(button_short){
      current_channel++;
      if(current_channel>14){
        current_channel=1;    // Wrap around back to channel 1 
      }
      button_short = false;
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, MSBFIRST, current_channel);
      digitalWrite(LATCH, HIGH);
    }
    if(!digitalRead(SWITCH)){
      if(button_long_started == false){
        button_long_started = true;
        button_long_timer = millis();
      }
      if(millis()-button_long_timer>1500){
        button_long_timer = 0;
        button_long_started = false;
        done_flag=true;
        EEPROM.write(CHANNEL_ADDR, current_channel);
        EEPROM.commit();    //Store data to EEPROM
      }
    }
    else{
      button_long_started = false;
     }
  }
  ESP.reset();
}

int find_strongest_channel(){
  int wifi_networks_n = 0;    // Number of wifi networks present, and used to reference details of the networks
  int max_rssi = -1000; // RSSIs are negative, so initialize to something below any actual network strength
  int strongest_channel = 0;  // AP Channel that has the strongest RSSI present
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  //delay(100);
  wifi_networks_n = WiFi.scanNetworks();

  if(wifi_networks_n == 0){
    Serial.println("No Networks Found, that's not right, who doesn't have a WiFi network around?");
  }
  else{
    Serial.print(wifi_networks_n);Serial.println(" networks found");
    // First Case
    for (int i = 0; i < wifi_networks_n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print("; ");
      Serial.print(WiFi.channel(i));
      Serial.println(")");
      if(WiFi.RSSI(i)>max_rssi){
        strongest_channel = WiFi.channel(i);
        max_rssi=WiFi.RSSI(i);
      }
    }
  }

  Serial.print("Strongest Channel is :"); Serial.println(strongest_channel);
  
}
