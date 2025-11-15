#pragma once
#pragma warning(disable : 4996)
#include "smartlogger.h"

const std::string SmartLogger::updatePrintSetting(const LogLevel &ll)
{
  std::ostringstream logMessage;
  if (ll >= LogLevel::RESET)
  {
    logMessage << "\033[0m";
  }
  else
  {
    auto log = mLogSettings[static_cast<int>(ll)];
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
  timestr << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S");
  timestr << "]";

  return timestr.str();
}

template <typename... Args>
void SmartLogger::printHelper(const LogLevel &loglevel, Args &&...args)
{
  std::string fmt;
  constexpr int argLen = sizeof...(args);
  for (int i = 0; i < argLen; ++i)
    fmt += "{}";
  std::ostringstream data;
  data << updatePrintSetting(loglevel) << std::vformat(fmt, std::make_format_args(args...))
       << updatePrintSetting(LogLevel::RESET) << "\n";

  std::cout << data.str();

  recordLogsIfNeeded(data.str());
}

void SmartLogger::recordLogsIfNeeded(const std::string &logs)
{
  if (!mRecord)
    return;
  std::lock_guard<std::mutex> lock(mLogMutex);
  auto recorder = SafeRecorder::getInstance();
  recorder->log(logs);
}

template <typename... Args>
void SmartLogger::Info(Args &&...args)
{
  printHelper(LogLevel::INFO, args...);
}

template <typename... Args>
void SmartLogger::Debug(Args &&...args)
{
  printHelper(LogLevel::DEBUG, args...);
}

template <typename... Args>
void SmartLogger::Warn(Args &&...args)
{
  printHelper(LogLevel::WARN, args...);
}

template <typename... Args>
void SmartLogger::Error(Args &&...args)
{
  printHelper(LogLevel::ERROR, args...);
}

template <typename... Args>
void SmartLogger::Fatal(Args &&...args)
{
  printHelper(LogLevel::FATAL, args...);
}

void SmartLogger::EnableRecord(bool record)
{
  mRecord = record;
}