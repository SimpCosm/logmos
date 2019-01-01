#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <cstdarg>
#include <sstream>
#include <string>

#include <syslog.h>

class Logger {
public:
    Logger(int level, const char* file, int line, bool linefeed)
        : level_ {level}
        , file_ {file}
        , line_ {line}
        , linefeed_ {linefeed} {}

    Logger() = delete;
    Logger(const Logger&) = default;
    Logger(Logger&&) = default;

    ~Logger() {
        log(level_, file_, line_, linefeed_, "%s", os_.str().c_str());
    }

    template <typename T>
    inline Logger& operator<<(const T& value) {
        os_ << value;
        return *this;
    }

    // printf fashion logging
    // example: DBG("%s", "Hello, World")
    static void log(int level, const char* file, int line, bool linefeed, const char* const fmt, ...);

    static void vlog(int level, const char* file, int line, bool linefeed, const char* fmt, va_list);

    // stream fashion logging
    // example: DBG() << "Hello, World!";
    static Logger log(int level, const char* file, int line, bool linefeed) {
        return {level, file, line, linefeed};
    }

private:
    int level_;                 // LOG_XXXX values
    const char* const file_;    // contextual filename
    const int line_;            // contextual line number
    bool linefeed_ {true};             // true if a '\n' (or any platform equivalent) has to be put at line end in console mode
    std::ostringstream os_;     // string stream used with C++ stream style (stream operator<<)
};

#define INFO(...) Logger::log(LOG_INFO, __FILE__, __LINE__, true, ## __VA_ARGS__)
#define DEBUG(...) Logger::log(LOG_DEBUG, __FILE__, __LINE__, true, ## __VA_ARGS__)
#define WARN(...) Logger::log(LOG_WARNING, __FILE__, __LINE__, true, ## __VA_ARGS__)
#define ERROR(...) Logger::log(LOG_ERR, __FILE__, __LINE__, true, ## __VA_ARGS__)

#endif  // __LOGGER_H__
