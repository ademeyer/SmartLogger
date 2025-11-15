#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <sstream>
#include "smartlogger.h"

int main()
{

  std::cout << "******************************************* Test Smartlogger *******************************************\n";
  auto workerThread = [](int taskCount)
  {
    SmartLogger logger;
    logger.EnableRecord(true);
    std::ostringstream logMessage;
    logMessage << "Thread Logger ID: " << taskCount << " -This is a Test ";
    logger.Info(logMessage.str(), "Info ", 0);
    logger.Debug(logMessage.str(), "Debug ", 1);
    logger.Warn(logMessage.str(), "Warn ", 2);
    logger.Error(logMessage.str(), "Error ", 3);
    logger.Fatal(logMessage.str(), "Fatal ", 4);
  };

  // create many workerThread
  std::vector<std::thread> threads;
  for (int k = 0; k < 10000; k++)
  {
    threads.emplace_back(workerThread, k + 1);
  }

  // wait for thread to finish
  for (auto &t : threads)
  {
    t.join();
  }

  std::cout << "***************************************** End Test Smartlogger *****************************************\n\n";

  return 0;
}