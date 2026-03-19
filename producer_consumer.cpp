#include <iostream>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<std::string> data_queue;
bool g_finished{false};

void producer()
{
    std::cout << std::endl << "Producing data..." << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        std::string item = "Item " + std::to_string(i);
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "-> Produced " << item << std::endl;
            data_queue.push(item);
        }
        cv.notify_one();
    }
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        g_finished = true;
    }
    cv.notify_one();
}

void consumer()
{
    std::cout << std::endl << "Consuming data..." << std::endl;

    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !data_queue.empty() || g_finished; });

        if (!data_queue.empty())
        {
            std::string item = data_queue.front();
            data_queue.pop();
            std::cout << "Consumed " << item << std::endl;
        }
        else if (g_finished)
        {
            break; // No more items will be produced
        }
    }
}

int main()
{
    std::jthread producer_thread(producer);
    std::jthread consumer_thread(consumer);

    return 0;
}
