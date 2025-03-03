#pragma once
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>

#define FileName "app_log.txt"
class SafeRecorder {
public:
    ~SafeRecorder();
    void log(const std::string&);
    static SafeRecorder* getInstance()
    {
        std::lock_guard<std::mutex> lock(mLogMutex);
        if(mInstance == nullptr)
        {
            mInstance = std::unique_ptr<SafeRecorder>(new SafeRecorder(FileName));
        }
        return mInstance.get();
    }
private:
    // delete copy constructor
    SafeRecorder(const SafeRecorder&) = delete;
    // delete assignment operator
    SafeRecorder& operator= (const SafeRecorder&) = delete;

    SafeRecorder(const std::string& fileName);

    static std::unique_ptr<SafeRecorder> mInstance;
    static std::mutex mLogMutex;
    std::ofstream mLogFile;
    
};