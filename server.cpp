#include <iostream>
#include <cstring>
#include <array>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


/**  
 * The basic routine is: server will wait for a connection,
 * accept() it, and fork() a child process to handle it.
 * 
 * source: https://beej.us/guide/bgnet/html/split/client-server-background.html
 */

constexpr int SERVER_PORT = 8080;

void die(std::string operation) {
    std::cerr << operation << ": " 
        << std::strerror(errno) << std::endl; 
    std::exit(EXIT_FAILURE);
}

int main() {
    // classic socket-bind-listen-accept pattern.
    std::cout << "Creating server socket" << std::endl;

    // create a TCP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        die("socket");
    }
    
    int on = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        die("setsocketopt");
    }
    sockaddr_in server_addr{};  // the zero initializer '{}' is needed, it zeroes everything out (like memset in C)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // bind the socket
    if (bind(server_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == -1) {
        die("bind");
    }

    // starts listening
    if (listen(server_fd, 10) == -1) {
        die("listen");
    }
    std::cout << "Server listening on 127.0.0.1:" << SERVER_PORT << '\n';

    // accepts connection
    while (true) {
        const int conn_fd = accept(server_fd, nullptr, nullptr);
        if (conn_fd == -1) {
            // EINTR is interrupt, resume if err due to interruption
            if (errno == EINTR) {
                continue;
            }
            die("accept");
        }
        std::array<char, 1024> buf{};
        const ssize_t bytes_received = recv(conn_fd, buf.data(), buf.size(), 0);
        if (bytes_received == -1) {
            close(conn_fd);
            die("recv");
        } else if (bytes_received > 0) {
            std::cout << "Received " << std::string(buf.data(), bytes_received) << std::endl;
            send(conn_fd, buf.data(), bytes_received, 0);
        }
        close(conn_fd);
    }
}




