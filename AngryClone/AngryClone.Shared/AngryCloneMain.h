#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"


#include "Level.h"
#include "Agile.h"
#include <btBulletDynamicsCommon.h>
#include "MyRenderer.h"
#include "AmmoRenderer.h"
#include "PseudoSphereRenderer.h"
#include "ExtraLargeRectangleRenderer.h"
#include "LargeRectangleRenderer.h"
#include "NormallRectangleRenderer.h"
#include "SmallRectangleRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace AngryClone
{
	class AngryCloneMain : public DX::IDeviceNotify
	{
	public:
		AngryCloneMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~AngryCloneMain();
		void CreateWindowSizeDependentResources();
		void StartTracking() {/* AmmunitionRenderer->StartTracking();*/ }
		void TrackingUpdate(float* positionX) { /*m_pointerLocationX = positionX; AmmunitionRenderer->TrackingUpdate(positionX);*/ }
		void StopTracking() { /*AmmunitionRenderer->StopTracking();*/ }
		bool IsTracking() { return false;/* AmmunitionRenderer->IsTracking(); */}
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;
		std::unique_ptr<MyRenderer> my_sceneRenderer;
	public:
		std::unique_ptr<Level> m_level;

		PseudoSphereRenderer* SphereRenderer;
		PseudoSphere^ MySphere;

		MyRenderer* m_renderer;

		SmallRectangleRenderer* SmallRectanglesRenderer;
		SmallRectangleRenderer* SmallRectanglesRenderer1;
		SmallRectangleRenderer* FirstPlatformRenderer;
		SmallRectangleRenderer* SecondPlatformRenderer;
		NormallRectangleRenderer* NormallRectanglesRenderer;
		LargeRectangleRenderer* LargeRectanglesRenderer;
		MyRenderer* ExtraLargeRectanglesRenderer;
		MyRenderer* CubesRenderer;
		AmmoRenderer* AmmunitionRenderer;
		///
		ExtraLargeRectangleRenderer* Terrain;
		///

		vector<Cube^> m_cubes;
		vector<PseudoSphere^> Enemies;
		vector<Ammo^> Ammunition;

		Platform::Agile<Windows::ApplicationModel::Core::CoreApplicationView> m_applicationView;
		bool m_windowClosed;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		// Track current input pointer position.
		float* m_pointerLocationX;
	};
}