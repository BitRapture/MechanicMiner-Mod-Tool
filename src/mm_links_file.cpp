#include "mm_links_file.h"
using namespace br;

const char* MMLinksFile::GetFileName() const
{
    return "main.mechanicminer_asset_64_links";
}

bool MMLinksFile::IsValid() const
{
    return !m_AssetIndices.empty();
}

bool MMLinksFile::Serialize(std::ofstream& oFile, size_t fileSize) const
{
    oFile.write(reinterpret_cast<char const*>(m_AssetIndices.data()), m_AssetIndices.size() * FileDefaults::c_U64Size);
    
    return true;
}

bool MMLinksFile::Deserialize(std::ifstream& iFile, size_t fileSize)
{
    size_t const indexCount = (fileSize / FileDefaults::c_U64Size) + 1;

    m_AssetIndices.clear();
    m_AssetIndices.resize(indexCount);

    iFile.read(reinterpret_cast<char*>(m_AssetIndices.data()), indexCount * FileDefaults::c_U64Size);

    return true;
}

MMLinksFile::MMLinksFile()
    : m_AssetIndices()
{ }