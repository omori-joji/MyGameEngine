#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

namespace Direct3D
{
	ID3D11Device* pDevice = nullptr;						//デバイス
	ID3D11DeviceContext* pContext = nullptr;				//デバイスコンテキスト
	IDXGISwapChain* pSwapChain = nullptr;					//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView = nullptr;	//レンダーターゲットビュー

	//Zバッファ法を用いて、３D物体の前後関係を正しく描画する
	ID3D11Texture2D* pDepthStencil;
	ID3D11DepthStencilView* pDepthStencilView;
	ID3D11VertexShader* pVertexShader = nullptr;			//頂点シェーダー
	ID3D11PixelShader* pPixelShader = nullptr;				//ピクセルシェーダー
	ID3D11InputLayout* pVertexLayout = nullptr;				//頂点インプットレイアウト
	ID3D11RasterizerState* pRasterizerState = nullptr;		//ラスタライザー

	//【ブレンドステート】
	//半透明のものをどのように表現するか
	ID3D11BlendState* pBlendState;
}

//初期化
void Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
	//準備
	Preparation(winW, winH, hWnd);

	//レンダーターゲットビュー作成
	RenderTargetView();

	//ブレンドステート作成
	BlendState();

	//ビューポート作成
	ViewPort(winW, winH);

	//シェーダー準備
	InitShader();
}

//シェーダー準備
void Direct3D::InitShader()
{
	DWORD vectorSize = sizeof(XMVECTOR);

	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
	assert(pVertexShader != nullptr);

	//頂点インプットレイアウト
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
		{ "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,sizeof(XMFLOAT3),	D3D11_INPUT_PER_VERTEX_DATA, 0 },//法線
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, sizeof(XMFLOAT3) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },//UV座標
	};
	pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
	//一時的に使った変数を消す
	SAFE_RELEASE(pCompileVS);;

	//ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
	pCompilePS->Release();

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	pDevice->CreateRasterizerState(&rdc, &pRasterizerState);
}

//描画開始
void Direct3D::BeginDraw()
{
	//それぞれをデバイスコンテキストにセット
	//（エフェクトを表示する時に別なシェーダーを使っているので、ここで毎回セットしなおす）
	pContext->VSSetShader(pVertexShader, NULL, 0);	//頂点シェーダー
	pContext->PSSetShader(pPixelShader, NULL, 0);	//ピクセルシェーダー
	pContext->IASetInputLayout(pVertexLayout);		//頂点インプットレイアウト
	pContext->RSSetState(pRasterizerState);			//ラスタライザー

	//背景の色
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//画面をクリア
	pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	//深度バッファクリア
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//描画終了
void Direct3D::EndDraw()
{
	//スワップ（バックバッファを表に表示する）
	pSwapChain->Present(0, 0);
}

//解放処理
void Direct3D::Release()
{
	SAFE_RELEASE(pBlendState);
	SAFE_RELEASE(pRasterizerState);
	SAFE_RELEASE(pVertexLayout);
	SAFE_RELEASE(pPixelShader);
	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pDepthStencilView);
	SAFE_RELEASE(pDepthStencil);
	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);
	SAFE_RELEASE(pContext);
	SAFE_RELEASE(pDevice);
}

void Direct3D::Preparation(int winW, int winH, HWND hWnd)
{
	///////////////////////////いろいろ準備するための設定///////////////////////////////
	//いろいろな設定項目をまとめた構造体
	DXGI_SWAP_CHAIN_DESC scDesc;

	//とりあえず全部0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//描画先のフォーマット
	scDesc.BufferDesc.Width = winW;
	scDesc.BufferDesc.Height = winH;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//FPS（1/60秒に1回）
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc.Windowed = TRUE;
	scDesc.OutputWindow = hWnd;
	scDesc.BufferCount = 1;

	//バックバッファの使い道＝画面に描画するために
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;

	////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,						// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,						// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		0,								// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,						// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,								// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,				// SDKのバージョン。必ずこの値
		&scDesc,						// 上でいろいろ設定した構造体
		&pSwapChain,					// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice,						// 無事完成したDeviceアドレスが返ってくる
		&level,							// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext);						// 無事完成したContextのアドレスが返ってくる
	//安全対策
	assert(pSwapChain != nullptr);
	assert(pDevice != nullptr);
	assert(pContext != nullptr);
}

void Direct3D::RenderTargetView()
{
	///////////////////////////レンダーターゲットビュー作成///////////////////////////////
	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//レンダーターゲットビューを作成
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	assert(pRenderTargetView != nullptr);
	assert(pBackBuffer != nullptr);

	//一時的にバックバッファを取得しただけなので解放
	pBackBuffer->Release();
}

void Direct3D::BlendState()
{
	//ブレンドステート
	//透過するため
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Direct3D::pDevice->CreateBlendState(&BlendDesc, &pBlendState);
	assert(pBlendState != nullptr);

	float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	Direct3D::pContext->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}

void Direct3D::ViewPort(int winW, int winH)
{
	///////////////////////////ビューポート（描画範囲）設定///////////////////////////////
	//レンダリング結果を表示する範囲
	D3D11_VIEWPORT vp;
	vp.Width = (float)winW;		//幅
	vp.Height = (float)winH;	//高さ
	vp.MinDepth = 0.0f;			//手前
	vp.MaxDepth = 1.0f;			//奥
	vp.TopLeftX = 0;			//左
	vp.TopLeftY = 0;			//上

	//深度ステンシルビューの作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = winW;
	descDepth.Height = winH;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	Direct3D::pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	Direct3D::pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);
	assert(pDepthStencil != nullptr);
	assert(pDepthStencilView != nullptr);

	//データを画面に描画するための一通りの設定（パイプライン）
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);			// データの入力種類を指定
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);				// 描画先を設定
	assert(pDepthStencilView != nullptr);
	assert(pRenderTargetView != nullptr);
	pContext->RSSetViewports(1, &vp);
}

