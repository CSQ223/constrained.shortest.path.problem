
#include <queue>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <network/Network.h>


namespace network
{


struct __Label_
{
    std::string node_id;
    std::string prev;
    double dist;
    double time;
};


static bool operator < (const __Label_& lhs, const __Label_& rhs)
{
    return (rhs.dist -lhs.dist) <= Network::EPS;
}

std::pair<std::list<std::string>, double> 
Network::LabelSetting(
    const std::string& source, 
    const std::string& target
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
    std::map<std::string, double> min_dist;
    for (auto& [node_id, _]: nodes_list_)
    {
        min_dist.insert({
            node_id,
            std::numeric_limits<double>::infinity()
        });
    }

    // 初始化
    std::priority_queue<__Label_> labels_pool;
    min_dist[source] = 0.0;
    labels_pool.push({source, source, min_dist[source], 0});

    // Label Setting
    while (!labels_pool.empty())
    {
        // 取出堆顶元素
        auto [cur_node, prev_node, cur_dist, cur_time] = labels_pool.top();
        labels_pool.pop();
        // fmt::print("cur node = {}, min dist = {}, cur time = {}\n", cur_node, min_dist[cur_node], cur_time);
        
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
            double dist_to_next = neighbor->GetDistance();
            double time_to_next = neighbor->GetTravelTime();
            // fmt::print("temp {0} {1}\n", next_id, cost + cost_to_next);
            if ((!is_settled[next_id]) && 
                (cur_time + time_to_next <= time_limit_) &&
                (cur_dist + dist_to_next <= min_dist[next_id]))
            {
                min_dist[next_id] = cur_dist + dist_to_next;
                labels_pool.push({next_id, cur_node, min_dist[next_id], cur_time + time_to_next});
                // fmt::print("next node = {}, current min dist = {}\n", next_id, min_dist[next_id]);
            }
        }
    }

    return {ParsePath(prev, source, target), min_dist[target]};
}


} // namespace network
