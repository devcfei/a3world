#pragma once


struct drawsettings
{
	bool lightOn;

	D3DCULL cullMode;

	D3DFILLMODE fillMode;
};
class draw
{
public:
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice) = 0;
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ,  float camAngleX, float camAngleY, float camAngleZ) = 0;
	virtual HRESULT Draw(drawsettings& ds) = 0;
	virtual HRESULT Reset() = 0;
};