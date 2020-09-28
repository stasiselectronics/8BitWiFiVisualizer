// Chandler McCowan
// Network Traffic Indicator using ESP8266 and 8 LEDs

// TODOs
// clean up styling of code
// add ability to switch channels using the button

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <EEPROM.h>

// Shift Register GPIO Pin Definitions
#define LATCH 10 //Pin D0
#define CLOCK 2  //Pin D1
#define DATA 4   //Pin D2
#define SWITCH 14
#define CLEAR 12
#define OUTPUTENABLE 13

#define disable 0
#define enable  1

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
int value = 1;

// Button ISR variables
unsigned long buttonTimer1  = 0;
unsigned long buttonTimer2  = 0;
byte          button_flag   = 0;
byte          button_state  = 0;

unsigned int ap_channel = 1;

// Capture packets and increment variable
void counter() {
  pkts++;
}


void setup() {
  Serial.begin(115200);

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
  digitalWrite(OUTPUTENABLE, HIGH);
  digitalWrite(CLEAR, LOW);
  digitalWrite(CLEAR, HIGH);
  digitalWrite(OUTPUTENABLE, LOW);
  //pinMode(SWITCH, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(SWITCH), button_ISR, CHANGE);
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
    Serial.print(derrivative);
    filter_current_output  = filter_alpha*derrivative + (1-filter_alpha)*filter_previous_output;
    filter_previous_output = filter_current_output;
    Serial.print(",");Serial.println(filter_current_output);
    derrivative = filter_current_output;
    
    if(derrivative < max_derrivative * 0.125)
    {
      value = 1; //  |-------
    }
    else if (derrivative < max_derrivative * 0.25)
    {
      value = 3; //  ||------
    }
    else if (derrivative < max_derrivative * 0.375)
    {
      value = 7; //  |||-----
    }
    else if (derrivative < max_derrivative * 0.5)
    {
      value = 15; // ||||----
    }
    else if (derrivative < max_derrivative * 0.625)
    {
      value = 31; // |||||---
    }
    else if (derrivative < max_derrivative * 0.75)
    {
      value = 63; // ||||||--
    }
    else if (derrivative < max_derrivative * 0.875)
    {
      value = 127; // |||||||-
    }
    else if (derrivative >= max_derrivative * 0.875)
    {
      value = 255; // ||||||||
    }
    if(oldvalue!=value){
      // Display Value
    digitalWrite(OUTPUTENABLE, HIGH);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, ~value);
    delay(1);
    digitalWrite(LATCH, HIGH);
    digitalWrite(OUTPUTENABLE, LOW);
    }
    oldvalue = value;
    
    // Reset auto ranging every hour
    if(s_counter>36000){
      max_derrivative = 0;
      s_counter = 0;
    }
    
    if(derrivative>max_derrivative){
      max_derrivative = derrivative;
      Serial.print("new max derrivative:");Serial.println(max_derrivative);
    }
  }
}

void button_ISR()
{
  Serial.println("Entered Button ISR");
  if(!digitalRead(SWITCH))
  {
    // button is pressed
    // active low
    if(button_state==0)
    {
      button_state = 1;
      buttonTimer1 = millis();
    }
  }
  else
  {
    if(button_state==0)
    {
      button_state = 1;
    }
    else if(millis()-buttonTimer1>50)
    {
      button_state = 0;
      buttonTimer2   = millis()-buttonTimer1;
      Serial.println("Button Debounced");
      Serial.println(buttonTimer2);
      button_flag = 1;
    }
  }
}
