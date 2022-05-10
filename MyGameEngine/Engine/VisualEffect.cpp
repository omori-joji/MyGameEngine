#include <d3dcompiler.h>
#include <vector>
#include <list>
#include <DirectXMath.h>
#include "VisualEffect.h"
#include "Texture.h"
#include "Direct3D.h"
#include "Common.h"
using namespace DirectX;


namespace VisualEffect
{
	std::vector<VFXTextureData*> textureDatas;
    std::list<VFX*> vfxs;

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ


    ID3D11VertexShader* pVertexShader = nullptr;	//頂点シェーダー
    ID3D11PixelShader* pPixelShader = nullptr;		//ピクセルシェーダー
    ID3D11InputLayout* pVertexLayout = nullptr;	//頂点インプットレイアウト
    ID3D11RasterizerState* pRasterizerState = nullptr;	//ラスタライザー
}



void VisualEffect::Initialize()
{
	// 頂点情報
	VERTEX vertices[] =
	{
        { XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f)}, // 四角形の頂点（左上）
        { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f)}, // 四角形の頂点（右上）
        { XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f)}, // 四角形の頂点（右下）
        { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f)}  // 四角形の頂点（左下）
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

	//インデックス情報
	int index[] = { 0,2,3, 0,1,2, };

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);






    // 頂点シェーダの作成（コンパイル）
    ID3DBlob* pCompileVS = nullptr;
    D3DCompileFromFile(L"VFX.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
    assert(pCompileVS != nullptr);
    Direct3D::pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
    assert(pVertexShader != nullptr);

    //頂点インプットレイアウト
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
    };
    Direct3D::pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
    SAFE_RELEASE(pCompileVS);;//一時的に使った変数を消す



    // ピクセルシェーダの作成（コンパイル）
    ID3DBlob* pCompilePS = nullptr;
    D3DCompileFromFile(L"VFX.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
    assert(pCompilePS != nullptr);
    Direct3D::pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
    pCompilePS->Release();

    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_BACK;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    Direct3D::pDevice->CreateRasterizerState(&rdc, &pRasterizerState);
}

int VisualEffect::Load(std::string fileName, DWORD width, DWORD height)
{
    //①構造体のインスタンスを作成。
    VFXTextureData* pData = new VFXTextureData;

    //②そのメンバのファイル名に引数の内容を代入
    pData->fileName = fileName;
    pData->width = width;
    pData->height = height;

    //すでにロードしていないか調べる
    bool isExit = false;
    for (int i = 0; i < textureDatas.size(); i++)
    {
        if (textureDatas[i]->fileName == fileName)
        {
            pData->pTexture = textureDatas[i]->pTexture;
            isExit = true;
            break;
        }
    }


    if (isExit == false)
    {
        //③Fbxオブジェクトを作成し、ロードする
        pData->pTexture = new Texture;
        pData->pTexture->Load(fileName);
    }


    //④構造体の中身が埋まったので動的配列に突っ込む
    textureDatas.push_back(pData);

    //⑤番号（配列の要素数-1）を返す
    return textureDatas.size() - 1;
}



void VisualEffect::Add(int hVfx, Transform transform, float speed, bool isLoop)
{
    VFX* pVFX = new VFX();
    pVFX->Create(textureDatas[hVfx], transform, speed, isLoop);
    vfxs.push_back(pVFX);
}

void VisualEffect::Update()
{
    //全エフェクトを更新
    for (auto i = vfxs.begin(); i != vfxs.end(); )
    {
        //更新
        bool isDestroy = (*i)->Update();

        if (isDestroy)
        {
            //そのエフェクトを削除
            SAFE_DELETE(*i);
            i = vfxs.erase(i);
        }
        else
        {
            i++;
        }
    }
}

void VisualEffect::Draw()
{
    //それぞれをデバイスコンテキストにセット
    Direct3D::pContext->VSSetShader(pVertexShader, NULL, 0);	//頂点シェーダー
    Direct3D::pContext->PSSetShader(pPixelShader, NULL, 0);	    //ピクセルシェーダー
    Direct3D::pContext->IASetInputLayout(pVertexLayout);	    //頂点インプットレイアウト
    Direct3D::pContext->RSSetState(pRasterizerState);		    //ラスタライザー

    //全エフェクトを描画
    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
    {
        (*i)->Draw();
    }
}

void VisualEffect::Release()
{
    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
    {
        SAFE_DELETE(*i);
    }
    vfxs.clear();
}
