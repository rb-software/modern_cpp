#include <iostream>
#include <thread>
#include <optional>

std::queue<size_t> g_resource; // < Data resource

namespace generic_worker
{
    std::mutex g_mutex; // < Mutext to secure resource

    /**
     * @brief GeneralActivity class that operates with g_resource
     */
    class GenericActivity
    {
    public:
        /**
         * @brief Default constructor
         */
        GenericActivity() = delete;

        /**
         * @brief Constructor C++17 string_view
         */
        GenericActivity(const std::string_view& threadName) :
            m_running(true),
            m_liveCycle(0U),
            m_genericActivityThread(&GenericActivity::genericActivityWorker, this)
        {
            std::cout << std::endl << "Hello it's me: " << threadName;
        }
        
        /**
         * @brief Destructor
         */
        ~GenericActivity()
        {
            std::cout << std::endl << "My life time end's up !";

            m_running.store(false);
            if (m_genericActivityThread.joinable())
            {
                m_genericActivityThread.join();
            }
        }

    private:
        // Private methods
        void genericActivityWorker()
        {
            while (m_running.load())
            {
                if (m_liveCycle > k_lifeCycles)
                {
                    m_running.store(false);
                }

                std::cout << std::endl << "Line: " <<  __LINE__ << "; " << __func__ << " working... ";
                std::this_thread::sleep_for(std::chrono::seconds(1U));

                // Critical section
                {
                    std::lock_guard<std::mutex> lock(generic_worker::g_mutex);

                    // Core logic -> intercept and flush front queue element
                    if (not g_resource.empty())
                    {
                        std::cout << std::endl << "Captuerd data: " <<  g_resource.front();
                        g_resource.pop();
                    }
                }

                ++m_liveCycle;
            }
        }

        // private members section
        std::atomic<bool> m_running;
        std::thread m_genericActivityThread;

        // Worker life cycle parameters
        size_t m_liveCycle;
        const size_t k_lifeCycles = 10U;
    };
}

int main()
{
    const std::string threadName = "GenericThread"; // thread name/id
    auto ptr = std::make_unique<generic_worker::GenericActivity>(threadName);

    std::thread leadingActivity([](){
        const size_t k_maxSizeLimiter = 10U;

        // C++17 optional
        auto dataInterceptor = []() -> std::optional<size_t> {
            size_t data = rand() % SIZE_T_MAX;

            // Demultiplexing
            if (data%2)
            {
                return data;
            }
            else
            {
                return std::nullopt;
            }
        };

        while (true)
        {
            std::cout << std::endl << "Line: " << __LINE__ << "; " << __func__ << " working... ";
            std::this_thread::sleep_for(std::chrono::seconds(1U));
            
            // Incomming data capturing procedure
            auto data = dataInterceptor(); 

            // Critical section
            {
                std::lock_guard<std::mutex> lock(generic_worker::g_mutex);
                
                // Core logic leading of leading thread
                if (g_resource.size() == k_maxSizeLimiter)
                {
                    std::cout << std::endl << "Maximal queue size exceeded - thread termination!";
                    break;
                }
                else if (data.has_value())
                {
                    g_resource.emplace(*data);
                }
                else
                {
                    std::cout << std::endl << "Value has been not captured - interation skipping";
                    continue;
                }
            }
        }
    });

    leadingActivity.join();

    return 0;
}