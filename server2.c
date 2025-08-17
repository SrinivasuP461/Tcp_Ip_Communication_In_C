#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Individual reply functions
void reply_packet41(int sock) {
    unsigned char reply[5] = {0xBB, 0x01, 0x02, 0x41, 0x41};
    send(sock, reply, sizeof(reply), 0);
    printf("Sent reply: BB 01 02 41 41\n");
}
void reply_packet42(int sock) {
    unsigned char reply[5] = {0xBB, 0x01, 0x02, 0x42, 0x42};
    send(sock, reply, sizeof(reply), 0);
    printf("Sent reply: BB 01 02 42 42\n");
}
void reply_packet43(int sock) {
    unsigned char reply[5] = {0xBB, 0x01, 0x02, 0x43, 0x43};
    send(sock, reply, sizeof(reply), 0);
    printf("Sent reply: BB 01 02 43 43\n");
}
void reply_packet44(int sock) {
    unsigned char reply[5] = {0xBB, 0x01, 0x02, 0x44, 0x44};
    send(sock, reply, sizeof(reply), 0);
    printf("Sent reply: BB 01 02 44 44\n");
}
void reply_packet45(int sock) {
    unsigned char reply[5] = {0xBB, 0x01, 0x02, 0x45, 0x45};
    send(sock, reply, sizeof(reply), 0);
    printf("Sent reply: BB 01 02 45 45\n");
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    unsigned char buffer[1024];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Reuse address/port
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept clients in a loop
    while (1) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;  // don’t exit, just try again
        }
        printf("Client connected.\n");

        // Handle client until disconnect
        while (1) {
            int valread = read(new_socket, buffer, sizeof(buffer));
            if (valread <= 0) {
                printf("Client disconnected.\n");
                close(new_socket);
                break; // go back to accept() for new client
            }

            printf("Received %d bytes: ", valread);
            for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
            printf("\n");

            if (valread >= 4) {
                switch (buffer[3]) {
                    case 0x21: reply_packet41(new_socket); break;
                    case 0x22: reply_packet42(new_socket); break;
                    case 0x23: reply_packet43(new_socket); break;
                    case 0x24: reply_packet44(new_socket); break;
                    case 0x25: reply_packet45(new_socket); break;
                    default:
                        printf("Unknown packet ID: %02X\n", buffer[3]);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
