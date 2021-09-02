#pragma once



class chara : public draw
{
public:
	chara();
	chara(LPCTSTR path);
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice);
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle);
	virtual HRESULT Draw(drawsettings& ds);
	HRESULT Reset();

private:

	std::vector<mesh*> m_vecMesh;

	LPCTSTR m_lpszPath;
};