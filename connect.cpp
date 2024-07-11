#include "connect.hpp"


Network::Network(const std::string& server, int port) : io_service(), socket(io_service), server(server), port(port) {
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(server, std::to_string(port));
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::connect(socket, endpoint_iterator);
    std::cout << "Connected to server" << std::endl;
    p = readResponse();
}

std::string Network::getP() {return p;}

std::string Network::send(const std::string& data) {
    boost::asio::write(socket, boost::asio::buffer(data));
    return readResponse();
}

std::string Network::readResponse() {
    boost::asio::streambuf response;
    boost::system::error_code error;
    boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error);
    std::istream response_stream(&response);
    std::string response_str((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());
    // std::cout << "Response: " << response_str << std::endl;
    return response_str;
}

