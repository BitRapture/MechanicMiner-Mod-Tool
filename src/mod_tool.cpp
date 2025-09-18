#include "mod_tool.h"
#include "gui_helpers.h"
using namespace br;

namespace ModToolDefaults
{
    int constexpr c_WindowWidth = 640;
    int constexpr c_WindowHeight = 480;
    char const* c_WindowTitle = "MM Mod Tool (v2.0)";
    unsigned int constexpr c_WindowFlags = FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT;
}

void ModTool::Run()
{
    if (!m_FileManager.IsDirectoriesValid())
        m_Window.Close();

    if (m_FileManager.FileExists(FilePaths::Root, m_Info))
    {
        if (m_FileManager.DeserializeFile(FilePaths::Root, m_Info))
        {
            if (!PopulateAssetFiles())
                m_Info = InfoFile();
        }
    }

    m_UI.ResizeContent(ModToolDefaults::c_WindowWidth, ModToolDefaults::c_WindowHeight);

    while (!m_Window.ShouldClose())
    {
        m_Window.BeginDrawing();
        m_Window.ClearBackground(raylib::Color::White());

        bool const infoValid = m_Info.IsValid();
        if (infoValid)
        {
            DrawMainScreen();
        }
        else
        {
            DrawRequirePathScreen();
        }

        m_Window.EndDrawing();
    }
}

void ModTool::DrawRequirePathScreen()
{
    static std::string s_GamePath = "";
    bool gamePathSubmitted = false;

    if (m_Window.IsResized())
    {
        m_UI.ResizeContent(m_Window.GetWidth(), m_Window.GetHeight());
    }

    size_t const elementCount = m_UI.GetElementCount();
    size_t current = 1;
    m_UI.GetRoot().TraverseChildren([&](UI::Element const& element)
    {
        raylib::Rectangle drawRect(element.GetX()
            , element.GetY()
            , element.GetWidth()
            , element.GetHeight());

        float const val = static_cast<float>(current) / static_cast<float>(elementCount);
        drawRect.Draw(ColorFromHSV(val * 360.0f, 1.0f, 1.0f));

        ++current;
    });

    raylib::Vector2 const mousePos = GetMousePosition();
    raylib::Rectangle drawRect;
    if (m_UI.FindLastElementRectForPosition(mousePos.x, mousePos.y, drawRect.x, drawRect.y, drawRect.width, drawRect.height))
    {
        drawRect.Draw(RAYWHITE);
    }

    ListBuilder::Build(m_Window.GetSize())
        .InputText(s_GamePath, Alignment::Left, 30)
        .Button("Submit", gamePathSubmitted);

    if (gamePathSubmitted)
    {
        m_Info.SetGamePath(s_GamePath);
        m_FileManager.SerializeFile(FilePaths::Root, m_Info);

        if (!PopulateAssetFiles())
            m_Info = InfoFile();
    }
}

void ModTool::DrawMainScreen()
{
    bool exportAssets = false;

    ListBuilder::Build(m_Window.GetSize())
        .Button("Export Assets", exportAssets);

    if (exportAssets)
        ExportAssets();
}

bool ModTool::PopulateAssetFiles()
{
    if (!m_Info.IsValid())
        return false;

    bool const linksExists = m_FileManager.FileExists(m_Info.GetGamePath(), m_AssetLinks);
    if (!linksExists)
        return false;

    bool const linksDeserialized = m_FileManager.DeserializeFile(m_Info.GetGamePath(), m_AssetLinks);
    if (!linksDeserialized)
        return false;

    if (!m_FileManager.FileExists(FilePaths::Backups, m_AssetLinks))
        m_FileManager.SerializeFile(FilePaths::Backups, m_AssetLinks);

    bool const assetsExists = m_FileManager.FileExists(m_Info.GetGamePath(), m_Assets);
    if (!assetsExists)
        return false;

    bool const assetsDeserialized = m_FileManager.DeserializeFile(m_Info.GetGamePath(), m_Assets);
    if (!assetsDeserialized)
        return false;

    if (!m_FileManager.FileExists(FilePaths::Backups, m_Assets))
        m_FileManager.SerializeFile(FilePaths::Backups, m_Assets);

    return true;
}

void ModTool::ExportAssets()
{
    if (!m_Assets.IsValid())
        return;

    std::vector<MMAssetsFile::Asset> const& assets = m_Assets.GetAssets();

    for (MMAssetsFile::Asset const& asset : assets)
    {
        m_FileManager.SerializeFile(FilePaths::Exports, asset);
    }
}

ModTool::ModTool()
    : m_Window(ModToolDefaults::c_WindowWidth
        , ModToolDefaults::c_WindowHeight
        , ModToolDefaults::c_WindowTitle
        , ModToolDefaults::c_WindowFlags)
    , m_FileManager()
    , m_Info()
    , m_AssetLinks()
    , m_Assets()
    , m_UI(UI::Element::Properties().SetChildContentLayout(UI::ChildContentLayout::Vertical)
        , { UI::Element()
            , UI::Element(UI::Element::Properties().SetChildContentLayout(UI::ChildContentLayout::Horizontal)
                , { UI::Element()
                    , UI::Element(UI::Element::Properties().SetChildContentLayout(UI::ChildContentLayout::Vertical)
                        , { UI::Element()
                            , UI::Element()
                            , UI::Element(UI::Element::Properties().SetChildContentLayout(UI::ChildContentLayout::Horizontal)
                                , { UI::Element()
                                    , UI::Element()
                                    , UI::Element()
                                    , UI::Element(UI::Element::Properties().SetID("Test"))})})
                    , UI::Element()})
            , UI::Element()})
{ }