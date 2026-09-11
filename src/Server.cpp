#include "Server.h"

Server::Server() {
    // classic socket-bind-listen-accept pattern.
    std::cout << "Creating server socket" << std::endl;

    // create a TCP socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        die("socket");
    }
    
    int on = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        die("setsocketopt");
    }
    sockaddr_in server_addr{};  // the zero initializer '{}' is needed, it zeroes everything out (like memset in C)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // bind the socket
    if (bind(socket_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == -1) {
        die("bind");
    }
}

void Server::run() {
    // starts listening
    if (listen(socket_fd, 10) == -1) {
        die("listen");
    }
    std::cout << "Server listening on 127.0.0.1:" << SERVER_PORT << '\n';

    // accepts connection
    while (true) {
        const int conn_fd = accept(socket_fd, nullptr, nullptr);
        if (conn_fd == -1) {
            // EINTR is interrupt, resume if err due to interruption
            if (errno == EINTR) {
                continue;
            }
            die("accept");
        }
        process_client(conn_fd);
    }
}

void Server::die(std::string operation) {
    std::cerr << operation << ": " 
        << std::strerror(errno) << std::endl; 
    std::exit(EXIT_FAILURE);
}


void Server::process_client(int conn_fd) {
    std::string question = get_question_from_client(conn_fd);
    std::string ans = get_answer_from_db(question);
   
    send(conn_fd, ans.data(), ans.size(), 0);
    close(conn_fd);
}

std::string Server::get_question_from_client(int conn_fd) {
    std::array<char, 1024> buf{};
    const ssize_t bytes_received = recv(conn_fd, buf.data(), buf.size(), 0);
    if (bytes_received == -1) {
        close(conn_fd);
        die("recv");
    } 
    const std::string question(buf.data(), bytes_received);
    std::cout << "Received " << question << std::endl;
    
    return question;
}

std::string Server::get_answer_from_db(std::string& question) {
     /**
     * Use pqxx to look up answer
     * 
     * 1. Connect to db server with pqxx::conneciton
     * 2. Create a transaction object on the connection (pqxx::work)
     * 3. Use transaction's exec, query_value, and stream funcitons to execute SQL statements
     * 4. Access the pqxx::result object returned by the above functions
     * 5. Call the transaction's commit function to finalize the work
     * 
     * Note: the connection is free to run a next transaction after current transaction is closed
     */

    pqxx::connection cx{"dbname=server_db"};
    pqxx::work tx(cx);
    
    
    pqxx::result r = tx.exec("SELECT answer FROM answers WHERE question = $1",
        pqxx::params{question});

    tx.commit();

    std::string ans{"No answer in DB!"}; 

    if (!r.empty()) {
        ans = r[0][0].as<std::string>();
    }
    return ans;
} 




