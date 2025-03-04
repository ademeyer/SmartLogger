#ifndef __SMARTLOGGER_H__
#define __SMARTLOGGER_H__
#include <array>
#include <iostream>
#include <format>
#include <sstream>
#include <string_view>
#include <chrono>
#include "saferecorder.h"

// Initialize static members
std::unique_ptr<SafeRecorder> SafeRecorder::mInstance;
std::mutex SafeRecorder::mLogMutex;

/*
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47


reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27

*/

enum class LogLevel {
    INFO,
    DEBUG,
    WARN,
    ERROR,
    FATAL,
    RESET
};

struct LogStat
{
    const std::string logLevelName;
    int color;
};

class SmartLogger
{
public:
    void EnableRecord(bool record);
    template<class... Args>
    void Info(const Args&... args);
    template<class... Args>
    void Debug(const Args&... args);
    template<class... Args>
    void Warn(const Args&... args);
    template<class... Args>
    void Error(const Args&... args);
    template<class... Args>
    void Fatal(const Args&... args);

private:
    //const SafeRecorder* mRecorder = SafeRecorder::getInstance();
    const std::array<LogStat, 5> mLogSettings{
        LogStat({std::string("INFO"), 32}),
        LogStat({std::string("DEBUG"), 37}),
        LogStat({std::string("WARN"), 33}),
        LogStat({std::string("ERROR"), 31}),
        LogStat({std::string("FATAL"), 31}),
    };
    template<class... Args>
    std::string printHelper(const Args&... args);
    const std::string updatePrintSetting(const LogLevel&);
    std::string getDateAndTime();
    void recordLogsIfNeeded(const std::string&);
    bool mRecord;
};

// This is manually include because linker error with template class
#include "smartlogger.cpp"
#endif