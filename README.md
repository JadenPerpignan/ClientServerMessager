
# Multimedia Group Chat Application

## Overview

The Multimedia Group Chat Application is a client-server project implemented in C++. It allows:
1. Text-based group chat.
2. Audio streaming between clients and the server.
3. Real-time video streaming using OpenCV.

The server manages multiple client connections efficiently using multithreading and a thread pool. Data packets for text, audio, and video are transmitted using a lightweight custom protocol.

## Features

- **Text Chat**: Send and receive group text messages.
- **Audio Stream**: Capture and transmit audio packets.
- **Video Stream**: Real-time video capture and display using OpenCV.
- **Multithreading**: Server handles multiple clients concurrently using a thread pool.
- **Synchronization**: Shared resources are synchronized using mutexes and condition variables.

## Directory Structure

```
MultimediaChat/
├── CMakeLists.txt
├── protocol.hpp                # Packet structure and protocol definitions
├── server/
│   ├── server.cpp              # Server application
│   ├── server_threadpool.hpp   # Thread pool implementation
│   └── CMakeLists.txt
├── client/
│   ├── client.cpp              # Client application
│   └── CMakeLists.txt
├── media/
│   ├── audio_capture.cpp       # Audio capture (future extension with FFmpeg)
│   ├── video_capture.cpp       # Video capture using OpenCV
│   └── media_utils.hpp         # Helper utilities for multimedia
├── build/                      # Build directory (created during build process)
├── README.md                   # This file
└── docs/
    └── design_notes.md         # Protocol and design notes
```

## Dependencies

Ensure the following libraries are installed on your system:

- **OpenCV**: For video capture and processing.
- **FFmpeg**: For future audio streaming support.
- **POSIX Sockets**: For client-server communication.

### Install Dependencies

Run the following commands:

```sh
sudo apt update
sudo apt install libopencv-dev libavcodec-dev libavformat-dev libswscale-dev ffmpeg
```

## Build Instructions

Follow these steps to build the project.

1. Clone the Repository:

```sh
git clone https://github.com/yourusername/FinalProject.git
cd MultimediaChat
```

2. Build the Project:

Create a build directory and compile using CMake:

```sh
mkdir build && cd build
cmake ..
make
```

3. Verify Build:

The server and client executables will be generated in the build directory.

## Run Instructions

1. **Start the Server**

Run the server application to listen for incoming client connections:

```sh
./server/server
```

The server listens on port 8080 and accepts multiple clients.

2. **Start the Client**

Run the client application in another terminal:

```sh
./client/client
```

- **Text Chat**: Enter messages into the client console.
- **Video Stream**: The client captures video frames from the webcam and sends them to the server.
- Press Enter to stop video capture.

3. **Run Multiple Clients**

To test scalability, open multiple terminal windows and start multiple clients:

```sh
./client/client
```

## How It Works

1. **Client**:
   - Captures text, audio, or video input.
   - Wraps the data into a Packet structure.
   - Sends packets to the server over a TCP connection.

2. **Server**:
   - Listens for incoming connections.
   - Uses a thread pool to handle multiple clients concurrently.
   - Processes incoming packets:
     - **Text**: Logs and broadcasts messages.
     - **Video**: Decodes and displays video frames using OpenCV.
     - **Audio**: (Future implementation using FFmpeg).

3. **Protocol**:
   A lightweight protocol is used to identify packet types and metadata:

   ```
   [PacketType|Metadata|Payload]
   ```

### Sample Protocol Examples

- **Text Message**:

  ```
  [MSG|USER1|ALL]
  Payload: "Hello Group!"
  ```

- **Video Frame**:

  ```
  [VIDEO|FRAME|RESOLUTION]
  Payload: Encoded JPEG frame data
  ```

## Testing

- Test the server with multiple client instances.
- Use tools like Wireshark to verify packet transmission:
  - Filter: tcp.port == 8080
- Run stress tests with 5–10 clients sending text and video packets simultaneously.

## Known Issues

- **Audio Transmission**: Audio streaming is under development using FFmpeg.
- **High Packet Load**: Large video frames may cause slight latency. Optimization suggestions:
  - Use lower resolution (e.g., 640x480).
  - Compress frames before transmission.

## Future Improvements

- Implement audio capture and playback using FFmpeg.
- Optimize video frame compression for real-time performance.
- Add encryption for secure communication.

## Contributors

- Jaden Perpignan: Project implementation, server/client logic, and synchronization.

## References

- OpenCV Documentation
- FFmpeg Documentation
- POSIX Sockets Tutorial
