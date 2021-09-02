#include "framework.h"
#include "a3dev.h"


using namespace std;

chara::chara()
{

}

chara::chara(LPCTSTR path)
	:m_lpszPath(path)
{

}


HRESULT chara::Create(LPDIRECT3DDEVICE9 d3dDevice)
{
	HRESULT hr = S_OK;

	TCHAR name[MAX_PATH];
	mesh* m;

	wsprintf(name, _T("%s\\head.csv"), m_lpszPath);
	m = new mesh(m_lpszPath, name);
	m->Create(d3dDevice);
	m_vecMesh.push_back(m);

	wsprintf(name, _T("%s\\chest.csv"), m_lpszPath);
	m = new mesh(m_lpszPath, name);
	m->Create(d3dDevice);
	m_vecMesh.push_back(m);

	wsprintf(name, _T("%s\\butt.csv"), m_lpszPath);
	m = new mesh(m_lpszPath, name);
	m->Create(d3dDevice);
	m_vecMesh.push_back(m);

	wsprintf(name, _T("%s\\arm.csv"), m_lpszPath);
	m = new mesh(m_lpszPath, name);
	m->Create(d3dDevice);
	m_vecMesh.push_back(m);

	wsprintf(name, _T("%s\\leg.csv"), m_lpszPath);
	m = new mesh(m_lpszPath, name);
	m->Create(d3dDevice);
	m_vecMesh.push_back(m);


	return hr;

}


HRESULT chara::Draw(drawsettings& ds)
{
	HRESULT hr = S_OK;

	for (vector<mesh*>::iterator it = m_vecMesh.begin();
		it != m_vecMesh.end();
		++it)
	{
		(*it)->Draw(ds);
	}
	return hr;

}



HRESULT chara::UpdateView(float eyeX, float eyeY, float eyeZ, float camAngle)
{

	HRESULT hr = S_OK;

	for (vector<mesh*>::iterator it = m_vecMesh.begin();
		it != m_vecMesh.end();
		++it)
	{
		(*it)->UpdateView(eyeX, eyeY, eyeZ, camAngle);
	}

	return hr;
}

HRESULT chara::Reset()
{
	HRESULT hr = S_OK;


	return hr;
}
