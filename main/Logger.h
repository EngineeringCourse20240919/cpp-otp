#ifndef CPP_OTP_LOGGER_H
#define CPP_OTP_LOGGER_H
#include "string"

class Logger {
public:
    virtual void log(const std::string& message);
};


#endif //CPP_OTP_LOGGER_H
