#pragma once

#include <algorithm>

namespace br::UI
{
    class PercentOrValue
    {
    public:
        enum class Type
        {
            Value = 0,
            Percent
        };

    public:
        float Get() const { return m_Data; }
        Type GetType() const { return m_Type; }

    public:
        float GetMinOrScaledValue(float value) const
        {
            return m_Type == Type::Value ? std::min(m_Data, value) : m_Data * value;
        }

    public:
        float operator=(float value) 
        { 
            m_Data = m_Type == Type::Value ? value : std::clamp(value, 0.0f, 1.0f); 
            return m_Data; 
        }

        bool operator<(float rhs) const
        {
            return m_Data < rhs;
        }
        bool operator<=(float rhs) const
        {
            return m_Data <= rhs;
        }
        bool operator>(float rhs) const
        {
            return m_Data > rhs;
        }
        bool operator>=(float rhs) const
        {
            return m_Data >= rhs;
        }

        operator float() const { return Get(); }

    public:
        PercentOrValue()
            : m_Data(0.0f)
            , m_Type(Type::Value)
        { }

        PercentOrValue(float value)
            : m_Data(value)
            , m_Type(Type::Value)
        { }

        PercentOrValue(float value, Type type)
            : m_Data(value)
            , m_Type(type)
        { }

    private:
        float m_Data;
        Type m_Type;
    };

    class Percent : public PercentOrValue
    {
    public:
        Percent(float value)
            : PercentOrValue(value, PercentOrValue::Type::Percent)
        { }
    };

    class Value : public PercentOrValue
    {
    public:
        Value(float value)
            : PercentOrValue(value, PercentOrValue::Type::Value)
        { }
    };
}