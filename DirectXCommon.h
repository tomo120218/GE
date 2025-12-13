#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include <array>

using Microsoft::WRL::ComPtr;

class DirectXCommon
{
public: // メンバ変数
	// 初期化
	void Initialize();
	// 描画開始
	void PreDraw();
	// 描画完了
	void PostDraw();

	void DeviceController();

	void Command();

	void SwapChain();

	void DepthBufferResource();

	void CreateDescriptorHeaps();

	void CreateRTV();

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);

	void CreateDSV();

	void CreateFence();

	void ViewportInitilize();

	void ScissoringInitilize();

	void CreateDXCCompiler();

	void ImGuiInitilize();

private:
	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(
		D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	HRESULT hr;

	//DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	ID3D12Fence* fence = nullptr;
	uint64_t fenceValue = 0;
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	WinApp* winApp = nullptr;
	ID3D12Device* device = nullptr;
	ID3D12InfoQueue* infoQueue = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12Resource* swapChainResources[2] = { nullptr };

	/// <summary>
	/// 指定番号のCPUディスクリプタハンドルを取得する
	/// </summary>
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(
		const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize,
		uint32_t index);

	/// <summary>
	/// 指定番号のGPUディスクリプタハンドルを取得する
	/// </summary>
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(
		const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize,
		uint32_t index);

	/// <summary>
	/// SRVの指定番号のCPUディスクリプタハンドルを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// SRVの指定番号のGPUディスクリプタハンドルを取得する
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	// スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);
	ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap = nullptr;
	ComPtr<ID3D12Resource> depthStencilResource = nullptr;
	uint32_t descriptorSizeRTV = 0;
	uint32_t descriptorSizeDSV = 0;
	uint32_t descriptorSizeSRV = 0;
};