#include "Engine/Model.h"
#include "Engine/Common.h"


namespace Model
{
    std::vector<ModelData*> datas;
}


int Model::Load(std::string fileName)
{
    //①構造体のインスタンスを作成。
    ModelData* pData = new ModelData;

    //②そのメンバのファイル名に引数の内容を代入
    pData->fileName = fileName;

    //すでにロードしていないか調べる
    bool isExit = false;
    for (int i = 0; i < datas.size(); i++)
    {
        if (datas[i]->fileName == fileName)
        {
            pData->pFbx = datas[i]->pFbx;
            isExit = true;
            break;
        }
    }


    if (isExit == false)
    {
        //③Fbxオブジェクトを作成し、ロードする
        pData->pFbx = new Fbx;
        pData->pFbx->Load(fileName);
    }


    //④構造体の中身が埋まったので動的配列に突っ込む
    datas.push_back(pData);

    //⑤番号（配列の要素数-1）を返す
    return datas.size()-1;
}

void Model::SetTransform(int hModele, Transform transform)
{
    datas[hModele]->transform = transform;
}

void Model::Draw(int hModele)
{
    datas[hModele]->pFbx->Draw(datas[hModele]->transform, 0);
}

void Model::AllRelese()
{
    for (int i = 0; i < datas.size(); i++)
    {
        //同じFBXオブジェクトを見てるやつがいるか探す
        bool isExit = false;
        for (int j = i+1; j < datas.size(); j++)
        {
            if (datas[i]->fileName == datas[j]->fileName)
            {
                isExit = true;
                break;
            }
        }
        if(isExit == false)
        {
            SAFE_DELETE(datas[i]->pFbx);
        }
    }

    //最後に配列を削除
    datas.clear();
}
