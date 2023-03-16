#include "FreeTypeTest.h"

#include "imgui_internal.h"

bool FreeTypeTest::PreNewFrame()
{
    if (!WantRebuild)
        return false;

    ImFontAtlas* atlas = ImGui::GetIO().Fonts;
    for (int n = 0; n < atlas->ConfigData.Size; n++)
        ((ImFontConfig*)&atlas->ConfigData[n])->RasterizerMultiply = RasterizerMultiply;

    // Allow for dynamic selection of the builder. 
    // In real code you are likely to just define IMGUI_ENABLE_FREETYPE and never assign to FontBuilderIO.
#ifdef IMGUI_ENABLE_FREETYPE
        if (BuildMode == FontBuildMode_FreeType)
        {
            atlas->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType();
            atlas->FontBuilderFlags = FreeTypeBuilderFlags;
        }
#endif
#ifdef IMGUI_ENABLE_STB_TRUETYPE
        if (BuildMode == FontBuildMode_Stb)
        {
            atlas->FontBuilderIO = ImFontAtlasGetBuilderForStbTruetype();
            atlas->FontBuilderFlags = 0;
        }
#endif
    atlas->Build();
    WantRebuild = false;
    return true;
}
