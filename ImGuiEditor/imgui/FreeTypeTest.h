#pragma once

struct FreeTypeTest
{
    enum FontBuildMode { FontBuildMode_FreeType, FontBuildMode_Stb };

    FontBuildMode   BuildMode = FontBuildMode_FreeType;
    bool            WantRebuild = true;
    float           RasterizerMultiply = 1.0f;
    unsigned int    FreeTypeBuilderFlags = 0;

    // Call _BEFORE_ NewFrame()
    bool PreNewFrame();

    // Call to draw UI
    void ShowFontsOptionsWindow();
};
