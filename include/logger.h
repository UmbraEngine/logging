#pragma once

#include "core.h"
#include "pch.h"

const int LOG_LEVEL_TRACE = 0;
const int LOG_LEVEL_DEBUG = 1;
const int LOG_LEVEL_INFO = 2;
const int LOG_LEVEL_WARNING = 3;
const int LOG_LEVEL_ERROR = 4;
const int LOG_LEVEL_FATAL = 5;
const int LOG_LEVEL_OFF = 6;

enum LogLevel : int {
  Trace = LOG_LEVEL_TRACE,
  Debug = LOG_LEVEL_DEBUG,
  Info = LOG_LEVEL_INFO,
  Warning = LOG_LEVEL_WARNING,
  Error = LOG_LEVEL_ERROR,
  Fatal = LOG_LEVEL_FATAL,
  Off = LOG_LEVEL_OFF
};

namespace Umbra {
namespace Logging {
class Logger {
 public:
  Logger(std::string name, bool debugEnabled = false);
  Logger(std::string name, std::string fileName, bool debugEnabled = false);
  ~Logger();

  Logger& operator=(const Logger& other)
  {
    if (this == &other) {
      return *this;
    }

    if (this->logFile.is_open()) {
      this->logFile.close();
    }

    std::string newFileName = other.logFile.rdbuf()->getloc().name();
    this->logFile.open(newFileName, std::ios::out | std::ios::app);

    return *this;
  }

  template <typename... Args>
  void trace(std::string_view message, Args&&... args)
  {
    log(LogLevel::Trace, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(std::string_view message, Args&&... args)
  {
    log(LogLevel::Debug, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void info(std::string_view message, Args&&... args)
  {
    log(LogLevel::Info, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warning(std::string_view message, Args&&... args)
  {
    log(LogLevel::Warning, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(std::string_view message, Args&&... args)
  {
    log(LogLevel::Error, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void fatal(std::string_view message, Args&&... args)
  {
    log(LogLevel::Fatal, message, std::forward<Args>(args)...);
  }

  bool enableDebugging();
  bool disableDebugging();

 private:
  std::string name;
  bool debugEnabled;
  std::ofstream logFile;
  std::string fileName;

  [[nodiscard]] bool shouldLogMessage(LogLevel level) const;
  [[nodiscard]] bool getDebugEnabled() const;
  void setColor(LogLevel level);
  void resetColor();
  std::string getLevelString(LogLevel level);
  std::string getTimestamp();

  template <typename... Args>
  void log(LogLevel level, std::string_view message, Args&&... args)
  {
    if (Logger::shouldLogMessage(level)) {
      std::string levelString = this->getLevelString(level);
      std::string loggerName = "[" + this->name + "] ";
      if (this->logFile.is_open()) {
        this->logFile << this->getTimestamp() << loggerName << levelString
                      << std::format(message, std::forward<Args>(args)...) << std::endl;
      }
      Logger::setColor(level);
      std::cout << this->getTimestamp() << loggerName << levelString
                << std::format(message, std::forward<Args>(args)...) << std::endl;
      Logger::resetColor();
    }
  };
};
}  // namespace Logging
}  // namespace Umbra
