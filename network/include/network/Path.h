#ifndef __NETWORK_PATH_H__
#define __NETWORK_PATH_H__


#include <string>
#include <map>
#include <network/Node.h>


namespace network
{


class Path
{
public:
    Path();
    ~Path();

private:
    std::map<int, std::string> node_list_;
};


}


#endif // __NETWORK_PATH_H__