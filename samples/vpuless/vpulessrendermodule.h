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

#pragma once

#define USE_FFX_API 1

#include "render/rendermodule.h"
#include "core/framework.h"
#include "core/uimanager.h"
#include "taa/taarendermodule.h"
#include "translucency/translucencyrendermodule.h"
#include "tonemapping/tonemappingrendermodule.h"

#include <ffx_api/ffx_api.hpp>
#include <ffx_api/ffx_upscale.hpp>
#include <ffx_api/ffx_framegeneration.hpp>

#include <functional>

namespace cauldron
{
    class Texture;
    class ParameterSet;
    class ResourceView;
    class RootSignature;
    class UIRenderModule;
}

class VPULessRenderModule : public cauldron::RenderModule
{
public:
    VPULessRenderModule();
    virtual ~VPULessRenderModule();

    void Init(const json& initData);
    void EnableModule(bool enabled) override;
    void OnPreFrame() override;

    /**
     * @brief   Setup parameters that the FSR API needs this frame and then call the FFX Dispatch.
     */
    void Execute(double deltaTime, cauldron::CommandList* pCmdList) override;
    
    /**
     * @brief   Recreate the FSR API Context to resize internal resources. Called by the framework when the resolution changes.
     */
    void OnResize(const cauldron::ResolutionInfo& resInfo) override;

private:

    bool m_ffxBackendInitialized = false;
    ffx::Context m_UpscalingContext;
    ffx::Context m_FrameGenContext;
    ffx::Context m_SwapChainContext;
    ffx::ConfigureDescFrameGeneration m_FrameGenerationConfig{};

    // FSR resources
    const cauldron::Texture*  m_pColorTarget           = nullptr;
    const cauldron::Texture*  m_pTonemappedColorTarget = nullptr;
    const cauldron::Texture*  m_pTempTexture           = nullptr;
    const cauldron::Texture*  m_pDepthTarget           = nullptr;
    const cauldron::Texture*  m_pMotionVectors         = nullptr;
    const cauldron::Texture*  m_pReactiveMask          = nullptr;
    const cauldron::Texture*  m_pCompositionMask       = nullptr;
    const cauldron::Texture*  m_pOpaqueTexture         = nullptr;

    // Raster views for reactive/composition masks
    std::vector<const cauldron::RasterView*> m_RasterViews           = {};
    cauldron::ResourceView*                  m_pUiTargetResourceView = nullptr;

    // For resolution updates
    std::function<cauldron::ResolutionInfo(uint32_t, uint32_t)> m_pUpdateFunc = nullptr;

    bool     s_enableSoftwareMotionEstimation = true;
    int32_t  s_uiRenderMode      = 2;

    // Surfaces for different UI render modes
    uint32_t                 m_curUiTextureIndex  = 0;
    const cauldron::Texture* m_pUiTexture[2]      = {};
    const cauldron::Texture* m_pHudLessTexture[2] = {};

    TAARenderModule*          m_pTAARenderModule         = nullptr;
    ToneMappingRenderModule*  m_pToneMappingRenderModule = nullptr;
    TranslucencyRenderModule* m_pTransRenderModule       = nullptr;
};

// alias to get sample.cpp to use this class.
using VPULessRenderModule = VPULessRenderModule;
