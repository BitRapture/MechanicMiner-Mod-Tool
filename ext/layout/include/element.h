#pragma once
#include "layout_properties.h"
#include "percent_or_value.h"

#include <functional>
#include <string>
#include <vector>

namespace br::UI
{
    class Layout;
    class Element;
    typedef std::vector<Element> Elements;
    typedef std::function<void(Element&)> ElementCallback;
    typedef std::function<void(Element const&)> ElementConstCallback;

    class Element
    {
    public:
        struct Properties
        {
        public:
            std::string m_ID = std::string();
            ChildContentLayout m_ChildContentLayout = ChildContentLayout::Vertical;
            ChildGrowthDirection m_ChildGrowthDirection = ChildGrowthDirection::LeftToRight;
            PercentOrValue m_MaxWidth = -1.0f;
            PercentOrValue m_MaxHeight = -1.0f;

        public:
            bool IsConstrained(ChildContentLayout layout) const;

        public:
            Properties& SetID(std::string const& id);
            Properties& SetChildContentLayout(ChildContentLayout layout);
            Properties& SetChildGrowthDirection(ChildGrowthDirection direction);
            Properties& SetMaxWidth(PercentOrValue const& maxWidth);
            Properties& SetMaxHeight(PercentOrValue const& maxHeight);
        };

    public:
        Elements const& GetChildren() const { return m_Children; }
        Properties const& GetProperties() const { return m_Properties; }
        float GetX() const { return m_X; }
        float GetY() const { return m_Y; }
        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }

    public:
        void AnchorToPosition(Anchor anchor, float& outX, float& outY) const;
        void AnchorToPosition(float normalX, float normalY, float& outX, float& outY) const;

    public:
        void ForEachChild(ElementCallback const& callback);
        void ForEachChild(ElementConstCallback const& callback) const;
        void TraverseChildren(ElementCallback const& callback);
        void TraverseChildren(ElementConstCallback const& callback) const;

    public:
        Element();
        explicit Element(Properties const& properties);
        explicit Element(Properties const& properties, Elements const&& children);
        explicit Element(Elements const&& children);

    private:
        Elements m_Children;
        Properties m_Properties;

    private:
        friend class Layout;
        float m_X;
        float m_Y;
        float m_Width;
        float m_Height;
    };
}