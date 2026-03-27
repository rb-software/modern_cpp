#include <iostream>
#include <coroutine>

template<typename T>
struct Generator
{
    struct promise_type
    {
        T current_value;

        std::suspend_always yield_value(T value)
        {
            current_value = value;
            return {};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        Generator get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    bool next()
    {
        handle.resume();
        return !handle.done();
    }

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { handle.destroy(); }

    T get() const { return handle.promise().current_value; }

    std::coroutine_handle<promise_type> handle;
};

Generator<int> producer()
{
    for (int i=0; i<5; ++i)
    {
        std::cout << "Producing value: " << i << std::endl;
        co_yield i;
    }
}

int main()
{
    std::cout << "Hello, Coroutines!" << std::endl;

    auto gen = producer();

    while (gen.next())
    {
        int value = gen.get();
        std::cout << "Consuming value: " << value << std::endl;
    }

    return 0;
}