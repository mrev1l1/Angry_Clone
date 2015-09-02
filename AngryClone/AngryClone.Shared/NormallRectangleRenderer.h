#pragma once
#include "Common\DeviceResources.h"
#include "Content\ShaderStructures.h"
#include "Common\StepTimer.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <memory>
#include "Cube.h"

class NormallRectangleRenderer
{
public:
	NormallRectangleRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
	~NormallRectangleRenderer();
	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();
	void ReleaseDeviceDependentResources();
	void Update(DX::StepTimer const& timer);
	void Render();
	void StartTracking();
	void TrackingUpdate(float positionX);
	void StopTracking();
	bool IsTracking() { return m_tracking; }

	Cube^ CreateRectangle();
	vector<Cube^> Rectangles;

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

	// System resources for cube geometry.
	AngryClone::ModelViewProjectionConstantBuffer	m_constantBufferData;
	uint32	m_indexCount;

	// Variables used with the rendering loop.
	bool	m_loadingComplete;
	float	m_degreesPerSecond;
	bool	m_tracking;
};

