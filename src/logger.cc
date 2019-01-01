#include "logmos/logger.h"
#include "logmos/color.h"

#include <iomanip>
#include <thread>

#include <ctime>
#include <sys/time.h>


static constexpr auto ENDL = "\n";

std::string contextHeader(const char* const file, int line)
{
    auto tid = std::this_thread::get_id();

    // timestamp
    unsigned int secs, milli;
    struct timeval tv;

    if (!gettimeofday(&tv, NULL)) {
        secs = tv.tv_sec;
        milli = tv.tv_usec / 1000;
    } else {
        secs = time(NULL);
        milli = 0;
    }

    std::ostringstream out;
    const auto prev_fill = out.fill();
    out << '[' << secs
        << '.' << std::right << std::setw(3) << std::setfill('0') << milli << std::left
        << '|' << std::right << std::setw(5) << std::setfill(' ') << tid << std::left;
    out.fill(prev_fill);

    // context
    if (file) {
        constexpr auto width = 18;
        out << '|'
            << std::setw(width) << file
            << ':'
            << std::setw(5) << std::setfill(' ') << line;
    }

    out << "] ";
    return out.str();
}

void Logger::log(int level, const char* file, int line, bool linefeed, const char* const format, ...)
{
    va_list ap;
    va_start(ap, format);
    Logger::vlog(level, file, line, linefeed, format, ap);
    va_end(ap);
}

void Logger::vlog(const int level, const char* file, int line, bool linefeed, const char* format, va_list ap)
{
    //if (consoleLog) {
        const char* color_header = CYAN;
        const char* color_prefix = "";

        switch (level) {
            case LOG_ERR:
                color_prefix = RED;
                break;
            case LOG_WARNING:
                color_prefix = YELLOW;
                break;
        }

        fputs(color_header, stderr);
        fputs(contextHeader(file, line).c_str(), stderr);
        fputs(END_COLOR, stderr);
        fputs(color_prefix, stderr);
        vfprintf(stderr, format, ap);
        if (linefeed)
            fputs(ENDL, stderr);
        fputs(END_COLOR, stderr);
    //} else {
    //    printf("Not Implemented Yet!\n");
    //}
}
