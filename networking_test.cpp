#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Network.hpp>

using json = nlohmann::json;

class Network {
public:
    sf::TcpSocket socket;
    std::string serverIp = "localhost"; // Example IP; replace with actual server IP
    unsigned short port = 5555; // Example port; replace with actual port

    Network() {
        socket.connect(serverIp, port);
    }

    std::string getP() {
        sf::Packet packet;
        packet << "get";
        if (socket.send(packet) == sf::Socket::Done) {
            if (socket.receive(packet) == sf::Socket::Done) {
                std::string response;
                packet >> response;
                return response;
            }
        }
        return "";
    }

    std::string send(const std::string& data) {
        sf::Packet packet;
        packet << data;
        if (socket.send(packet) == sf::Socket::Done) {
            if (socket.receive(packet) == sf::Socket::Done) {
                std::string response;
                packet >> response;
                return response;
            }
        }
        return "";
    }
};

int main() {
    // Create an instance of the Network class
    Network myNetwork;

    // Now you can use the instance to call member functions
    // Wait until a message is received
    while (true) {
        std::string message = myNetwork.getP();
        if (!message.empty()) {
            std::cout << "Something" << std::endl;
            break;
        }
        std::cout << "Test" << std::endl;
    }

}
