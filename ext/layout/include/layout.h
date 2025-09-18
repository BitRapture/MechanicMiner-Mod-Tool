#pragma once
#include "element.h"

#include <vector>
#include <unordered_map>

namespace br::UI
{
    class Layout
    {
    public:
        bool HasID(std::string const& id) const;
        Element const& GetElement(std::string const& id) const;
        bool FindLastElementRectForPosition(float x, float y, float& outX, float& outY, float& outWidth, float& outHeight) const;

    public:
        Element const& GetRoot() const { return m_Root; }
        size_t GetElementCount() { return m_TotalElements; }
    
    public:
        void ResizeContent(float width, float height);

    public:
        Layout();
        explicit Layout(Element::Properties const& properties, Elements const&& children);
        explicit Layout(Elements const&& children);

    private:
        void PopulateIDs();
        void UpdateElement(Element& element);

    private:
        Element m_Root;

        std::unordered_map<std::string, size_t> m_IDIndexMap;
        std::vector<Element const*> m_IDElements;
        size_t m_TotalElements;
    };
}