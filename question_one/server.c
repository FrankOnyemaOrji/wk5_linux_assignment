#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *save_message(void *arg);
void *count_words(void *arg);

typedef struct {
    int new_socket;
    char message[BUFFER_SIZE];
} ThreadArgs;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t thread1, thread2;
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args->new_socket = new_socket;
        read(new_socket, args->message, BUFFER_SIZE);

        pthread_create(&thread1, NULL, save_message, (void *)args);
        pthread_create(&thread2, NULL, count_words, (void *)args);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        close(new_socket);
    }

    return 0;
}

void *save_message(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    FILE *file = fopen("received_message.txt", "a");
    if (file == NULL) {
        perror("file open failed");
        pthread_exit(NULL);
    }

    fprintf(file, "%s\n", args->message);
    fclose(file);
    pthread_exit(NULL);
}

void *count_words(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int word_count = 0;
    char *token = strtok(args->message, " ");
    
    while (token != NULL) {
        word_count++;
        token = strtok(NULL, " ");
    }

    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, "Word count: %d", word_count);
    send(args->new_socket, response, strlen(response), 0);
    pthread_exit(NULL);
}
