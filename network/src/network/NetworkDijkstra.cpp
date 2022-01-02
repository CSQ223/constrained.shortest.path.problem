
#include <queue>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <network/Network.h>


namespace network
{


struct Label_
{
    std::string node_id;
    std::string prev;
    double cost;
};


static bool operator < (const Label_& lhs, const Label_& rhs)
{
    return (rhs.cost -lhs.cost) <= Network::EPS;
}

std::pair<std::list<std::string>, double> 
Network::Dijkstra(
    const std::string& source, 
    const std::string& target, 
    double lambda,
    double coeff_dist
) const
{
    // 用于记录路径
    std::map<std::string, std::string> prev;

    // 标记是否寻找到最短路
    std::map<std::string, bool> is_settled;
    for (auto& [node_id, _]: nodes_list_)
    {
        is_settled.insert({
            node_id,
            false
        });
    }
    
    // 标记最小成本
    std::map<std::string, double> min_cost;
    for (auto& [node_id, _]: nodes_list_)
    {
        min_cost.insert({
            node_id,
            std::numeric_limits<double>::infinity()
        });
    }

    // 初始化
    std::priority_queue<Label_> labels_pool;
    min_cost[source] = 0.0;
    labels_pool.push({source, source,min_cost[source]});

    // Label Setting
    while (!labels_pool.empty())
    {
        // 取出堆顶元素
        auto [cur_node, prev_node, cost] = labels_pool.top();
        labels_pool.pop();
        // fmt::print("cur node = {}, min cost = {}\n", cur_node, min_cost[cur_node]);
        
        // 更新
        is_settled[cur_node] = true;
        prev[cur_node] = prev_node;
        // 扩展到目的点
        if (cur_node == target) break;
        // fmt::print("cost = {}\n", cost);

        // 扩展
        auto& neighbors = adjacencies_list_.at(cur_node);
        int i = 0;
        for (auto& neighbor: neighbors)
        {
            // fmt::print("cost = {} , i = {}\n", cost, i++);
            std::string next_id = neighbor->GetTargetId();
            double cost_to_next = neighbor->GetCost(lambda, coeff_dist);
            // fmt::print("temp {0} {1}\n", next_id, cost + cost_to_next);
            if ((!is_settled[next_id]) &&
                (cost + cost_to_next < min_cost[next_id]))
            {
                min_cost[next_id] = cost + cost_to_next;
                labels_pool.push({next_id, cur_node, min_cost[next_id]});
                // fmt::print("next node = {}, current min cost = {}\n", next_id, min_cost[next_id]);
            }
        }
    }

    return {ParsePath(prev, source, target), min_cost[target]};
}


std::list<std::string> 
Network::ParsePath(
    const std::map<std::string, std::string>& prev, 
    const std::string& source, 
    const std::string& target
) const
{
    std::list<std::string> path;

    if (prev.find(target) == prev.cend()) 
        throw std::runtime_error("Network::ParsePath(): Parse Path Error");

    std::string cur_node = target;
    while (path.front() != source) 
    {
        path.push_front(cur_node);
        cur_node = prev.at(cur_node);

        if (prev.find(cur_node) == prev.cend()) 
            throw std::runtime_error("Network::ParsePath(): Parse Path Error");
    }

    return path;
}


} // namespace network
