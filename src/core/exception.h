#ifndef UKPM_CORE_EXCEPTION_H_
#define UKPM_CORE_EXCEPTION_H_

#pragma once

#include <exception>
#include <string>

namespace ukpm {

class Exception : public std::exception {
  public:
    explicit Exception(std::string message) : _message(std::move(message)) {};

    [[nodiscard]]
    const char *what() const noexcept override {
        return _message.c_str();
    };

  protected:
  private:
    std::string _message;
};

class ArchiveException : public ukpm::Exception {
  public:
    explicit ArchiveException(const std::string &message)
        : Exception(message) {};

    explicit ArchiveException(const std::string &message,
                              const std::string &description)
        : Exception(message + description) {};

  protected:
  private:
};

} // namespace ukpm

#endif // UKPM_CORE_EXCEPTION_H_
