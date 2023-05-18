#pragma once

#include <vector>
#include <sstream>

#include "ImStructs.h"
#include "ImSerialise.h"

namespace ImStructs
{
    // Takes in a value and returns a compiled function argument TODO: overhaul his

    inline std::string FormatFloat(float value)
    {
        return std::format("{}", value);
    }

    inline std::string FormatDouble(double value)
    {
        return std::format("{}", value);
    }
    
    inline std::string ArgumentToString(const char value)          { return std::to_string(value); }
    inline std::string ArgumentToString(const int value)           { return std::to_string(value); }
    inline std::string ArgumentToString(const int* value)          { return "new int(" + std::format("{}", *value) + ")"; }
    inline std::string ArgumentToString(const long value)          { return std::to_string(value); }
    inline std::string ArgumentToString(const float value)         { return FormatFloat(value); }
    inline std::string ArgumentToString(const float* value)        { return "new float(" + FormatFloat(*value) + ")"; }
    inline std::string ArgumentToString(const double value)        { return std::to_string(value); }
    inline std::string ArgumentToString(const double* value)       { return "new double(" + FormatDouble(*value) + ")"; }
    inline std::string ArgumentToString(const bool value)          { return value ? "true" : "false"; }
    inline std::string ArgumentToString(const bool* value)         { return "new bool(" + std::to_string(*value) + ")"; }
    inline std::string ArgumentToString(const char* value)         { return "\"" + std::string(value) + "\""; }
    inline std::string ArgumentToString(const std::string& value)  { return "\"" + value + "\""; }
    inline std::string ArgumentToString(const std::string* value)  { return "new std::string(\"" + *value + "\")"; }
    inline std::string ArgumentToString(const ImVec2& value)       { return "ImVec2(" + FormatFloat(value.x) + ", " + FormatFloat(value.y) + ")"; }
    inline std::string ArgumentToString(const ImVec4& value)       { return "ImVec4(" + FormatFloat(value.x) + ", " + FormatFloat(value.y) + ", " + FormatFloat(value.z) + ", " + FormatFloat(value.w) + ")"; }
    inline std::string ArgumentToString(const ImColor& value)      { return "ImColor(" + FormatFloat(value.Value.x) + ", " + FormatFloat(value.Value.y) + ", " + FormatFloat(value.Value.z) + ", " + FormatFloat(value.Value.w) + ")"; }
    inline std::string ArgumentToString(const ImU32& value)        { return "ImU32(" + std::to_string(value) + ")"; }
    inline std::string ArgumentToString(const nullptr_t value)     { return "nullptr /*nullptr_t*/"; }

    // TODO: Find out what to do with callbacks since they are function pointers and a custom class
    inline std::string ArgumentToString(ImGuiInputTextCallbackData value)     { return "nullptr /*ImGuiInputTextCallbackData*/"; }
    inline std::string ArgumentToString(ImGuiInputTextCallback value)     { return "nullptr /*ImGuiInputTextCallback*/"; }
    inline std::string ArgumentToString(void* value)     { return "nullptr /*void**/"; }                             // Don't think this can ever be just a raw value since function in final program will differ
    
    template <typename F, typename... Args>
    class ComponentWrapper : public ImStructComponent
    {
    public:

        std::string              Name;
        std::string              FunctionName;
        std::vector<std::string> ArgumentNames;
        using result_type = std::invoke_result_t<F, Args...>;
    
        ComponentWrapper(F&& f, Args&&... args) : Function(std::forward<F>(f)), Arguments(std::forward<Args>(args)...) {}

        void Draw() override
        {
            ImStructComponent::Draw();
            // if the tuple doesn't have any arguments, just call the function
            if constexpr (sizeof...(Args) == 0)
            {
                Function();
            }
            else {
                apply();
            }
            if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
            if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
        }

        result_type apply()
        {
            if constexpr (std::is_same_v<result_type, bool>)
            {
                DrawReturn = std::apply(Function, Arguments);
                return DrawReturn;
            }
            return std::apply(Function, Arguments);
        }

        // print all the arguments and their types
        void Editor() override
        {
            ImStructComponent::Editor();

            ImGui::PushID(this);

            if(ArgumentNames.size() != sizeof...(Args))
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
            
            ImGui::PopID();
        }

        std::string Compile() override
        {
            if(FunctionName.empty())
            {
                return "#warning Function call couldnt be compiled because the function name was empty";
            }

            if(ArgumentNames.size() != sizeof...(Args))
            {
                return "#warning Function call couldn't be compiled because the argument names were empty or not the same size";
            }
            
            std::string call_args;
            
            std::apply([&](auto&&... args) {
                ((call_args += ArgumentToString(args) + ", "), ...);
            }, Arguments);

            // remove the last comma without pop_back
            call_args = call_args.substr(0, call_args.size() - 2);

            if constexpr (std::is_same_v<bool, result_type>)
            {
                return ImStructComponent::Compile() + "if(" + FunctionName + "(" + call_args + ")) { /** TODO: Add code here for " + EditorLabel + " **/ }";
            }
            else
            {
                return ImStructComponent::Compile() + FunctionName + "(" + call_args + ");";
            }
            
        }

        [[nodiscard]] std::string Serialise() const override {
            std::stringstream ss;
            ss << Name << "##" << "69420" << "("; // TODO: Implement hash
            ss << ImStructComponent::Serialise() << ", ";
            const auto serialise = [&ss](auto&& arg) {
                ImSerialise(ss, arg);
                ss << ", ";
            };
            std::apply([&serialise](const auto&... args) { (serialise(args), ...);}, Arguments);
            ss.seekp(-2, std::ios_base::end);
            ss << ")";
            return ss.str().substr(0, ss.str().length() - 1);
        }
        
        void Deserialise(const std::string str) override {
            const ImSerialisation::Call call(str);
            assert(call.Params.size() == sizeof...(Args) + 1 && "ComponentWrapper initialised with incorrect amount of arguments");
            ImStructComponent::Deserialise(call.Params[0]);
            std::stringstream ss;
            for (size_t i = 1; i < call.Params.size(); i++)
            {
                ss << call.Params[i] << " ";
            }
            
            std::apply([&ss](auto&... args)
            {
                (ImDeserialise(ss, args), ...);
            }, Arguments);
        }

        // write a destructor
        ~ComponentWrapper() override
        {
            ImStructComponent::~ImStructComponent();
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