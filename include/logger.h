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

  Logger &operator=(const Logger &other) {
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

  void log(LogLevel level, std::string_view message);

  void trace(std::string_view message);
  void debug(std::string_view message);
  void info(std::string_view message);
  void warning(std::string_view message);
  void error(std::string_view message);
  void fatal(std::string_view message);

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
};
} // namespace Logging
} // namespace Umbra
