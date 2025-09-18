#pragma once
#include "file_i.h"

#include <string>

namespace br
{
    class InfoFile : public IFile
    {
    public:
        std::string const& GetGamePath() const { return m_GamePath; }

    public:
        virtual const char* GetFileName() const override;
        virtual bool IsValid() const override;

    public:
        virtual bool Serialize(std::ofstream& oFile, size_t fileSize) const override;
        virtual bool Deserialize(std::ifstream& iFile, size_t fileSize) override;

    public:
        void SetGamePath(std::string const& path);

    public:
        InfoFile();

    private:
        std::string m_GamePath;
    };
}