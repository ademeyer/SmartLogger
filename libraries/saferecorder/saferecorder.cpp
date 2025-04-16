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
    mLogFile << message << std::endl;
}