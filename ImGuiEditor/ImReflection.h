#pragma once
#include <vector>

#include "ImStructs.h"

namespace ImReflection
{
    enum Type
    {
        FLOAT,
        VEC2,
        INT,
        BOOL,
        CATEGORY,
        CATEGORY_POP
    };

    inline Type GetType(const std::string_view& name)
    {
        if (name == "float")
        {
            return FLOAT;
        }
        if (name == "ImVec2")
        {
            return VEC2;
        }
        if (name == "int")
        {
            return INT;
        }
        if (name == "bool")
        {
            return BOOL;
        }
        if (name == "CATEGORY")
        {
            return CATEGORY;
        }
        if (name == "CATEGORY_POP")
        {
            return CATEGORY_POP;
        }
        assert(false && "Unknown type");
        return FLOAT;
    }

    struct Member
    {
        Type Type;
        std::string_view Name = "";

        union
        {
            void* Value = nullptr;
            float* Float;
            ImVec2* Vec2;
            int* Int;
            bool* Bool;
        };
    };

    // ReSharper disable once CppParameterMayBeConstPtrOrRef
    // because EditorHelper modifies the value of the member
    inline void Editor(std::vector<Member>& members, std::string_view search = "")
    {
        bool last_category_open = false;
        size_t category_stack = 0;
        for (const auto& member : members)
        {
            if (member.Type == CATEGORY)
            {
                const auto flags = search.empty() ? ImGuiTreeNodeFlags_None : ImGuiTreeNodeFlags_DefaultOpen;
                last_category_open = ImGui::TreeNodeEx(member.Name.data(), flags);
                category_stack++;
            }
            else if (member.Type == CATEGORY_POP)
            {
                assert(category_stack > 0 && "Category pop was called too much");
                if (last_category_open)
                {
                    ImGui::TreePop();
                }
                category_stack--;
            }

            if(category_stack > 0 && !last_category_open)
            {
                continue;
            }

            if(!member.Name.contains(search))
            {
                continue;
            }
            
            if (member.Type == FLOAT)
            {
                ImStructs::EditorHelper(member.Name, member.Float, ImStructs::EditorHelperFlags_Slider);
            }
            else if (member.Type == VEC2)
            {
                ImStructs::EditorHelper(member.Name, member.Vec2);
            }
            else if (member.Type == INT)
            {
                ImStructs::EditorHelper(member.Name, member.Int);
            }
            else if (member.Type == BOOL)
            {
                ImStructs::EditorHelper(member.Name, member.Bool);
            }
        }
        assert(category_stack == 0 && "Category pop was not called enough");
    }
};
