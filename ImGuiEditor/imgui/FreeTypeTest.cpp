#include "FreeTypeTest.h"

#include "imgui_internal.h"
#include "misc/freetype/imgui_freetype.h"

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

void FreeTypeTest::ShowFontsOptionsWindow()
{
    ImFontAtlas* atlas = ImGui::GetIO().Fonts;

    ImGui::Begin("FreeType Options");
    ImGui::ShowFontSelector("Fonts");
    WantRebuild |= ImGui::RadioButton("FreeType", (int*)&BuildMode, FontBuildMode_FreeType);
    ImGui::SameLine();
    WantRebuild |= ImGui::RadioButton("Stb (Default)", (int*)&BuildMode, FontBuildMode_Stb);
    WantRebuild |= ImGui::DragInt("TexGlyphPadding", &atlas->TexGlyphPadding, 0.1f, 1, 16);
    WantRebuild |= ImGui::DragFloat("RasterizerMultiply", &RasterizerMultiply, 0.001f, 0.0f, 2.0f);
    ImGui::Separator();

    if (BuildMode == FontBuildMode_FreeType)
    {
#ifndef IMGUI_ENABLE_FREETYPE
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Error: FreeType builder not compiled!");
#endif
        WantRebuild |= ImGui::CheckboxFlags("NoHinting", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_NoHinting);
        WantRebuild |= ImGui::CheckboxFlags("NoAutoHint", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_NoAutoHint);
        WantRebuild |= ImGui::CheckboxFlags("ForceAutoHint", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_ForceAutoHint);
        WantRebuild |= ImGui::CheckboxFlags("LightHinting", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_LightHinting);
        WantRebuild |= ImGui::CheckboxFlags("MonoHinting", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_MonoHinting);
        WantRebuild |= ImGui::CheckboxFlags("Bold", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_Bold);
        WantRebuild |= ImGui::CheckboxFlags("Oblique", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_Oblique);
        WantRebuild |= ImGui::CheckboxFlags("Monochrome", &FreeTypeBuilderFlags, ImGuiFreeTypeBuilderFlags_Monochrome);
    }

    if (BuildMode == FontBuildMode_Stb)
    {
#ifndef IMGUI_ENABLE_STB_TRUETYPE
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Error: stb_truetype builder not compiled!");
#endif
    }
    ImGui::End();
}
