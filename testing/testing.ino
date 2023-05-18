
#include <SPI.h>
#include <XBOXUSB.h>
#include <Servo.h>

uint16_t level = 0;
uint16_t sigPerLevel = 10;

USB usb;
XBOXUSB xb(&usb);

void setup(void) {

  Serial.begin(4800);

  if(usb.Init() == -1) {
    Serial.println("Failed to initialize USB. Halt.");
    while(true);
  }

  
  Servo esc[6];
  for (auto i = 0; i < 6; i++) {
    pinMode(i+2, OUTPUT);
    esc[i].attach(i+2, 1100, 1900);
    esc[i].writeMicroseconds(1500);
  }
  delay(7000);
}

uint16_t sig = 1500;

void loop(void) {
  
  Serial.print("Level ");
  Serial.println(level);

  while(!(xb.getButtonClick(A) || xb.getButtonClick(B)));
  if(xb.getButtonPress(A)) {
    level++;
    Serial.println("Increase!");
    return;
  }
  if(xb.getButtonPress(B)) {
    level--;
    Serial.println("Decrease!");
    return;
  }
}
