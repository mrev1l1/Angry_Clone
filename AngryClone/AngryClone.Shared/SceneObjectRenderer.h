#pragma once

#include <memory>
#include <d3d11.h>
#include "SceneObject.h"
#include <DirectXMath.h>
#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\ShaderStructures.h"

class SceneObjectRenderer
	{
	public:
		SceneObjectRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources, std::wstring model, std::wstring texture);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float* objectPosition);
		void StopTracking();
		bool IsTracking() { return ControlShiftingTrackingState; }
		

	private:
		void Rotate(float radians);

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> Sampler;
		// System resources for cube geometry.
		AngryClone::ModelViewProjectionConstantBuffer	m_constantBufferData;
		uint32	ModelBufferIndexCount;
		// Variables used with the rendering loop.
		bool	ResourceLoadingComplete;
		float	m_degreesPerSecond;
		bool	ControlShiftingTrackingState;
		std::wstring TexturePath;
		std::wstring ModelPath;
		int SingleRotator;

		float TotalDeltaX;
		float TotalDeltaY;
	
	public:
		SceneObject^ CreateObject();
		std::vector<SceneObject^> Objects;
		
	};


