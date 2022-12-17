#pragma once

#include <vector>
#include "ImGuiStructs.h"
using ImStructs::ImStruct;

namespace ImStructs
{
    // Takes in a value and returns a compiled function argument
    std::string ArgumentToString(char value)                { return std::to_string(value); }
    std::string ArgumentToString(int value)                 { return std::to_string(value); }
    std::string ArgumentToString(long value)                { return std::to_string(value); }
    std::string ArgumentToString(float value)               { return std::to_string(value); }
    std::string ArgumentToString(double value)              { return std::to_string(value); }
    std::string ArgumentToString(bool value)                { return value ? "true" : "false"; }
    std::string ArgumentToString(const char* value)         { return "\"" + std::string(value) + "\""; }
    std::string ArgumentToString(const std::string& value)  { return "\"" + std::string(value) + "\""; }
    std::string ArgumentToString(const ImVec2& value)       { return "ImVec2(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")"; }
    std::string ArgumentToString(const ImVec4& value)       { return "ImVec4(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ", " + std::to_string(value.w) + ")"; }
    std::string ArgumentToString(const ImColor& value)      { return "ImColor(" + std::to_string(value.Value.x) + ", " + std::to_string(value.Value.y) + ", " + std::to_string(value.Value.z) + ", " + std::to_string(value.Value.w) + ")"; }
    std::string ArgumentToString(const ImU32& value)        { return "ImU32(" + std::to_string(value) + ")"; }
    std::string ArgumentToString(const nullptr_t value)     { return "nullptr"; }
    
    template <typename F, typename... Args>
    class ComponentWrapper : public ImStruct
    {
    public:

        std::string              Name;
        std::string              FunctionName;
        std::vector<std::string> ArgumentNames;
    
        ComponentWrapper(F&& f, Args&&... args) : Function(std::forward<F>(f)), Arguments(std::forward<Args>(args)...)
        {
            // if the first argument is a c string, use it as the label
            // since the label is actually defined in ImStruct we point the first argument to the label
            // this is a bit hacky but it works (thanks copilot)
            if constexpr (std::is_same_v<const char*, std::decay_t<decltype(std::get<0>(Arguments))>>) {
                std::get<0>(Arguments) = fallBackLabel;
            }
        }

        void Draw() override
        {
            ImStruct::Draw();
            if constexpr (std::is_same_v<const char*, std::decay_t<decltype(std::get<0>(Arguments))>>) {
                if(fallBackLabel)
                {
                    std::get<0>(Arguments) = fallBackLabel;
                }
            }
            std::apply(Function, Arguments);
        }

        int apply()
        {
            return std::apply(Function, Arguments);
        }

        // print all the arguments and their types
        void Editor() override
        {
            ImStruct::Editor();

            if(ArgumentNames.size() != std::tuple_size_v<std::tuple<Args...>>) // TODO: Add named editor for arguments
                {
                // print all the arguments and their types
                std::apply([](auto&&... args) {
                    (EditorHelper("No Name Value", &args), ...);
                }, Arguments);
            }
            else
            {
                size_t i = 0;
                std::apply([this, &i](auto&&... args) {
                    (EditorHelper(ArgumentNames[i++], &args), ...);
                }, Arguments);
            }
        }

        std::string Compile() override
        {
            if(FunctionName.empty())
            {
                return "#warning Function call couldnt be compiled because the function name was empty";
            }

            if(ArgumentNames.size() != std::tuple_size_v<std::tuple<Args...>>)
            {
                return "#warning Function call coudlnt be compiled because the argument names were empty";
            }
            
            std::string call_args = "";
            
            std::apply([&](auto&&... args) {
                ((call_args += ArgumentToString(args) + ", "), ...);
            }, Arguments);

            // remove the last comma without pop_back
            call_args = call_args.substr(0, call_args.size() - 2);

            using result_type = std::invoke_result_t<F, Args...>;
            if(std::is_same_v<bool, result_type>)
            {
                return "if(" + FunctionName + "(" + call_args + ")) { /** TODO: Add code here for " + label + " **/ }";
            }
            else
            {
                return FunctionName + "(" + call_args + ");";
            }
            
        }

        // write a destructor
        ~ComponentWrapper() override
        {
            ImStruct::~ImStruct();
            // call the destructors of the elements in the tuple
            std::apply([](auto&&... args) {
                (std::destroy_at(&args), ...);
            }, Arguments);
        }

    private:
        F Function;
        std::tuple<Args...> Arguments;
    };

    template <typename F, typename... Args>
    ComponentWrapper<F, Args...>* make_component_wrapper(F&& f, Args&&... args)
    {
        return new ComponentWrapper<F, Args...>{std::forward<F>(f), std::forward<Args>(args)...};
    }
}