#ifndef __NETWORK_NETWORK_H__
#define __NETWORK_NETWORK_H__


#include <string>
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <limits>


#include <network/Node.h>
#include <network/Edge.h>


namespace network
{


class Network
{
public:
    static constexpr double EPS = 10E-6;

public:
    Network(const std::string& id);
    ~Network();

    static std::shared_ptr<Network>
    Factory(const std::string& network_json);

    std::pair<std::list<std::string>, double> 
    Dijkstra(
        const std::string& source, 
        const std::string& target, 
        double lambda,
        double coeff_dist = 1
    ) const;

    std::pair<std::list<std::string>, double> 
    LagrangianRelaxation(
        const std::string& source, 
        const std::string& target
    ) const;

    void PushEdge(std::shared_ptr<Edge> edge);

    const std::string& GetId() const;
    std::shared_ptr<Node> GetNodeById(const std::string& node) const;
    std::shared_ptr<Edge> GetEdgeById(const std::string& edge) const;

public:
    void BuildAdjacenciesList();

    std::list<std::string> ParsePath(
        const std::map<std::string, std::string>& prev, 
        const std::string& source, 
        const std::string& target
    ) const;

    double GetCostOfPath(
        const std::list<std::string>& path, 
        double coeff_dist, 
        double coeff_time
    ) const;

private:
    std::string id_;
    std::map<std::string, std::shared_ptr<Node>> nodes_list_;
    std::map<std::string, std::shared_ptr<Edge>> edges_list_;

    double time_limit_ = std::numeric_limits<double>::infinity();

private:
    std::map<std::string, std::list<std::shared_ptr<Edge>>> adjacencies_list_;
};


} // namespace network


#endif // __NETWORK_NETWORK_H__