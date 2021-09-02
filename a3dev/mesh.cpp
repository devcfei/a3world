#include "framework.h"
#include "a3dev.h"

using namespace std;

struct CUSTOMVERTEX
{
    FLOAT x, y, z, u, v; // The transformed position for the vertex
    //DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)



mesh::mesh()
{

}

mesh::mesh(LPCTSTR path, LPCTSTR fullname)
    :m_lpszPath(path)
    ,m_lpszFileName(fullname)
    ,m_preVS(true)
{

    LPCTSTR p;

    int nSize = lstrlen(m_lpszFileName);
    for (int i = nSize - 1; i > 0; --i)
    {
        if (m_lpszFileName[i] == _T('.'))	// find the suffix
        {
            p = &m_lpszFileName[i];

            if (i > 5)
            {
                p -= 5;

                if (!lstrcmp(p, _T("_post.csv")))
                {
                    m_preVS = false;
                }

            }
            break;
        }
    }
    
}


void mesh::getFileName(TCHAR* szFileName, int size)
{
    LPCTSTR p;
    LPCTSTR q;
    int n = 0;

    int nSize = lstrlen(m_lpszFileName);
    for (int i = nSize - 1; i > 0; --i)
    {
        if (m_lpszFileName[i] == _T('\\'))	// find the suffix
        {
            p = &m_lpszFileName[i+1];

            q = p;

            while (q != NULL && n<size)
            {
                if (*q == _T('.'))
                {
                    szFileName[n] = 0;
                    break;
                }
                else
                {
                    szFileName[n] = *q;
                }
                n++;
                q++;
                
            }
            
            
            break;
        }
    }
}


int mesh::getMeshInfo(char* path, int& triangleCount, int & vertexCount)
{
    int line = 0;
    int indexMax = 0;
    int line_elem = 0;


    ifstream inFile(path, ios::in);

    string lineStr;
    vector<vector<string>> strArray;



    while (getline(inFile, lineStr))
    {
        if (line != 0)
        {

            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;

            line_elem = 0;

            while (getline(ss, str, ','))
            {
                if (line_elem == 1)
                {
                    int n=atoi(str.c_str());
                    if (n > indexMax)
                        indexMax = n;
                }
                
                lineArray.push_back(str);

                line_elem++;
            }
            strArray.push_back(lineArray);

        }
        line++;
    }


    vertexCount = indexMax + 1;

    triangleCount = (line - 1) / 3;

    return 0;

}

void mesh::initVertices(char* path, VOID* p, int vectexCount)
{
    int line = 0;
    int indexMax = 0;
    int line_elem = 0;
    ifstream inFile(path, ios::in);

    string lineStr;
    vector<vector<string>> strArray;


    CUSTOMVERTEX v = { -1.0f, -1.0f, -1.0f, 0xffff0000 };

    int n=0;

    while (getline(inFile, lineStr))
    {
        if (line != 0)
        {

            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;

            line_elem = 0;

            while (getline(ss, str, ','))
            {
                if (line_elem == 1)
                {
                    n = atoi(str.c_str());
                    if (n > indexMax)
                        indexMax = n;
                }
                CUSTOMVERTEX* pv = (CUSTOMVERTEX*)p;
                if (line_elem == 2) //x
                {
                    pv[n].x = (FLOAT)atof(str.c_str());
                    pv[n].x /= 2000.0f; 

                }
                if (line_elem == 3) //y
                {
                    pv[n].y = (FLOAT)atof(str.c_str());
                    pv[n].y /= 2000.0f;
                    pv[n].y -= 4.0f;

                }

                if (line_elem == 4) //z
                {
                    pv[n].z = (FLOAT)atof(str.c_str());
                    pv[n].z /= 2000.0f;
                }

                if (line_elem == 11) //u
                {
                    pv[n].u = (FLOAT)atof(str.c_str());
                }

                if (line_elem == 12) //v
                {
                    pv[n].v = (FLOAT)atof(str.c_str());
      
                }

                lineArray.push_back(str);

                line_elem++;
            }
            strArray.push_back(lineArray);

        }
        line++;
    }


}


void mesh::initVerticespost(char* path, VOID* p, int vectexCount)
{
    int line = 0;
    int indexMax = 0;
    int line_elem = 0;
    ifstream inFile(path, ios::in);

    string lineStr;
    vector<vector<string>> strArray;


    CUSTOMVERTEX v = { -1.0f, -1.0f, -1.0f, 0xffff0000 };

    int n = 0;

    while (getline(inFile, lineStr))
    {
        if (line != 0)
        {

            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;

            line_elem = 0;

            while (getline(ss, str, ','))
            {
                if (line_elem == 1)
                {
                    n = atoi(str.c_str());
                    if (n > indexMax)
                        indexMax = n;
                }
                CUSTOMVERTEX* pv = (CUSTOMVERTEX*)p;
                if (line_elem == 3) //x
                {
                    pv[n].x = (FLOAT)atof(str.c_str());


                }
                if (line_elem == 4) //y
                {
                    pv[n].y = (FLOAT)atof(str.c_str());

                }

                if (line_elem == 5) //z
                {
                    pv[n].z = (FLOAT)atof(str.c_str());


                   
                }

                if (line_elem == 16) //u
                {
                    pv[n].u = (FLOAT)atof(str.c_str());
                }

                if (line_elem == 17) //v
                {
                    pv[n].v = (FLOAT)atof(str.c_str());

                }

                lineArray.push_back(str);

                line_elem++;
            }
            strArray.push_back(lineArray);

        }
        line++;
    }


}

void mesh::initIB(char* path, VOID* p, int triangleCount)
{
    int line = 0;
    int indexMax = 0;
    int line_elem = 0;
    ifstream inFile(path, ios::in);
    string lineStr;
    vector<vector<string>> strArray;


    int n = 0;
    int i = 0;

    while (getline(inFile, lineStr))
    {
        if (line != 0)
        {

            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;

            line_elem = 0;

            while (getline(ss, str, ','))
            {
                if (line_elem == 0)
                {
                    i = atoi(str.c_str());
                    if (n > indexMax)
                        indexMax = n;
                }

                if (line_elem == 1)
                {
                    n = atoi(str.c_str());
                    if (n > indexMax)
                        indexMax = n;

                    WORD* pw = (WORD*)p;

                    pw[i] = n;

                    TRACE(_T("INDIEX[%d]:%d\n"), i, n);
                }


                lineArray.push_back(str);

                line_elem++;
            }
            strArray.push_back(lineArray);

        }
        line++;
    }


}

HRESULT mesh::Create(LPDIRECT3DDEVICE9 d3dDevice)
{
    HRESULT hr;
    m_d3dDevice = d3dDevice;

    //
    // Read csv file from disk
    //

    TCHAR strT[256];

    USES_CONVERSION;
    char* str = T2A(m_lpszFileName);

    getMeshInfo(str, triangleCount, vertexCount);

    if (FAILED(d3dDevice->CreateVertexBuffer(vertexCount * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &m_pVB, NULL)))
    {
        return E_FAIL;
    }

    VOID* pVertices;
    if (FAILED(m_pVB->Lock(0, vertexCount * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
        return E_FAIL;


    if (m_preVS)
    {
        initVertices(str, pVertices, vertexCount);

    }
    else
    {
        initVerticespost(str, pVertices, vertexCount);

    }


    m_pVB->Unlock();



    if (FAILED(d3dDevice->CreateIndexBuffer(triangleCount *3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, 0)))
        return E_FAIL;

    WORD* k = 0;
    if (FAILED(m_pIB->Lock(0, 0, (void**)&k, 0)))
        return E_FAIL;

    initIB(str, k, triangleCount);


    if (FAILED(m_pIB->Unlock()))
        return E_FAIL;


    // get the mesh name and see if texture there
    TCHAR name[64];

    getFileName(name, 64);


    LPDIRECT3DTEXTURE9 tex;

    for(int j=0;j<10;++j)   // max 10 textures
    {

        wsprintf(strT, _T("%s\\%s%d.bmp"), m_lpszPath,name, j );

        // 
        hr = D3DXCreateTextureFromFile(m_d3dDevice, strT, &tex);

        if (SUCCEEDED(hr))
        {
            m_vecTex.push_back(tex);
        }
        else
            break;
    }



    //{
    //    DWORD dwShaderFlags = D3DXSHADER_DEBUG | D3DXSHADER_SKIPVALIDATION;
    //    // shader
    //    LPD3DXBUFFER pCode;
    //    hr = D3DXAssembleShaderFromFile(_T("aa.vsh"), NULL, NULL, dwShaderFlags, &pCode, NULL);


    //    // Create the vertex shader
    //    hr = m_d3dDevice->CreateVertexShader((DWORD*)pCode->GetBufferPointer(), &m_vsh);
    //    pCode->Release();
    //}


    //{

    //    DWORD dwShaderFlags = D3DXSHADER_DEBUG | D3DXSHADER_SKIPVALIDATION;
    //    LPD3DXBUFFER pCode;
    //    hr = D3DXAssembleShaderFromFile(_T("aa.psh"), NULL, NULL, dwShaderFlags, &pCode, NULL);

    //    hr = m_d3dDevice->CreatePixelShader((DWORD*)pCode->GetBufferPointer(), &m_psh);

    //    pCode->Release();
    //}



    return S_OK;
}


HRESULT mesh::Draw(drawsettings& ds)
{


    HRESULT hr;


    hr = m_d3dDevice->SetRenderState(D3DRS_LIGHTING, ds.lightOn);
    hr = m_d3dDevice->SetRenderState(D3DRS_CULLMODE, ds.cullMode);
    hr = m_d3dDevice->SetRenderState(D3DRS_FILLMODE, ds.fillMode);




    hr = m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    hr = m_d3dDevice->SetIndices(m_pIB);
    hr = m_d3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);


    for (std::vector< LPDIRECT3DTEXTURE9>::iterator it = m_vecTex.begin();
        it != m_vecTex.end();
        ++it)
    {

        int index = it - m_vecTex.begin();
        hr = m_d3dDevice->SetTexture(index, (*it));

    }

    m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    m_d3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);


    hr = m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);

    return S_OK;
}




HRESULT mesh::UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle)
{
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

    FLOAT fAngle = D3DX_PI * camAngle / 18;   // WY - one step for 10 degree 
    D3DXMatrixRotationY(&matWorld, fAngle);
    m_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt(eyeX, eyeY, eyeZ);
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    m_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
    m_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
    return S_OK;
}



HRESULT mesh::Reset()
{
    HRESULT hr = S_OK;


    if (m_d3dDevice)
    {
        m_d3dDevice = NULL;
    }

    if (m_pVB)
        m_pVB->Release();



    if (m_pIB)
        m_pIB->Release();



    return hr;
}