#include <thread>
#include <functional>
#include <iostream>
#include "periodicTimer.h"



periodicTimer::periodicTimer(int interval, std::function<void()> func) : _execute(true)
    {
        //std::cout << "ran2"<<std::endl;
        m_pThread = std::make_unique<std::thread>([this, interval, func]()
        {
            //std::cout << "ran3"<<std::endl;
            while (_execute.load(std::memory_order_acquire))
            {
            func();
            //std::cout << "ran4"<<std::endl;
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
