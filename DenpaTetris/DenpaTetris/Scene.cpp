#include"Scene.h"

Scene::~Scene()
{
	while (!m_keyValue.empty())
	{
		//�o�b�t�@�[�̃f�[�^�����ׂĔj��
		m_keyValue.pop();
	}
}