#pragma once
#pragma warning(disable : 4996)
#include "smartlogger.h"

const std::string SmartLogger::updatePrintColor(const LogLevel &ll) const
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
  }
  return logMessage.str();
}

std::string SmartLogger::getLogName(const LogLevel &ll) const
{
  auto idx = static_cast<int>(ll);
  if (idx < 0 || idx >= static_cast<int>(mLogSettings.size()))
    return "UNKNOWN";
  auto log = mLogSettings[idx];
  return log.logLevelName;
}

std::string SmartLogger::getDateAndTime() const
{
  auto t_now = std::chrono::system_clock::now();
  auto time_now = std::chrono::system_clock::to_time_t(t_now);
  std::ostringstream timestr;
  timestr << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S");
  return timestr.str();
}

template <typename... Args>
void SmartLogger::printHelper(const LogLevel &loglevel, Args &&...args)
{
  static_assert(sizeof...(args) > 0, "No log arguments provided");
  // Take mutex
  std::lock_guard<std::mutex> lock(mLogMutex);
  std::string fmt;
  constexpr int argLen = sizeof...(args);
  for (int i = 0; i < argLen; ++i)
    fmt += "{}";

  std::string plainLog;
  plainLog = "[" + getLogName(loglevel) + "]" + "\t[" + getDateAndTime() + "]:\t\t" +
             std::vformat(fmt, std::make_format_args(args...));

  std::ostringstream data;
  data << updatePrintColor(loglevel)
       << plainLog
       << updatePrintColor(LogLevel::RESET)
       << std::endl;

  std::cout << data.str();

  try
  {
    recordLogsIfNeeded(plainLog);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
}

void SmartLogger::recordLogsIfNeeded(const std::string &logs)
{
  if (!mRecord)
    return;
  auto recorder = SafeRecorder::getInstance();
  if (!recorder)
    throw std::runtime_error("Saferecorder instance returned a NULL \n");
  recorder->log(logs);
}

template <LogArgs... Args>
void SmartLogger::Info(Args &&...args)
{
  printHelper(LogLevel::INFO, args...);
}

template <LogArgs... Args>
void SmartLogger::Debug(Args &&...args)
{
  printHelper(LogLevel::DEBUG, args...);
}

template <LogArgs... Args>
void SmartLogger::Warn(Args &&...args)
{
  printHelper(LogLevel::WARN, args...);
}

template <LogArgs... Args>
void SmartLogger::Error(Args &&...args)
{
  printHelper(LogLevel::ERROR, args...);
}

template <LogArgs... Args>
void SmartLogger::Fatal(Args &&...args)
{
  printHelper(LogLevel::FATAL, args...);
}

void SmartLogger::EnableRecord(bool record)
{
  mRecord = record;
}