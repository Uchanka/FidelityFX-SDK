// This file is part of the FidelityFX SDK.
//
// Copyright (C) 2024 Advanced Micro Devices, Inc.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "vpulessrendermodule.h"
#include "render/rendermodules/ui/uirendermodule.h"
#include "render/rasterview.h"
#include "render/dynamicresourcepool.h"
#include "render/parameterset.h"
#include "render/pipelineobject.h"
#include "render/rootsignature.h"
#include "render/swapchain.h"
#include "render/resourceviewallocator.h"
#include "core/backend_interface.h"
#include "core/scene.h"
#include "misc/assert.h"
#include "render/profiler.h"
#include "translucency/translucencyrendermodule.h"
#include "core/win/framework_win.h"

#if defined(FFX_API_DX12)
#include <ffx_api/dx12/ffx_api_dx12.hpp>
#include "render/dx12/device_dx12.h"
#include "render/dx12/commandlist_dx12.h"
#elif defined(FFX_API_VK)
#include <ffx_api/vk/ffx_api_vk.hpp>
#include "render/vk/device_vk.h"
#include "render/vk/commandlist_vk.h"
#include "render/vk/swapchain_vk.h"
#endif  // FFX_API_DX12

#include <functional>

using namespace std;
using namespace cauldron;

VPULessRenderModule::VPULessRenderModule()
    : RenderModule(L"VPULessFSRAPIRenderModule")
{

}

VPULessRenderModule::~VPULessRenderModule()
{
    
}

void VPULessRenderModule::Init(const json& initData)
{
}

void VPULessRenderModule::EnableModule(bool enabled)
{
    RenderModule::EnableModule(enabled);
}

void VPULessRenderModule::OnPreFrame()
{

}

void VPULessRenderModule::Execute(double deltaTime, CommandList* pCmdList)
{

}

void VPULessRenderModule::OnResize(const ResolutionInfo& resInfo)
{
}

