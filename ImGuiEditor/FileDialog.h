#pragma once
#include <filesystem>
#include <windows.h>

namespace FileSystem
{
    std::filesystem::path ShowOpenFileDialog();
    std::filesystem::path ShowSaveFileDialog(std::string_view default_name = "", std::string_view default_extension = "");
    std::string ReadFile(std::filesystem::path path);
    bool WriteFile(std::filesystem::path path, std::string_view data);
};
