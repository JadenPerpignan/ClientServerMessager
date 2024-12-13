#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <mutex>
#include <opencv2/opencv.hpp>
#include "server_threadpool.hpp"
#include "../protocol.hpp"

const int PORT = 8080;

// Shared chat log
std::vector<std::string> chatLog;
std::mutex logMutex; // Mutex to protect chat log

void handleClient(int client_fd) {
    Packet packet;

    // Receive packet
    while (read(client_fd, &packet, sizeof(packet)) > 0) {
        std::string metadata(packet.metadata);
        std::string payload(packet.data);

        switch (packet.type) {
            case PacketType::TEXT:
                std::cout << "Text Message: " << payload << std::endl;
                break;

            case PacketType::AUDIO:
                std::cout << "Audio Packet Received: Size " << payload.size() << " bytes\n";
                break;

            case PacketType::VIDEO: {
                std::cout << "Video Packet Received: Size " << payload.size() << " bytes\n";

                // Decode the frame
                std::vector<uchar> buffer(payload.begin(), payload.end());
                cv::Mat frame = cv::imdecode(buffer, cv::IMREAD_COLOR);

                if (!frame.empty()) {
                    // Display the frame
                    cv::imshow("Server Video Stream", frame);
                    cv::waitKey(1); // Required to render the frame
                }
                break;
            }
        }

        // Send acknowledgment
        std::string response = "Server ACK: " + metadata;
        send(client_fd, response.c_str(), response.size(), 0);
    }

    close(client_fd);
}

int main() {
    int server_fd;
    sockaddr_in address{};
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    ThreadPool pool(4);

    while (true) {
        int client_fd = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        pool.enqueue([client_fd]() { handleClient(client_fd); });
    }

    close(server_fd);
    return 0;
}