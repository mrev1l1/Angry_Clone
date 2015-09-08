#include "pch.h"
#include "AngryCloneMain.h"
#include "Common\DirectXHelper.h"

using namespace AngryClone;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

//std::wstring operator+(std::wstring lvalue, std::string ending)
//{
//	lvalue += std::wstring(ending.begin(), ending.end());
//	return lvalue;
//}

// Loads and initializes application assets when the application is loaded.
AngryCloneMain::AngryCloneMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_deviceResources(deviceResources), m_pointerLocationX(nullptr), GameLevelPhysics(std::unique_ptr<Level>(new Level()))
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: Replace this with your app's content initialization.
	std::wstring managedPath = Windows::Storage::ApplicationData::Current->LocalFolder->Path->Data();

	this->SmallRectanglesRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\small.txt", managedPath + L"\\textures\\eye.dds"));
	this->NormallRectanglesRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\normal.txt", managedPath + L"\\textures\\eye.dds"));
	this->ExtraLargeRectanglesRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\extraLarge.txt", managedPath + L"\\textures\\eye.dds"));
	this->CubesRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\box.txt", managedPath + L"\\textures\\eye.dds"));
	this->VillainsRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\villain.txt", managedPath + L"\\Level_0.1\\villain.dds"));
	this->AmmoRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\eggModel_1.txt", managedPath + L"\\textures\\ammo.dds"));
	this->LargeRectanglesRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\Level_0.1\\large.txt", managedPath + L"\\textures\\eye.dds"));

	this->GameLevelPhysics->InitialiseTerrain();
	this->GameLevelPhysics->InitialiseSmallRectangles(SmallRectanglesRenderer.get());
	this->GameLevelPhysics->InitialiseLargeRectangles(LargeRectanglesRenderer.get());
	this->GameLevelPhysics->InitialiseNormalRectangles(NormallRectanglesRenderer.get());
	this->GameLevelPhysics->InitialiseExtraLargeRectangles(ExtraLargeRectanglesRenderer.get());
	this->GameLevelPhysics->InitialiseBoxes(CubesRenderer.get());
	this->GameLevelPhysics->InitialiseVillains(VillainsRenderer.get());
	this->GameLevelPhysics->InitialiseAmmo(AmmoRenderer.get());
	
	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

AngryCloneMain::~AngryCloneMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void AngryCloneMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	this->NormallRectanglesRenderer->CreateWindowSizeDependentResources();
	this->SmallRectanglesRenderer->CreateWindowSizeDependentResources();
	this->VillainsRenderer->CreateWindowSizeDependentResources();
	this->AmmoRenderer->CreateWindowSizeDependentResources();
	this->CubesRenderer->CreateWindowSizeDependentResources();
	this->LargeRectanglesRenderer->CreateWindowSizeDependentResources();
	this->ExtraLargeRectanglesRenderer->CreateWindowSizeDependentResources();
}

void AngryCloneMain::StartRenderLoop()
{
	// If the animation render loop is already running then do not start another thread.
	if (m_renderLoopWorker != nullptr && m_renderLoopWorker->Status == AsyncStatus::Started)
	{
		return;
	}
	
	// Create a task that will be run on a background thread.
	auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^ action)
	{
		// Calculate the updated frame and render once per vertical blanking interval.
		while (action->Status == AsyncStatus::Started)
		{
			critical_section::scoped_lock lock(m_criticalSection);
			Update();
			if (Render())
			{
				concurrency::critical_section::scoped_lock lk(m_deviceResources->devCtxCs);
				m_deviceResources->Present();
			}
		}
	});

	// Run task on a dedicated high priority background thread.
	m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
}

void AngryCloneMain::StopRenderLoop()
{
	m_renderLoopWorker->Cancel();
}

