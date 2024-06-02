#ifndef CONNECT_HPP
#define CONNECT_HPP

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

class Connect {

public:
    Connect(boost::asio::io_service& ios, const std::string& ip, const std::string& port);

    void send(const nlohmann::json& j);
    nlohmann::json start();
    std::string receive_board();



private:
    boost::asio::io_service& ios;
    boost::asio::ip::tcp::socket endpoint;

};

#endif