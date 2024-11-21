#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Port number
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    char buffer[128];
    iovec iov{};
    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    msghdr msg{};
    msg.msg_name = &client_addr;
    msg.msg_namelen = client_len;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = nullptr;
    msg.msg_controllen = 0;


    for (int i = 0; i < 10000000; i++) {
        if (i % 100000 == 0) {
            std::cout << "Got " << i << "messages" << std::endl;
        }

        ssize_t received = recvmsg(sockfd, &msg, 0);
        if (received < 0) {
            perror("Recvmsg failed");
            close(sockfd);
            return 1;
        }
    }


    close(sockfd);
    return 0;
}
