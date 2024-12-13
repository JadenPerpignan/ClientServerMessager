#pragma once
#include <string>
#include <cstring>

// Enum for packet types
enum class PacketType {
    TEXT,
    AUDIO,
    VIDEO
};

// Packet structure
struct Packet {
    PacketType type;          // Type of message
    char metadata[64];        // Metadata: "MSG|USER_ID|DEST_ID"
    char data[1024];          // Payload data

    // Helper to create packets
    static Packet createPacket(PacketType type, const std::string& meta, const std::string& payload) {
        Packet p;
        p.type = type;
        strncpy(p.metadata, meta.c_str(), sizeof(p.metadata));
        strncpy(p.data, payload.c_str(), sizeof(p.data));
        return p;
    }
};