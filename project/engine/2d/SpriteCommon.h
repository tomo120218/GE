#pragma once

#include "DirectXCommon.h"
#include <d3d12.h>
#include <wrl.h>

class SpriteCommon
{
public: // メンバ変数
	void Initialize(DirectXCommon* dxCommon);

	//　共通描画設定
	void SetCommonDrawSettings(ID3D12GraphicsCommandList* commandList);

	DirectXCommon* GetDxCommon() const { return dxCommon_; }

private:
	DirectXCommon* dxCommon_;

	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// グラフィックスパイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;

	// ルートシグネチャの作成
	// ルートシグネチャの作成
	void CreateRootSignature();
	// グラフィックスパイプラインの生成
	void CreateGraphicsPipelineState();
};

