#include "Arduino.h"
//Nick Sells, 2023
//ETSU Underwater Robotics

#include <SPI.h>
#include <Ethernet.h>

#include "lowercomms.h"

uint16_t LowerComms::signals[NUM_SIGS];
static char* buffer = reinterpret_cast<char*>(LowerComms::signals);
static constexpr size_t DATA_LEN = sizeof(*LowerComms::signals) * NUM_SIGS;

static uint8_t mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
static const IPAddress ip(10,101,1,211);
static const IPAddress subnet(255,255,255,0);
static const IPAddress gateway(10,101,1,210);
static const IPAddress dns(0,0,0,0);
static const int port = 4080;
static EthernetServer server(port);

//establish the server side of a TCP connection
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

  }
  else
    Serial.println("No client connected");
}
