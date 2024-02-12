#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;  // Singleton instance
        return instance;
    }

    void log(LogLevel level, const std::string& message) {
        // Your logging logic here
        // For demonstration, I'll print to console
        std::cout << "[" << levelToString(level) << "] " << message << std::endl;
    }

private:
    Logger() {}  // Private constructor to prevent external instantiation

    std::string levelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            case CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }
};


#endif //LOGGER_HPP
