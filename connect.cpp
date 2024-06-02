#include "connect.hpp"

Connect::Connect(boost::asio::io_service& service, const std::string& ip, const std::string& port)
    : ios(service), endpoint(ios){
    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
    boost::asio::connect(endpoint, endpoints);
}

// send json object
void Connect::send(const nlohmann::json& j){
    endpoint.send(boost::asio::buffer(j.dump() + "\n"));
}

// recieve json object with nhlohmann::json
nlohmann::json Connect::start(){ 
    boost::asio::streambuf buf;
    boost::asio::read_until(endpoint, buf, "");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    nlohmann::json j = nlohmann::json::parse(data);
    return j.dump(4);
   
}

// recieve json object and convert to string, listen for data until something is received
std::string Connect::receive_board(){
    boost::asio::streambuf buf;
    boost::asio::read_until(endpoint, buf, "");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    nlohmann::json j = nlohmann::json::parse(data);
    return j.dump(4);
}
