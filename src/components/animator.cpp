#include "animator.h"

#include <lib/json.hpp>
#include <core/asset.h>
#include <iostream>
#include <render/renderer.h>
#include <core/file/atl.h>

Vec2 Animator::get_frame_size()
{
	if (this->m_currentLoopingAnim != nullptr)
	{
		return m_currentLoopingAnim->atl->Frames[m_currentLoopingAnim->currentFrame]->texSize;
	}
	else if (this->m_currentAnim != nullptr)
	{
		return m_currentAnim->atl->Frames[m_currentAnim->currentFrame]->texSize;
	}

	return Vec2(0, 0);
}

void Animator::add_animation(String path)
{
	AnimData dat;
	dat.atl = Asset::load_atlas(path);
	m_ad.push_back(dat);
}

void Animator::play_one_shot(String name, std::function<void()> on_finish_anim, float speed_mul)
{
	m_finish_anim_cb = on_finish_anim;

	for (auto& anim : m_ad)
	{
		if (anim.atl->name == name)
		{
			m_currentAnim = &anim;
			m_currentAnim->speed_override = speed_mul;
			m_animInProgress = false;
			m_oneShotInProgress = true;
			break;
		}
	}
}

void Animator::play_anim(String name, float speed_mul)
{
	for (auto& anim : m_ad)
	{
		if (anim.atl->name == name)
		{
			m_currentLoopingAnim = &anim;
			m_currentLoopingAnim->speed_override = speed_mul;
			m_animInProgress = true;
			break;
		}
	}
}


void Animator::play_anim_scaled(String name, float speed_mul, float scale)
{
	for (auto& anim : m_ad)
	{
		if (anim.atl->name == name)
		{
			anim_scale = scale;
			m_currentLoopingAnim = &anim;
			m_currentLoopingAnim->speed_override = speed_mul;
			m_animInProgress = true;
			break;
		}
	}
}


void Animator::update()
{
	if (m_oneShotInProgress)
	{
		timer++;

		if (timer % int(4 * m_currentAnim->speed_override) == 0)
		{
			m_currentAnim->currentFrame++;
		}

		if (m_currentAnim->currentFrame >= m_currentAnim->atl->Frames.size())
		{
			m_currentAnim->currentFrame = 0;
			m_oneShotInProgress = false;
			if (m_currentLoopingAnim != nullptr)
				m_animInProgress = true;
			m_finish_anim_cb();
		}
	}

	if (m_animInProgress && !m_oneShotInProgress)
	{
		timer++;

		if (timer % int(4 * m_currentLoopingAnim->speed_override) == 0)
		{
			m_currentLoopingAnim->currentFrame++;
		}

		if (m_currentLoopingAnim->currentFrame >= m_currentLoopingAnim->atl->Frames.size())
		{
			m_currentLoopingAnim->currentFrame = 0;
		}
	}
}

void Animator::render(Renderer* ren)
{

	if (m_oneShotInProgress)
	{
		if (shader != nullptr)
			ren->draw_subtex_s(m_currentAnim->atl->Frames[m_currentAnim->currentFrame], entity->position, shader, 1.0f, anim_scale, flip);
		else
			ren->draw_subtex(m_currentAnim->atl->Frames[m_currentAnim->currentFrame], entity->position, 1.0f, anim_scale, flip);
		//ren->draw_box(entity->position, m_currentAnim->Frames[m_currentAnim->currentFrame]->texSize, Vec3(1, 1, 1));
	}

	if (m_animInProgress && !m_oneShotInProgress)
	{
		if (shader != nullptr)
			ren->draw_subtex_s(m_currentLoopingAnim->atl->Frames[m_currentLoopingAnim->currentFrame], entity->position, shader, 1.0f, anim_scale, flip);
		else
			ren->draw_subtex(m_currentLoopingAnim->atl->Frames[m_currentLoopingAnim->currentFrame], entity->position, 1.0f, anim_scale, flip);
		//ren->draw_box(entity->position, m_currentLoopingAnim->Frames[m_currentLoopingAnim->currentFrame]->texSize, Vec3(1, 1, 1));
	}
}
