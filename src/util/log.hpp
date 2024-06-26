#pragma once

#include "spdlog/spdlog.h"

#if defined(LEARN_OPENGL_ENABLE_LOGGING)
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_DEBUG(...)    spdlog::debug(__VA_ARGS__)
#else
#define LOG_INFO(...)
#define LOG_TRACE(...)
#define LOG_WARN(...)
#define LOG_CRITICAL(...)
#define LOG_ERROR(...)
#define LOG_DEBUG(...)
#endif