# ImGuiEditor (Name Not Final)
ImGuiEditor is a visual editor for Dear ImGui. Browse through all the available components and drag them onto the canvas. Rearrange components, edit them and when done easily compile them to a C++ file to integrate into your own project! Missing components from a library? Check out how to add them via the [Plugin System](#plugin-system) 

![Screenshot of the program](https://i.ibb.co/ctJpNDp/screenshot.png)

## Features
- Drag and drop most ImGui components
- Rapidly prototype
- Save files as layout files and open them later!
- Compile to your favorite language (C++ support only for now)
- Load plugins for third party libraries
- Different Themes: Renewed, [Visual Studio](https://github.com/Patitotective/ImThemes) and ImGui dark, light and classic

## Plugin System
Need a component from a third party library? Easily integrate a component just under 10 lines of code! Compile your Plugin to a dll file and just load it to access your custom components! 
```cpp
inline ImStructs::ImGuiComponentFactory* ColoredButtonV1 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColoredButtonV1, 
      ImString("Hello, Fancy Button!"), 
        ImVec2(0, 0), 
        *new ImColor(1.0f, 1.0f, 1.0f, 1.0f), 
        *new ImColor(0xA020F0FF), 
        *new ImColor(0x296d98FF)
    );
    component->Name = "ColoredButtonV1";
    component->FunctionName = "ImGui::ColoredButtonV1";
    component->ArgumentNames = {"Label", "Size", "Text Color", "Top Color", "Bottom Color"};
    return component;
});
```
Check out the [DefaultComponent](DefaultComponents/) library shipped with the editor to get an idea of how plugins are written! Feel free to notify us about any libraries you have integrated into ImGuiEditor and we might make a page of third party plugins!

:warning: **Pllugin API very experimental**: The API for defining plugins is not final will change!
