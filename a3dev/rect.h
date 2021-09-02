#pragma once



class rect : public draw
{
public:
	rect();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice);
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle);
	virtual HRESULT Draw(drawsettings& ds);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	IDirect3DIndexBuffer9* m_pIB;

	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPDIRECT3DTEXTURE9 m_tex;
};