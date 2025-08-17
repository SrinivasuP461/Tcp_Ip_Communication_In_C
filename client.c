#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// === Individual packet senders ===
void send_packet21(int sock) {
    unsigned char packet[5] = {0xBB, 0x01, 0x02, 0x21, 0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    printf("Sent packet21: BB 01 02 21 CC\n");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Reply: ");
        for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
}

void send_packet22(int sock) {
    unsigned char packet[5] = {0xBB, 0x01, 0x02, 0x22, 0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    printf("Sent packet22: BB 01 02 22 CC\n");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Reply: ");
        for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
}

void send_packet23(int sock) {
    unsigned char packet[5] = {0xBB, 0x01, 0x02, 0x23, 0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    printf("Sent packet23: BB 01 02 23 CC\n");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Reply: ");
        for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
}

void send_packet24(int sock) {
    unsigned char packet[5] = {0xBB, 0x01, 0x02, 0x24, 0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    printf("Sent packet24: BB 01 02 24 CC\n");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Reply: ");
        for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
}

void send_packet25(int sock) {
    unsigned char packet[5] = {0xBB, 0x01, 0x02, 0x25, 0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    printf("Sent packet25: BB 01 02 25 CC\n");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Reply: ");
        for (int i = 0; i < valread; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
}

// === NEW FUNCTION: send all packets continuously ===
void send_all_packets(int sock) {
    printf("Sending all packets (21–25) continuously...\n");
    send_packet21(sock);
    sleep(1);
    send_packet22(sock);
    sleep(1);
    send_packet23(sock);
    sleep(1);
    send_packet24(sock);
    sleep(1);
    send_packet25(sock);
    printf("Finished sending all packets.\n");
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    printf("Connected to server.\n");
    printf("Type 21, 22, 23, 24, 25 to send a packet, 'all' to send all, or 'q' to quit.\n");

    char input[10];
    while (1) {
        printf("Enter packet id: ");
        if (scanf("%s", input) != 1) break;

        if (strcmp(input, "21") == 0) send_packet21(sock);
        else if (strcmp(input, "22") == 0) send_packet22(sock);
        else if (strcmp(input, "23") == 0) send_packet23(sock);
        else if (strcmp(input, "24") == 0) send_packet24(sock);
        else if (strcmp(input, "25") == 0) send_packet25(sock);
        else if (strcmp(input, "all") == 0) send_all_packets(sock);
        else if (strcmp(input, "q") == 0) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid input! Type 21–25, 'all', or q to quit.\n");
        }
    }

    close(sock);
    return 0;
}
