#pragma once
#include <string>
#include <d3d12.h>

class Shader {
public:
	// シェーダーファイル読み込み、コンパイル済みデータ生成する
	void Load(const std::wstring& filePath, const std::string& shaderModel);

	// 生成したコンパイル済みデータ取得する
	ID3DBlob* GetBlod();

	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader();

private:
	ID3DBlob* blob_ = nullptr;

};
