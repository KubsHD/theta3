#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <fstream>
#include <functional>


struct AnimData {
	String name;
	Vector<Subtexture*> Frames;
	int currentFrame;
	Texture* animTex;
};

class Animator : public Component {
private:
	Vector<AnimData> m_ad;
	int timer = 0;
	AnimData* m_currentAnim;
	bool m_animInProgress = false;
	std::function<void()> m_finish_anim_cb;
public:
	void add_animation(String path);
	void play_anim(String name, std::function<void()> on_finish_anim);
	void update() override;
	void render(Renderer* ren) override;
};