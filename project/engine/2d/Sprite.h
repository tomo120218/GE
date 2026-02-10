#pragma once
#include <math.h>
#include <d3d12.h>
#include <wrl.h>
#include <string>

class SpriteCommon;

class Sprite
{
public: // メンバ変数
	void Initialize(SpriteCommon* spriteCommon);

	void Update();

private:
	SpriteCommon* spriteCommon = nullptr;

	// 頂点データ
	struct VertexData {
		math::Vector4 position;
		math::Vector2 texcoord;
		math::Vector3 normal;
	};

	// マテリアルデータ
	struct Material {
		math::Vector4 color;
		int32_t enableLighting;
		float padding[3];
		math::Matrix4x4 uvTransform;
	};

	// 座標転換行列データ
	struct TransformationMatrix {
		math::Matrix4x4 WVP;
		math::Matrix4x4 World;
	};

	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;

	//頂点インデックス
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResourceSprite;

	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;

	// バッファリソース内のデータを指すポインタ
	Material* materialData = nullptr;

	// バッファリソース内のデータを指すポインタ
	VertexData* vertexData = nullptr;
	uint32_t* indexData = nullptr;

	// バッファリソースの使い道を補足するバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;

	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;

	// バッファリソース内のデータを指すポインタ
	Material* materialData = nullptr;

	// バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResourceSprite;

	// バッファリソース内のデータを指すポインタ
	TransformationMatrix* transforMatrixData = nullptr;

};

