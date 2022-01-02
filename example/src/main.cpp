#include <network/Network.h>
#include <fmt/format.h>
#include <fmt/ranges.h>


int 
main(int argc, char* args[])
{
    if (argc < 4)
    {
        fmt::print("[Usage:] ./program instance-file source-node target-node\n");
    }
    else
    {
        auto network = network::Network::Factory(args[1]);
        network->BuildAdjacenciesList();

        // Lagrangian Relaxation
        auto [path, min_cost] = network->LagrangianRelaxation(args[2], args[3]);
        fmt::print("Lagrangian Relaxation: path = {}, cost = {}\n", path, min_cost);

        // Label Setting
        std::tie(path, min_cost) = network->LabelSetting(args[2], args[3]);
        fmt::print("Label Setting: path = {}, cost = {}\n", path, min_cost);
    }

    return 0;
}
