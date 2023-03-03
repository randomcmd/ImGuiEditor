#include <imgui.h>
#include <imgui_stdlib.h>
#include <ranges>

#include "ImGuiExtension.h"
#include <tuple>
#include <sstream>
#include <string>

#include "ComponentWrapper.h"

std::ostream& operator<<(std::ostream& os, const ImVec2& vec)
{
    os << vec.x << " " << vec.y << " ";
    return os;
}

std::istream& operator>>(std::istream& is, ImVec2& vec)
{
    is >> vec.x >> vec.y;
    return is;
}

template <typename... Args>
std::string serialise_tuple(const std::tuple<Args...>& t) {
    std::stringstream ss;
    std::apply([&ss](const auto&... args) { ((ss << args << " "), ...); }, t);
    return ss.str();
}

template <typename... Args>
std::tuple<Args...> deserialise_tuple(const std::string& str) {
    std::stringstream ss(str);
    std::tuple<Args...> t;
    std::apply([&ss](auto&... args) { ((ss >> args), ...); }, t);
    return t;
}

void SerialiseTest(const std::string hello, ImVec2 size = ImVec2(0, 0))
{
    ImGui::Button(hello.c_str(), size);
}

std::vector<std::string> Split(std::string str, std::string delimiter) {
    std::vector<std::string> parts;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        parts.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    parts.push_back(str);
    return parts;
}

void LayLangParser()
{
    static std::string eggxample = "ComponentName##Hash((\"Label\"), (Vec2.x Vec2.y));";
    // write code that parses the comonent name hash and all the parameters as string
    const std::string component_name = eggxample.substr(0, eggxample.find("##"));
    const std::string hash = eggxample.substr(eggxample.find("##") + 2, eggxample.find("(") - eggxample.find("##") - 2);
    const std::string parameters = eggxample.substr(eggxample.find("(") + 1, eggxample.find(");") - eggxample.find("(") - 1);
    std::stringstream ss(parameters);
    // split the parameters into a vector of strings
    const std::vector<std::string> params = Split(parameters, ", ");

    // remove braces from the params
    std::vector<std::string> params_no_braces;
    for (const auto& param : params) {
        params_no_braces.push_back(param.substr(1, param.size() - 2));
    }

    // print
    std::cout << "Component Name: " << component_name << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Parameters: ";
    for (const auto& param : params_no_braces) {
        std::cout << param << " ";
    }
    std::cout << std::endl;
}

void Gui()
{
    // create a component wrapper serialise it's arguments and then deserialize them
    static auto component = ImStructs::make_component_wrapper(SerialiseTest, std::string("Button"), ImVec2());
    static std::string serialised;
    ImGui::InputText("Serialised", &serialised);
    
    if (ImGui::Button("Serialise"))
    {
        serialised = serialise_tuple(component->Arguments);
    }
    ImGui::BeginDisabled(serialised.empty());
    if (ImGui::Button("Deserialise")) {
        component = ImStructs::make_component_wrapper(SerialiseTest, std::string("New button that is a button"), ImVec2(10.0f, 10.0f));
        component->Arguments = deserialise_tuple<std::string, ImVec2>(serialised);
    }
    ImGui::EndDisabled();
    ImGui::InputText("Label", &std::get<0>(component->Arguments));
    ImGui::DragFloat2("Width", (float*)&std::get<1>(component->Arguments));
    ImGui::Separator();
    component->Draw();

    if(ImGui::Button("Parse"))
    {
        LayLangParser();
    }

    static std::string lays;
    static ImSerialisation::Call call("ImCall##1234(123, 456, 789)");
    ImGui::InputText("New And Improved LayLang Parser Only 39$", &lays);
    ImGui::PushID("gay");
    if (ImGui::Button("Parse"))
    {
        call = ImSerialisation::Call(lays);
    }
    ImGui::PopID();

    ImGui::Text("Function Name %s", call.FunctionName.data());
    ImGui::Text("Hash %d", call.Hash.value_or(-1));

    for(const auto& param : call.Params)
    {
        ImGui::Text("%s", param.data());
        ImGui::SameLine();
    }
    ImGui::NewLine();
}