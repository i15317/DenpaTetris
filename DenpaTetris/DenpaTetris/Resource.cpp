#include"Resource.h"



//�O���[�o���ϐ��̎��ԍ쐬
TetrisRender g_tetrisRender;
std::queue<WPARAM>keyBuf;
HWND hMainWnd;
WNDPROC dxWndProc;


//���상�b�Z�[�W�v���V�[�W���[
LRESULT CALLBACK messageProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		//�L���[�ɃL�[�C�x���g�̃L�[���i�[����
		keyBuf.push(wparam);
		break;

	//Dxlib�̓E�B���h�E�N���[�Y�̃C�x���g�����܂����Ə������Ă���Ȃ��̂ł�����ŉ��Ƃ�����
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	}

}

