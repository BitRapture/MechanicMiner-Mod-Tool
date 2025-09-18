#include "file_manager.h"
using namespace br;

#include "file_i.h"
#include <filesystem>

namespace FileManagerDefaults
{
    char const* c_RootFolder = "MM_Mod_Tool";
    char const* c_BackupsFolder = "Backups";
    char const* c_TexturePacksFolder = "Texture_Packs";
    char const* c_ExportsFolder = "Exports";

    std::string const c_Separator = { static_cast<char>(std::filesystem::path::preferred_separator) };
    std::string const c_ProgramPath = std::filesystem::current_path().string().c_str();

    std::string const c_RootPath = c_ProgramPath + c_Separator + c_RootFolder;
    std::string const c_BackupsPath = c_RootPath + c_Separator + c_BackupsFolder;
    std::string const c_TexturePacksPath = c_RootPath + c_Separator + c_TexturePacksFolder;
    std::string const c_ExportsPath = c_RootPath + c_Separator + c_ExportsFolder;
}

bool FileManager::FileExists(FilePaths path, IFile const& file)
{
    std::string const& pathStr = GetPath(path);
    return FileExists(pathStr + FileManagerDefaults::c_Separator + file.GetFileName());
}

bool FileManager::FileExists(std::string const& path, IFile const& file)
{
    return FileExists(path + FileManagerDefaults::c_Separator + file.GetFileName());
}

bool FileManager::FileExists(std::string const& path)
{
    return std::filesystem::exists(path);
}

bool FileManager::SerializeFile(FilePaths path, IFile const& file)
{
    return SerializeFile(GetPath(path), file);
}

bool FileManager::SerializeFile(std::string const& path, IFile const& file)
{
    if (!file.IsValid())
        return false;

    std::ios_base::openmode const openFlags = file.IsBinary() ? std::ios_base::binary : static_cast<std::ios_base::openmode>(0);
    std::string fullPath = path + FileManagerDefaults::c_Separator + file.GetFileName();
    std::ofstream oFile(fullPath, openFlags);

    if (!oFile.is_open())
        return false;

    size_t const fileSize = std::filesystem::file_size(fullPath);
    bool const isSerialized = file.Serialize(oFile, fileSize);
    oFile.close();

    return isSerialized;
}

bool FileManager::DeserializeFile(FilePaths path, IFile& out_File)
{
    return DeserializeFile(GetPath(path), out_File);
}

bool FileManager::DeserializeFile(std::string const& path, IFile& out_File)
{
    std::ios_base::openmode const openFlags = out_File.IsBinary() ? std::ios_base::binary : static_cast<std::ios_base::openmode>(0);
    std::string fullPath = path + FileManagerDefaults::c_Separator + out_File.GetFileName();
    std::ifstream iFile(fullPath, openFlags);

    if (!iFile.is_open())
        return false;

    size_t const fileSize = std::filesystem::file_size(fullPath);
    bool const isDeserialized = out_File.Deserialize(iFile, fileSize);
    iFile.close();

    return isDeserialized;
}

FileManager::FileManager()
    : m_DirectoriesValid(false)
{
    ValidateDirectories();
}

std::string const& FileManager::GetPath(FilePaths path)
{
    switch (path)
    {
    case FilePaths::Root:
        return FileManagerDefaults::c_RootPath;
    case FilePaths::Backups:
        return FileManagerDefaults::c_BackupsPath;
    case FilePaths::TexturePacks:
        return FileManagerDefaults::c_TexturePacksPath;
    case FilePaths::Exports:
        return FileManagerDefaults::c_ExportsPath;
    }

    throw;
}

void FileManager::ValidateDirectories()
{
    bool directoriesValid = true;

    if (!std::filesystem::exists(FileManagerDefaults::c_RootPath))
        directoriesValid &= std::filesystem::create_directory(FileManagerDefaults::c_RootPath);

    if (!std::filesystem::exists(FileManagerDefaults::c_BackupsPath))
        directoriesValid &= std::filesystem::create_directory(FileManagerDefaults::c_BackupsPath);

    if (!std::filesystem::exists(FileManagerDefaults::c_TexturePacksPath))
        directoriesValid &= std::filesystem::create_directory(FileManagerDefaults::c_TexturePacksPath);

    if (!std::filesystem::exists(FileManagerDefaults::c_ExportsPath))
        directoriesValid &= std::filesystem::create_directory(FileManagerDefaults::c_ExportsPath);

    m_DirectoriesValid = directoriesValid;
}