// Updates the application state once per frame.
void AngryCloneMain::Update() 
{
	ProcessInput();

	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		GameLevelPhysics->Update();
		
		if (this->GameLevelPhysics->IsAmmoLost == true)
		{
			std::wstring managedPath = Windows::Storage::ApplicationData::Current->LocalFolder->Path->Data();

			SceneObjectRenderer* oldRenderer = this->AmmoRenderer.release();
			delete oldRenderer;
			this->AmmoRenderer = std::unique_ptr<SceneObjectRenderer>(new SceneObjectRenderer(m_deviceResources, managedPath + L"\\eggModel_1.txt", managedPath + L"\\textures\\ammo.dds"));
			this->GameLevelPhysics->ReinitialiseAmmo(this->AmmoRenderer.get());
			this->AmmoRenderer->CreateWindowSizeDependentResources();
			this->AmmoRenderer->CreateDeviceDependentResources();
			this->GameLevelPhysics->IsAmmoLost = false;
		}

		//Разрушаемость - не решена
	/*	if (this->GameLevelPhysics->objToDelete > 0)
		{
			int t = this->GameLevelPhysics->objToDelete;
			if (this->GameLevelPhysics->objToDelete > 2 && this->GameLevelPhysics->objToDelete < this->GameLevelPhysics->objQuantity - 2)
				this->CubesRenderer->Objects.erase(CubesRenderer->Objects.begin() + this->GameLevelPhysics->objToDelete - 3);
			else
				this->VillainsRenderer->Objects.erase(VillainsRenderer->Objects.begin());

			this->GameLevelPhysics->objToDelete = 0;
		}*/
		
		this->NormallRectanglesRenderer->Render();
		this->SmallRectanglesRenderer->Render();
		this->CubesRenderer->Render();
		this->VillainsRenderer->Render();
		this->AmmoRenderer->Render();
		this->LargeRectanglesRenderer->Render();
		this->ExtraLargeRectanglesRenderer->Render();
	});
}

// Process all input from the user before updating game state
void AngryCloneMain::ProcessInput()
{
	// TODO: Add per frame input handling here.
	
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool AngryCloneMain::Render() 
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	{
		concurrency::critical_section::scoped_lock lk(m_deviceResources->devCtxCs);
		auto context = m_deviceResources->GetD3DDeviceContext();

		// Reset the viewport to target the whole screen.
		auto viewport = m_deviceResources->GetScreenViewport();
		context->RSSetViewports(1, &viewport);

		// Reset render targets to the screen.
		ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
		context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

		// Clear the back buffer and depth stencil view.
		context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
		context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	
	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.

	this->NormallRectanglesRenderer->Render();
	this->SmallRectanglesRenderer->Render();
	this->CubesRenderer->Render();
	VillainsRenderer->Render();
	AmmoRenderer->Render();
	this->LargeRectanglesRenderer->Render();
	this->ExtraLargeRectanglesRenderer->Render();

	return true;
}

// Notifies renderers that device resources need to be released.
void AngryCloneMain::OnDeviceLost()
{
	this->NormallRectanglesRenderer->ReleaseDeviceDependentResources();
	this->SmallRectanglesRenderer->ReleaseDeviceDependentResources();
	this->CubesRenderer->ReleaseDeviceDependentResources();
	this->VillainsRenderer->ReleaseDeviceDependentResources();
	this->AmmoRenderer->ReleaseDeviceDependentResources();
	this->LargeRectanglesRenderer->ReleaseDeviceDependentResources();
	this->ExtraLargeRectanglesRenderer->ReleaseDeviceDependentResources();
	
}

// Notifies renderers that device resources may now be recreated.
void AngryCloneMain::OnDeviceRestored()
{
	this->NormallRectanglesRenderer->CreateDeviceDependentResources();
	this->SmallRectanglesRenderer->CreateDeviceDependentResources();
	this->CubesRenderer->CreateDeviceDependentResources();
	this->VillainsRenderer->CreateDeviceDependentResources();
	this->AmmoRenderer->CreateDeviceDependentResources();
	this->LargeRectanglesRenderer->CreateDeviceDependentResources();
	this->ExtraLargeRectanglesRenderer->CreateDeviceDependentResources();
	
	CreateWindowSizeDependentResources();
}
