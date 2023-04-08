#include "FileDialog.h"

#include <fstream>

std::filesystem::path FileSystem::ShowOpenFileDialog()
{
    OPENFILENAME open_file_name;
    char szFile[260];       // buffer for file name
    HWND hwnd = nullptr;     // owner window
    HANDLE hf = nullptr;     // file handle

    // Initialize OPENFILENAME
    ZeroMemory(&open_file_name, sizeof(open_file_name));
    open_file_name.lStructSize = sizeof(open_file_name);
    open_file_name.hwndOwner = hwnd;
    open_file_name.lpstrFile = reinterpret_cast<LPWSTR>(szFile);
    open_file_name.lpstrFile[0] = '\0';
    open_file_name.nMaxFile = sizeof(szFile);
    open_file_name.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    open_file_name.nFilterIndex = 1;
    open_file_name.lpstrFileTitle = nullptr;
    open_file_name.nMaxFileTitle = 0;
    open_file_name.lpstrInitialDir = L"resources\\Sample Save Files";
    
    open_file_name.Flags = OFN_EXPLORER & OFN_ENABLEHOOK & OFN_FILEMUSTEXIST & OFN_PATHMUSTEXIST;
    const auto opened_file = GetOpenFileName(&open_file_name);
    if(!opened_file)
    {
        // return empty path
        return {};
    }
    return { open_file_name.lpstrFile };
}

std::filesystem::path FileSystem::ShowSaveFileDialog(std::string_view default_name, std::string_view default_extension)
{
    OPENFILENAME open_file_name;
    char szFile[260];       // buffer for file name
    HWND hwnd = nullptr;     // owner window
    HANDLE hf = nullptr;     // file handle

    // Initialize OPENFILENAME
    ZeroMemory(&open_file_name, sizeof(open_file_name));
    open_file_name.lStructSize = sizeof(open_file_name);
    open_file_name.hwndOwner = hwnd;
    open_file_name.lpstrFile = reinterpret_cast<LPWSTR>(szFile);
    open_file_name.lpstrFile[0] = '\0';
    open_file_name.nMaxFile = sizeof(szFile);
    open_file_name.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    open_file_name.nFilterIndex = 1;
    open_file_name.lpstrFileTitle = nullptr;
    open_file_name.nMaxFileTitle = 0;
    open_file_name.lpstrInitialDir = L"resources\\Sample Save Files";
    open_file_name.Flags = OFN_EXPLORER & OFN_ENABLEHOOK & OFN_PATHMUSTEXIST;
    const auto opened_file = GetSaveFileName(&open_file_name);
    if(!opened_file)
    {
        // return empty path
        return {};
    }
    return { open_file_name.lpstrFile };
}

std::string FileSystem::ReadFile(std::filesystem::path path)
{
    std::ifstream file_stream(path);
    return std::string(std::istreambuf_iterator<char>(file_stream), std::istreambuf_iterator<char>());
}

bool FileSystem::WriteFile(std::filesystem::path path, std::string_view data)
{
    std::ofstream output_file { path };
    if(!output_file.is_open())
    {
        return false;
    }
    output_file << data;
    return true;
}

