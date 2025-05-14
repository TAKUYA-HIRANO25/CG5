#pragma once
#include <string>
#include <d3dcompiler.h>
#include <dxcapi.h>
#pragma comment(lib, "dxcompiler.lib")

class Shader {
public:
	// シェーダーファイル読み込み、コンパイル済みデータ生成する
	void Load(const std::wstring& filePath, const std::wstring& shaderModel);
	void LoadDxc(const std::wstring& filePath, const std::wstring& shaderModel);

	// 生成したコンパイル済みデータ取得する
	ID3DBlob* GetBlod();

	IDxcBlob* GetDxcBlob();

	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader();

private:
	ID3DBlob* blob_ = nullptr;

	IDxcBlob* dxcBlob_ = nullptr;
};
