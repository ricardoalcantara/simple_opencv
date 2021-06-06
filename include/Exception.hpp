#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

class Exception : public std::exception
{
public:
    Exception(int line, const char *file, const char *message)
        : line(line), file(file), message(message) {}
    virtual const char *GetType() const{ return "Exception"; }
    const char *GetErrorString() const { return message; }
    std::string GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << "[File] " << file << std::endl
            << "[Line] " << line;
        return oss.str();
    }
    const char *what() const noexcept override
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "[Description] " << GetErrorString() << std::endl;

        oss << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

private:
    const int line;
    const char *file;
    const char *message;
    mutable std::string whatBuffer;
};

#endif
