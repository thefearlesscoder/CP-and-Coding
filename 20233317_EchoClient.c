#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_LEN 32

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server-IP> \"<Message>\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *serverIP = argv[1];
    char *message = argv[2];
    int len = strlen(message);

    if (len < 1 || len > MAX_LEN) {
        fprintf(stderr, "Error: Input string length must be between 1 and 32 bytes.\n");
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[MAX_LEN + 1];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);

    addr_size = sizeof(serverAddr);

    // Send message to server
    sendto(sockfd, (const char *)message, strlen(message), 0,
       (const struct sockaddr *)&serverAddr, addr_size);


    // Receive echo from server
    ssize_t n = recvfrom(sockfd, (char *)buffer, MAX_LEN, MSG_WAITALL,
                         (struct sockaddr *)&serverAddr, &addr_size);
    buffer[n] = '\0';
    printf("Received from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
