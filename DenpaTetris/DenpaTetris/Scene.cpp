#include"Scene.h"

Scene::~Scene()
{
	while (!m_keyValue.empty())
	{
		//バッファーのデータをすべて破棄
		m_keyValue.pop();
	}
}