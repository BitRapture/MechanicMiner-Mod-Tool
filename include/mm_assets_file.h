#pragma once
#include "file_i.h"

#include <vector>

namespace br
{
    class MMAssetsFile : public IFile
    {
    public:
        enum class AssetType
        {
            Invalid = -1,
            PNG = 0,
            WAV
        };

        class Asset : public IFile
        {
        public:
            virtual const char* GetFileName() const override;
            virtual bool IsValid() const override;
            virtual bool IsBinary() const override { return true; }

        public:
            virtual bool Serialize(std::ofstream& oFile, size_t fileSize) const override;
            virtual bool Deserialize(std::ifstream& iFile, size_t fileSize) override;

        public:
            Asset();

        private:
            friend class MMAssetsFile;
            std::vector<u8> m_AssetData;
            std::string m_FileName;
            AssetType m_AssetType;
        };

    public:
        std::vector<u64> const& GetAssetIndices() const { return m_AssetIndices; }
        std::vector<Asset> const& GetAssets() const { return m_Assets; }
        static AssetType GetAssetType(std::vector<u8> const& rawData);
        static std::string const& GetAssetExtension(AssetType assetType);

    public:
        virtual const char* GetFileName() const override;
        virtual bool IsValid() const override;
        virtual bool IsBinary() const override { return true; }

    public:
        virtual bool Serialize(std::ofstream& oFile, size_t fileSize) const override;
        virtual bool Deserialize(std::ifstream& iFile, size_t fileSize) override;

    public:
        MMAssetsFile();

    private:
        std::vector<u64> m_AssetIndices;
        std::vector<Asset> m_Assets;
    };
}