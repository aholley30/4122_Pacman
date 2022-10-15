#include <thread>
#include <functional>
#include <iostream>
#include "periodicTimer.h"

periodicTimer::periodicTimer() :_execute(true) {}

void periodicTimer::start(int interval, std::function<void()> func)
    {
        m_pThread = std::make_unique<std::thread>([this, interval, func]()
        {
            while (_execute.load(std::memory_order_acquire))
            {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }
        });
    }

periodicTimer::~periodicTimer()
    {
        //std::cout << "destroyed" << std::endl;
        _execute.store(false, std::memory_order_release);
        if (m_pThread->joinable())
            m_pThread->join();
    }
