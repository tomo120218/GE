#pragma once
#include <MyMath.h>
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <cstdint>
#include "DirectXCommon.h"

class SpriteCommon;

class Sprite
{
public: // メンバ変数
	void Initialize(SpriteCommon* spriteCommon, std::string textureFilePath);

	void Update();

	void Draw();

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	// getter
	const MyMath::Vector2& GetPosition() const { return position; }
	// setter
	void SetPosition(const MyMath::Vector2& position) { this->position = position; }

	// 回転
	float GetRotation() const { return rotation; }
	void SetRotation(float rotation) { this->rotation = rotation; }

	// 色
	const MyMath::Vector4& GetColor() const { return materialData->color; }
	void SetColor(const MyMath::Vector4& color) { materialData->color = color; }

	// サイズ
	const MyMath::Vector2& GetSize() const { return size; }
	void SetSize(const MyMath::Vector2& size) { this->size = size; }

	uint32_t textureIndex = 0;

	// getter
	const MyMath::Vector2& GetAnchorPoint() const { return anchorPoint; }
	// setter
	void SetAnchorPoint(const MyMath::Vector2& anchorPoint) { this->anchorPoint = anchorPoint; }

	// 左右フリップ
	bool isFlipX_ = false;
	// 上下フリップ
	bool isFlipY_ = false;

	const BOOL& GetIsFlipX()const { return isFlipX_; }
	void SetIsFlipX(const BOOL& isFlipX_) { this->isFlipX_ = isFlipX_; }


	const BOOL& GetIsFlipY()const { return isFlipY_; }
	void SetIsFlipY(const BOOL& isFlipY_) { this->isFlipY_ = isFlipY_; }


	const MyMath::Vector2& GetTextureLeftTop()const { return textureLeftTop; }
	void SetTextureLeftTop(const MyMath::Vector2& textureLeftTop) { this->textureLeftTop = textureLeftTop; }


	const MyMath::Vector2& GetTextureSize() { return textureSize; }
	void SetTextureSize(const MyMath::Vector2& textureSize) { this->textureSize = textureSize; }

private:

	DirectXCommon* dxCommon_;

	// 頂点データ
	struct VertexData {
		MyMath::Vector4 position;
		MyMath::Vector2 texcoord;
		MyMath::Vector3 normal;
	};

	// マテリアルデータ
	struct Material {
		MyMath::Vector4 color;
		int32_t enableLighting;
		/*float padding[3];
		MyMath::Matrix4x4 uvTransform;*/
	};

	// 座標転換行列データ
	struct TransformationMatrix {
		MyMath::Matrix4x4 WVP;
		MyMath::Matrix4x4 World;
	};

	SpriteCommon* spriteCommon = nullptr;
	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	//頂点インデックス
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResourceSprite;
	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;

	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResourceSprite;

	Microsoft::WRL::ComPtr<ID3D12Resource> textureResouce;

	// バッファリソース内のデータを指すポインタ
	Material* materialData = nullptr;
	// バッファリソース内のデータを指すポインタ
	VertexData* vertexData = nullptr;
	uint32_t* indexData = nullptr;

	// バッファリソース

	// バッファリソース内のデータを指すポインタ
	TransformationMatrix* transforMatrixData = nullptr;

	MyMath::Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	MyMath::Transform cameraTransform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };

	MyMath::Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	MyMath::Vector2 position = { 0.0f, 0.0f };

	float rotation = 0.0f;

	// サイズ
	MyMath::Vector2 size = { 100.0f, 100.0f };

	MyMath::Vector2 anchorPoint = { 0.0f, 0.0f };

	// テキスチャ左上座標
	MyMath::Vector2 textureLeftTop = { 0.0f,0.0f };
	// テキスチャ切り出しサイズ
	MyMath::Vector2 textureSize = { 100.0f, 100.0f };

	//テクスチャサイズをイメージに合わせる
	void AdjustTextureSize();
};

