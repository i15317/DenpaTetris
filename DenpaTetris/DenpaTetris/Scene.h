#pragma once
#include<queue>
#include<Windows.h>

class Scene
{
public:
	Scene() {};
	virtual ~Scene();
	virtual void Update() = 0;
	virtual void Render() = 0;
	void RegistKeyValue(WPARAM wparam) { m_keyValue.push(wparam); }
protected:
	std::queue<WPARAM> m_keyValue;
};