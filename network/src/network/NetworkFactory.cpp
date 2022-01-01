#include <fstream>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include <network/Network.h>


namespace network
{


std::shared_ptr<Network>
Network::Factory(const std::string& network_file_name)
{
    nlohmann::json network_json;

    std::fstream network_json_file(network_file_name, std::ios::in);
    network_json_file >> network_json;

    std::shared_ptr<Network> network = std::make_shared<Network>(network_json["network"]);

    network->time_limit_ = network_json["time-limit"];

    auto network_edge_list = network_json["edge-list"];
    for (auto edge: network_edge_list)
    {
        network->PushEdge(
            std::make_shared<Edge>(
                fmt::format("{}-{}", edge["source_id"], edge["target_id"]),
                fmt::format("{}-{}", edge["source_id"], edge["target_id"]),
                edge["source_id"], 
                edge["target_id"], 
                edge["distance"].get<double>(), 
                edge["travel_time"].get<double>()
            )
        );
    }

    return network;
}


} // namespace network
