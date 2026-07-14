#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define CINTERFACE
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>

LPDIRECT3D9				g_pD3D 		= NULL;
LPDIRECT3DDEVICE9		g_pDevice 	= NULL;
LPDIRECT3DVERTEXSHADER9	g_pVS		= NULL;
LPDIRECT3DPIXELSHADER9	g_pPS		= NULL;

int main() {
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	LPD3DXBUFFER vsb;
	LPD3DXBUFFER psb;
	LPD3DXBUFFER erb;
	D3DPRESENT_PARAMETERS d3dpp;
	float fullscreentriangle[8];

	fullscreentriangle[0] = -0.99f; 
	fullscreentriangle[1] =  0.99f;

	fullscreentriangle[2] =  0.99f; 
	fullscreentriangle[3] =  0.99f;

	fullscreentriangle[6] =	 0.99f; 
	fullscreentriangle[7] =	-0.99f;

	fullscreentriangle[4] =	-0.99f; 
	fullscreentriangle[5] =	-0.99f;

	hwnd = CreateWindowA
	(
		"edit", "title",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL, NULL, NULL, NULL
	);

	vsb = NULL;
	psb = NULL;
	erb = NULL;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed		= TRUE;
	d3dpp.SwapEffect	= D3DSWAPEFFECT_DISCARD;

	if(FAILED(
		g_pD3D->lpVtbl->CreateDevice
		(
			g_pD3D,
			0,
			D3DDEVTYPE_HAL,
			hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pDevice
		)
	)) return 0;

	hr = D3DXCompileShaderFromFile
	(
		"SHADERS.HLSL",
		NULL, NULL, 
		"vs_main", "vs_3_0",
		0, &vsb, &erb, NULL 
	);

	hr = D3DXCompileShaderFromFile
	(
		"SHADERS.HLSL",
		NULL, NULL,
		"ps_main", "ps_3_0",
		0, &psb, &erb, NULL
	);

	if (FAILED(hr)) {
		if (erb) {
			const char* errorMsg = (const char*)erb->lpVtbl->GetBufferPointer(erb);
			MessageBoxA(hwnd, errorMsg, "Vertex Shader Error", MB_OK | MB_ICONERROR);
			erb->lpVtbl->Release(erb);
		} else {
			MessageBoxA(hwnd, "Ð¤Ð°Ð¹Ð» SHADERS.HLSL Ð½Ðµ Ð½Ð°Ð¹Ð´ÐµÐ½!", "Error", MB_OK | MB_ICONERROR);
		}
		return 0;
	}

	g_pDevice->lpVtbl->CreateVertexShader
	(
		g_pDevice, 
		(DWORD*)vsb->lpVtbl->GetBufferPointer(vsb),
		&g_pVS
	);

	g_pDevice->lpVtbl->CreatePixelShader
	(
		g_pDevice,
		(DWORD*)psb->lpVtbl->GetBufferPointer(psb),
		&g_pPS
	);

	vsb->lpVtbl->Release(vsb);
	psb->lpVtbl->Release(psb);

	while(IsWindow(hwnd)) {
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if( msg.message == WM_KEYDOWN &&
				msg.wParam == VK_ESCAPE
			  ) DestroyWindow(hwnd);
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}

		g_pDevice->lpVtbl->Clear
		(
			g_pDevice, 
			0, NULL, 
			D3DCLEAR_TARGET, 
			D3DCOLOR_XRGB(0, 40, 100),
			1.0f, 0
		);

		g_pDevice->lpVtbl->BeginScene(g_pDevice);
		g_pDevice->lpVtbl->SetVertexShader(g_pDevice, g_pVS);
		g_pDevice->lpVtbl->SetPixelShader(g_pDevice, g_pPS);
		g_pDevice->lpVtbl->SetFVF(g_pDevice, D3DFVF_XYZ);

		g_pDevice->lpVtbl->DrawPrimitiveUP
		(
			g_pDevice,
			D3DPT_TRIANGLESTRIP,
			2, fullscreentriangle, 
			sizeof(float)*2
		);

		g_pDevice->lpVtbl->EndScene(g_pDevice);
		g_pDevice->lpVtbl->Present
		(
			g_pDevice,
			NULL, NULL, NULL, NULL
		);

		Sleep(16);
	}

	if(g_pVS) g_pVS->lpVtbl->Release(g_pVS);
	if(g_pPS) g_pPS->lpVtbl->Release(g_pPS);
	g_pDevice->lpVtbl->Release(g_pDevice);
	g_pD3D->lpVtbl->Release(g_pD3D);

	return 0;
}
