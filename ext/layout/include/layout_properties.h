#pragma once

namespace br::UI
{
    enum class Anchor
    {
        TopLeft = 0,
        TopMiddle,
        TopRight,
        CenterLeft,
        CenterMiddle,
        CenterRight,
        BottomLeft,
        BottomMiddle,
        BottomRight,

        Center = CenterMiddle
    };

    inline constexpr void AnchorToNormal(Anchor anchor, float& outX, float& outY)
    {
        switch (anchor)
        {
        case Anchor::TopLeft:
            outX = 0.0f;
            outY = 0.0f;
            break;
        case Anchor::TopMiddle:
            outX = 0.5f;
            outY = 0.0f;
            break;
        case Anchor::TopRight:
            outX = 1.0f;
            outY = 0.0f;
            break;
        case Anchor::CenterLeft:
            outX = 0.0f;
            outY = 0.5f;
            break;
        case Anchor::CenterMiddle:
            outX = 0.5f;
            outY = 0.5f;
            break;
        case Anchor::CenterRight:
            outX = 1.0f;
            outY = 0.5f;
            break;
        case Anchor::BottomLeft:
            outX = 0.0f;
            outY = 1.0f;
            break;
        case Anchor::BottomMiddle:
            outX = 0.5f;
            outY = 1.0f;
            break;
        case Anchor::BottomRight:
            outX = 1.0f;
            outY = 1.0f;
            break;
        }
    }

    enum class ChildContentLayout
    {
        Floating = 0,
        Vertical,
        Horizontal
    };

    inline constexpr void ChildContentLayoutToNormal(ChildContentLayout layout, float& outX, float& outY)
    {
        switch (layout)
        {
        case ChildContentLayout::Floating:
            outX = 0.0f;
            outY = 0.0f;
            break;
        case ChildContentLayout::Vertical:
            outX = 0.0f;
            outY = 1.0f;
            break;
        case ChildContentLayout::Horizontal:
            outX = 1.0f;
            outY = 0.0f;
            break;
        }
    }

    enum class ChildGrowthDirection
    {
        LeftToRight = 0,
        Center,
        RightToLeft,

        TopToBottom = LeftToRight,
        BottomToTop = RightToLeft 
    };
}