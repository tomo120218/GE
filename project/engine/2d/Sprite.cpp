#include "Sprite.h"
#include "SpriteCommon.h"
#include "DirectXCommon.h"

void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	// 引数で受け取ってメンバ変数にする
	this->spriteCommon = spriteCommon;

	// バーテックスリソース
	vertexResource = spriteCommon->GetDxCommon()->CreateBufferResource(sizeof(VertexData) * 6);
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//1枚目の三角形
	vertexData[0].position = { 0.0f,360.0f,0.0f,1.0f };//左下
	vertexData[0].texcoord = { 0.0f,1.0f };
	//vertexData[0].normal = { 0.0f,0.0f, -1.0f };
	vertexData[1].position = { 0.0f,0.0f,0.0f,1.0f };//左上
	vertexData[1].texcoord = { 0.0f,0.0f };
	//vertexData[1].normal = { 0.0f,0.0f, -1.0f };
	vertexData[2].position = { 640.0f,360.0f,0.0f,1.0f };//右下
	vertexData[2].texcoord = { 1.0f,1.0f };
	//vertexData[2].normal = { 0.0f,0.0f, -1.0f };
	vertexData[3].position = { 640.0f,0.0f,0.0f,1.0f };//右上
	vertexData[3].texcoord = { 1.0f,0.0f };
	//vertexData[3].normal = { 0.0f,0.0f, -1.0f };

	// インデックスリソーススプライト
	indexResourceSprite = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(uint32_t) * 6);
	indexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	//マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	materialResource = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(Material));
	//マテリアルにデータを書き込む
	materialData = nullptr;
	//書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//今回は白を書き込んでみる
	// マテリアルデータの初期値を書き込む
	materialData->color = MyMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	materialData->enableLighting = false;
	//materialData->uvTransform = MyMath::MakeIdentity4x4();

	//wvpResource = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(MyMath::Matrix4x4));
	//データを書き込む

	//書き込むためのアドレスを取得
	//wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//単位行列を書き込んでおく
	//*wvpData = MyMath::MakeIdentity4x4();


	//Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResourceSprite = spriteCommon->GetDxCommon()->CreateBufferResource(/*device,*/ sizeof(MyMath::Matrix4x4));
	//データを書き込む
	//書き込むためのアドレスを取得
	transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transforMatrixData));
	//単位行列を書き込んでおく
	//*transformationMatrixDataSprite = MyMath::MakeIdentity4x4();

	// 単位行列を書き込んでおく
	transforMatrixData->WVP = MyMath::MakeIdentity4x4();
	transforMatrixData->World = MyMath::MakeIdentity4x4();

	//リソースの先頭のアドレスから使う
	vertexBufferViewSprite.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 4;
	//1頂点あたりのサイズ
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);

	//D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
	//リソースの先頭のアドレスから使う
	indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
	//使用するリソースのサイズはインデックス6つ分のサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_tとする
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = spriteCommon->GetDxCommon()->GetSRVCPUDescriptorHandle(1);
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = spriteCommon->GetDxCommon()->GetSRVGPUDescriptorHandle(1);

	DirectX::ScratchImage mipImages = spriteCommon->GetDxCommon()->LoadTexture("resources/uvChecker.png");
	//DirectX::ScratchImage mipImages = dxCommon->LoadTexture(modelData.material.textureFilePath);

	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	textureResouce = spriteCommon->GetDxCommon()->CreateTextureResource(metadata);
	spriteCommon->GetDxCommon()->UpLoadTextureData(textureResouce, mipImages);

	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
	spriteCommon->GetDxCommon()->GetDevice()->CreateShaderResourceView(textureResouce.Get(), &srvDesc, textureSrvHandleCPU);
}

void Sprite::Update() {
	// 接点リソースにデータを書き込む
	// インデックスリソースにデータを書き込む
	//インデックスリソースにデータを書き込む

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	//1枚目の三角形
	vertexData[0].position = { 0.0f,360.0f,0.0f,1.0f };//左下
	vertexData[0].texcoord = { 0.0f,1.0f };
	//vertexData[0].normal = { 0.0f,0.0f, -1.0f };
	vertexData[1].position = { 0.0f,0.0f,0.0f,1.0f };//左上
	vertexData[1].texcoord = { 0.0f,0.0f };
	//vertexData[1].normal = { 0.0f,0.0f, -1.0f };
	vertexData[2].position = { 640.0f,360.0f,0.0f,1.0f };//右下
	vertexData[2].texcoord = { 1.0f,1.0f };
	//vertexData[2].normal = { 0.0f,0.0f, -1.0f };
	vertexData[3].position = { 640.0f,0.0f,0.0f,1.0f };//右上
	vertexData[3].texcoord = { 1.0f,0.0f };
	//vertexData[3].normal = { 0.0f,0.0f, -1.0f };

	// Transform情報を作る
	// TransformからWorldMatrixを作る
	// ViewMatrixを作って単位行列を代入
	// ProjectionMatrixを作って並行投影行列を書き込む
	MyMath::Matrix4x4 worldMatrix = MyMath::MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	//* wvpData = worldMatrix;
	MyMath::Matrix4x4 cameraMatrix = MyMath::MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	MyMath::Matrix4x4 viewMatrix = MyMath::MakeIdentity4x4();
	MyMath::Matrix4x4 projectionMatrix =
		MyMath::MakeOrthorgraphicMatrix(
			0.0f,
			0.0f,
			float(WinApp::kClientWidth),
			float(WinApp::kClientHeight),
			0.0f,
			100.0f
		);
	transforMatrixData->WVP =
		MyMath::Multiply(worldMatrix,
			MyMath::Multiply(viewMatrix, projectionMatrix));
	transforMatrixData->World = worldMatrix;
}

void Sprite::Draw()
{
	// VertexBufferViewを設定
	//Spriteの描画。変更が必要なものだけ変更する
	spriteCommon->GetDxCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);//VBVを設定
	//TransformationMatrixCBufferの場所を設定
	spriteCommon->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());
	//インデックスを指定
	spriteCommon->GetDxCommon()->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);//IBVを設定

	spriteCommon->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());

	// SRVのDescriptorTableの先頭を設定
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = spriteCommon->GetDxCommon()->GetSRVGPUDescriptorHandle(1);
	spriteCommon->GetDxCommon()->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);

	//描画！(DrawCall/ドローコール)6個のインデックスを使用し1つのインスタンスを描画。その他当面0で良い
	spriteCommon->GetDxCommon()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

	// マテリアルCBufferの場所を設定
	// 座標変換行列CBffferの場所を設定

	// SRVのDescriptorTableの場所を設定
	// 描画！(DrawCall/ドローコール)
}