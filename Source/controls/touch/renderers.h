#pragma once

#if defined(VIRTUAL_GAMEPAD) && !defined(USE_SDL1)

#include "controls/plrctrls.h"
#include "controls/touch/gamepad.h"
#include "engine/surface.hpp"
#include "utils/png.h"
#include "utils/sdl_ptrs.h"

namespace devilution {

enum VirtualGamepadButtonType {
	GAMEPAD_ATTACK,
	GAMEPAD_ATTACKDOWN,
	GAMEPAD_TALK,
	GAMEPAD_TALKDOWN,
	GAMEPAD_ITEM,
	GAMEPAD_ITEMDOWN,
	GAMEPAD_OBJECT,
	GAMEPAD_OBJECTDOWN,
	GAMEPAD_CASTSPELL,
	GAMEPAD_CASTSPELLDOWN,
	GAMEPAD_BACK,
	GAMEPAD_BACKDOWN,
	GAMEPAD_BLANK,
	GAMEPAD_BLANKDOWN,
};

enum VirtualGamepadPotionType {
	GAMEPAD_HEALING,
	GAMEPAD_MANA,
	GAMEPAD_REJUVENATION,
	GAMEPAD_FULL_HEALING,
	GAMEPAD_FULL_MANA,
	GAMEPAD_FULL_REJUVENATION,
	GAMEPAD_SCROLL_OF_HEALING,
};

typedef std::function<void(Art &art, SDL_Rect *src, SDL_Rect *dst)> RenderFunction;

class VirtualDirectionPadRenderer {
public:
	VirtualDirectionPadRenderer(VirtualDirectionPad *virtualDirectionPad)
	    : virtualDirectionPad(virtualDirectionPad)
	{
	}

	void LoadArt(SDL_Renderer *renderer);
	void Render(RenderFunction renderFunction);
	void UnloadArt();

private:
	VirtualDirectionPad *virtualDirectionPad;
	Art padArt;
	Art knobArt;

	void RenderPad(RenderFunction renderFunction);
	void RenderKnob(RenderFunction renderFunction);
};

class VirtualPadButtonRenderer {
public:
	VirtualPadButtonRenderer(VirtualPadButton *virtualPadButton)
	    : virtualPadButton(virtualPadButton)
	{
	}

	void Render(RenderFunction renderFunction, Art &buttonArt);

protected:
	VirtualPadButton *virtualPadButton;

	virtual VirtualGamepadButtonType GetButtonType() = 0;
};

class PrimaryActionButtonRenderer : public VirtualPadButtonRenderer {
public:
	PrimaryActionButtonRenderer(VirtualPadButton *primaryActionButton)
	    : VirtualPadButtonRenderer(primaryActionButton)
	{
	}

private:
	VirtualGamepadButtonType GetButtonType();
	VirtualGamepadButtonType GetTownButtonType();
	VirtualGamepadButtonType GetDungeonButtonType();
	VirtualGamepadButtonType GetInventoryButtonType();
};

class SecondaryActionButtonRenderer : public VirtualPadButtonRenderer {
public:
	SecondaryActionButtonRenderer(VirtualPadButton *secondaryActionButton)
	    : VirtualPadButtonRenderer(secondaryActionButton)
	{
	}

private:
	VirtualGamepadButtonType GetButtonType();
};

class SpellActionButtonRenderer : public VirtualPadButtonRenderer {
public:
	SpellActionButtonRenderer(VirtualPadButton *spellActionButton)
	    : VirtualPadButtonRenderer(spellActionButton)
	{
	}

private:
	VirtualGamepadButtonType GetButtonType();
};

class CancelButtonRenderer : public VirtualPadButtonRenderer {
public:
	CancelButtonRenderer(VirtualPadButton *cancelButton)
	    : VirtualPadButtonRenderer(cancelButton)
	{
	}

private:
	VirtualGamepadButtonType GetButtonType();
};

class PotionButtonRenderer : public VirtualPadButtonRenderer {
public:
	PotionButtonRenderer(VirtualPadButton *potionButton, belt_item_type potionType)
	    : VirtualPadButtonRenderer(potionButton)
	    , potionType(potionType)
	{
	}

	void RenderPotion(RenderFunction renderFunction, Art &potionArt);

private:
	belt_item_type potionType;

	VirtualGamepadButtonType GetButtonType();
	std::optional<VirtualGamepadPotionType> GetPotionType();
};

class VirtualGamepadRenderer {
public:
	VirtualGamepadRenderer(VirtualGamepad *virtualGamepad)
	    : directionPadRenderer(&virtualGamepad->directionPad)
	    , primaryActionButtonRenderer(&virtualGamepad->primaryActionButton)
	    , secondaryActionButtonRenderer(&virtualGamepad->secondaryActionButton)
	    , spellActionButtonRenderer(&virtualGamepad->spellActionButton)
	    , cancelButtonRenderer(&virtualGamepad->cancelButton)
	    , healthButtonRenderer(&virtualGamepad->healthButton, BLT_HEALING)
	    , manaButtonRenderer(&virtualGamepad->manaButton, BLT_MANA)
	{
	}

	void LoadArt(SDL_Renderer *renderer);
	void Render(RenderFunction renderFunction);
	void UnloadArt();

private:
	VirtualDirectionPadRenderer directionPadRenderer;

	PrimaryActionButtonRenderer primaryActionButtonRenderer;
	SecondaryActionButtonRenderer secondaryActionButtonRenderer;
	SpellActionButtonRenderer spellActionButtonRenderer;
	CancelButtonRenderer cancelButtonRenderer;

	PotionButtonRenderer healthButtonRenderer;
	PotionButtonRenderer manaButtonRenderer;

	Art buttonArt;
	Art potionArt;
};

void InitVirtualGamepadGFX(SDL_Renderer *renderer);
void RenderVirtualGamepad(SDL_Renderer *renderer);
void RenderVirtualGamepad(SDL_Surface *surface);
void FreeVirtualGamepadGFX();

} // namespace devilution

#endif
