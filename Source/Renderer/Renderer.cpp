#include "Renderer.h"
#include <Window//Window.h>

#include <stdio.h>

Renderer::Renderer(Window* pWindow)
	: mWindow(pWindow)
	, mDevice(nullptr)
	, mDeviceContext(nullptr)
	, mSwapchain(nullptr)
	, mRenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapchain();
	CreateRenderTargetView();
}

void Renderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };


	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1,
		D3D11_SDK_VERSION, mDevice.GetAddressOf(), nullptr, mDeviceContext.GetAddressOf())))
	{
		printf("Failed to create d3d11 device and context!\n");
		abort();
	}
	else
	{
		printf("Successfully create d3d11 device and context!\n");
	}

}

void Renderer::CreateSwapchain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = mWindow->GetSize().X;
	swapChainDesc.BufferDesc.Height = mWindow->GetSize().Y;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = mWindow->GetWindowNativeHandler();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	ComPtr<IDXGIDevice> dxgiDevice;
	mDevice.As(&dxgiDevice);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	ComPtr<IDXGIFactory> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	if (FAILED(dxgiFactory->CreateSwapChain(
		mDevice.Get(), &swapChainDesc, mSwapchain.GetAddressOf())))
	{
		printf("Failed to create swapchain!\n");
	}
	else
	{
		printf("Successfully create swapchain!\n");
	}

}

void Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> colorBuffer;
	mSwapchain->GetBuffer(0, IID_PPV_ARGS(&colorBuffer));

	if (FAILED(mDevice->CreateRenderTargetView(
		colorBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf())))
	{
		printf("Failed to create RenderTargetView!\n");
		abort();
	}
	else
	{
		printf("Successfully create RenderTargetView!\n");
	}
}

void Renderer::ClearColor(XMFLOAT4 color)
{
	float clearColor[] = {color.x, color.y, color.z, color.z};
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), clearColor);
}

void Renderer::Present()
{
	mSwapchain->Present(1, 0);
}
