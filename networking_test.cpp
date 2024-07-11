#include <iostream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;
using json = nlohmann::json;

class Network {
public:

    boost::asio::io_service io_service;
    tcp::socket socket;
    std::string server;
    int port;
    std::string p;

    Network(const std::string& server, int port) : io_service(), socket(io_service), server(server), port(port) {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(server, std::to_string(port));
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::connect(socket, endpoint_iterator);
        std::cout << "Connected to server" << std::endl;
        p = readResponse();
    }

    std::string getP() {return p;}

    std::string send(const std::string& data) {
        boost::asio::write(socket, boost::asio::buffer(data));
        return readResponse();
    }

    std::string readResponse() {
        boost::asio::streambuf response;
        boost::system::error_code error;
        boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error);
        std::istream response_stream(&response);
        std::string response_str((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());
        // std::cout << "Response: " << response_str << std::endl;
        return response_str;
    }

};

void mainLoop(Network& network, int player) {
        bool turn = 0;
        while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 FPS


        std::string game_data = network.send(json("get").dump());


        auto game = json::parse(game_data);

        if (game["bothConnected"].get<bool>()) {
            if ((player == 0 && game["player1"].get<bool>()) || (player == 1 && game["player2"].get<bool>())) {
                std::cout << "New Board: " << game["board"].get<std::string>() << std::endl;
                std::cout << "New Time: " << game["time"].get<int>() << std::endl;
                std::string move;
                if (player == 0 && turn == 0) move = "G7-H7";
                else if (player == 0 && turn == 1) move = "H7-G7";
                else if (player == 1 && turn == 0) move = "G2-H2";
                else if (player == 1 && turn == 1) move = "H2-G2";
                
                
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "Sent move: " << move << " Player: " << player << " Turn: " << turn << std::endl;
                network.send(json(move).dump());
                turn = !turn;
            }
        }

        }
}

int main() {
    Network network("localhost", 5555);
    int player = std::stoi(network.getP());
    std::cout << "You are player " << player << std::endl;

    mainLoop(network, player);


    return 0;
}