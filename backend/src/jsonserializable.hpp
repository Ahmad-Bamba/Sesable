#ifndef SESABLE_HEADER_JSONSERIALIZABLE_HPP
#define SESABLE_HEADER_JSONSERIALIZABLE_HPP

#include <string>
#include <ostream>

class IJsonSerializable {
public:
    virtual ~IJsonSerializable = default();
    virtual void dump(std::basic_ostream<char_t>& to_file) = 0;
    virtual std::string dumps() = 0;
};

#endif

