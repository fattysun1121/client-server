#include <iostream>
#include <cstring>
#include <array>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <pqxx/pqxx>

#pragma once

#define DB_SIZE 3

constexpr int SERVER_PORT = 8080;


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

class Client {
public:
    Client();
    void run();
private:
    static void die(std::string);
    void connect_to_server();
    std::string get_question();
    std::string get_answer(std::string&);
    void close_connection();
    int client_fd;
};