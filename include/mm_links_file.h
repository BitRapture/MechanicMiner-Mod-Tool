#pragma once
#include "file_i.h"

#include <vector>

namespace br
{
    class MMLinksFile : public IFile
    {
    public:
        virtual const char* GetFileName() const override;
        virtual bool IsValid() const override;
        virtual bool IsBinary() const override { return true; }

    public:
        virtual bool Serialize(std::ofstream& oFile, size_t fileSize) const override;
        virtual bool Deserialize(std::ifstream& iFile, size_t fileSize) override;

    public:
        MMLinksFile();

    private:
        std::vector<u64> m_AssetIndices;
    };
}