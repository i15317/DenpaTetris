#pragma once
#include<Windows.h>
#include<queue>
#include<iostream>
class Scene;

enum SCENE {
	DEFAULT = 0,
	TOP,
	TETRIS
};

class Executor
{
public:
	Executor();
private:
	void init();
	void Render();
	void Update();
	void Run();

private:
	void render();
	void update();

	Microsoft::WRL::ComPtr<Scene>m_currentScene;

	Microsoft::WRL::ComPtr<Scene>m_tetrisScene;
	Microsoft::WRL::ComPtr<Scene>m_topScene;
	SCENE current_scene;
	SCENE prev_scene;
	SCENE next_scene;



};