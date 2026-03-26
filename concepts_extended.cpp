#include <iostream>

// C++20 Concepts
template<typename T>
concept Arithmetic = std::integral<T>;

template<typename T>
concept Summarizer = std::integral<T> || std::floating_point<T>;

auto sum(Summarizer auto a, Summarizer auto b)
{
    return a + b;
}

// Global variable of type Summarizer
Summarizer auto g_x = 69.69f; // This will be a double

int main()
{
    {
        int lhs = 5;
        int rhs = 8;
        int result = 13;
        
        if (sum (lhs, rhs) != result)
        {
            std::cout << "Wrong 1: " << lhs << " + " << rhs << " != " << result << " (" << sum (lhs, rhs) << ")" << std::endl;
        }
    }

    {
        double lhs = 10.2f;
        double rhs = 12.6f;
        double result = 22.8;

        auto suma = sum(lhs, rhs);

        auto calculateDelta = [result, suma]() { 
            return fabs(result - suma); 
        };

        constexpr float maxTreshold = 0.0001f;

        if (calculateDelta() > maxTreshold)
        {
            std::cout << "Wrong 2: " << lhs << " + " << rhs << " != " << result << " (" << sum (lhs, rhs) << ")" << std::endl;
        }
    }

    {
        uint8_t lhs = 210u; 
        uint8_t rhs = 180u;
        uint16_t result = 390;
        
        if (sum (lhs, rhs) != result) 
        {
            std::cout << "Wrong 3: " << lhs << " + " << rhs << " != " << result << " (" << sum (lhs, rhs) << ")" << std::endl;
        }
    }

    {
        uint16_t lhs = 12210;
        uint8_t rhs = 180;
        uint16_t result = 12390;
        
        if (sum (lhs, rhs) != result)
        {
            std::cout << "Wrong 4: " << lhs << " + " << rhs << " != " << result << " (" << sum (lhs, rhs) << ")" << std::endl;
        }
    }

    {
        uint16_t rhs = 12210;
        uint8_t lhs = 180;
        uint16_t result = 12390;
        
        if (sum (lhs, rhs) != result)
        {
            std::cout << "Wrong 5: " << lhs << " + " << rhs << " != " << result << " (" << sum (lhs, rhs) << ")" << std::endl;
        }
    }
    return 0;
}