#pragma once
#include "raygui_impl.h"
#include "raylib-cpp.hpp"

#include <string>

namespace br
{
    enum class Alignment
    {
        Left = 0,
        Center
    };
    
    namespace ListBuilderDefaults
    {
        int constexpr c_TempTextSize = 240;
    }

    class ListBuilder
    {
    public:
        ListBuilder& Text(std::string const& text, Alignment alignment = Alignment::Left, int textSize = 16)
        {
            DrawText(text.c_str(), 0.0f, m_Pointer, textSize, BLACK);
            
            m_Pointer += textSize;
            return *this;
        }   

        ListBuilder& InputText(std::string& text, Alignment alignment = Alignment::Left, int textSize = 16)
        {
            static char s_TempText[ListBuilderDefaults::c_TempTextSize]{ 0 };
            for (int i = 0; i < ListBuilderDefaults::c_TempTextSize; ++i)
                s_TempText[i] = i < text.size() ? text.at(i) : 0;

            GuiTextBox(raylib::Rectangle(0.0f, m_Pointer, m_ContextSize.x, textSize), s_TempText, ListBuilderDefaults::c_TempTextSize, true);
            text = s_TempText;

            m_Pointer += textSize;
            return *this;
        }

        ListBuilder& Button(std::string const& text, bool& out_Pressed, Alignment alignment = Alignment::Left, int textSize = 16)
        {
            int const pressed = GuiButton(raylib::Rectangle(0.0f, m_Pointer, m_ContextSize.x, textSize), text.c_str());

            out_Pressed = pressed > 0;
            m_Pointer += textSize;
            return *this;
        }

    public:
        static ListBuilder Build(raylib::Vector2 contextSize) { return ListBuilder(contextSize); }

        ListBuilder(raylib::Vector2 const& contextSize)
            : m_ContextSize(contextSize)
            , m_Pointer(0.0f)
        { }

        ListBuilder()
            : ListBuilder(raylib::Vector2::Zero())
        { }

    private:
        raylib::Vector2 m_ContextSize;
        float m_Pointer;
    };
}