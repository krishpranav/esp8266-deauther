// includes
#include "ESP8266WiFi.h"

// packet byte function
uint8_t packet[26] = {
    0xC0, 0x00,
    0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00
};

// sending packets for a wifi function
bool sendPacket(uint8_t* packet, uint16_t packetSize, uint8_t wifi_channel, uint16_t tries) {
    wifi_set_channel(wifi_channel);
    bool sent = false;
    for (int i = 0; i < tries && !sent; i++) sent = wifi_send_pkt_freedom(packet, packetSize, 0) == 0;

    return sent;
}


