#include "pch.h"
#include "AngryCloneMain.h"
#include "Common\DirectXHelper.h"

using namespace AngryClone;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// Loads and initializes application assets when the application is loaded.
AngryCloneMain::AngryCloneMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_deviceResources(deviceResources), m_pointerLocationX(nullptr), m_level(std::unique_ptr<Level>(new Level()))
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: Replace this with your app's content initialization.

	/*this->SmallRectanglesRenderer = new SmallRectangleRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\ammo_platform.txt");
	this->FirstPlatformRenderer = new SmallRectangleRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\platform1.txt");
	this->SecondPlatformRenderer = new SmallRectangleRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\platform2.txt");
	*/this->NormallRectanglesRenderer = new NormallRectangleRenderer(m_deviceResources);

	/*this->SmallRectanglesRenderer1 = new SmallRectangleRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\normallRectangleModel.txt");
	this->LargeRectanglesRenderer = new LargeRectangleRenderer(m_deviceResources);
	this->ExtraLargeRectanglesRenderer = new MyRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\extraLargeRectangleModel.txt");
	SphereRenderer = new PseudoSphereRenderer(m_deviceResources);
this->Terrain = new ExtraLargeRectangleRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\sky\\sky.txt", L"C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\terrain\\water..ish.dds");
*/
	this->CubesRenderer = new MyRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\newTerrain\\Model.txt", L"C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\terrain\\text.dds");
	//this->AmmunitionRenderer = new AmmoRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\eggModel_1copy.txt", L"C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\textures\\egg.dds");

	//m_level->InitialiseExtraLargeRectangles(CubesRenderer);
	//m_level->InitialiseAmmo(this->AmmunitionRenderer);
//m_level->Initialise(SphereRenderer);
	//m_level->InitialiseSmallRectangles(SmallRectanglesRenderer);
	//m_level->InitialiseNormallRectangles(SmallRectanglesRenderer1);
	m_level->InitialiseNormallRectangles(NormallRectanglesRenderer);
	/*m_level->InitialiseLargeRectangles(LargeRectanglesRenderer);
	m_level->InitialiseExtraLargeRectangles(ExtraLargeRectanglesRenderer);
	
	
	
	
	m_level->InitialiseTerrain(Terrain);*/

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
//this->CubesRenderer->CreateWindowSizeDependentResources();
	/*this->SmallRectanglesRenderer->CreateWindowSizeDependentResources();
	this->FirstPlatformRenderer->CreateWindowSizeDependentResources();
	this->SecondPlatformRenderer->CreateWindowSizeDependentResources();*/
	this->NormallRectanglesRenderer->CreateWindowSizeDependentResources();
//	this->AmmunitionRenderer->CreateWindowSizeDependentResources();
	/*this->SmallRectanglesRenderer1->CreateWindowSizeDependentResources();
	this->LargeRectanglesRenderer->CreateWindowSizeDependentResources();
	this->ExtraLargeRectanglesRenderer->CreateWindowSizeDependentResources();
	
	
	
Terrain->CreateWindowSizeDependentResources();

SphereRenderer->CreateWindowSizeDependentResources();*/
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

		m_level->Update();
		//this->SmallRectanglesRenderer->Update(m_timer);
		//this->FirstPlatformRenderer->Update(m_timer);
		//this->SecondPlatformRenderer->Update(m_timer);
		this->CubesRenderer->Update(m_timer);
		//
		/*this->SmallRectanglesRenderer1->Update(m_timer);
		
		Terrain->Update(m_timer);

		this->NormallRectanglesRenderer->Update(m_timer);
		this->LargeRectanglesRenderer->Update(m_timer);
		this->ExtraLargeRectanglesRenderer->Update(m_timer);
		
		SphereRenderer->Update(m_timer);
		this->AmmunitionRenderer->Update(m_timer);
		
		*/

		if (this->m_level->IsAmmoLost == true)
		{
		/*	delete this->AmmunitionRenderer;
			this->AmmunitionRenderer = new AmmoRenderer(m_deviceResources, "C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\eggModel_1copy.txt", L"C:\\Users\\Олександр\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\textures\\egg.dds");
			m_level->ReinitialiseAmmo(this->AmmunitionRenderer);
			this->AmmunitionRenderer->CreateWindowSizeDependentResources();
			this->AmmunitionRenderer->CreateDeviceDependentResources();

			this->m_level->IsAmmoLost = false;*/
		}

	/*	this->SmallRectanglesRenderer->Render();
		this->FirstPlatformRenderer->Render();
		this->SecondPlatformRenderer->Render();*/
		this->CubesRenderer->Render();
		this->NormallRectanglesRenderer->Render();
	//	this->AmmunitionRenderer->Render();
		/*this->SmallRectanglesRenderer1->Render();
		this->LargeRectanglesRenderer->Render();
		this->ExtraLargeRectanglesRenderer->Render();
		SphereRenderer->Render();
	    
		
Terrain->Render();*/
		//m_renderer->Present(); // This call is synchronized to the display frame rate.
	});
}

// Process all input from the user before updating game state
void AngryCloneMain::ProcessInput()
{
	// TODO: Add per frame input handling here.
	//m_sceneRenderer->TrackingUpdate(m_pointerLocationX);
	//my_sceneRenderer->TrackingUpdate(m_pointerLocationX);
	
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

	this->CubesRenderer->Render();
	/*this->SmallRectanglesRenderer->Render();
	this->FirstPlatformRenderer->Render();
	this->SecondPlatformRenderer->Render();*/
	this->NormallRectanglesRenderer->Render();
	//AmmunitionRenderer->Render();
	/*this->SmallRectanglesRenderer1->Render();
	this->LargeRectanglesRenderer->Render();
	this->ExtraLargeRectanglesRenderer->Render();
	
	SphereRenderer->Render();
	
	
Terrain->Render();*/
	return true;
}

// Notifies renderers that device resources need to be released.
void AngryCloneMain::OnDeviceLost()
{
	/*this->SmallRectanglesRenderer->ReleaseDeviceDependentResources();
	this->NormallRectanglesRenderer->ReleaseDeviceDependentResources();
	this->LargeRectanglesRenderer->ReleaseDeviceDependentResources();
	this->ExtraLargeRectanglesRenderer->ReleaseDeviceDependentResources();
	this->CubesRenderer->ReleaseDeviceDependentResources();
	SphereRenderer->ReleaseDeviceDependentResources();
	
	this->AmmunitionRenderer->ReleaseDeviceDependentResources();*///Terrain->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void AngryCloneMain::OnDeviceRestored()
{
	/*this->SmallRectanglesRenderer->CreateDeviceDependentResources();
	this->NormallRectanglesRenderer->CreateDeviceDependentResources();
	this->LargeRectanglesRenderer->CreateDeviceDependentResources();
	this->ExtraLargeRectanglesRenderer->CreateDeviceDependentResources();
	this->CubesRenderer->CreateDeviceDependentResources();
	SphereRenderer->CreateDeviceDependentResources();
	
	this->AmmunitionRenderer->CreateDeviceDependentResources();*///Terrain->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
