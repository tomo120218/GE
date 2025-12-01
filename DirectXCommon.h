#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
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

	void // レンダーターゲットビューの初期化ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

private:
	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(
		D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	// WindowsAPI
	WinApp* winApp = nullptr;
};

