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
        auto [path, min_cost] = network->LagrangianRelaxation(args[2], args[3]);
        fmt::print("path = {}, cost = {}\n", path, min_cost);
    }

    return 0;
}
