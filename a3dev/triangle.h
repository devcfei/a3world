#pragma once



class triangle : public draw
{
public:
	triangle();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice);
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle);
	virtual HRESULT Draw(drawsettings& ds);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	IDirect3DIndexBuffer9* m_pIB;

	LPDIRECT3DDEVICE9 m_d3dDevice;
};