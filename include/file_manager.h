#pragma once

#include <string>

namespace br
{
    class IFile;

    enum class FilePaths
    {
        Root = 0,
        TexturePacks,
        Backups,
        Exports
    };

    class FileManager
    {
    public:
        bool IsDirectoriesValid() const { return m_DirectoriesValid; }
        static bool FileExists(FilePaths path, IFile const& file);
        static bool FileExists(std::string const& path, IFile const& file);
        static bool FileExists(std::string const& path);

    public:
        static bool SerializeFile(FilePaths path, IFile const& file);
        static bool SerializeFile(std::string const& path, IFile const& file);
        static bool DeserializeFile(FilePaths path, IFile& out_File);
        static bool DeserializeFile(std::string const& path, IFile& out_File);

    public:
        FileManager();

    private:
        static std::string const& GetPath(FilePaths path);
        void ValidateDirectories();

    private:
        bool m_DirectoriesValid;
    };
}