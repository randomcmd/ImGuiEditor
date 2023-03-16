#pragma once
#include <algorithm>
#include "imgui.h"
#include <iostream>
#include <optional>
#include <sstream>
#include <stack>
#include <string>

inline void ImDeserialise(std::stringstream& is)                                              { }
inline void ImDeserialise(std::stringstream& is, char& value)                                 { is >> value; }
inline void ImDeserialise(std::stringstream& is, int& value)                                  { is >> value; }
inline void ImDeserialise(std::stringstream& is, int*& value)                                 { is >> *value; }
inline void ImDeserialise(std::stringstream& is, long& value)                                 { is >> value; }
inline void ImDeserialise(std::stringstream& is, float& value)                                { is >> value; }
inline void ImDeserialise(std::stringstream& is, float*& value)                               { is >> *value; }
inline void ImDeserialise(std::stringstream& is, double& value)                               { is >> value; }
inline void ImDeserialise(std::stringstream& is, double*& value)                              { is >> *value; }
inline void ImDeserialise(std::stringstream& is, bool& value)                                 { is >> value; }
inline void ImDeserialise(std::stringstream& is, bool*& value)                                { is >> *value; }
inline void ImDeserialise(std::stringstream& is, char*& value)                                { is >> *value; }
inline void ImDeserialise(std::stringstream& is, ImU32& value)                                { is >> value; }
inline void ImDeserialise(std::stringstream& is, nullptr_t& value)                            { value = nullptr; }
inline void ImDeserialise(std::stringstream& is, ImGuiInputTextCallbackData& value)           { value = ImGuiInputTextCallbackData(); }
inline void ImDeserialise(std::stringstream& is, ImGuiInputTextCallback& value)               { value = nullptr; }
inline void ImDeserialise(std::stringstream& is, void*& value)                                { value = nullptr; }

inline std::string* FirstString(std::stringstream& is) // This might leak value but who cares it's only a few bytes
{
    const auto new_string = new std::string(is.str());
    const size_t start = new_string->find_first_of('\"', is.tellg()) + 1;
    size_t end = std::string::npos;
    for(size_t i = start; i < new_string->size(); i++)
    {
        if(i >= 1 && new_string->at(i) == '\"' && new_string->at(i - 1) != '\\')
        {
            end = i;
            break;
        }
    }
    if(end == std::string::npos)
    {
        end = start;
    }
    *new_string = new_string->substr(start, end - start);
    std::erase(*new_string, '\\');
    is.seekg(end + 1);
    return new_string;
}

inline void ImDeserialise(std::stringstream& is, const char*& value)
{
    const auto new_string = FirstString(is);
    value = new_string->c_str();
}
inline void ImDeserialise(std::stringstream& is, std::string& value)
{
    value = *FirstString(is);
}
inline void ImDeserialise(std::stringstream& is, std::string*& value)
{
    value = FirstString(is);
}
inline void ImDeserialise(std::stringstream& is, ImVec2& value)
{
    is >> value.x >> value.y;
}
inline void ImDeserialise(std::stringstream& is, ImVec4& value)
{
    is >> value.x >> value.y >> value.z >> value.w;
}
inline void ImDeserialise(std::stringstream& is, ImColor& value)
{
    is >> value.Value.x >> value.Value.y >> value.Value.z >> value.Value.w;
}

