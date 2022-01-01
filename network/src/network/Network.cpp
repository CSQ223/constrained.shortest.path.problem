#include <fmt/format.h>

#include <network/Network.h>


namespace network
{


Network::Network(const std::string& id)
:
    id_( id )
{
}


Network::~Network()
{
}


void Network::PushEdge(std::shared_ptr<Edge> edge)
{
    auto source_id = edge->GetSourceId();
    auto target_id = edge->GetTargetId();
    auto edge_id = fmt::format("{0}-{1}", source_id, target_id);

    // 1. 添加 Node
    if (nodes_list_.find(source_id) == nodes_list_.cend())
    {
        nodes_list_.insert({
            source_id, 
            std::make_shared<Node>(source_id, source_id)
        });
    }

    if (nodes_list_.find(target_id) == nodes_list_.cend())
    {
        nodes_list_.insert({
            target_id, 
            std::make_shared<Node>(target_id, target_id)
        });
    }

    // 2. 添加 Edge
    if (edges_list_.find(edge_id) == edges_list_.cend())
    {
        edges_list_.insert({
            edge_id,
            edge
        });
    }
}


const std::string& Network::GetId() const
{
    return id_;
}


std::shared_ptr<Node> Network::GetNodeById(const std::string& node) const
{
    if (nodes_list_.find(node)!= nodes_list_.cend()) 
        nodes_list_.at(node);

    return nullptr;
}


std::shared_ptr<Edge> Network::GetEdgeById(const std::string& edge) const
{
    if (edges_list_.find(edge)!= edges_list_.cend()) 
        edges_list_.at(edge);
        
    return nullptr;
}


void Network::BuildAdjacenciesList()
{
    for (auto& [node_id, _]: nodes_list_)
    {
        adjacencies_list_.insert({
            node_id, {}
        });
    }

    for (auto& [_, edge]: edges_list_)
    {
        adjacencies_list_[edge->GetSourceId()].push_back(edge);
    }
}


} // namespace network
