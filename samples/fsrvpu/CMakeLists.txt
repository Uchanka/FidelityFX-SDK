# This file is part of the FidelityFX SDK.
# 
# Copyright (C) 2024 Advanced Micro Devices, Inc.
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files(the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions :
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Declare project
project(FSR_VPU)

# ---------------------------------------------
# Fidelity FX Api FSR Sample
# ---------------------------------------------

# Import SDK libs
add_library(amd_fidelityfx SHARED IMPORTED)
set_target_properties(amd_fidelityfx PROPERTIES
					  INTERFACE_INCLUDE_DIRECTORIES "${API_ROOT}/include"
					  IMPORTED_LOCATION_RELEASEDX12 "${API_ROOT}/bin/amd_fidelityfx_dx12.dll"
					  IMPORTED_LOCATION_RELWITHDEBINFODX12 "${API_ROOT}/bin/amd_fidelityfx_dx12drel.dll"
					  IMPORTED_LOCATION_DEBUGDX12 "${API_ROOT}/bin/amd_fidelityfx_dx12d.dll"
					  IMPORTED_LOCATION_RELEASEVK "${API_ROOT}/bin/amd_fidelityfx_vk.dll"
					  IMPORTED_LOCATION_RELWITHDEBINFOVK "${API_ROOT}/bin/amd_fidelityfx_vkdrel.dll"
					  IMPORTED_LOCATION_DEBUGVK "${API_ROOT}/bin/amd_fidelityfx_vkd.dll"
					  IMPORTED_IMPLIB_RELEASEDX12 "${API_ROOT}/bin/amd_fidelityfx_dx12.lib"
					  IMPORTED_IMPLIB_RELWITHDEBINFODX12 "${API_ROOT}/bin/amd_fidelityfx_dx12drel.lib"
					  IMPORTED_IMPLIB_DEBUGDX12 "${API_ROOT}/bin/amd_fidelityfx_dx12d.lib"
					  IMPORTED_IMPLIB_RELEASEVK "${API_ROOT}/bin/amd_fidelityfx_vk.lib"
					  IMPORTED_IMPLIB_RELWITHDEBINFOVK "${API_ROOT}/bin/amd_fidelityfx_vkdrel.lib"
					  IMPORTED_IMPLIB_DEBUGVK "${API_ROOT}/bin/amd_fidelityfx_vkd.lib")

# FSR render module files
set(vpuful_src ${CMAKE_CURRENT_SOURCE_DIR}/fsrvpurendermodule.h ${CMAKE_CURRENT_SOURCE_DIR}/fsrvpurendermodule.cpp)

# Add config file
set(config_file ${CMAKE_CURRENT_SOURCE_DIR}/config/fsrvpuconfig.json)
copyCommand("${config_file}" ${CONFIG_OUTPUT})

set(rm_config_json ${CMAKE_CURRENT_SOURCE_DIR}/config/fsrvpurendermodule.json)
set(rm_config_dest ${CONFIG_OUTPUT}/rm_configs/fsrvpurendermodule.json)
configure_file(${rm_config_json} ${rm_config_dest} COPYONLY)

# Add the sample to the solution
add_executable(${PROJECT_NAME} WIN32 ${default_icon_src} ${default_entry_point} ${default_sample_files} ${config_file} ${vpuful_src} ${fsr_shaders})
# add_executable(${PROJECT_NAME} ${default_icon_src} ${config_file} ${vpuless_src} ${fsr_shaders})

# Setup the correct exe based on backend name
set(EXE_OUT_NAME ${PROJECT_NAME}_)

# Link everything
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Framework RenderModules d3dcompiler amd_fidelityfx backend_interface_stub)
set_target_properties(${PROJECT_NAME} PROPERTIES
						OUTPUT_NAME_DEBUGDX12 "${EXE_OUT_NAME}DX12D"
						OUTPUT_NAME_DEBUGVK "${EXE_OUT_NAME}VKD"
						OUTPUT_NAME_RELEASEDX12 "${EXE_OUT_NAME}DX12"
						OUTPUT_NAME_RELEASEVK "${EXE_OUT_NAME}VK"
						OUTPUT_NAME_RELWITHDEBINFODX12 "${EXE_OUT_NAME}drelDX12"
						OUTPUT_NAME_RELWITHDEBINFOVK "${EXE_OUT_NAME}drelVK"
						VS_DEBUGGER_WORKING_DIRECTORY "${BIN_OUTPUT}")

file(GLOB api_dlls ${API_ROOT}/bin/*.dll)

# Copy amd_fidelityfx dll to output. Relies on it being built before this project is configured!
# TODO: remove tech debt from build system....
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${api_dlls} ${BIN_OUTPUT})

# Add compile definitions to identify the sample
target_compile_definitions(${PROJECT_NAME} PRIVATE SampleName=L"FSRVPU Benchmark"
										   ConfigFileName=L"configs/fsrvpuconfig.json"
										   ConfigSampleName="FSR_VPU"
										   RenderModuleName=FSRVPU)

# Add manifest info
addManifest(${PROJECT_NAME})

# And solution layout definitions
source_group(""						FILES ${default_entry_point})
source_group("Sample" 					FILES ${fsr_sample_files})
source_group("Icon"    					FILES ${default_icon_src})
source_group("Config" 					FILES ${config_file} ${config_rm_file})
source_group("RenderModule"				FILES ${vpuful_src})
