#include <Client.h>


Client::Client() {
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        die("socket");
    }    
}

void Client::run() {
    connect_to_server();
    std::string question = get_question();
    std::cout << "I will ask this question: " << question << std::endl;

    std::string answer = get_answer(question);
    std::cout << answer << std::endl;
    close_connection();
}

void Client::connect_to_server() {
    sockaddr_in server_addr{};  // the zero initializer '{}' is needed, it zeroes everything out (like memset in C)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // connect to server
    if (connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        die("connect");
    }
}

std::string Client::get_question() {
    // Retrive a question from client_db
    pqxx::connection cx{"dbname=client_db"};
    pqxx::work tx(cx);
    pqxx::result r = tx.exec("SELECT question FROM questions ORDER BY random() LIMIT 1");

    tx.commit();

    // Assumes client_db will always have some questions
    std::string question{r[0][0].as<std::string>()};
    
    return question;   
}

std::string Client::get_answer(std::string& question) {
    if (send(client_fd, question.data(), question.size(), 0) != question.size()) {
        die("send");
    }

    std::string received(1024, '\0');
    const ssize_t bytes_received = recv(client_fd, received.data(), received.size(), 0);
    if (bytes_received < 0) {
        close(client_fd);
        die("recv");
    } 
    received.resize(bytes_received);
    return received;
}

void Client::close_connection() {
    close(client_fd);
}

void Client::die(std::string operation) {
    std::cerr << operation << ": " 
        << std::strerror(errno) << std::endl; 
    std::exit(EXIT_FAILURE);
}





