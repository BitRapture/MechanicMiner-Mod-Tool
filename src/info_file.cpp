#include "info_file.h"
using namespace br;

#include <filesystem>
#include <string>

namespace InfoFileDefaults
{
    int constexpr c_VersionMajor = 1;
    int constexpr c_VersionMinor = 0;

    std::string const c_VersionStr = std::to_string(c_VersionMajor) + "." + std::to_string(c_VersionMinor);
}

const char* InfoFile::GetFileName() const
{
    return "info.txt";
}

bool InfoFile::IsValid() const
{
    return !m_GamePath.empty();
}

bool InfoFile::Serialize(std::ofstream& oFile, size_t fileSize) const
{
    oFile << InfoFileDefaults::c_VersionStr; oFile << '\n';
    oFile << m_GamePath;

    return true;
}

bool InfoFile::Deserialize(std::ifstream& iFile, size_t fileSize)
{
    std::string versionStr;
    std::getline(iFile, versionStr);
    if (versionStr != InfoFileDefaults::c_VersionStr)
        return false;
    
    std::string gamePathStr;
    std::getline(iFile, gamePathStr);
    if (gamePathStr.empty() || !std::filesystem::exists(gamePathStr))
        return false;

    m_GamePath = gamePathStr;
    return true;
}

void InfoFile::SetGamePath(std::string const& path)
{
    if (!std::filesystem::exists(path))
        return;
    
    m_GamePath = path;
}

InfoFile::InfoFile()
    : m_GamePath()
{ }