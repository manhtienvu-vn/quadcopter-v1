#include <Arduino.h>
#include "bluepad32.h"

#define TX_PIN 19
#define RX_PIN 18

#define DPAD_CENTERED    0x00
#define DPAD_UP          0x01
#define DPAD_RIGHT       0x04
#define DPAD_DOWN        0x02
#define DPAD_LEFT        0x08

#define BTN_A        0x0001
#define BTN_B        0x0002
#define BTN_X        0x0004
#define BTN_Y        0x0008
#define BTN_L1       0x0010
#define BTN_R1       0x0020
#define BTN_L2       0x0040
#define BTN_R2       0x0080

uint8_t face_button = 0;
uint8_t shoulder_button = 0;
uint8_t LEFT_X, LEFT_Y, RIGHT_X, RIGHT_Y;
uint8_t KP;
uint8_t buffer[7];

GamepadPtr myGamepad;

void onConnectedGamepad(GamepadPtr gp) {
  Serial.println("✅ PS5 Controller connected!");
  myGamepad = gp;
}

void onDisconnectedGamepad(GamepadPtr gp) {
  Serial.println("❌ Controller disconnected");
  myGamepad = nullptr;
}

void setup() {
  /* Default UART is used for logging info */
  Serial.begin(115200);
  Serial.println("🔵 Starting Bluepad32...");

  /* User-configured UART is used for sending command */
  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
}

void ProcessGamepad(){
  uint16_t buttons = myGamepad->buttons();

  face_button = 0;
  shoulder_button = 0;

  /* FACE BUTTONS */
  if (buttons & BTN_A) {
    face_button |= (1 << 0);
    Serial.println("🅰️ A button");
  }
  else{
    face_button &= ~(1 << 0);
  }

  if (buttons & BTN_B) {
    face_button |= (1 << 1);
    Serial.println("🅱️ B button");
  }
  else{
    face_button &= ~(1 << 1);
  }

  if (buttons & BTN_X){
    face_button |= (1 << 2);
    Serial.println("✖️ X button");
  }
  else{
    face_button &= ~(1 << 2);
  }

  if (buttons & BTN_Y){
    face_button |= (1 << 3);
    Serial.println("(🇾) button");
  } 
  else{
    face_button &= ~(1 << 3);
  }

  /* SHOULDER BUTTONS */
  if (buttons & BTN_L1) {
    shoulder_button |= (1<<3);
    Serial.println("[L1] pressed");
  } else {
    shoulder_button &= ~(1<<3);
  }

  if (buttons & BTN_R1) {
    shoulder_button |= (1<<2);
    Serial.println("[R1] pressed");
  } else {
    shoulder_button &= ~(1<<2);
  }

  if (buttons & BTN_L2) {
    shoulder_button |= (1<<1);
    Serial.println("[L2] pressed");
  } else {
    shoulder_button &= ~(1<<1);
  }

  if (buttons & BTN_R2) {
    shoulder_button |= (1<<0);
    Serial.println("[R2] pressed");
  } else {
    shoulder_button &= ~(1<<0);
  }

  // Nút analog stick nhấn vào

  if (myGamepad->thumbR()){
    shoulder_button |= (1<<4);
    Serial.println("Right Stick pressed");
  } 
  else{
    shoulder_button &= ~(1<<4);
  }

  /* D_PAD BUTTONS */
  switch (myGamepad->dpad()) {
    case DPAD_UP:    
      Serial.println("⬆️ DPad Up");
      face_button |= (1<<4);
      break;

    case DPAD_DOWN:
      Serial.println("⬇️ DPad Down");
      face_button |= (1<<5);
      break;

    case DPAD_LEFT:  
      Serial.println("⬅️ DPad Left");
      face_button |= (1<<6); 
      break;

    case DPAD_RIGHT: 
      Serial.println("➡️ DPad Right"); 
      face_button |= (1<<7); 
      break;

  }

  int lx = myGamepad->axisX();
  LEFT_X = map(lx, -512, 511, 0, 255);
  int ly = myGamepad->axisY();
  LEFT_Y = map(ly, -512, 511, 255, 0);

  int rx = myGamepad->axisRX();
  RIGHT_X = map(rx, -512, 511, 0, 255);
  int ry = myGamepad->axisRY();
  RIGHT_Y = map(ry, -512, 511, 255, 0);
}

char message[20];

void loop() {
  BP32.update();
  if (myGamepad && myGamepad->isConnected()) {
    ProcessGamepad();
    if(Serial.available() > 0){
      int bytesRead = Serial.readBytesUntil('\n', message, sizeof(message)-1);
      message[bytesRead] = '\0';
      KP = atoi(message);
      // float number_ = (float)converted_/100;
      // Serial.println(number_);
    }
    
    buffer[0] = face_button;
    buffer[1] = shoulder_button;
    buffer[2] = LEFT_X;
    buffer[3] = LEFT_Y;
    buffer[4] = RIGHT_X;
    buffer[5] = RIGHT_Y;
    buffer[6] = KP;

    // Send Command via UART
    Serial1.write(buffer, 7);
    delay(5);
  }
}
