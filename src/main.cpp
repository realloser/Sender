#include <Arduino.h>

#include <RFTransmitter.h>


#define NODE_ID          1
#define OUTPUT_PIN       11

// Send on digital pin 11 and identify as node 1
RFTransmitter transmitter(OUTPUT_PIN, NODE_ID);
unsigned long start, finished, elapsed;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void sendMessage(bool resend) {
  char *msg = "Hello World!";
  Serial.println("sending...");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  start=millis();
  if(resend) {
    transmitter.resend((byte *)msg, strlen(msg) + 1);
  }
  else {
    transmitter.send((byte *)msg, strlen(msg) + 1);
  }

  finished=millis();
  elapsed=finished-start;
  if (resend){
    Serial.print("re");
  }
  Serial.print("send:");
  Serial.print(elapsed);
  Serial.println(" milliseconds elapsed");
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);

}

void loop() {
  sendMessage(false);

  delay(4000);

  sendMessage(true);
}
