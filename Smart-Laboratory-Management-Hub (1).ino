/*
  Smart Laboratory Management Hub
  Arduino + 433 MHz RF Receiver + 4-Channel Relay

  Note:
  Replace BUTTON_1 to BUTTON_4 with the actual RF codes
  from your remote control.
*/

#include <RCSwitch.h>

RCSwitch rfReceiver = RCSwitch();

// RF receiver data pin
const int RF_RECEIVER_PIN = 2;

// Relay pins
const int RELAY_1 = 8;
const int RELAY_2 = 9;
const int RELAY_3 = 10;
const int RELAY_4 = 11;

// Placeholder RF codes - replace with your actual remote codes
const unsigned long BUTTON_1 = 123456;
const unsigned long BUTTON_2 = 123457;
const unsigned long BUTTON_3 = 123458;
const unsigned long BUTTON_4 = 123459;

bool relay1State = false;
bool relay2State = false;
bool relay3State = false;
bool relay4State = false;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Initial state: all devices OFF
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);

  // Start RF receiver
  rfReceiver.enableReceive(digitalPinToInterrupt(RF_RECEIVER_PIN));

  Serial.println("Smart Laboratory Management Hub");
  Serial.println("System Ready...");
}

void loop() {
  if (rfReceiver.available()) {

    unsigned long receivedCode = rfReceiver.getReceivedValue();

    Serial.print("RF Code Received: ");
    Serial.println(receivedCode);

    if (receivedCode == BUTTON_1) {
      relay1State = !relay1State;
      digitalWrite(RELAY_1, relay1State ? LOW : HIGH);
      Serial.println("Laboratory Device 1 toggled");
    }

    else if (receivedCode == BUTTON_2) {
      relay2State = !relay2State;
      digitalWrite(RELAY_2, relay2State ? LOW : HIGH);
      Serial.println("Laboratory Device 2 toggled");
    }

    else if (receivedCode == BUTTON_3) {
      relay3State = !relay3State;
      digitalWrite(RELAY_3, relay3State ? LOW : HIGH);
      Serial.println("Laboratory Device 3 toggled");
    }

    else if (receivedCode == BUTTON_4) {
      relay4State = !relay4State;
      digitalWrite(RELAY_4, relay4State ? LOW : HIGH);
      Serial.println("Laboratory Device 4 toggled");
    }

    else {
      Serial.println("Unknown RF command");
    }

    rfReceiver.resetAvailable();
  }
}
