#pragma once

#define CASE_NULL		0
#define CASE_TRIANGLE	1
#define CASE_RECTANGLE	2
#define CASE_CUBE		3
#define CASE_MESH		4
#define CASE_A3CHARA		5



struct dx9settings
{
	bool show_demo_window ;
	ImVec4 clear_color;


	int drawcase;
	draw* pdraw;


	LPDIRECT3DDEVICE9 d3dDevcie;

	// view
	float eyeX;
	float eyeY;
	float eyeZ;
	float camAngle;


	drawsettings drawSet;

	char szMeshPath[MAX_PATH];


	// a3 related
	char szA3CharPath[MAX_PATH];




};
void DrawSettings(dx9settings& settings);