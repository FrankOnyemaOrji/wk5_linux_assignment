#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("invalid address / address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        return -1;
    }

    while (1) {
        printf("Client: ");
        fgets(message, BUFFER_SIZE, stdin);
        send(sock, message, strlen(message), 0);

        valread = read(sock, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}
