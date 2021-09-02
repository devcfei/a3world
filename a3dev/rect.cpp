#include "framework.h"
#include "a3dev.h"


struct ColorVertex
{
    ColorVertex() {}

    ColorVertex(float x, float y, float z, float u, float v)
    {
        _x = x;	 _y = y;  _z = z; _u = u; _v = v;
    }

    float _x, _y, _z, _u, _v;

    static const DWORD FVF;
};
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;




rect::rect()
{

}





HRESULT rect::Create(LPDIRECT3DDEVICE9 d3dDevice)
{
    HRESULT hr;
  
    m_d3dDevice = d3dDevice;


    m_d3dDevice->CreateVertexBuffer(4 * sizeof(ColorVertex), D3DUSAGE_WRITEONLY,
        ColorVertex::FVF, D3DPOOL_DEFAULT, &m_pVB, 0);

    ColorVertex* vertexs;
    m_pVB->Lock(0, 0, (void**)&vertexs, 0);

    vertexs[0] = ColorVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    vertexs[1] = ColorVertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    vertexs[2] = ColorVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f);
    vertexs[3] = ColorVertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f);

    m_pVB->Unlock();



    hr = D3DXCreateTextureFromFile(m_d3dDevice, TEXT("..\\data\\cube.jpg"), &m_tex);


    return S_OK;
}


HRESULT rect::Draw(drawsettings& ds)
{

    HRESULT hr;

    m_d3dDevice->SetRenderState(D3DRS_LIGHTING, ds.lightOn);
    m_d3dDevice->SetRenderState(D3DRS_CULLMODE, ds.cullMode);
    m_d3dDevice->SetRenderState(D3DRS_FILLMODE, ds.fillMode);



    hr = m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(ColorVertex));
    hr = m_d3dDevice->SetFVF(ColorVertex::FVF);
    hr = m_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


    //hr = m_d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

    hr = m_d3dDevice->SetTexture(0, m_tex);


    return S_OK;
}




HRESULT rect::UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle)
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