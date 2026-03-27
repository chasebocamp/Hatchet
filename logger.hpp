#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> // For colored console output
#include <memory>

class Logger {
public:
    static void Init() {
        // 1. Create a "Sink" (where the text goes). 
        // 'stdout_color_mt' means "Multi-threaded Colored Console"
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        
        // 2. Set the pattern: [Time] [Level] Message
        // Example: [10:30:05] [info] Vulkan Instance Created
        consoleSink->set_pattern("%^[%T] %n: %v%$");

        // 3. Create the actual logger object
        m_EngineLogger = std::make_shared<spdlog::logger>("HATCHET", consoleSink);
        m_EngineLogger->set_level(spdlog::level::trace);

        spdlog::register_logger(m_EngineLogger);
    }

    // These inline functions let us use Logger::Info("message") easily
    static std::shared_ptr<spdlog::logger>& GetLogger() { return m_EngineLogger; }

private:
    static std::shared_ptr<spdlog::logger> m_EngineLogger;
};

// We define the actual memory for the logger here
inline std::shared_ptr<spdlog::logger> Logger::m_EngineLogger;

// Macros to make typing shorter and cleaner
#define HT_INFO(...)  Logger::GetLogger()->info(__VA_ARGS__)
#define HT_WARN(...)  Logger::GetLogger()->warn(__VA_ARGS__)
#define HT_ERROR(...) Logger::GetLogger()->error(__VA_ARGS__)
#define HT_TRACE(...) Logger::GetLogger()->trace(__VA_ARGS__)
