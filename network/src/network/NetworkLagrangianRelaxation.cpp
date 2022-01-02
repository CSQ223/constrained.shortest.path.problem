
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <network/Network.h>


namespace network
{


double 
Network::GetCostOfPath(
    const std::list<std::string>& path, 
    double coeff_dist, 
    double coeff_time
) const
{
    double time = 0;

    std::string source = path.front();
    
    for (auto iter = ++path.cbegin(); iter!=path.cend(); iter++)
    {
        std::string target = *iter;
        auto edge_id = fmt::format("{0}-{1}", source, target);
        time += edges_list_.at(edge_id)->GetCost(coeff_time, coeff_dist);
        source = target;
    }

    return time;
}


std::pair<std::list<std::string>, double> 
Network::LagrangianRelaxation(
    const std::string& source, 
    const std::string& target
) const
{
    auto [path, time] = Dijkstra(source, target, 1, 0);
    if (time > time_limit_) 
        return {{}, std::numeric_limits<double>::infinity()};

    double lambda = 0;
    double delta = 1;
    double lower_bound = -std::numeric_limits<double>::infinity();
    std::list<std::string> best_path = path;
    double upper_bound = GetCostOfPath(path, 1, 0);

    fmt::print("iter UB      LB    lambda  delta best_path\n");

    for (int iter = 1; delta >= EPS && (upper_bound-lower_bound) / upper_bound >= EPS; iter++)
    {
        auto [path, cost] = Dijkstra(source, target, lambda);
        double time = GetCostOfPath(path, 0, 1);

        if ((cost - lambda * time_limit_) >= lower_bound)
        {
            // 更新下界
            lower_bound = (cost - lambda*time_limit_);
            
            // 检查可行性
            if (time <= time_limit_)
            {
                // 更新上界
                best_path = path;
                upper_bound = GetCostOfPath(best_path, 1, 0);
            }
        }
        delta = 1.0 / (iter+1);
        lambda = std::max(0.0, lambda + delta*(time - time_limit_));
        fmt::print("{0:4d} {1:>6.3f} {2:>6.3f} {3:>6.3f} {4:>6.3f} {5}\n", iter, upper_bound, lower_bound, lambda, delta, best_path);
    }

    return {best_path, upper_bound};
}


} // namespace network
