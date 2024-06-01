#include "connect.hpp"

Connect::Connect(boost::asio::io_service& service, const std::string& ip, const std::string& port)
    : ios(service), endpoint(ios){
    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
    boost::asio::connect(endpoint, endpoints);
}


void Connect::send(const std::string& message){
    endpoint.send(boost::asio::buffer(message));
}
