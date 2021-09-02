#include "framework.h"
#include "a3dev.h"


struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

static CUSTOMVERTEX m_vertices[8];

cube::cube()
{
    CUSTOMVERTEX vertices[] =
    {
		{ -1.0f, -1.0f, -1.0f, 0xffff0000, },
		{ -1.0f,  1.0f, -1.0f, 0xff0000ff, },
        { 1.0f,  1.0f, -1.0f, 0xff00ff00, },
        { 1.0f, -1.0f, -1.0f, 0xffff0000, },
		{ -1.0f, -1.0f,  1.0f, 0xff0000ff, },
		{ -1.0f,  1.0f,  1.0f, 0xff00ff00, },
		{ 1.0f,  1.0f,  1.0f, 0xffff0000, },
		{ 1.0f, -1.0f,  1.0f, 0xff0000ff, },

    };

    CopyMemory(m_vertices, vertices, sizeof(vertices));
}


HRESULT cube::Create(LPDIRECT3DDEVICE9 d3dDevice)
{
    m_d3dDevice = d3dDevice;

    if (FAILED(d3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &m_pVB, NULL)))
    {
        return E_FAIL;
    }

    VOID* pVertices;
    if (FAILED(m_pVB->Lock(0, sizeof(m_vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    CopyMemory(pVertices, m_vertices, sizeof(m_vertices));
    m_pVB->Unlock();



    if (FAILED(d3dDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, 0)))
        return E_FAIL;


    // Now lock it to obtain a pointer to its internal data, and write the
    // cube's index data.

    WORD* k = 0;

    if (FAILED(m_pIB->Lock(0, 0, (void**)&k, 0)))
        return E_FAIL;

    // Front face.
    k[0] = 0; k[1] = 1; k[2] = 2;
    k[3] = 0; k[4] = 2; k[5] = 3;

    // Back face.
    k[6] = 4; k[7] = 6; k[8] = 5;
    k[9] = 4; k[10] = 7; k[11] = 6;

    // Left face.
    k[12] = 4; k[13] = 5; k[14] = 1;
    k[15] = 4; k[16] = 1; k[17] = 0;

    // Right face.
    k[18] = 3; k[19] = 2; k[20] = 6;
    k[21] = 3; k[22] = 6; k[23] = 7;

    // Top face.
    k[24] = 1; k[25] = 5; k[26] = 6;
    k[27] = 1; k[28] = 6; k[29] = 2;

    // Bottom face.
    k[30] = 4; k[31] = 0; k[32] = 3;
    k[33] = 4; k[34] = 3; k[35] = 7;

    if (FAILED(m_pIB->Unlock()))
        return E_FAIL;


    return S_OK;
}


HRESULT cube::Draw(drawsettings& ds)
{

    HRESULT hr;

    hr = m_d3dDevice->SetRenderState(D3DRS_LIGHTING, ds.lightOn);
    hr = m_d3dDevice->SetRenderState(D3DRS_CULLMODE, ds.cullMode);
    hr = m_d3dDevice->SetRenderState(D3DRS_FILLMODE, ds.fillMode);

    hr = m_d3dDevice->SetTexture(0, NULL);


    hr = m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    hr = m_d3dDevice->SetIndices(m_pIB);
    hr = m_d3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    hr = m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

    return S_OK;
}




HRESULT cube::UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle)
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


HRESULT cube::Reset()
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