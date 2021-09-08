#pragma once



class triangle : public draw
{
public:
	triangle();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice);
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ, float camAngleX, float camAngleY, float camAngleZ);
	virtual HRESULT Draw(drawsettings& ds);
	HRESULT Reset();
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	IDirect3DIndexBuffer9* m_pIB;

	LPDIRECT3DDEVICE9 m_d3dDevice;
};