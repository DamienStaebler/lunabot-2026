#include <Arduino.h>

// Pin definitions
int digitalPins[4] = {15, 0, 16, 5};
int pwmPins[4] = {2, 4, 17, 18};
int analogPins[2] = {20, 18};

String input = "";

void setup() {
  Serial.begin(9600);

  // Setup digital pins
  for (int i = 0; i < 4; i++) {
    pinMode(digitalPins[i], OUTPUT);
  }

  // Setup PWM pins
  for (int i = 0; i < 4; i++) {
    pinMode(pwmPins[i], OUTPUT);
  }
}

void processCommand(String cmd) {
    if (cmd.startsWith("D")) {
      int pin, val;
      sscanf(cmd.c_str(), "D,%d,%d", &pin, &val);
      digitalWrite(pin, val);
    }
  else if (cmd.startsWith("P")) {
    int pin, val;
    sscanf(cmd.c_str(), "P,%d,%d", &pin, &val);
    analogWrite(pin, val);
  }
  else if (cmd.startsWith("R")) {
    int val0 = analogRead(analogPins[0]);
    int val1 = analogRead(analogPins[1]);

    Serial.print("A,");
    Serial.print(val0);
    Serial.print(",");
    Serial.println(val1);
  }
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      processCommand(input);
      input = "";
    } else {
      input += c;
    }
  }
}

