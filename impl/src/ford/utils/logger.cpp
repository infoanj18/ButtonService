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

#include "ford/utils/logger.hpp"

#ifdef FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING
#include <sys/slog2.h>
#endif

#include <stdarg.h>
#include <vector>

#ifdef FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING
// QNX global variable that holds the basename of the program being executed
extern char *__progname;
#endif

namespace ford {
namespace utils {

#ifdef FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING
static bool slog2_is_initialized = false;
static slog2_buffer_t buffer_handle = {};

static void logger_initialize_slog2() {
    if (slog2_is_initialized)
        return; // nothing to do, it's already done

    slog2_buffer_set_config_t buffer_config;

    buffer_config.buffer_set_name = __progname;
    buffer_config.num_buffers = 1;
    buffer_config.buffer_config[0].buffer_name = "button_service";
    // This creates a 4KiBx32=128KiB buffer
    buffer_config.buffer_config[0].num_pages = 32;
    #ifdef FORD_BUTTON_SERVICE_DEBUG
        buffer_config.verbosity_level = SLOG2_DEBUG2;
    #else
        buffer_config.verbosity_level = SLOG2_INFO;
    #endif

    if (slog2_register(&buffer_config, &buffer_handle, 0) != -1)
        slog2_is_initialized = true;
}
#endif

Logger::Logger(const char* tag) {
    m_tag = tag;

    #ifdef FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING
        logger_initialize_slog2();
    #endif
}

Logger::~Logger() {
}

static void platformLogHandler(LogLevel level, const char* message) {
    #ifdef FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING
        uint8_t severity = SLOG2_NOTICE;
        switch (level) {
            case LogLevel::Critical:severity = SLOG2_CRITICAL; break;
            case LogLevel::Error:   severity = SLOG2_ERROR; break;
            case LogLevel::Warning: severity = SLOG2_WARNING; break;
            case LogLevel::Info:    severity = SLOG2_INFO; break;
            case LogLevel::Debug:   severity = SLOG2_DEBUG1; break;
            case LogLevel::Verbose: severity = SLOG2_DEBUG2; break;
            default: break;
        }
        if (slog2_is_initialized)
            slog2c(buffer_handle, static_cast<uint16_t>(level), severity, message);
    #else
        const char* levelStr = "LOG";
        switch (level) {
            case LogLevel::Critical: levelStr = "CRITICAL"; break;
            case LogLevel::Error: levelStr = "ERROR"; break;
            case LogLevel::Warning: levelStr = "WARNING"; break;
            case LogLevel::Info: levelStr = "INFO"; break;
            case LogLevel::Debug: levelStr = "DEBUG"; break;
            case LogLevel::Verbose: levelStr = "VERBOSE"; break;
            default: break;
        }
        printf("BUTTON_SERVICE %s: %s\n", levelStr, message);
    #endif
}

void Logger::logImpl(LogLevel level, const char* format, ...) const // NOSONAR
{
    if (!loggingEnabled) return;

    va_list args;

    // See if we can format it in a stack buffer.
    char buffer[256];
    size_t total = static_cast<size_t>(snprintf(buffer, sizeof(buffer), "%s: ", m_tag.c_str()));
    va_start(args, format);
    total += static_cast<size_t>(vsnprintf(
            (total < sizeof(buffer)) ? buffer + total : nullptr,
            (total < sizeof(buffer)) ? sizeof(buffer) - total : 0,
            format,
            args));
    va_end(args);
    if (total < sizeof(buffer)) {
        platformLogHandler(level, buffer);
        return;
    }

    // Otherwise we have to allocate a buffer large enough to format the message.
    size_t capacity = total + 1;
    std::vector<char> vbuffer(capacity);
    size_t offset = static_cast<size_t>(snprintf(vbuffer.data(), capacity, "%s: ", m_tag.c_str()));
    va_start(args, format);
    vsnprintf(vbuffer.data() + offset, capacity - offset, format, args);
    va_end(args);
    platformLogHandler(level, vbuffer.data());
}

} // namespace utils
} // namespace ford
