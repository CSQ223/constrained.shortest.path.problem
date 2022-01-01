#include <network/Node.h>


namespace network
{


Node::Node(
    const std::string& id, 
    const std::string& name
):
    id_( id ),
    name_( name )
{
}
    
    
Node::~Node()
{
}


const std::string& 
Node::GetId() const
{
    return id_;
}


const std::string& 
Node::GetName() const
{
    return name_;
}


}
