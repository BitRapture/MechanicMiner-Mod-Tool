#include "layout.h"
using namespace br::UI;

#include <utility>

namespace LayoutHelpers
{
    constexpr float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    constexpr float GetRelevantSize(ChildContentLayout layout, float width, float height)
    {
        switch (layout)
        {
        case ChildContentLayout::Floating:
            return std::max(width, height);
        case ChildContentLayout::Horizontal:
            return width;
        case ChildContentLayout::Vertical:
            return height;
        }
        return 0.0f;
    }

    constexpr bool InRectBounds(float x, float y, float rectX, float rectY, float width, float height)
    {
        return x >= rectX && x <= rectX + width && y >= rectY && y <= rectY + height;
    }
}

bool Layout::HasID(std::string const& id) const
{
    return m_IDIndexMap.find(id) != m_IDIndexMap.end();
}

Element const& Layout::GetElement(std::string const& id) const
{
    if (!HasID(id))
        throw;
    
    return *m_IDElements.at(m_IDIndexMap.at(id));
}

bool Layout::FindLastElementRectForPosition(float x, float y, float& outX, float& outY, float& outWidth, float& outHeight) const
{
    bool foundRect = false;
    Element const* lastElement = &m_Root;
    while (lastElement && !lastElement->m_Children.empty())
    {
        for (Element const& child : lastElement->m_Children)
        {
            if (LayoutHelpers::InRectBounds(x, y, child.m_X, child.m_Y, child.m_Width, child.m_Height))
            {
                outX = child.m_X;
                outY = child.m_Y;
                outWidth = child.m_Width;
                outHeight = child.m_Height;

                foundRect = true;
                lastElement = &child;
                break;
            }
        }

        if (!foundRect)
            break;
    }
    
    return foundRect;
}

void Layout::ResizeContent(float width, float height)
{
    m_Root.m_X = 0.0f;
    m_Root.m_Y = 0.0f;
    m_Root.m_Width = width;
    m_Root.m_Height = height;

    UpdateElement(m_Root);
}

void Layout::PopulateIDs()
{
    m_IDIndexMap.clear();
    m_IDElements.clear();
    m_TotalElements = 1;

    m_Root.TraverseChildren([&](Element const& element)
    {
        Element::Properties const& properties = element.m_Properties;
        if (!properties.m_ID.empty())
        {
            m_IDIndexMap[properties.m_ID] = m_IDElements.size();
            m_IDElements.emplace_back(&element);
        }

        ++m_TotalElements;
    });
}

void Layout::UpdateElement(Element& element)
{
    Element::Properties const& properties = element.m_Properties;
    bool const iteratorDir = properties.m_ChildGrowthDirection != ChildGrowthDirection::RightToLeft;

    float childLayoutNormX = 0.0f;
    float childLayoutNormY = 0.0f;
    ChildContentLayoutToNormal(properties.m_ChildContentLayout, childLayoutNormX, childLayoutNormY);

    size_t const childCount = element.m_Children.size();
    float const childFract = childCount > 0 ? 1.0f / static_cast<float>(childCount) : 0.0f;

    float totalConstrainedWidth = 0.0f;
    float totalConstrainedHeight = 0.0f;
    int totalConstrained = 0;
    for (size_t i = 0; i < childCount; ++i)
    {
        Element& child = element.m_Children[i];
        Element::Properties const& childProps = child.m_Properties;

        if (childProps.IsConstrained(properties.m_ChildContentLayout))
        {
            child.m_Width = childProps.m_MaxWidth >= 0.0f ? std::min(element.m_Width, childProps.m_MaxWidth) : element.m_Width;
            child.m_Height = childProps.m_MaxHeight >= 0.0f ? std::min(element.m_Height, childProps.m_MaxHeight) : element.m_Height;

            totalConstrainedWidth += child.m_Width;
            totalConstrainedHeight += child.m_Height;
            ++totalConstrained;
        }
        else
        {
            child.m_Width = LayoutHelpers::Lerp(element.m_Width, 0.0f, childLayoutNormX);
            child.m_Height = LayoutHelpers::Lerp(element.m_Height, 0.0f, childLayoutNormY);
        }
    }

    float const remainderWidth = element.m_Width - totalConstrainedWidth;
    float const remainderHeight = element.m_Height - totalConstrainedHeight;
    float const relevantRemainderSize = LayoutHelpers::GetRelevantSize(properties.m_ChildContentLayout, remainderWidth, remainderHeight);
    int const totalUnconstrained = childCount - totalConstrained;

    if (relevantRemainderSize < 0.0f)
    {
        float const overRemovalAmount = abs(relevantRemainderSize);
        float const relevantTotalConstrainSize = LayoutHelpers::GetRelevantSize(properties.m_ChildContentLayout, totalConstrainedWidth, totalConstrainedHeight);

        for (size_t i = 0; i < childCount; ++i)
        {
            Element& child = element.m_Children[i];
            Element::Properties const& childProps = child.m_Properties;

            if (childProps.IsConstrained(properties.m_ChildContentLayout))
            {
                float const relevantSize = LayoutHelpers::GetRelevantSize(properties.m_ChildContentLayout, child.m_Width, child.m_Height);
                float const removePortion = overRemovalAmount * (relevantSize / relevantTotalConstrainSize);

                child.m_Width -= LayoutHelpers::Lerp(0.0f, removePortion, childLayoutNormX);
                child.m_Height -= LayoutHelpers::Lerp(0.0f, removePortion, childLayoutNormY);
            }
        }
    }
    else if (relevantRemainderSize > 0.0f && totalUnconstrained > 0)
    {
        float const unconstrainedFract = 1.0f / static_cast<float>(totalUnconstrained);
        float const unconstrainChildPortion = relevantRemainderSize * unconstrainedFract;

        for (size_t i = 0; i < childCount; ++i)
        {
            Element& child = element.m_Children[i];
            Element::Properties const& childProps = child.m_Properties;

            if (!childProps.IsConstrained(properties.m_ChildContentLayout))
            {
                child.m_Width = LayoutHelpers::Lerp(child.m_Width, unconstrainChildPortion, childLayoutNormX);
                child.m_Height = LayoutHelpers::Lerp(child.m_Height, unconstrainChildPortion, childLayoutNormY);
            }
        }
    }

    float posX = element.m_X;
    float posY = element.m_Y;
    for (size_t i = 0; i < childCount; ++i)
    {
        Element& child = element.m_Children[i];

        child.m_X = posX;
        child.m_Y = posY;

        posX += LayoutHelpers::Lerp(0.0f, child.m_Width, childLayoutNormX);
        posY += LayoutHelpers::Lerp(0.0f, child.m_Height, childLayoutNormY);
    }

    for (size_t i = 0; i < childCount; ++i)
    {
        Element& child = element.m_Children[i];
        UpdateElement(child);
    }
}

Layout::Layout()
    : m_Root()
    , m_IDIndexMap()
    , m_IDElements()
    , m_TotalElements(1)
{ }

Layout::Layout(Element::Properties const& properties, Elements const&& children)
    : m_Root(properties, std::move(children))
    , m_IDIndexMap()
    , m_IDElements()
    , m_TotalElements(1)
{
    PopulateIDs();
}

Layout::Layout(Elements const&& children)
    : m_Root(std::move(children))
    , m_IDIndexMap()
    , m_IDElements()
    , m_TotalElements(1)
{
    PopulateIDs();
}