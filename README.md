
<img width="720" height="532" alt="gui" src="https://github.com/user-attachments/assets/6216b2ba-22ad-411c-bb65-bb7abe12c4ca" />


# TCP/IP Communication in C (Terminal + GUI)

## 📄 Description

This project demonstrates TCP/IP socket communication in C with both **terminal-based** and **GUI-based** implementations.

### 🔹 Terminal Mode
- `server.c`: A simple TCP server.
- `client.c`: A terminal-based client.
- The client connects to the server, sends a packet (with message ID and data), and receives a response.
- The server checks the message ID and replies.
- When the client disconnects or quits, the server **automatically stops**.

### 🔹 GUI Mode
- `server2.c`: A persistent TCP server that stays running.
- `client_gui.c`: A GTK-based GUI client.
- The client can **connect/disconnect multiple times** without stopping the server.
- Sent and received packets are **displayed in the GUI**.

---

## ⚙️ Features

### Terminal Version (`server.c` + `client.c`)
- One-time TCP communication
- Message ID validation
- Auto shutdown of server on client disconnect

### GUI Version (`server2.c` + `client_gui.c`)
- GTK-based graphical interface
- Connect/Disconnect functionality
- Display of sent and received data
- Server runs continuously

---

## 🧰 Technologies Used

- C (GCC)  
- POSIX Sockets (TCP/IP)  
- GTK 3 (`client_gui.c`)  
- Linux/Unix environment

---

## 🚀 Getting Started

### 🧱 Prerequisites

Install required packages (for GUI):

```bash
sudo apt-get update
sudo apt-get install build-essential libgtk-3-dev
