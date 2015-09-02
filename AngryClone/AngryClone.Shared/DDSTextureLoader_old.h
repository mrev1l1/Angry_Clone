//--------------------------------------------------------------------------------------
// File: DDSTextureLoader.h
//
// Function for loading a DDS texture and creating a Direct3D 11 runtime resource for it
//
// Note this function is useful as a light-weight runtime loader for DDS files. For
// a full-featured DDS file reader, writer, and texture processing pipeline see
// the 'Texconv' sample and the 'DirectXTex' library.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "Direct3DBase.h"

void CreateDDSTextureFromMemory(
	_In_ ID3D11Device* d3dDevice,
	_In_reads_bytes_(ddsDataSize) const byte* ddsData,
	_In_ size_t ddsDataSize,
	_Out_opt_ ID3D11Resource** texture,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_In_ size_t maxsize = 0
	);

void CreateTexture(
	_In_ bool decodeAsDDS,
	_In_reads_bytes_(dataSize) byte* data,
	_In_ uint32 dataSize,
	_Out_opt_ ID3D11Texture2D** texture,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_In_opt_ Platform::String^ debugName,
	_In_ ID3D11Device2* m_d3dDevice
	);