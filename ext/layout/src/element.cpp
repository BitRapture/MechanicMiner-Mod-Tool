#include "element.h"
using namespace br::UI;

#include <algorithm>

bool Element::Properties::IsConstrained(ChildContentLayout layout) const
{
    bool const constrainedX = m_MaxWidth >= 0 && layout == ChildContentLayout::Horizontal;
    bool const constrainedY = m_MaxHeight >= 0 && layout == ChildContentLayout::Vertical;

    return constrainedX || constrainedY;
}

Element::Properties& Element::Properties::SetID(std::string const& id)
{
    m_ID = id;
    return *this;
}

Element::Properties& Element::Properties::SetChildContentLayout(ChildContentLayout layout)
{
    m_ChildContentLayout = layout;
    return *this;
}

Element::Properties& Element::Properties::SetChildGrowthDirection(ChildGrowthDirection direction)
{
    m_ChildGrowthDirection = direction;
    return *this;
}

Element::Properties& Element::Properties::SetMaxWidth(float maxWidth)
{
    m_MaxWidth = maxWidth;
    return *this;
}

Element::Properties& Element::Properties::SetMaxHeight(float maxHeight)
{
    m_MaxHeight = maxHeight;
    return *this;
}

void Element::AnchorToPosition(Anchor anchor, float& outX, float& outY) const
{
    float normalX = 0.0f;
    float normalY = 0.0f;
    AnchorToNormal(anchor, normalX, normalY);
    AnchorToPosition(normalX, normalY, outX, outY);
}

void Element::AnchorToPosition(float normalX, float normalY, float& outX, float& outY) const
{
    normalX = std::clamp(normalX, 0.0f, 1.0f);
    normalY = std::clamp(normalY, 0.0f, 1.0f);

    outX = m_X + m_Width * normalX;
    outY = m_Y + m_Height * normalY;
}

void Element::ForEachChild(ElementCallback const& callback)
{
    for (Element& child : m_Children)
    {
        callback(child);
    }
}

void Element::ForEachChild(ElementConstCallback const& callback) const
{
    for (Element const& child : m_Children)
    {
        callback(child);
    }
}

void Element::TraverseChildren(ElementCallback const& callback)
{
    for (Element& child : m_Children)
    {
        callback(child); 
        child.TraverseChildren(callback);
    }
}

void Element::TraverseChildren(ElementConstCallback const& callback) const
{
    for (Element const& child : m_Children)
    {
        callback(child);
        child.TraverseChildren(callback);
    }
}

Element::Element()
    : m_Properties()
    , m_Children()
    , m_X(0.0f), m_Y(0.0f)
    , m_Width(0.0f), m_Height(0.0f)
{ }

Element::Element(Properties const& properties)
    : m_Properties(properties)
    , m_Children()
    , m_X(0.0f), m_Y(0.0f)
    , m_Width(0.0f), m_Height(0.0f)
{ }

Element::Element(Properties const& properties, Elements const&& children)
    : m_Properties(properties)
    , m_Children(children)
    , m_X(0.0f), m_Y(0.0f)
    , m_Width(0.0f), m_Height(0.0f)
{ }

Element::Element(Elements const&& children)
    : m_Properties()
    , m_Children(children)
    , m_X(0.0f), m_Y(0.0f)
    , m_Width(0.0f), m_Height(0.0f)
{ }