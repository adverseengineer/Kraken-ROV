//Nick Sells, 2023
//ETSU Underwater Robotics

#include <SPI.h>
#include <Ethernet.h>
#include <PS2X_lib.h>

#include "uppercomms.h"

uint16_t UpperComms::signals[NUM_SIGS];
static char* buffer = reinterpret_cast<char*>(UpperComms::signals);
static constexpr size_t DATA_LEN = sizeof(*UpperComms::signals) * NUM_SIGS;

static uint8_t mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03};
static const IPAddress ip(10,101,1,210);
static const IPAddress subnet(255,255,255,0);
static const IPAddress gateway(10,101,1,211);
static const IPAddress dns(0,0,0,0);
static const int port = 4080;
static EthernetClient client;

//establish the client side of a TCP connection
void UpperComms::Init(void) noexcept {

  //initialize the ethernet shield with our settings
  Ethernet.begin(mac, ip, subnet, gateway, dns);

  //establish an ethernet connection to the lower arduino
  if(client.connect(gateway, port))
    Serial.println(F("Successfully connected to server!"));
  else
    Serial.println(F("Failed to connect to server"));
}

void UpperComms::Update(void) noexcept {

  Serial.print("PWM: { ");
  for(size_t i = 0; i < 8; i++) {
    Serial.print(signals[i]);
    Serial.print(' ');
  }
  Serial.println('}');

  //if our ethernet connection is still open
  if(client.connected()) {
    
    client.write(buffer, DATA_LEN);
    client.flush();
  }
  else {
    //attempt to reconnect every tick until we are reconnected
    Serial.println(F("Disconnected from server!"));
    client.stop();

    if(client.connect(gateway, port))
      Serial.println(F("Successfully reconnected to server!"));
    else
      Serial.println(F("Failed to reconnect to server!"));
  }
}

