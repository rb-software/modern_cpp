#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>


std::queue<std::string> data_queue;
std::mutex mtx;
std::condition_variable_any cv;

void producer(std::stop_token token)
{
    std::cout << "Producer is producing data..." << std::endl;

    for (size_t i=0; i<10; ++i)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::string item = "Item " + std::to_string(i);
            data_queue.push(item);
        }

        cv.notify_one();

        if (token.stop_requested())
        {
            std::cout << "Producer received stop request. Stopping production." << std::endl;
            break;
        }
    }

    cv.notify_all();

    std::cout << "Producer has stopped producing." << std::endl;
}

void consumer(std::stop_token token)
{
    std::cout << "Consumer is consuming data..." << std::endl;

    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, token, []{
            return !data_queue.empty();});
            
        if (token.stop_requested() && data_queue.empty())
        {
            std::cout << "Consumer received stop request. Stopping consumption." << std::endl;
            break;
        }

        if (!data_queue.empty())
        {
            std::string item = data_queue.front();
            data_queue.pop();
            lock.unlock(); // Unlock before processing the item
            std::cout << "Consuming: " << item << std::endl;
        }
    }

    std::cout << "Consumer has stopped consuming." << std::endl;
}

int main()
{
    std::jthread producer_thread(producer);
    std::jthread consumer_thread(consumer);

    //producer_thread.join();
    //consumer_thread.request_stop(); // Request the consumer to stop after the producer is done

    return 0;
}