inline void ImSerialise(std::stringstream& os)                                             { }
inline void ImSerialise(std::stringstream& os, char value)                                 { os << value; }
inline void ImSerialise(std::stringstream& os, int value)                                  { os << value; }
inline void ImSerialise(std::stringstream& os, int* value)                                 { os << *value; }
inline void ImSerialise(std::stringstream& os, long value)                                 { os << value; }
inline void ImSerialise(std::stringstream& os, float value)                                { os << value; }
inline void ImSerialise(std::stringstream& os, float* value)                               { os << *value; }
inline void ImSerialise(std::stringstream& os, double value)                               { os << value; }
inline void ImSerialise(std::stringstream& os, double* value)                              { os << *value; }
inline void ImSerialise(std::stringstream& os, bool value)                                 { os << value; }
inline void ImSerialise(std::stringstream& os, bool* value)                                { os << *value; }
inline void ImSerialise(std::stringstream& os, char* value)                                { os << *value; }
inline void ImSerialise(std::stringstream& os, const char* value)                          { std::string new_string = value; os << '\"' << value << '\"'; } // TODO: Add escape characters
inline void ImSerialise(std::stringstream& os, std::string value)                          { os << "\""<< value << "\""; }
inline void ImSerialise(std::stringstream& os, std::string* value)                         { os << "\""<< *value << "\""; }
inline void ImSerialise(std::stringstream& os, ImVec2 value)                               { os << value.x << " " << value.y; }
inline void ImSerialise(std::stringstream& os, ImVec4 value)                               { os << value.x << " " << value.y << " " << value.z << " " << value.w; }
inline void ImSerialise(std::stringstream& os, ImColor value)                              { os << value.Value.x << " " << value.Value.y << " " << value.Value.z << " " << value.Value.w; }
inline void ImSerialise(std::stringstream& os, ImU32 value)                                { os << value; }
inline void ImSerialise(std::stringstream& os, nullptr_t value)                            { os << "nullptr"; }
inline void ImSerialise(std::stringstream& os, ImGuiInputTextCallbackData value)           { os << "ImGuiInputTextCallbackData()"; }
inline void ImSerialise(std::stringstream& os, ImGuiInputTextCallback value)               { os << "nullptr"; }
inline void ImSerialise(std::stringstream& os, void* value)                                { os << "nullptr"; }

// Lay Lang
namespace ImSerialisation
{
    using Parameters = std::vector<std::string>;
    Parameters ParseArgsFromCall(const std::string_view& call, size_t parameter_start, size_t parameter_end);
    
    struct Call
    {
        Call(std::string_view call)
        {
            // Assert this is a valid laylang call
            // Assert that it starts with a function name
            // Optional ## with a hash
            // ( with parameters seperated by ,
            // ends with )

            const auto parameter_start = call.find_first_of("(");
            const std::string_view func_name_and_hash = call.substr(0, parameter_start);
            const bool hash_hash = func_name_and_hash.find_first_of("##(") != std::string::npos;
            
            if(hash_hash)
            {
                FunctionName = func_name_and_hash.substr(0, func_name_and_hash.find_first_of("##"));
                const auto hash_begin = func_name_and_hash.find_first_of("##") + 2;
                const std::string hash_string = std::string(func_name_and_hash.substr(hash_begin, parameter_start - hash_begin));
                Hash = std::stoul(hash_string);
            }
            else
            {
                FunctionName = func_name_and_hash;
            }

            Params = ParseArgsFromCall(call, parameter_start + 1, call.find_last_of(")"));
        }
        
        std::string FunctionName;
        std::optional<size_t> Hash;
        Parameters Params;
    };

    inline Parameters ParseArgsFromCall(const std::string_view& call, size_t parameter_start, size_t parameter_end)
    {
        Parameters parameters;
        std::stack<char> nesting_stack;
        size_t i = parameter_start, start_param = parameter_start;
        for(const char& c : call.substr(parameter_start, parameter_end - parameter_start))
        {
            if(c == '(')
            {
                nesting_stack.push(c);
            }
            if(c == ')')
            {
                nesting_stack.pop();
            }

            const bool can_end_param = c == ',' || i == parameter_end - 1;
            if(can_end_param && nesting_stack.empty())
            {
                if (nesting_stack.empty())
                {
                    if(i == parameter_end - 1)
                    {
                        i++;
                    }
                    const size_t count = i - start_param;
                    // if it's only whitespace then continue
                    if (std::all_of(call.begin() + start_param, call.begin() + i, isspace))
                    {
                        start_param = i + 1;
                        continue;
                    }
                    auto param = std::string(call.substr(start_param, count));
                    // remove leading and trailing whitespace
                    std::erase(param, '\t');
                    std::erase(param, '\n');
                    parameters.push_back(param);
                }
                start_param = i + 1;
            }
            i++;
        }
        return parameters;
    }
}