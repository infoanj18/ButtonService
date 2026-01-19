//
// CONFIDENTIAL - FORD MOTOR COMPANY
//
// This is an unpublished work, which is a trade secret, created in
// 2026. Ford Motor Company owns all rights to this work and intends
// to maintain it in confidence to preserve its trade secret status.
// Ford Motor Company reserves the right to protect this work as an
// unpublished copyrighted work in the event of an inadvertent or
// deliberate unauthorized publication. Ford Motor Company also
// reserves its rights under the copyright laws to protect this work
// as a published work. Those having access to this work may not copy
// it, use it, or disclose the information contained in it without
// the written authorization of Ford Motor Company.
//

#ifndef FORD_UTILS_LOGGING_HPP
#define FORD_UTILS_LOGGING_HPP

#include <string>
#include <cstdio>
#include <atomic>

enum class LogLevel {
    Critical = 0,
    Error,
    Warning,
    Info,
    Debug,
    Verbose,
};

#define LogC(logger, ...) ((logger).logImpl(LogLevel::Critical, __VA_ARGS__)) // NOSONAR
#define LogE(logger, ...) ((logger).logImpl(LogLevel::Error, __VA_ARGS__)) // NOSONAR
#define LogW(logger, ...) ((logger).logImpl(LogLevel::Warning, __VA_ARGS__)) // NOSONAR
#define LogI(logger, ...) ((logger).logImpl(LogLevel::Info, __VA_ARGS__)) // NOSONAR
#ifdef FORD_BUTTON_SERVICE_DEBUG
    #ifndef LogD
        #define LogD(logger, ...) ((logger).logImpl(LogLevel::Debug, __VA_ARGS__)); // NOSONAR
    #endif
    #ifndef LogV
        #define LogV(logger, ...) ((logger).logImpl(LogLevel::Verbose, __VA_ARGS__)); // NOSONAR
    #endif
#else
    #ifndef LogD
        #define LogD(logger, ...) ((void)logger);
    #endif
    #ifndef LogV
        #define LogV(logger, ...) ((void)logger);
    #endif
#endif

//
// LogStatic*() are used to log something in a static context where you
// don't have an instance of a Logger.
//

#define LogStaticC(tag, ...) do { \
    ford::utils::Logger logger(tag); \
    LogC(logger, __VA_ARGS__); \
} while (0)

#define LogStaticE(tag, ...) do { \
    ford::utils::Logger logger(tag); \
    LogE(logger, __VA_ARGS__); \
} while (0)

namespace ford {
namespace utils {

class Logger {
public:
    explicit Logger(const char* tag);
    virtual ~Logger();

    // set to false to stop calls to any platform services
    std::atomic<bool> loggingEnabled {true};

    // These need to be public to be usable by the Log*() macros.
    std::string m_tag;
    void logImpl(LogLevel level, const char* format, ...) const // NOSONAR
        #ifdef __GNUC__
        __attribute__((format(printf, 3, 4)))
        #endif
        ;

    #ifdef FORD_BUTTON_SERVICE_DEBUG
        bool m_debugEnabled = false;
    #endif

    Logger(const Logger&) = delete;
    Logger(const Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(const Logger&&) = delete;
};

} // namespace utils
} // namespace ford

#endif /* FORD_UTILS_LOGGING_HPP */
