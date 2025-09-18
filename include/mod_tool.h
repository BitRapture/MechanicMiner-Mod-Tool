#pragma once
#include "raylib-cpp.hpp"
#include "file_manager.h"
#include "info_file.h"
#include "mm_links_file.h"
#include "mm_assets_file.h"
#include "layout.h"

namespace br
{
    class ModTool
    {
    public:
        void Run();

    public:
        ModTool();

    private:
        void DrawRequirePathScreen();
        void DrawMainScreen();

    private:
        bool PopulateAssetFiles();
        void ExportAssets();

    private:
        raylib::Window m_Window;
        FileManager m_FileManager;

        InfoFile m_Info;
        MMLinksFile m_AssetLinks;
        MMAssetsFile m_Assets;
        UI::Layout m_UI;
    };
}