#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <sstream>
#include "smartlogger.h"
#include "saferecorder.h"

// Initialize static members
std::unique_ptr<SafeRecorder> SafeRecorder::mInstance;
std::mutex SafeRecorder::mLogMutex;

int main()
{
    std::cout << "******************************************* Test Saferecorder *******************************************\n";
    auto workerThread = [](SafeRecorder& logger, int threadID)
    {
        for(int i = 0; i < 5; i++)
        {
            std::ostringstream logMessage;
            logMessage << "Thread " << threadID << " -log entry " << i;
            logger.log(logMessage.str());
            // wait for 100ms before logging next message
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    auto sr = SafeRecorder::getInstance();
    // create many workerThread
    std::vector<std::thread> threads;
    for(int k = 0; k < 10; k++)
    {
        threads.emplace_back(workerThread, std::ref(*sr), k+1);
    }

    // wait for thread to finish
    for(auto& t : threads)
    {
        t.join();
    }

    std::cout << "***************************************** End Test Saferecorder *****************************************\n\n";
    
    
    std::cout << "******************************************* Test Smartlogger *******************************************\n";
    SmartLogger sm;
    SmartLogger<int> logger2;
    int num = 7;
    sm.Info("This is Info");
    sm.Debug("This is Debug");
    sm.Warn("This is Warn");
    sm.Error("This is Error");
    sm.Fatal("This is Fatal");
    std::cout << "***************************************** End Test Smartlogger *****************************************\n\n";
    
    return 0;
}