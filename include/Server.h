#include <iostream>
#include <cstring>
#include <array>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <pqxx/pqxx>


/**  
 * The basic routine is: server will wait for a connection,
 * accept() it, and fork() a child process to handle it.
 * 
 * source: https://beej.us/guide/bgnet/html/split/client-server-background.html
 */

constexpr int SERVER_PORT = 8080;

class Server {
public:
    Server();
    void run();
private:
    static void die(std::string);
    void process_client();
    std::string get_question();
    std::string get_answer(std::string);
    int socket_fd;
}