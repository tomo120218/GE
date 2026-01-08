#pragma once
#include "WinApp.h"
#include <array>
#include <d3d12.h>
#include <dxcapi.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <chrono>

#include "externals/DirectXTex/DirectXTex.h"

using Microsoft::WRL::ComPtr;

class DirectXCommon
{
public: // メンバ変数
	// 初期化
	void Initialize(WinApp* winApp);
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
	HRESULT hr;

	//DepthStencilStateの設定
	HANDLE fenceEvent{};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	D3D12_RESOURCE_DESC resourceDesc{};
	D3D12_HEAP_PROPERTIES heapProperties{};
	D3D12_CLEAR_VALUE depthClearValue{};
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	D3D12_VIEWPORT viewport{};
	D3D12_RESOURCE_BARRIER barrier{};
	D3D12_RECT scissorRect{};
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	uint64_t fenceValue = 0;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;
	WinApp* winApp = nullptr;
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12Debug1> debugController;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter;
	Microsoft::WRL::ComPtr<ID3D12Resource> resource;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descriptorHeap;
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils;
	Microsoft::WRL::ComPtr<IDxcCompiler3>  dxcCompiler;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource;
	Microsoft::WRL::ComPtr<IDxcBlobEncoding> shaderSource;
	Microsoft::WRL::ComPtr<IDxcResult> shaderResultr;
	Microsoft::WRL::ComPtr<IDxcBlobUtf8> shaderError;
	Microsoft::WRL::ComPtr<IDxcBlob> shaderBlob;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResouce;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	Microsoft::WRL::ComPtr<ID3D12CommandList> commandLists;
	//ID3D12CommandList* commandLists;

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

	/// <summary>
	/// バッファリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizzeInBytes);

	/// <summary>
	/// テクスチャリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// テクスチャデータの転送
	/// </summary>
	void UpLoadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& texture, const DirectX::ScratchImage& mipImages);

	/// <summary>
	/// テクスチャファイルの読み込み
	/// </summary>
	/// <param name* "filePath">テキスチャファイルのパス</param>
	/// <returns>画像イメージデータ</returns>
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);	
	uint32_t descriptorSizeRTV = 0;
	uint32_t descriptorSizeDSV = 0;
	uint32_t descriptorSizeSRV = 0;

	// getter
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }

	// シェーダーコンパイル
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile
	);


	// FPS固定初期化
	void InitializeFixFPS();

	// FPS固定更新
	void UpdateFixFPS();

	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;
};