#include "animator.h"

#include <lib/json.hpp>
#include <core/asset.h>

void Animator::add_animation(String path)
{
	m_ad.push_back(AnimData());
	auto& ad = m_ad.back();

	ad.name = Path(std::string(Asset::get_asset_path(path.c_str())) + ".json").filename().stem().string();

	//log_info("Loaded anim: %s\n", ad.name);

	std::ifstream ifs(std::string(Asset::get_asset_path(path.c_str())) + ".json");
	auto data = nlohmann::json::parse(ifs);
	ad.animTex = Asset::load_texture(path + ".png");

	for (auto frame : data["frames"])
	{
		ad.Frames.push_back(new Subtexture
			{ ad.animTex,
				{ frame["frame"]["x"], frame["frame"]["y"] },
				{ frame["frame"]["w"], frame["frame"]["h"] },
			}
		);
	}
}

void Animator::play_one_shot(String name, std::function<void()> on_finish_anim, float speed_mul)
{
	m_finish_anim_cb = on_finish_anim;

	for (auto& anim : m_ad)
	{
		if (anim.name == name)
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
		if (anim.name == name)
		{
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

		if (m_currentAnim->currentFrame >= m_currentAnim->Frames.size())
		{
			m_currentAnim->currentFrame = 0;
			m_oneShotInProgress = false;
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

		if (m_currentLoopingAnim->currentFrame >= m_currentLoopingAnim->Frames.size())
		{
			m_currentLoopingAnim->currentFrame = 0;
		}
	}
}

void Animator::render(Renderer* ren)
{

	if (m_oneShotInProgress)
	{
		ren->draw_subtex(m_currentAnim->Frames[m_currentAnim->currentFrame], entity->position, 1.0f, 1.0f, flip);
		//ren->draw_box(entity->position, m_currentAnim->Frames[m_currentAnim->currentFrame]->texSize, Vec3(1, 1, 1));
	}

	if (m_animInProgress && !m_oneShotInProgress)
	{
		ren->draw_subtex(m_currentLoopingAnim->Frames[m_currentLoopingAnim->currentFrame], entity->position, 1.0f, 1.0f, flip);
		//ren->draw_box(entity->position, m_currentLoopingAnim->Frames[m_currentLoopingAnim->currentFrame]->texSize, Vec3(1, 1, 1));
	}
}
