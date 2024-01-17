#include "text_popup.h"

namespace Factory {

	void CreateTextPopup(Scene* scn, Vec2 pos, String textToPopup)
	{
		auto ent = scn->create("popup");
		auto c = ent->add(TextPopup());
		ent->position = pos + Vec2(rand() % 10 - 5, 0);
		c->text = textToPopup;
	}
}