#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./chattergen [frame_size]\n");
    }

    int len = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Port number
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Localhost

    char* message = (char*) malloc(len * sizeof(char));
    iovec iov{};
    iov.iov_base = (void*)message;
    iov.iov_len = len;

    msghdr msg{};
    msg.msg_name = &server_addr;
    msg.msg_namelen = sizeof(server_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = nullptr;
    msg.msg_controllen = 0;

    for (int i = 0; i < 10000000; i++) {
        if (i % 100000 == 0) {
            std::cout << "Sent " << i << "messages" << std::endl;
        }

        if (sendmsg(sockfd, &msg, 0) < 0) {
            perror("Sendmsg failed");
            close(sockfd);
            return 1;
        }
    }

    std::cout << "Message sent: " << message << std::endl;

    close(sockfd);
    return 0;
}
