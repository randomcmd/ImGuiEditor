#pragma once
#include <string>

class ImString
{
public:
    ImString();
    ImString(std::string_view string) : m_BackingString(string) {}

    std::string String() { return m_BackingString; }
    std::string& StringReference() { return m_BackingString; }
    std::string* StringPointer() { return &m_BackingString; }
    
    // Implicit conversion to const char*
    // This is used by templates to convert to const char* when needed by a parameter but still remain editing functionality without casting away const
    operator const char*() const { return m_BackingString.c_str(); }
private:
    std::string m_BackingString;
};