#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_LEN 32

int main() {
    int sockfd;
    char buffer[MAX_LEN + 1];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    ssize_t n;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address setup
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server started ... waiting for connection ...\n");

    addr_size = sizeof(clientAddr);

    // Receive message
    n = recvfrom(sockfd, (char *)buffer, MAX_LEN, MSG_WAITALL,
                 (struct sockaddr *)&clientAddr, &addr_size);
    buffer[n] = '\0';
    printf("Received from client: %s\n", buffer);

    // Echo message back
    sendto(sockfd, (const char *)buffer, strlen(buffer), 0,
       (const struct sockaddr *)&clientAddr, addr_size);

    printf("Echoed back to client: %s\n", buffer);

    close(sockfd);
    return 0;
}
