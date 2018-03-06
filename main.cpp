#define		NAME			"3D Viewer"  //�^�C�g���o�[�ɕ\������e�L�X�g
#define		ID_TIMER		234271
#define		WINDOW_WIDTH	900
#define		WINDOW_HEIGHT	600

#include    <windows.h>
#include	<cmath>
#include	"game_engine.h"

RECT recDisplay;

LRESULT  CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);
int      WINAPI     WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
void				drawWindow(HWND,HDC);

LRESULT  CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static int frame = 0;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
		case WM_CREATE	:	SetTimer(hWnd, ID_TIMER, 1, NULL);	break;			//�N��������
		case WM_DESTROY	:	PostQuitMessage(0);					break;			//�I������
		case WM_PAINT	:														//�`�揈��
							hdc = BeginPaint(hWnd, &ps);
							drawWindow(hWnd,hdc);
							EndPaint(hWnd, &ps);
							break;												

		case WM_TIMER	:	
							if(frame++==30) frame = 0;
							InvalidateRect(hWnd, NULL, true);
							UpdateWindow(hWnd);
							break;
		case WM_SIZE	:														//�E�B���h�E�T�C�Y�ύX������
							if (!GetWindowRect(hWnd, &recDisplay)) break;
							hdc = BeginPaint(hWnd, &ps);
							drawWindow(hWnd,hdc);
							EndPaint(hWnd, &ps);
							break;

		default			:	return DefWindowProc(hWnd, msg, wParam, lParam);	//�f�t�H����
	}
	return 0L;
}

int  WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG  msg;

	WNDCLASS wc = { CS_CLASSDC,
					WndProc,								//�C�x���gcallback�֐�
					0,
					0,
					hInstance,
					NULL,                                   //�A�C�R��
					LoadCursor(NULL, IDC_ARROW),			//�}�E�X�J�[�\��
					(HBRUSH)GetStockObject(WHITE_BRUSH),	//�w�i�F
					NULL,                                   //���j���[
					NAME };                                 //�N���X��

	if (RegisterClass(&wc) == 0) return FALSE;

	hWnd = CreateWindow(	NAME,							//�^�C�g���o�[�e�L�X�g
							NAME,							//�N���X��
							WS_OVERLAPPEDWINDOW,			//�E�C���h�E�X�^�C��
							CW_USEDEFAULT,					//�E�C���h�E����x���W
							CW_USEDEFAULT,					//�E�C���h�E����y���W
							WINDOW_WIDTH,					//�E�C���h�E��
							WINDOW_HEIGHT,					//�E�C���h�E����
							NULL,							//�e�E�C���h�E�̃n���h��
							NULL,
							hInstance,
							NULL				);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);     //Window ��\��
	UpdateWindow(hWnd);             //�\����������
	SetFocus(hWnd);                 //�t�H�[�J�X��ݒ�

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void drawWindow(HWND hWnd, HDC hdc) {

	static int angle = 0;
	int R = 150;
	int r = 100;

	int center_x = (recDisplay.right - recDisplay.left) / 2;
	int center_y = (recDisplay.bottom - recDisplay.top) / 2;

	int point_x = center_x + cos(angle * 3.14 / 180.0)*R;
	int point_y = center_y + +sin(angle * 3.14 / 180.0)*R;

	for (int i = 0; i < 720; i++) {
		SetPixel(hdc, point_x+ cos(i * 3.14 / 360.0)*r, point_y+sin(i * 3.14 / 360.0)*r, 0xFF);
	}

	for (int i = -50; i < 50; i++){
		SetPixel(hdc, center_x+i, center_y	, 0xFF);
		SetPixel(hdc, center_x	, center_y+i, 0xFF);
	}

	angle += 2;
	if (angle == 360) angle = 0;
}