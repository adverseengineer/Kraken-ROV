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

static DataChunk chunk;
static char* buffer = reinterpret_cast<char*>(&chunk);
static const size_t DATA_LEN = sizeof(typeof(chunk));

//establish an ethernet connection, and initialize our controller
void UpperComms::Init(void) noexcept {

  chunk.sigs[2] = 2222;
  chunk.sigs[5] = 11092;
  chunk.sigs[7] = 999;

  //initialize the ethernet shield with our settings
  Ethernet.begin(mac, ip, subnet, gateway, dns);

  //establish an ethernet connection to the lower arduino
  if(client.connect(gateway, port))
    Serial.println(F("Successfully connected to server!"));
  else
    Serial.println(F("Failed to connect to server"));
}

void UpperComms::Update(void) noexcept {

  //if our ethernet connection is still open
  if(client.connected()) {
    
    client.write(buffer, DATA_LEN);
    client.flush();

    Serial.println(F("Still Good!"));
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
