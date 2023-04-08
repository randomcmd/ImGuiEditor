#include "../ImGuiEditor/plugin/Plugin.h"
#include "../ImGuiEDitor/ImGuiExtension.h"
#include "../ImGuiEditor/ImStructs.h"
#include "../ImGuiEditor/ComponentWrapper.h"

inline int add(int a, int b)
{
    return a + b;
}

extern "C" __declspec(dllexport) Plugin* create(ImGuiContext* context, ImGuiMemAllocFunc allocFunc,
                                                ImGuiMemFreeFunc freeFunc)
{
    auto plugin = new Plugin();
    ImGui::SetCurrentContext(context);
    ImGui::SetAllocatorFunctions(allocFunc, freeFunc);
    plugin->PluginSpecs = {
        .Name = "Default Components",
        .Version = "0.1.0",
        .Author = "ReMi",
        .Description = "Most of the default ImGui components",
        .Github = "https://www.github.com/randomcmd/ImGuiEditor"
    };

    plugin->ComponentMaps = {
        {
            "Built-in",
            {
                    {
                        "Add random text",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            return new ImStructs::Text();
                        })
                    },
                    {
                        "Add random button",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            const auto component = new ImStructs::Button();
                            component->Label = "hej button";
                            return component;
                        })
                    },
                    {
                        "Add random input",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            const auto inputTextData = new ImStructs::InputText();
                            inputTextData->Label = "hej user input";
                            return inputTextData;
                        })
                    },
                    {
                        "just for compilation",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            const auto component = ImStructs::make_component_wrapper(&add, 1, 2);
                            component->Name = "add";
                            component->FunctionName = "add";
                            component->ArgumentNames = {"a", "b"};
                            component->CanvasFlags = ImStructs::CanvasFlags_Clicked;
                            return component;
                        })
                    },
                    {
                        "Add text (ComponentWrapper)##ImGui::TextUnformatted",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            const auto text = ImStructs::make_component_wrapper(
                                &ImGui::TextUnformatted, static_cast<const char*>("Hello, world!"), nullptr);
                            text->Name = "Text";
                            text->FunctionName = "ImGui::TextUnformatted";
                            text->ArgumentNames = {"text", "text_end"};
                            return text;
                        })
                    },
                    {
                        "Add input text (ComponentWrapper)##ImGui::InputText",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*InputText)(const char*, std::string*, ImGuiInputTextFlags, ImGuiInputTextCallback,
                                              void*) = ImGui::InputText;
                            const auto input_text = ImStructs::make_component_wrapper(
                                std::function(InputText), static_cast<const char*>("Input Text In Me"),
                                new std::string("Buffer"), 0, static_cast<ImGuiInputTextCallback>(nullptr),
                                static_cast<void*>(nullptr));
                            input_text->Name = "Input Text";
                            input_text->FunctionName = "ImGui::InputText";
                            input_text->ArgumentNames = {"Label", "Buf", "Flags", "Callback", "User_data"};
                            return input_text;
                        })
                    },
                    {
                        "Add float slider (ComponentWrapper)##ImGui::SliderFloat",
                        new ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*SliderFloat)(const char*, float*, float, float, const char*, ImGuiSliderFlags) = ImGui::SliderFloat;
                            const auto slider_float = ImStructs::make_component_wrapper(
                                std::function(SliderFloat), static_cast<const char*>("Slider Float In Me"), new float(0.0f),
                                0.0f, 1.0f, static_cast<const char*>("%.3f"), 1.0f);
                            slider_float->Name = "Slider Float";
                            slider_float->FunctionName = "ImGui::SliderFloat";
                            slider_float->ArgumentNames = {"Label", "V", "V_min", "V_max", "Format", "Power"};
                            return slider_float;
                        })
                    },
                    {
                        "Add Gradient Button V1 (ComponentWrapper)##ImGui::ColoredButtonV1",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*ColoredButton)(const char*, const ImVec2&, unsigned int, unsigned int, unsigned int) =
                                ImGui::ColoredButtonV1;
                            const auto colored_button = ImStructs::make_component_wrapper(
                                std::function(ColoredButton), static_cast<const char*>("Gradient Button V1"),
                                *new ImVec2(0, 0), *new ImColor(1.0f, 1.0f, 1.0f, 1.0f), *new ImColor(0xA020F0FF),
                                *new ImColor(0x296d98FF));
                            colored_button->Name = "Gradient Button V1";
                            colored_button->FunctionName = "ImGui::ColoredButtonV1";
                            colored_button->ArgumentNames = {"Label", "Size", "Color", "ColorHovered", "ColorActive"};
                            return colored_button;
                        })
                    },
                },
            },
            {
                "Scoped ImStructs Test",
                {
                    {
                        "Window",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*Begin)(const char*, bool*, ImGuiWindowFlags) = ImGui::Begin;
                            void (*End)() = ImGui::End;
                            const auto begin = ImStructs::make_component_wrapper(
                                ImGui::Begin, static_cast<const char*>("Window"), new bool(false), 0);
                            const auto end = ImStructs::make_component_wrapper(ImGui::End);
                            const auto window = new ImStructs::ScopedImStruct(begin, end);
                            begin->Name = "Begin";
                            begin->FunctionName = "ImGui::Begin";
                            begin->ArgumentNames = {"Name", "Open", "Flags"};
                            end->Name = "End";
                            end->FunctionName = "ImGui::End";
                            end->ArgumentNames = {};
                            window->CallEndOnlyIfBeginReturnsTrue = false;                      // This is for using the legacy scoped functions
                            window->CanvasFlags = ImStructs::CanvasFlags_Clicked;               // TODO: Add proper way to click on the window
                            return window;
                        })
                    },
                    {
                        "Tree Node##ImGui::TreeNode",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*TreeNode)(const char*) = ImGui::TreeNode;
                            void (*TreePop)() = ImGui::TreePop;
                            const auto tree_node = ImStructs::make_component_wrapper(std::function(TreeNode), static_cast<const char*>("Tree Node"));
                            const auto tree_pop = ImStructs::make_component_wrapper(ImGui::TreePop);
                            const auto tree = new ImStructs::ScopedImStruct(tree_node, tree_pop);
                            tree->Name = "ImGui::TreeNode";
                            tree->CanvasFlags = ImStructs::CanvasFlags_Clicked;
                            tree_node->Name = "Tree Node";
                            tree_node->FunctionName = "ImGui::TreeNode";
                            tree_node->ArgumentNames = {"Label"};
                            tree_pop->Name = "Tree Pop";
                            tree_pop->FunctionName = "ImGui::TreePop";
                            tree_pop->ArgumentNames = {};
                            return tree;
                        })
                    },
                    {
                        "Combo",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*BeginCombo)(const char*, const char*, ImGuiComboFlags) = ImGui::BeginCombo;
                            void (*EndCombo)() = ImGui::EndCombo;
                            const auto begin_combo = ImStructs::make_component_wrapper(
                                ImGui::BeginCombo, static_cast<const char*>("Combo"), static_cast<const char*>("Combo"), 0);
                            const auto end_combo = ImStructs::make_component_wrapper(ImGui::EndCombo);
                            const auto combo = new ImStructs::ScopedImStruct(begin_combo, end_combo);
                            combo->CanvasFlags = ImStructs::CanvasFlags_Clicked;
                            begin_combo->Name = "Begin Combo";
                            begin_combo->FunctionName = "ImGui::BeginCombo";
                            begin_combo->ArgumentNames = {"Label", "Preview_value", "Flags"};
                            end_combo->Name = "End Combo";
                            end_combo->FunctionName = "ImGui::EndCombo";
                            end_combo->ArgumentNames = {};
                            return combo;
                        })
                    },
                    {
                        "Selectable",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*Selectable)(const char*, bool*, ImGuiSelectableFlags, const ImVec2&) = ImGui::Selectable;
                            const auto selectable = ImStructs::make_component_wrapper(
                                std::function(Selectable), static_cast<const char*>("Selectable"), new bool(false), 0, *new ImVec2(0, 0));
                            selectable->Name = "Selectable";
                            selectable->FunctionName = "ImGui::Selectable";
                            selectable->ArgumentNames = {"Label", "Selected", "Flags", "Size"};
                            return selectable;
                        })
                    },
                    {
                        "Collapsing Header",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*CollapsingHeader)(const char*, ImGuiTreeNodeFlags) = ImGui::CollapsingHeader;
                            const auto begin_collapsing_header = ImStructs::make_component_wrapper(
                                std::function(CollapsingHeader), static_cast<const char*>("Collapsing Header"), 0);
                            const auto end_collapsing_header = ImStructs::make_component_wrapper(std::function([]() {}));
                            const auto collapsing_header = new ImStructs::ScopedImStruct(begin_collapsing_header, end_collapsing_header);
                            begin_collapsing_header->Name = "Collapsing Header";
                            begin_collapsing_header->FunctionName = "ImGui::CollapsingHeader";
                            begin_collapsing_header->ArgumentNames = {"Label", "Flags"};
                            end_collapsing_header->Name = "End Collapsing Header";
                            end_collapsing_header->FunctionName = "// Collapsing Header Has No End Function";
                            end_collapsing_header->ArgumentNames = {};
                            return collapsing_header;
                        })
                    },
                    {
                        "Tab Bar",
                        new const ImStructs::ImGuiComponentFactory([]()
                        {
                            bool (*BeginTabBar)(const char*, ImGuiTabBarFlags) = ImGui::BeginTabBar;
                            void (*EndTabBar)() = ImGui::EndTabBar;
                            const auto begin_tab_bar = ImStructs::make_component_wrapper(
                                std::function(BeginTabBar), static_cast<const char*>("Tab Bar"), 0);
                            const auto end_tab_bar = ImStructs::make_component_wrapper(std::function(EndTabBar));
                            const auto tab_bar = new ImStructs::ScopedImStruct(begin_tab_bar, end_tab_bar);
                            begin_tab_bar->Name = "Begin Tab Bar";
                            begin_tab_bar->FunctionName = "ImGui::BeginTabBar";
                            begin_tab_bar->ArgumentNames = {"Str_id", "Flags"};
                            end_tab_bar->Name = "End Tab Bar";
                            end_tab_bar->FunctionName = "ImGui::EndTabBar";
                            end_tab_bar->ArgumentNames = {};
                            return tab_bar;
                        })
                    }
                }   
            }
        };
    return plugin;
}
            