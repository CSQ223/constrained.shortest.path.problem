#ifndef __NETWORK_EDGE_H__
#define __NETWORK_EDGE_H__


#include <string>


namespace network
{


class Edge
{
public:
    Edge(
        const std::string& id,
        const std::string& name,
        const std::string& source_id,
        const std::string& target_id,
        double distance,
        double travel_time
    );
    
    ~Edge();

    const std::string& GetId() const;

    const std::string& GetName() const;

    const std::string& GetSourceId() const;

    const std::string& GetTargetId() const;

    double GetDistance() const;

    double GetTravelTime() const;

    double GetCost(double coeff_time, double coeff_dist = 1) const;

private:
    std::string id_;
    std::string name_;
    std::string source_id_;
    std::string target_id_;
    double distance_;
    double travel_time_;
};


} // namespace network


#endif // __NETWORK_EDGE_H__