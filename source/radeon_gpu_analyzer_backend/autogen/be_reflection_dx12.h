//=================================================================
// Copyright 2024 Advanced Micro Devices, Inc. All rights reserved.
//=================================================================

#ifndef RGA_RADEONGPUANALYZERBACKEND_SRC_BE_REFLECTION_DX12_H_
#define RGA_RADEONGPUANALYZERBACKEND_SRC_BE_REFLECTION_DX12_H_

// Local.
#include "radeon_gpu_analyzer_backend/autogen/be_include_dx12.h"

// C++
#include <cassert>
#include <string>

class BeDx12Reflection
{
 public:
    // Struct for storing hlsl file paths created via reflection.
    struct HlslOutput
    {
        std::string vs;
        std::string ps;
        std::string gpso;
        std::string root_signature;
    };

    // Auto-Generate Dx12 files for single shader compilation.
    beKA::beStatus AutoGenerateFiles(IDxcUtils*                dxc_utils,
                                     const BeDx12AutoGenInput& input, 
                                     HlslOutput&               hlsl_output,
                                     std::stringstream&        err) const;

 private:
     // Internal struct storing output from dxc reflection.
     struct DxcReflectionOutput
     {
         Microsoft::WRL::ComPtr<ID3D12ShaderReflection> shader_reflection_ptr;
         D3D12_SHADER_DESC                              shader_desc = {};
         std::vector<D3D12_SHADER_INPUT_BIND_DESC>      resource_bindings;
         std::vector<D3D12_SIGNATURE_PARAMETER_DESC>    param_desc_inputs;
         std::vector<D3D12_SIGNATURE_PARAMETER_DESC>    param_desc_outputs;
     };

     // Calls Dxc's CreateReflection function and populates dxc_output.
     beKA::beStatus CreateReflection(IDxcUtils*                    dxc_utils, 
                                     const BeDx12ShaderBinaryBlob& src_blob,
                                     DxcReflectionOutput&          dxc_output) const;

     // Auto-Generate root signature for compute pipeline.
     beKA::beStatus GenerateRootSignatureCompute(const DxcReflectionOutput& cs_dxc_output,
                                                 std::string&               root_signauture_hlsl,
                                                 std::stringstream&         err) const;
     
     // Auto-Generate root signature for compute pipeline.
     beKA::beStatus GenerateRootSignatureGraphics(UINT64                     shader_requires_flags,
                                                  bool                       has_vs,
                                                  const DxcReflectionOutput& vs_output,
                                                  bool                       has_ps,
                                                  const DxcReflectionOutput& ps_output,
                                                  std::string&               root_signauture_hlsl,
                                                  std::stringstream&         err) const;

     // Auto-Generate pixel shader.
     beKA::beStatus GeneratePixelShader(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* gpso,
                                        const DxcReflectionOutput&                dxc_output,
                                        std::string&                              pixel_shader,
                                        std::stringstream&                        err) const;
    
     // Auto-Generate vertex shader.
     beKA::beStatus GenerateVertexShader(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* gpso,
                                         const DxcReflectionOutput&                dxc_output,
                                         std::string&                              vertex_shader,
                                         std::stringstream&                        err) const;
    
     // Auto-Generate Gpso file.
     beKA::beStatus GenerateGpso(UINT64                     shader_requires_flags,
                                 bool                       has_vs, 
                                 const DxcReflectionOutput& vs_output,
                                 bool                       has_ps,
                                 const DxcReflectionOutput& ps_output,
                                 std::string&               gpso_text,
                                 std::stringstream&         err) const;
};

#endif  // RGA_RADEONGPUANALYZERBACKEND_SRC_BE_REFLECTION_DX12_H_
