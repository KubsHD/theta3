/*****************************************************************//**
 * \file   animator.h
 * \brief  component responsible for playing animations
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <fstream>
#include <functional>


#include <core/file/atl.h>

/// <summary>
/// This struct holds data about animation
/// </summary>
struct AnimData {

	/// <summary>
	/// Reference to the atlas
	/// </summary>
	Atlas* atl;

	/// <summary>
	/// Speed of the animation
	/// </summary>
	float speed_override = 1.0f;

	/// <summary>
	/// Current frame of the animation
	/// </summary>
	int currentFrame = 0;
};

/// <summary>
/// this class manage animations
/// </summary>
class Animator : public Component {
private:

	/// <summary>
	/// Vector of animations attached to this component
	/// </summary>
	Vector<AnimData> m_ad;

	/// <summary>
	/// Timer used to calculate current frame
	/// </summary>
	int timer = 0;

	/// <summary>
	/// Scale of the animation
	/// </summary>
	float anim_scale = 1.0f;

	/// <summary>
	/// Current animation
	/// </summary>
	AnimData* m_currentAnim;

	/// <summary>
	/// Is animation in progress
	/// </summary>
	bool m_animInProgress = false;

	/// <summary>
	/// Is one shot animation in progress
	/// </summary>
	bool m_oneShotInProgress = false;

	/// <summary>
	/// Callback called when one shot animation is finished
	/// </summary>
	std::function<void()> m_finish_anim_cb;

	/// <summary>
	/// Current looping animation
	/// </summary>
	AnimData* m_currentLoopingAnim;

public:
	/// <summary>
	/// Is the animation flipped
	/// </summary>
	bool flip = false;

	/// <summary>
	/// Get the size of the current frame
	/// </summary>
	/// <returns>Size in vec2</returns>
	Vec2 get_frame_size();

	/// <summary>
	/// Add animation to the component
	/// </summary>
	/// <param name="path">path to the atl file with the animation</param>
	void add_animation(String path);

	/// <summary>
	/// Play one shot animation
	/// </summary>
	/// <param name="name">Animation name</param>
	/// <param name="on_finish_anim">Callback called when animation is finished</param>
	/// <param name="speed_mul">animation speed</param>
	void play_one_shot(String name, std::function<void()> on_finish_anim, float speed_mul = 1.0f);

	/// <summary>
	/// Play looping animation
	/// </summary>
	/// <param name="name">Animation name</param>
	/// <param name="speed_mul">Speed multiplier</param>
	void play_anim(String name, float speed_mul = 1.0f);

	/// <summary>
	/// Play looping animation with scale
	/// </summary>
	/// <param name="name">Animation name</param>
	/// <param name="speed_mul">Speed multiplier</param>
	/// <param name="scale">Animation scaled</param>
	void play_anim_scaled(String name, float speed_mul, float scale);
	
	void update() override;
	void render(Renderer* ren) override;
};