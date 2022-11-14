#include "include.h"

#include "Runtime/Demo/senrenbanka.h"

using namespace Senrenbanka;

int main()
{
    LOG_INFO("Erisu Engine Start.");
    ErisuApp app;

    std::shared_ptr<GLRenderer> renderer = std::make_shared<GLRenderer>(Global::CanvasWidth, Global::CanvasHeight, Global::WindowTitle.c_str());
    Erisu::Global::Init();

    if (Global::DebugMode)
    {
        LOG_INFO("Debug Mode: ON");
        renderer->AddImGuiWindow([&]() { DrawSceneHierarchy(test_scene); });
        renderer->AddImGuiWindow(DrawInspector);
    }

    CreateStartScene();

    app.SetRenderer(renderer);
    app.SetScene(test_scene);
    app.Run();

    test_scene->Destroy();

    return 0; // do not use exit(0), it will cause memory leak.
}
