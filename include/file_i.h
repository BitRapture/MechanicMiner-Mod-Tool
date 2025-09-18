#pragma once

#include <cstdint>
#include <fstream>

namespace br
{
    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint8_t u8;

    namespace FileDefaults
    {
        size_t constexpr c_U64Size = sizeof(u64);
        size_t constexpr c_U32Size = sizeof(u32);
        size_t constexpr c_U8Size = sizeof(u8);
    }

    class IFile
    {
    public:
        virtual const char* GetFileName() const { return ""; }
        virtual bool IsValid() const { return false; }
        virtual bool IsBinary() const { return false; }

    public:
        virtual bool Serialize(std::ofstream& oFile, size_t fileSize) const { return false; }
        virtual bool Deserialize(std::ifstream& iFile, size_t fileSize) { return false; }
    };
}