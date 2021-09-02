#pragma once



class mesh : public draw
{
public:
	mesh();
	mesh(LPCTSTR path,LPCTSTR fullname);
	virtual HRESULT Create(LPDIRECT3DDEVICE9 d3dDevice);
	virtual HRESULT UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle);
	virtual HRESULT Draw(drawsettings& ds);
	HRESULT Reset();

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	IDirect3DIndexBuffer9* m_pIB;

	LPDIRECT3DDEVICE9 m_d3dDevice;


	int vertexCount;
	int triangleCount;


	LPDIRECT3DTEXTURE9 m_tex;
	LPDIRECT3DTEXTURE9 m_tex1;
	LPDIRECT3DTEXTURE9 m_tex2;


	IDirect3DVertexShader9* m_vsh;
	IDirect3DPixelShader9* m_psh;

	LPCTSTR m_lpszPath;
	LPCTSTR m_lpszFileName;



	bool m_preVS;

	int getMeshInfo(char* path, int& triangleCount, int& vertexCount);
		
	void initIB(char* path, VOID* p, int triangleCount);

	void initVerticespost(char* path, VOID* p, int vectexCount);

	void initVertices(char* path, VOID* p, int vectexCount);


	void getFileName(TCHAR *szFileName, int size);

	std::vector< LPDIRECT3DTEXTURE9> m_vecTex;
};