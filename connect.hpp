#ifndef CONNECT_HPP
#define CONNECT_HPP

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <string>

class Connect {

public:
    Connect(boost::asio::io_service& ios, const std::string& ip, const std::string& port);

    void send(const std::string& message);



private:
    boost::asio::io_service& ios;
    boost::asio::ip::tcp::socket endpoint;

};

#endif