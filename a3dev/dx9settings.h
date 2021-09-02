#pragma once

#define CASE_NULL		0
#define CASE_TRIANGLE	1
#define CASE_RECTANGLE	2


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

};
void DrawSettings(dx9settings& settings);