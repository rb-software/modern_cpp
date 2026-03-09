#include <iostream>
#include <memory>

int main()
{
    auto deleter = [](FILE* file)
    {
        if (file)
        {
            std::cout << std::endl << "Custom shared_ptr deleter";
            fclose(file);
        }
    };

    std::shared_ptr<FILE> ptr(fopen("text.txt", "r"), deleter);

    return 0;
}