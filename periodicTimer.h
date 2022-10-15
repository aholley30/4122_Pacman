#include <thread>
#include <functional>
#include <atomic>

class periodicTimer
{
public:
    //bool updateRequired;
    periodicTimer();
    void start(int interval, std::function<void()> func);

    ~periodicTimer();

private:
    std::atomic<bool> _execute;
    std::unique_ptr<std::thread> m_pThread;
};
