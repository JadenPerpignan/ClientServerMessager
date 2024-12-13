#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "../protocol.hpp"

std::atomic<bool> stopVideoCapture(false);

// Function to capture video and send it to the server
void captureAndSendVideo(int sock) {
    cv::VideoCapture cap(0); // Open the default webcam (0)
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open webcam\n";
        return;
    }

    std::cout << "Video capture started. Press Enter to stop.\n";

    cv::Mat frame;
    while (!stopVideoCapture) {
        cap >> frame; // Capture a frame

        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured\n";
            continue;
        }

        // Encode the frame as JPEG to reduce size
        std::vector<uchar> buffer;
        cv::imencode(".jpg", frame, buffer);

        // Wrap the encoded frame into a Packet
        Packet videoPacket = Packet::createPacket(PacketType::VIDEO, "VIDEO|FRAME|RESOLUTION",
                                                 std::string(buffer.begin(), buffer.end()));

        // Send the packet to the server
        send(sock, &videoPacket, sizeof(videoPacket), 0);
    }

    std::cout << "Video capture stopped.\n";
}

int main() {
    int sock = 0;
    sockaddr_in serv_addr{};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return 1;
    }

    // Connect to server
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return 1;
    }

    std::cout << "Connected to server. Press Enter to stop video capture.\n";

    // Start video capture in a separate thread
    std::thread videoThread(captureAndSendVideo, sock);

    // Wait for user input to stop
    std::cin.get();
    stopVideoCapture = true;

    videoThread.join();
    close(sock);
    return 0;
}