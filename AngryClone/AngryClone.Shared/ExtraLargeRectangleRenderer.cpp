#include "pch.h"
#include "ExtraLargeRectangleRenderer.h"
#include "ModelFileHandler.h"
#include "Common\DirectXHelper.h"
#include "BasicReaderWriter.h"
#include "DDSTextureLoader.h"

using namespace AngryClone;
using namespace DirectX;
using namespace Windows::Foundation;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
ExtraLargeRectangleRenderer::ExtraLargeRectangleRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources, char* model, wchar_t* texture) :
m_loadingComplete(false),
m_degreesPerSecond(45),
m_indexCount(0),
m_tracking(false),
m_deviceResources(deviceResources),
singleRotator(0),
modelPath(model),
texturePath(texture)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Initializes view parameters when the window size changes.
void ExtraLargeRectangleRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);
	
	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	static const XMVECTORF32 eye = { 37.5, 25, 30, 0 };//{ -12.0f, 15.0f, -40.f, 0.f };//{ -30.0f, 0.7f, -30.0f, 0.0f };
	static const XMVECTORF32 at = { 10, 0, 10, 0 };//{ -12.0f, 12.0f, 0.0f, 0.0f };//
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	/*static const XMVECTORF32 eye = { 10.1f, 0.2f, 3.625f, 0.0f };
	static const XMVECTORF32 at = { -0.f, -0.1f, -0.f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };*/

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void ExtraLargeRectangleRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		if (singleRotator<1)
			Rotate(radians);
		singleRotator++;
	}
}

// Rotate the 3D cube model a set amount of radians.
void ExtraLargeRectangleRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
	//Render();
}


// Renders one frame using the vertex and pixel shaders.
void ExtraLargeRectangleRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	//concurrency::critical_section::scoped_lock lk(m_deviceResources->devCtxCs);
	auto context = m_deviceResources->GetD3DDeviceContext();

	//for (auto& rect : Rectangles)
	//{
	//		XMStoreFloat4x4(&m_constantBufferData.model, rect->m_modelMatrix);


		// Prepare the constant buffer to send it to the graphics device.
		concurrency::critical_section::scoped_lock lk(m_deviceResources->devCtxCs);
		context->UpdateSubresource(
			m_constantBuffer.Get(),
			0,
			NULL,
			&m_constantBufferData,
			0,
			0
			);

		// Each vertex is one instance of the VertexPositionColor struct.
		UINT stride = sizeof(AngryClone::VertexPositionTextureCoord);
		UINT offset = 0;
		context->IASetVertexBuffers(
			0,
			1,
			m_vertexBuffer.GetAddressOf(),
			&stride,
			&offset
			);

		context->IASetIndexBuffer(
			m_indexBuffer.Get(),
			DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
			0
			);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->IASetInputLayout(m_inputLayout.Get());

		// Attach our vertex shader.
		context->VSSetShader(
			m_vertexShader.Get(),
			nullptr,
			0
			);

		// Send the constant buffer to the graphics device.
		context->VSSetConstantBuffers(
			0,
			1,
			m_constantBuffer.GetAddressOf()
			);

		// Attach our pixel shader.
		context->PSSetShader(
			m_pixelShader.Get(),
			nullptr,
			0
			);

		context->PSSetShaderResources(
			0,
			1,
			textureView.GetAddressOf()
			);

		context->PSSetSamplers(
			0,
			1,
			sampler.GetAddressOf()
			);

		// Draw the objects.
		context->DrawIndexed(
			m_indexCount,
			0,
			0
			);
	//}
}

void ExtraLargeRectangleRenderer::CreateDeviceDependentResources()
{
	// Load shaders asynchronously.
	auto loadVSTask = DX::ReadDataAsync(L"TexturedVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"TexturedPixelShader.cso");

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileData[0],
			fileData.size(),
			nullptr,
			&m_vertexShader
			)
			);

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			
		};

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileData[0],
			fileData.size(),
			&m_inputLayout
			)
			);
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&fileData[0],
			fileData.size(),
			nullptr,
			&m_pixelShader
			)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&m_constantBuffer
			)
			);
	});

	// Once both shaders are loaded, create the mesh.
	auto createCubeTask = (createPSTask && createVSTask).then([this]() {

		

		ModelFileHandler mfh(modelPath,'t');
		const AngryClone::VertexPositionTextureCoord* testv = mfh.getTexturedVertices();


		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = testv;//cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(mfh.getVerticesBufferSize()/*sizeof(cubeVertices)*/, D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
			)
			);

		
		static unsigned short* testcu = mfh.getIndices();
		m_indexCount = mfh.getIndicesCount();// ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = testcu;// cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(mfh.getIndicesBufferSize()/*sizeof(cubeIndices)*/, D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&m_indexBuffer
			)
			);
		
		
		Microsoft::WRL::ComPtr<ID3D11Resource> Mytexture;
		
		DirectX::CreateDDSTextureFromFile(m_deviceResources->GetD3DDevice(),
			(texturePath),
			&Mytexture,
			&textureView);

		
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		// The sampler does not use anisotropic filtering, so this parameter is ignored.
		samplerDesc.MaxAnisotropy = 0;

		// Specify how texture coordinates outside of the range 0..1 are resolved.
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		// Use no special MIP clamping or bias.
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// Don't use a comparison function.
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		// Border address mode is not used, so this parameter is ignored.
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateSamplerState(
			&samplerDesc,
			&sampler
			)
			);
		/////////////////
	});

	// Once the cube is loaded, the object is ready to be rendered.
	createCubeTask.then([this]() {
		m_loadingComplete = true;
	});
}

void ExtraLargeRectangleRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}

void ExtraLargeRectangleRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void ExtraLargeRectangleRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void ExtraLargeRectangleRenderer::StopTracking()
{
	m_tracking = false;
}

Cube^ ExtraLargeRectangleRenderer::CreateRectangle()
{
	auto rect = ref new Cube();
	Rectangles.push_back(rect);
	return rect;
}

ExtraLargeRectangleRenderer::~ExtraLargeRectangleRenderer()
{
}
