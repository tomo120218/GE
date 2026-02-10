#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "dxcapi.h"
#include <cassert>    

void SpriteCommon::Initialize(DirectXCommon* dxCommon)
{
    // 引数で受け取ってメンバ変数に記録する
    dxCommon_ = dxCommon;

    // グラフィックスパイプラインの生成を呼び出す
    CreateGraphicsPipelineState();
}

void SpriteCommon::SetCommonDrawSettings(ID3D12GraphicsCommandList* commandList) {

    // ルートシグネチャをセットするコマンド
    commandList->SetGraphicsRootSignature(rootSignature.Get());

    // グラフィックスパイプラインステートをセットするコマンド
    commandList->SetPipelineState(graphicsPipelineState.Get());

    // プリミティブトポロジーをセットするコマンド
    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}