#include <stdio.h>
#include <Arduino.h>
#include <IRremote.h>


const int relayPin = 7;
const int recv_pin = 2; 

IRrecv irrecv(recv_pin);
decode_results results;

const long int LIGHT_ON_CODE = 0xFF30CF;
const long int LIGHT_OFF_CODE = 0xFF18E7; 

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn();
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
}

void loop() {
    if (irrecv.decode(&results)) {
        long int receivedCode = results.value;
        Serial.print("Received IR Code: ");
    Serial.println(receivedCode, HEX); 


        if (receivedCode == LIGHT_ON_CODE) {
            digitalWrite(relayPin, HIGH); 
            Serial.println("Light ON");
        } else if (receivedCode == LIGHT_OFF_CODE) {
            digitalWrite(relayPin, LOW); 
            Serial.println("Light OFF");
        }

        irrecv.resume();
    }
}
