#include "animator.h"

#include <lib/json.hpp>

void Animator::add_animation(String path)
{
	m_ad.push_back(AnimData());
	auto& ad = m_ad.back();

	ad.name = Path(path + ".json").filename().stem().string();

	//log_info("Loaded anim: %s\n", ad.name);

	std::ifstream ifs(path + ".json");
	auto data = nlohmann::json::parse(ifs);
	ad.animTex = new Texture(path + ".png");

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

void Animator::play_anim(String name, std::function<void()> on_finish_anim)
{
	if (m_animInProgress)
		return;

	m_finish_anim_cb = on_finish_anim;

	for (auto& anim : m_ad)
	{
		if (anim.name == name)
		{
			m_currentAnim = &anim;
			m_animInProgress = true;
			break;
		}
	}
}

void Animator::update()
{
	if (m_animInProgress)
	{
		timer++;

		if (timer % 4 == 0)
		{
			m_currentAnim->currentFrame++;
		}

		if (m_currentAnim->currentFrame >= m_currentAnim->Frames.size())
		{
			m_currentAnim->currentFrame = 0;
			m_animInProgress = false;
			m_finish_anim_cb();
		}
	}
}

void Animator::render(Renderer* ren)
{
	if (m_animInProgress)
	{
		ren->draw_subtex(m_currentAnim->Frames[m_currentAnim->currentFrame], entity->position, 1.0f, 1.0f, flip);
		ren->draw_box(entity->position, m_currentAnim->Frames[m_currentAnim->currentFrame]->texSize, Vec3(1, 1, 1));
	}
}
