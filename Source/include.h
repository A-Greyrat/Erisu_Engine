//
// Created by Adarion on 2022/10/30.
//

#ifndef ERISU_ENGINE_INCLUDE_H
#define ERISU_ENGINE_INCLUDE_H

// main.cpp includes this .h file
// NOTICE: not included in any other .cpp files

#include <Log/LogSystem.h>
#include <imgui.h>
#include <Global/Global.h>

#include "Runtime/Function/Render/GLRenderer.h"
#include "Runtime/Function/Application/ErisuApp.h"
#include "Runtime/Function/Base/Light.h"
#include "Runtime/Resource/ModelImport/ModelImport.h"
#include "RendererQueue.h"
#include "Runtime/Function/Utility/ImGuiUtility.h"
#include "Runtime/Function/Animation/AnimationCurve.h"

#include "Runtime/Function/UI/Core/Component/UIImage.h"
#include "Runtime/Function/UI/Core/Component/UIText.h"
#include "Runtime/Function/UI/Core/Base/UIObject.h"
#include "Runtime/Function/UI/Core/Base/UIInput.h"
#include "Runtime/Function/UI/Core/Utility/UIInputUti.h"

#include "Runtime/Function/Animation/Timeline/Timeline.h"

using namespace Erisu;
using namespace Erisu::Function;
using namespace Erisu::Core;
using namespace Erisu::Resource;
using namespace Erisu::Global;

#if defined(ENABLE_DISCRETE_GPU)
    // force system to use discrete GPU, if available
    extern "C" {
        _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
        _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    }
#endif

#endif //ERISU_ENGINE_INCLUDE_H
