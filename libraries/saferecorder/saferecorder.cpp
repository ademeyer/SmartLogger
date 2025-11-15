#include "saferecorder.h"

SafeRecorder::SafeRecorder(const std::string &fileName) : mLogFile(fileName, std::ios::app)
{
  if (!mLogFile.is_open())
  {
    throw std::runtime_error("Failed to open log file");
  }
}

SafeRecorder::~SafeRecorder()
{
  if (mLogFile.is_open())
  {
    mLogFile.close();
  }
}

void SafeRecorder::log(const std::string &message)
{
  mLogFile << message << std::endl;
}