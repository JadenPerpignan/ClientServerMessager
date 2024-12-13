FinalProject: Multimedia Group Chat Application

Overview

This Final Project is a C++ multimedia group chat application designed to showcase key operating system concepts and advanced features:
	•	Group Text Chat: Multiple clients can connect to a central server, exchange text messages, and broadcast them to all connected clients.
	•	Future Audio/Video Support: Integration of audio and video streams using FFmpeg and OpenCV for real-time communication.
	•	Operating System Concepts:
	•	Multithreading: Concurrently handle multiple clients with threads.
	•	Synchronization: Use mutexes and condition variables to safely share resources.
	•	Scheduling (Thread Pools): Efficiently manage client tasks and reduce overhead by implementing a thread pool.
	•	Memory Management: Manage buffers for incoming/outgoing data efficiently.

The application is designed to be developed in CLion and deployed on a remote Linux environment (e.g., DigitalOcean Droplet or other cloud providers).

Features
	•	Text Chat:
	•	Multiple clients can connect to a single server.
	•	All messages sent by one client are broadcast to all others.
	•	Planned Features:
	•	Audio Support: Capture, encode, and send audio data using FFmpeg.
	•	Video Support: Capture from webcam, encode with FFmpeg, and send frames. Use OpenCV for decoding and displaying video.

Directory Structure

FinalProject/
├─ CMakeLists.txt         // Top-level CMake configuration
├─ protocol.hpp           // Protocol definition & packet structure
├─ server/
│  ├─ CMakeLists.txt      // Server CMake configuration
│  └─ server.cpp          // Server implementation
├─ client/
│  ├─ CMakeLists.txt      // Client CMake configuration
│  └─ client.cpp          // Client implementation
├─ media/                 // Future: audio/video capture utils & sources
└─ docs/                  // Documentation and design notes

Getting Started

Prerequisites
	•	Operating System: Linux (Ubuntu 20.04+ recommended)
	•	Compiler: g++ with C++17 or C++20/C++23 support
	•	Build Tool: CMake (version 3.10+)
	•	Optional: CLion IDE for local or remote development

Install Dependencies

On Ubuntu/Debian-based systems:

sudo apt update
sudo apt install -y build-essential cmake g++

For future audio/video features, you’ll eventually need:

sudo apt install -y libopencv-dev ffmpeg libavcodec-dev libavformat-dev libavutil-dev libswscale-dev

Building the Project
	1.	Clone or transfer the project to your server or local machine:

git clone https://github.com/yourusername/FinalProject.git
cd FinalProject


	2.	Create a build directory and run CMake:

mkdir build && cd build
cmake ..
make

This will produce two executables:
	•	server_executable (in build/server/)
	•	client_executable (in build/client/)

Running the Server and Client
	1.	Run the Server:

cd build/server
./server_executable

You should see:

Server started on port 8080


	2.	Run the Client:
In another terminal or SSH session:

cd build/client
./client_executable

You should see:

Connected to server

Type a message in the client’s terminal and press Enter. The server terminal will log the received message, and any other connected client will display it.

Connecting Multiple Clients

Open another client session:

cd build/client
./client_executable

Now, typing in one client’s terminal should broadcast the message to all connected clients.

Remote Development with CLion

If using CLion Remote Development:
	•	Configure CLion to connect to your remote server/Droplet via SSH.
	•	Open the FinalProject directory as a project.
	•	CLion will handle syncing files, building, and providing a terminal.
	•	Use CLion’s built-in Run/Debug Configurations to run server_executable and client_executable.

Protocol Design

Current Protocol (Initial):
	•	protocol.hpp defines a Packet struct with a header and data.
	•	Initially using simple strings (e.g., "TEXT", "AUDIO", "VIDEO" in header).
	•	Future enhancements:
	•	Add metadata for text (MSG|USER_ID|DEST_ID)
	•	Add metadata for video (VIDEO|FRAME_NUM|RESOLUTION)
	•	Add metadata for audio (frame numbers, timestamps)

OS Concepts and Planned Enhancements
	•	Multithreading:
Already implemented: The server creates a new thread (handleClient) for each client connection.
	•	Synchronization:
Using std::mutex and std::lock_guard to protect shared resources (e.g., client_sockets vector).
	•	Thread Pools (Coming Soon):
Replace per-client threads with a thread pool to handle requests more efficiently.
	•	Memory Management:
As we add audio/video data, we’ll introduce buffer pools or memory management strategies.
	•	Scalability:
	•	Test with 10+ clients connected simultaneously.
	•	Use tools like top, htop, or profiling to measure resource usage.
	•	CI/CD:
	•	Consider setting up GitHub Actions or DigitalOcean App Platform build triggers.
	•	Automated builds and tests on each commit.

Testing and Debugging
	•	Test multiple local clients (via SSH sessions) connected to one server.
	•	For debugging memory issues, consider using valgrind or AddressSanitizer.
	•	For network troubleshooting, use netstat, lsof, or tcpdump to ensure connections are established.

Future Roadmap
	1.	Implement Thread Pool:
	•	Add a ThreadPool class and refactor server code to enqueue client tasks rather than spawning a thread per client.
	2.	Add Audio Streaming:
	•	Capture audio using FFmpeg.
	•	Encode and send audio frames as PacketType::AUDIO.
	3.	Add Video Streaming:
	•	Use OpenCV to capture webcam frames.
	•	Encode video frames with FFmpeg and send as PacketType::VIDEO.
	•	On client side, decode and display using OpenCV’s imshow.
	4.	Authentication and User Management:
	•	Add user IDs, authentication steps, and possibly private messages.
