#pragma once
#pragma warning (disable : 4996)
#include "smartlogger.h"

const std::string SmartLogger::updatePrintSetting(const LogLevel& ll)
{
    std::ostringstream logMessage;
    if (ll >= LogLevel::RESET)
    {
        logMessage << "\033[0m";
    }
    else
    {
        auto log = mLogSettings[int(ll)];
        logMessage << "\033[1;" << std::to_string(log.color) << "m";
        logMessage << "[" << log.logLevelName << "]" << getDateAndTime() << ": ";
    }
    return logMessage.str();
}   

std::string SmartLogger::getDateAndTime()
{
    auto t_now = std::chrono::system_clock::now();  
    auto time_now = std::chrono::system_clock::to_time_t(t_now);
    std::ostringstream timestr;
    timestr << "[";
    timestr <<  std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S");
    timestr << "]";

    return timestr.str();
}

template<class... Args>
std::string SmartLogger::printHelper(const Args&... args)
{
    std::string fmt = "";
    constexpr int argLen = sizeof...(args);
    for(int i = 0; i < argLen; i++)
        fmt += "{}";
    return std::vformat(fmt, std::make_format_args(args...));
}

void SmartLogger::recordLogsIfNeeded(const std::string& logs)
{
    if(!mRecord) return;
    auto recorder = SafeRecorder::getInstance();
    recorder->log(logs);
}

template<class... Args>
void SmartLogger::Info(const Args&... args)
{
    std::ostringstream data;
    data << updatePrintSetting(LogLevel::INFO) << printHelper(args...)
                            << updatePrintSetting(LogLevel::RESET) << "\n";
    auto out = data.str();
    std::cout << out;
    recordLogsIfNeeded(out);
}

template<class... Args>
void SmartLogger::Debug(const Args&... args)
{
    std::ostringstream data;
    data << updatePrintSetting(LogLevel::DEBUG) << printHelper(args...)
                            << updatePrintSetting(LogLevel::RESET) << "\n";
    auto out = data.str();
    std::cout << out;
    recordLogsIfNeeded(out);
}

template<class... Args>
void SmartLogger::Warn(const Args&... args)
{
    std::ostringstream data;
    data << updatePrintSetting(LogLevel::WARN) << printHelper(args...)
                            << updatePrintSetting(LogLevel::RESET) << "\n";
    auto out = data.str();
    std::cout << out;
    recordLogsIfNeeded(out);
}

template<class... Args>
void SmartLogger::Error(const Args&... args)
{
    std::ostringstream data;
    data << updatePrintSetting(LogLevel::ERROR) << printHelper(args...)
                            << updatePrintSetting(LogLevel::RESET) << "\n";
    auto out = data.str();
    std::cout << out;
    recordLogsIfNeeded(out);
}

template<class... Args>
void SmartLogger::Fatal(const Args&... args)
{
    std::ostringstream data;
    data << updatePrintSetting(LogLevel::FATAL) << printHelper(args...)
                            << updatePrintSetting(LogLevel::RESET) << "\n";
    auto out = data.str();
    std::cout << out;
    recordLogsIfNeeded(out);
}

void SmartLogger::EnableRecord(bool record)
{
    mRecord = record;
}