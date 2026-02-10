#include "Sprite.h"
#include "SpriteCommon.h"
#include "DirectXCommon.h"

void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	// 引数で受け取ってメンバ変数にする
	this->spriteCommon = spriteCommon;

    vertexResource = spriteCommon->GetDxCommon()->CreateBufferResource(sizeof(VertexData) * 6);
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
    vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
    vertexBufferView.SizeInBytes = sizeof(VertexData) * 6;
    vertexBufferView.StrideInBytes = sizeof(VertexData);

    indexResourceSprite = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(uint32_t) * 6);
    D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
    //リソースの先頭のアドレスから使う
    indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
    //使用するリソースのサイズはインデックス6つ分のサイズ
    indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
    //インデックスはuint32_tとする
    indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;

    //マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
    materialResource = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(materialData));
    //マテリアルにデータを書き込む
    materialData = nullptr;
    //書き込むためのアドレスを取得
    materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
    //今回は白を書き込んでみる
    //*materialData = math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

    // マテリアルデータの初期値を書き込む
    materialData->color = MyMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    materialData->enableLighting = false;
    materialData->uvTransform = MyMath::MakeIdentity4x4();

    wvpResource = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(MyMath::Matrix4x4));
    //データを書き込む
	MyMath::Matrix4x4* wvpData = nullptr;
	//書き込むためのアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//単位行列を書き込んでおく
	*wvpData = MyMath::MakeIdentity4x4();

    //Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
    transformationMatrixResourceSprite = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(MyMath::Matrix4x4));
    //データを書き込む
    MyMath::Matrix4x4* transformationMatrixDataSprite = nullptr;
    //書き込むためのアドレスを取得
    transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));
    //単位行列を書き込んでおく
    *transformationMatrixDataSprite = MyMath::MakeIdentity4x4();

    MyMath::Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

    // 単位行列を書き込んでおく
    transformationMatrixData->WVP = MyMath::MakeIdentity4x4();
    transformationMatrixData->World = MyMath::MakeIdentity4x4();
}

------------------------------------GE3-05-03-p18~

void Sprite::Update() {

}