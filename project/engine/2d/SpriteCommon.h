#pragma once

#include "DirectXCommon.h"
#include <d3d12.h>
#include <wrl.h>

class SpriteCommon
{
public: // メンバ変数
	void Initialize(DirectXCommon* dxCommon);

	//　共通描画設定
	void SetCommonDrawSettings();

	DirectXCommon* GetDxCommon() const { return dxCommon_; }

private:
	DirectXCommon* dxCommon_;

	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// グラフィックスパイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;

	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	// ルートシグネチャの作成
	// ルートシグネチャの作成
	void CreateRootSignature();
	// グラフィックスパイプラインの生成
	void CreateGraphicsPipelineState();
};

