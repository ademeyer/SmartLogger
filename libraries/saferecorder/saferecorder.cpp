#pragma warning (disable : 4996)

#include "saferecorder.h"

SafeRecorder::SafeRecorder(const std::string& fileName) : mLogFile(fileName, std::ios::app)
{
    if(!mLogFile.is_open())
    {
        throw std::runtime_error("Failed to open log file");
    }
}

SafeRecorder::~SafeRecorder()
{
    if(mLogFile.is_open())
    {
        mLogFile.close();
    }
}


void SafeRecorder::log(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mLogMutex);
    auto t_now = std::chrono::system_clock::now();  
    auto time_now = std::chrono::system_clock::to_time_t(t_now);
    mLogFile << "[" << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S") << "]: " << message << std::endl;
}