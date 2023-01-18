#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <fstream>
#include <functional>


#include <core/file/atl.h>

struct AnimData {
	Atlas* atl;
	float speed_override = 1.0f;
	int currentFrame = 0;
};

class Animator : public Component {
private:
	Vector<AnimData> m_ad;
	int timer = 0;
	float anim_scale = 1.0f;
	AnimData* m_currentAnim;
	bool m_animInProgress = false;
	bool m_oneShotInProgress = false;
	std::function<void()> m_finish_anim_cb;

	AnimData* m_currentLoopingAnim;

public:
	
	// zarówno entity jak i animator maj¹ pole flip, przyda³oby siê imo zunifikowaæ to
	bool flip = false;

	Vec2 get_frame_size();
	void add_animation(String path);
	void play_one_shot(String name, std::function<void()> on_finish_anim, float speed_mul = 1.0f);
	void play_anim(String name, float speed_mul = 1.0f);
	void play_anim_scaled(String name, float speed_mul, float scale);
	void update() override;
	void render(Renderer* ren) override;
};