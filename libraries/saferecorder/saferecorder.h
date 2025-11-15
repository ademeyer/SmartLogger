#ifndef __SAFERECORDER_H_
#define __SAFERECORDER_H_
#include <thread>
#include <fstream>
#include <iomanip>
#include <memory>

#define FileName "../../../app_log.txt"
class SafeRecorder
{
public:
  ~SafeRecorder();
  void log(const std::string &);
  static SafeRecorder *getInstance()
  {
    if (mInstance == nullptr)
    {
      mInstance = std::unique_ptr<SafeRecorder>(new SafeRecorder(FileName));
    }
    return mInstance.get();
  }

private:
  // delete copy constructor
  SafeRecorder(const SafeRecorder &) = delete;
  // delete move constructor
  SafeRecorder(SafeRecorder &&) = delete;
  // delete copy assignment operator
  SafeRecorder &operator=(const SafeRecorder &) = delete;
  // delete move assignment operator
  SafeRecorder &operator=(SafeRecorder &&) = delete;
  // delete swap/copy assignment operator
  SafeRecorder &operator=(SafeRecorder) = delete;

  SafeRecorder(const std::string &fileName);

  static std::unique_ptr<SafeRecorder> mInstance;
  std::ofstream mLogFile;
};

#endif