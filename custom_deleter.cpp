#include <iostream>
#include <memory>

struct FileCloser
{
    void operator()(FILE* file) const
    {
        if (file)
        {
            std::cout << std::endl << "Custom deleter - operator";
            fclose(file);
        }
    }
};

int main(void)
{
    std::unique_ptr<FILE, FileCloser> file_a(fopen("test_a.txt", "r"));

    auto deleter = [](FILE* file){
        if (file)
        {
            std::cout << std::endl << "Custom deleter - lambda";
            fclose(file);
        }
    };

    std::unique_ptr<FILE, decltype(deleter)> file_b(fopen("test_b.txt", "r"));

    return 0;
}