#include <Client.h>


Client::Client() {
    
}


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

    if (!r.empty()) {
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
            received.resize(bytes_received);
            std::cout << received << std::endl;
        }
        close(client_fd);
    }
}




