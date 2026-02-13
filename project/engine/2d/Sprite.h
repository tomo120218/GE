#pragma once
#include <MyMath.h>
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <cstdint>

class SpriteCommon;

class Sprite
{
public: // メンバ変数
	void Initialize(SpriteCommon* spriteCommon);

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

private:
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
};

