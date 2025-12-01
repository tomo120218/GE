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
private:
	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	// WindowsAPI
	WinApp* winApp = nullptr;
};

