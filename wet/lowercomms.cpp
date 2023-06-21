#include "Arduino.h"
//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Ethernet.h>
#include <SPI.h>

#include "lowercomms.h"

static uint8_t mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
static const IPAddress ip(10,101,1,211);
static const IPAddress subnet(255,255,255,0);
static const IPAddress gateway(10,101,1,210);
static const IPAddress dns(0,0,0,0);
static const int port = 4080;
static EthernetServer server(port);

static uint16_t sigs[8];
static char* buffer = reinterpret_cast<char*>(&sigs);
static const size_t DATA_LEN = 16;

void LowerComms::Init(void) noexcept {

  //initialize the ethernet shield with our settings
  Ethernet.begin(mac, ip, subnet, gateway, dns);
  //begin listening for TCP clients
  server.begin();
}

void LowerComms::Update(void) noexcept {
  //wait for a connection from the dry arduino
  EthernetClient client = server.available();

  if(client) {

    char recv;
    for(size_t i = 0; i < DATA_LEN; i++) {
      recv = client.read();
      if(recv == -1) break;
      buffer[i] = recv;
    }
    PrintSignals();
  }
  else
    Serial.println("No client connected");
}

void LowerComms::GiveSignals(uint16_t* sigs_) noexcept {
  for(size_t i = 0; i < 8; i++)
    sigs_[i] = sigs[i];
}

void LowerComms::PrintSignals(void) noexcept {
  Serial.print("{ ");
  for(size_t i = 0; i < 8; i++) {
    Serial.print(sigs[i]);
    Serial.print(' ');
  }
  Serial.println('}');
}
