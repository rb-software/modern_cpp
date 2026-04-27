#include <iostream>
#include <map>

int main()
{
    std::map<int, int> mymap;
    
    if (mymap[5]) // allocate element 
    {
        std::cout << std::endl << __LINE__ << " map[5]: " << mymap[5] << std::endl;
    }

    for (const auto [key, val] : mymap)
    { 
        std::cout << std::endl << __LINE__ <<  " key: " << key << " val: " << val << std::endl;
    }
    
    if (mymap.at(4)) // not allocate element -> throws excpetion
    {
        std::cout << std::endl << __LINE__ << " map.at(4): " << mymap.at(4) << std::endl;
    }
    for (const auto [key, val] : mymap)
    {
        std::cout << std::endl << __LINE__ <<  " key: " << key << " val: " << val << std::endl;
    }

    return 0;
}