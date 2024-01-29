#ifndef LOGGER
#define LOGGER


#include "Logger.hpp"
#include "Config.hpp"

void Logger::Log(const std::string& content) {
    if(!config::EnableLogs)
        return;
    std::cout << content << std::endl;




}

#endif //LOGGER
