#ifndef __NETWORK_NODE_H__
#define __NETWORK_NODE_H__


#include <string>


namespace network
{


class Node
{
public:
    Node(
        const std::string& id, 
        const std::string& name
    );
    
    ~Node();

    const std::string& GetId() const;

    const std::string& GetName() const;

private:
    std::string id_;
    std::string name_;
};


} // namespace network


#endif // __NETWORK_NODE_H__