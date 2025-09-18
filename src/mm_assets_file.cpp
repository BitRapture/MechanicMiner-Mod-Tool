#include "mm_assets_file.h"
using namespace br;

#include <string>

namespace MMAssetsFileDefaults
{
    std::string const c_PNGHeader = "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A";
    std::string const c_WAVRIFFHeader = "RIFF";

    std::string const c_PNGExtension = ".png";
    std::string const c_WAVExtension = ".wav";
    std::string const c_InvalidExtension = ".asset";
}

const char* MMAssetsFile::Asset::GetFileName() const
{
    return (m_FileName + MMAssetsFile::GetAssetExtension(m_AssetType)).c_str();
}

bool MMAssetsFile::Asset::IsValid() const
{
    return m_AssetType != MMAssetsFile::AssetType::Invalid 
            && !m_FileName.empty() 
            && !m_AssetData.empty();
}

bool MMAssetsFile::Asset::Serialize(std::ofstream& oFile, size_t fileSize) const
{
    oFile.write(reinterpret_cast<char const*>(m_AssetData.data()), m_AssetData.size() * FileDefaults::c_U8Size);

    return true;
}

bool MMAssetsFile::Asset::Deserialize(std::ifstream& iFile, size_t fileSize)
{
    m_AssetData.clear();
    m_AssetData.resize(fileSize);

    iFile.read(reinterpret_cast<char*>(m_AssetData.data()), fileSize * FileDefaults::c_U8Size);

    MMAssetsFile::AssetType const assetType = MMAssetsFile::GetAssetType(m_AssetData);
    m_AssetType = assetType; 

    return true;
}

MMAssetsFile::Asset::Asset()
    : m_AssetData()
    , m_FileName()
    , m_AssetType(MMAssetsFile::AssetType::Invalid)
{ }

bool AnalyzeHeader(std::string const& header, std::vector<u8> const& rawData)
{
    if (rawData.size() >= header.size())
    {
        bool match = true;
        for (int i = 0; i < header.size(); ++i)
        {
            match &= rawData[i] == header.at(i);
        }

        if (match)
            return true;
    }

    return false;
}

MMAssetsFile::AssetType MMAssetsFile::GetAssetType(std::vector<u8> const& rawData)
{
    if (AnalyzeHeader(MMAssetsFileDefaults::c_PNGHeader, rawData))
        return AssetType::PNG;

    if (AnalyzeHeader(MMAssetsFileDefaults::c_WAVRIFFHeader, rawData))
        return AssetType::WAV;

    return AssetType::Invalid;
}

std::string const& MMAssetsFile::GetAssetExtension(AssetType assetType)
{
    switch (assetType)
    {
    case AssetType::Invalid:
        return MMAssetsFileDefaults::c_InvalidExtension;
    case AssetType::PNG:
        return MMAssetsFileDefaults::c_PNGExtension;
    case AssetType::WAV:
        return MMAssetsFileDefaults::c_WAVExtension;
    }

    throw;
}

const char* MMAssetsFile::GetFileName() const
{
    return "main.mechanicminer_asset_64";
}

bool MMAssetsFile::IsValid() const
{
    return !m_Assets.empty() && !m_AssetIndices.empty();
}

bool MMAssetsFile::Serialize(std::ofstream& oFile, size_t fileSize) const
{    
    for (Asset const& asset : m_Assets)
    {
        u32 const assetSize = asset.m_AssetData.size();
        oFile.write(reinterpret_cast<char const*>(&assetSize), FileDefaults::c_U32Size);

        if (!asset.Serialize(oFile, fileSize))
            return false;
    }

    return true;
}

bool MMAssetsFile::Deserialize(std::ifstream& iFile, size_t fileSize)
{
    m_Assets.clear();
    m_AssetIndices.clear();

    u64 currentIndex = 0;
    u32 assetSize = 0;
    while (iFile.read(reinterpret_cast<char*>(&assetSize), FileDefaults::c_U32Size))
    {
        if (assetSize == 0 || assetSize >= fileSize || currentIndex + assetSize >= fileSize)
            return false;

        Asset& asset = m_Assets.emplace_back();
        asset.m_FileName = std::to_string(m_Assets.size());

        if (!asset.Deserialize(iFile, assetSize))
            return false;

        m_AssetIndices.emplace_back(currentIndex);
        currentIndex += assetSize + FileDefaults::c_U32Size;
    }

    return true;
}

MMAssetsFile::MMAssetsFile()
    : m_Assets()
    , m_AssetIndices()
{ }