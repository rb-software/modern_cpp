#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 2, 3, 2};
    int k = 2;
    
    std::map<int, int> frequency;

    std::sort(vec.begin(), vec.end());

    int currentMax = 0;

    for (size_t i = 0; i < vec.size(); ++i)
    {
        frequency[vec[i]]++;

        if (currentMax < frequency[vec[i]])
        {
            currentMax = frequency[vec[i]];
            k = vec[i];
        }
    }

    for (auto x : frequency)
    {
        std::cout << std::endl << "Record: " << x.first  << " " << x.second;
    }

    std::cout << std::endl << "k: " << k << ", frequency: " << currentMax;

    return 0;
}