#include "framework.h"
#include "a3dev.h"

struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

static CUSTOMVERTEX m_vertices[3];

triangle::triangle()
{
    CUSTOMVERTEX vertices[] =
    {
        { -1.0f,-1.0f, 0.0f, 0xffff0000, },
        {  1.0f,-1.0f, 0.0f, 0xff0000ff, },
        {  0.0f, 1.0f, 0.0f, 0xff00ff00, },

    };

    CopyMemory(m_vertices, vertices, sizeof(vertices));
}


HRESULT triangle::Create(LPDIRECT3DDEVICE9 d3dDevice)
{
    m_d3dDevice = d3dDevice;

    if (FAILED(d3dDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
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


    return S_OK;
}


HRESULT triangle::Draw(drawsettings& ds)
{

    m_d3dDevice->SetRenderState(D3DRS_LIGHTING, ds.lightOn);
    m_d3dDevice->SetRenderState(D3DRS_CULLMODE, ds.cullMode);
    m_d3dDevice->SetRenderState(D3DRS_FILLMODE, ds.fillMode);


    m_d3dDevice->SetTexture(0,NULL);
    m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    m_d3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    m_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);


    return S_OK;
}




HRESULT triangle::UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle)
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

HRESULT triangle::Reset()
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