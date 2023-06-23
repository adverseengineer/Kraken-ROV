//Nick Sells, 2023
//ETSU Underwater Robotics

#include <SPI.h>
#include <Ethernet.h>
#include <PS2X_lib.h>

#include "uppercomms.h"

static uint8_t mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03};
static const IPAddress ip(10,101,1,210);
static const IPAddress subnet(255,255,255,0);
static const IPAddress gateway(10,101,1,211);
static const IPAddress dns(0,0,0,0);
static const int port = 4080;
static EthernetClient client;

static uint16_t sigs[8];
static char* buffer = reinterpret_cast<char*>(sigs);
static const size_t DATA_LEN = 16;

//establish an ethernet connection, and initialize our controller
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

  // Serial.print("{ ");
  // for(size_t i = 0; i < 8; i++) {
  //   Serial.print(sigs[i]);
  //   Serial.print(' ');
  // }
  // Serial.println('}');

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

void UpperComms::GetSignals(uint16_t* sigs_) noexcept {
  for(size_t i = 0; i < 8; i++)
    sigs[i] = sigs_[i];
}

void UpperComms::PrintSignals(void) noexcept {
  Serial.print("{ ");
  for(size_t i = 0; i < 8; i++) {
    Serial.print(sigs[i]);
    Serial.print(' ');
  }
  Serial.println('}');
}
