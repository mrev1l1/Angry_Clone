#pragma once

#include "Level.h"
#include "Agile.h"
#include "Common\StepTimer.h"
#include "SceneObjectRenderer.h"
#include "Common\DeviceResources.h"
#include <btBulletDynamicsCommon.h>
#include "Content\SampleFpsTextRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace AngryClone
{
	class AngryCloneMain : public DX::IDeviceNotify
	{
	public:
		AngryCloneMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~AngryCloneMain();
		void CreateWindowSizeDependentResources();
		void StartTracking() { AmmoRenderer->StartTracking();}
		void TrackingUpdate(float* positionX) { m_pointerLocationX = positionX; AmmoRenderer->TrackingUpdate(positionX); }
		void StopTracking() { AmmoRenderer->StopTracking(); }
		bool IsTracking() { return AmmoRenderer->IsTracking();  }
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
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;
	public:
		std::unique_ptr<Level> GameLevelPhysics;
				
		std::unique_ptr<SceneObjectRenderer> NormallRectanglesRenderer;
		std::unique_ptr<SceneObjectRenderer> LargeRectanglesRenderer;
		std::unique_ptr<SceneObjectRenderer> ExtraLargeRectanglesRenderer;
		std::unique_ptr<SceneObjectRenderer> CubesRenderer;
		std::unique_ptr<SceneObjectRenderer> SmallRectanglesRenderer;
		std::unique_ptr<SceneObjectRenderer> VillainsRenderer;
		std::unique_ptr<SceneObjectRenderer> AmmoRenderer;
		
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