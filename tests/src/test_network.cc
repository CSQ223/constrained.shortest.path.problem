#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"


#include <Network.h>


using namespace network;


TEST_CASE("[test] network::Node") {
    std::string node_id{"node-id"};
    std::string node_name{"node-name"};

    Node node{node_id, node_name};
    
    CHECK(node_id == node.GetId());
    CHECK(node_name == node.GetName());
}


TEST_CASE("[test] network::Edge") {
    std::string edge_id{"edge-id"};
    std::string edge_name{"edge-name"};
    std::string edge_source_node_id{"edge_source_node_id"};
    std::string edge_target_node_id{"edge_target_node_id"};

    Edge edge{
        edge_id, 
        edge_name, 
        edge_source_node_id, 
        edge_target_node_id, 
        10, 
        1.2
    };

    CHECK(edge_id == edge.GetId());
    CHECK(edge_name == edge.GetName());
    CHECK(edge_source_node_id == edge.GetSourceId());
    CHECK(edge_target_node_id == edge.GetTargetId());
    CHECK(10 == edge.GetDistance());
    CHECK(edge.GetTravelTime() == doctest::Approx(1.2).epsilon(10E-6));
    CHECK(edge.GetCost(10) == doctest::Approx(22).epsilon(10E-6));
}


TEST_CASE("[test] network::factory") {
    auto network = network::Network::Factory("./instance/network-6.json");
    CHECK("network-6" == network->GetId());
}
