#include<DxLib.h>
#include<Windows.h>
#include"Resource.h"
#include"Scene.h"
#include"Tetris.h"
#include"Executor.h"

//�����_�[
extern TetrisRender g_tetrisRender;
//�E�B���h�E�n���h��
extern HWND hMainWnd;
//�L�[���͏����𒙂߂Ă����L���[
extern std::queue<WPARAM>keyBuf;
//�E�B���h�E�v���V�[�W���̃A�h���X
extern WNDPROC dxWndProc;

Executor::Executor()
{
	prev_scene = DEFAULT;
	current_scene = DEFAULT;
	next_scene = TOP;
}

void Executor::init()
{
	//Dxlib�̏����Z�b�g�A�b�v
	{
		SetWindowSize(800, 600);
		ChangeWindowMode(true);
	}

	//Dxlib�̏���������
	{
		//�ŏI����������
		if (DxLib_Init() == -1)		// �c�w���C�u��������������
		{
			std::exit(1);			// �G���[���N�����璼���ɏI��
		}
	}

	//Dxlib�̏�������̏���
	{
		//�o�b�N�o�b�t�@�̐ݒ肩�ȁH
		SetDrawScreen(DX_SCREEN_BACK);
		// �����ǂݍ��ݐݒ�ɕύX
		SetUseASyncLoadFlag(FALSE);

		ClearDrawScreen();
	}

	//�L�[�C�x���g�����̐ݒ�
	{
		//�E�B���h�E�n���h���̎擾
		hMainWnd = GetMainWindowHandle();
		//���C���E�B���h�E�̃E�B���h�E�v���V�[�W���̃A�h���X���擾
		dxWndProc = (WNDPROC)GetWindowLong(hMainWnd, GWLP_WNDPROC);
		//�E�B���h�E�v���V�[�W���̃A�h���X�o�^
		SetWindowLongW(hMainWnd, GWLP_WNDPROC, (LONG)messageProc);
	}

	//�V�[���̍쐬
	{
		m_tetrisScene = new Tetris();
	}

}

void Executor::Run()
{
	while (true)
	{
		//���C���A�b�v�f�[�g
		update();

		render();
	}
}

void Executor::Update()
{
	m_currentScene->Update();
}


void Executor::update()
{

	/*
	���g�̃��C�t�T�C�N���ōs������
	*/

	//�V�[������
	switch (next_scene)
	{
	case DEFAULT:
		break;
	case TOP:
		prev_scene = current_scene;
		current_scene = TOP;
		break;
	case TETRIS:
		prev_scene = current_scene;
		current_scene = TETRIS;
	}

	switch (current_scene)
	{	
	case TOP:
		m_currentScene = m_topScene;
		break;
	case TETRIS:
		m_currentScene = m_tetrisScene;
		break;
	case DEFAULT:
		break;
	}
	
	while (!keyBuf.empty())
	{
		//���݂̃V�[���Ƀo�b�t�@�[�̃L�[�{�[�h�C�x���g�����ׂė���
		m_currentScene->RegistKeyValue(keyBuf.front());
		keyBuf.pop();
	}

	/*
	�z���I�u�W�F�N�g�Ƀ��C�t�T�C�N����J�ڂ���
	*/

	//Executor�z���̃I�u�W�F�N�g��update����
	Update();
}

void Executor::render()
{
	/*
	���g�̃��C�t�T�C�N���ōs������
	*/

	//�N���A����
	ClearDrawScreen();


	/*
	�z���I�u�W�F�N�g�Ƀ��C�t�T�C�N����J�ڂ���
	*/

	//�`�揈��
	Render();
}

void Executor::Render()
{
	m_currentScene->Render();
}