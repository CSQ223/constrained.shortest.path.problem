#include <network/Edge.h>


namespace network
{


Edge::Edge(
    const std::string& id,
    const std::string& name,
    const std::string& source_id,
    const std::string& target_id,
    double distance,
    double travel_time
):
    id_( id ),
    name_( name ),
    source_id_( source_id ),
    target_id_( target_id ),
    distance_( distance ),
    travel_time_( travel_time )
{
}


Edge::~Edge()
{
}


const std::string& 
Edge::GetId() const
{
    return id_;
}


const std::string& 
Edge::GetName() const
{
    return name_;
}


const std::string& 
Edge::GetSourceId() const
{
    return source_id_;
}


const std::string& 
Edge::GetTargetId() const
{
    return target_id_;
}


double 
Edge::GetDistance() const
{
    return distance_;
}


double 
Edge::GetTravelTime() const
{
    return travel_time_;
}


double 
Edge::GetCost(double coeff_time, double coeff_dist) const
{
    return coeff_dist * GetDistance() + coeff_time * GetTravelTime();
}


}
