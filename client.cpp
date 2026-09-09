#include <iostream>
#include <cstring>
#include <array>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include<pqxx/pqxx>

/**
 * Client workflow:
 *
 *  1. 建立一個 TCP socket
 *  2. 建立 server 的 IPv4 address information
 *  3. 填入 AF_INET
 *  4. 填入 server port
 *  5. 填入 127.0.0.1
 *  6. 呼叫 connect()
 *  7. 準備一段要傳送的文字
 *  8. 呼叫 send()，或重用你已經理解的 send_all()
 *  9. 準備接收 buffer
 * 10. 呼叫 recv()
 * 11. 根據 recv() 回傳的 byte 數處理資料
 * 12. close()
 */

 #define DB_SIZE 3

constexpr int SERVER_PORT = 8080;

void die(std::string operation) {
    std::cerr << operation << ": " 
        << std::strerror(errno) << std::endl; 
    std::exit(EXIT_FAILURE);
}

int main() {
    std::cout << "creating client socket" << std::endl;

    // create a TCP socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        die("socket");
    }
    
    sockaddr_in server_addr{};  // the zero initializer '{}' is needed, it zeroes everything out (like memset in C)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // connect to server
    if (connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        die("connect");
    }

    // Retrive a question from client_db
    pqxx::connection cx{"dbname=client_db"};
    pqxx::work tx(cx);
    pqxx::result r = tx.exec("SELECT question FROM questions ORDER BY random() LIMIT 1");

    tx.commit();

    std::string question{r[0][0].as<std::string>()};
    std::cout << "I will ask this question: " << question << std::endl;
    if (send(client_fd, question.data(), question.size(), 0) != question.size()) {
        die("send");
    }

    std::string received(1024, '\0');
    const ssize_t bytes_received = recv(client_fd, received.data(), received.size(), 0);
    if (bytes_received < 0) {
        close(client_fd);
        die("recv");
    } else {
        // print out what's been received
        std::cout << received << std::endl;
    }
    close(client_fd);
}




