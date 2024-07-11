#ifndef CONNECT_HPP
#define CONNECT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;
using json = nlohmann::json;

class Network {
public:
    Network(const std::string& server, int port);

    std::string getP();
    std::string send(const std::string& data);

private:
    std::string readResponse();

    boost::asio::io_service io_service;
    tcp::socket socket;
    std::string server;
    int port;
    std::string p;
};

#endif