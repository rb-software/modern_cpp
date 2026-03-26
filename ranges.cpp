#include    <iostream>
#include    <ranges>
#include    <vector>
#include    <algorithm>

int main()
{
    std::vector<int> vec{5, 4, 3, 2, 1};
    std::ranges::sort(vec);

    auto range = vec | std::views::filter([](int i){ return i % 2 == 0; })
                    | std::views::transform([](int i){ return i * 10; });

    for (int i : range)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    return 0;
}