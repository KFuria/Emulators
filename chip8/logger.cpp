#include <iostream>
#include <memory>
#include <string>
#include "logger.h"

std::shared_ptr<TLogger> TLogger::loggerInstance = nullptr;

TLogger::TLogger() : 
    logLevel(ELogLevel::DEBUG){
}

void TLogger::log(std::string message, ELogLevel level)
{
    std::string buff = "";

    if(level <= logLevel)
    {
        switch(level)
        {
            case ELogLevel::ERROR: buff += "\033[31m[ERROR] "; break;
            case ELogLevel::WARN: buff += "\033[33m[WARN] "; break;
            case ELogLevel::INFO: buff += "\033[32m[INFO] "; break;
            case ELogLevel::DEBUG: buff += "\033[0m[DEBUG] "; break;
            case ELogLevel::OP : buff += "\033[36m[OP] "; break;
            default: break;
        }

        buff += message + "\n";
        std::cout << buff;
    }
}

void TLogger::setLogLevel(ELogLevel logLevel)
{
    logLevel = logLevel;
}

std::shared_ptr<TLogger> TLogger::getInstance()
{
    if(loggerInstance == nullptr)
        loggerInstance = std::shared_ptr<TLogger>(new TLogger());

    return loggerInstance;
}

ELogLevel TLogger::getLogLevel(){
    return logLevel;
}
