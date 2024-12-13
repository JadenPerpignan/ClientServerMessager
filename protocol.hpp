// FinalProject/protocol.hpp
#include <iostream>
#include <string>
#include <cstring>

struct Packet {
    char header[10];  // e.g., "TEXT", "AUDIO", "VIDEO"
    char data[1024];  // Payload
};

Packet createPacket(const std::string& header, const std::string& message) {
    Packet packet;
    strncpy(packet.header, header.c_str(), sizeof(packet.header));
    strncpy(packet.data, message.c_str(), sizeof(packet.data));
    return packet;
}