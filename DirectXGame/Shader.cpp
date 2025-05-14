#include "Shader.h"
#include <d3dcompiler.h>
#include <cassert>
#include "MiscUtility.h"

void Shader::Load(const std::wstring& filePath, const std::wstring& shaderModel) {
	// コンパイル済みのShader,エラー時情報の格納場所の用意
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	std::string mbShaderModel = ConvertString(shaderModel);

	HRESULT hr = D3DCompileFromFile(filePath.c_str(), 
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		"main", mbShaderModel.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 
		0, &shaderBlob, &errorBlob);

	if (FAILED(hr)) {
		if (errorBlob) {
			OutputDebugStringA(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		}
		assert(false);
	}
	// 生成したshaderBlobを取っておく
	blob_ = shaderBlob;

}

// シェーダーファイルを読み込み、コンパイルする
// *外部コンパイル版 シェーダーモデル 6.0以上で利用する
void Shader::LoadDxc(const std::wstring& filePath, const std::wstring& shaderModel) {
	// DXC(DirectX Shader Comipiler)を初期化
	static IDxcUtils* dxcUtils = nullptr;
	static IDxcCompiler3* dxccompiler = nullptr;
	static IDxcIncludeHandler* includeHandler = nullptr;

	HRESULT hr;
	if (dxcUtils == nullptr) {
		hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcUtils));
		assert(SUCCEEDED(hr));
	}
	if (dxccompiler == nullptr) {
		hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxccompiler));
		assert(SUCCEEDED(hr));
	}
	if (includeHandler == nullptr) {
		hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&includeHandler));
		assert(SUCCEEDED(hr));
	}

	// 1. Hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	assert(SUCCEEDED(hr));

	// 読み込んだファイルの内容をDxcBufferに設定する
	DxcBuffer shaderSourceBuffer{};
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;

	// 2. Compileする
	//    Compileに必要なコンパイルオプションの準備
	LPCWSTR arguments[] = {
	    filePath.c_str(),
	    L"-E",
	    L"main",
	    L"-T",
	    shaderModel.c_str(),
	    L"-Zi",
	    L"-Qembed_debug",
	    L"-Qd",
	    L"-Zpr",
	};

	// 実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	hr = dxccompiler->Compile(
		&shaderSourceBuffer, 
		arguments, _countof(arguments), 
		includeHandler, 
		IID_PPV_ARGS(&shaderResult)
	);
	assert(SUCCEEDED(hr));

	// 3. 警告 エラーが出ていないか確認する
	IDxcBlobUtf8* shadererror = nullptr;
	IDxcBlobWide* nameBlob = nullptr;

}

ID3DBlob* Shader::GetBlod() { 
	return blob_;

}

Shader::Shader() {

}

Shader::~Shader() {

	if (blob_ != nullptr) {
		blob_->Release();
		blob_ = nullptr;
	}

}
