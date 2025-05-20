#pragma once
#include <string>
#include <d3d12.h>

#include <d3dcompiler.h>
#include <dxcapi.h>

class Shader {
public:
	// シェーダーファイル読み込み、コンパイル済みデータ生成する
	void Load(const std::wstring& filePath, const std::wstring& shaderModel);
	void LoadDxc(const std::wstring& filePath, const std::wstring& shaderModel);

	// 生成したコンパイル済みデータ取得する
	IDxcBlob* GetDxcBlob();

	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader();

private:
	ID3DBlob* blob_ = nullptr;

	IDxcBlob* dxcBlob_ = nullptr;
};
