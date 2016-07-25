#ifndef KEYBOARD_H
#define KEYBOARD_H


class KeyboardInstruction
{
public:
	int keys[3]; // up to 3 keys can be held down (ctrl +alt + del)
};

class InstructionSet
{
public:

	KeyboardInstruction mapping[256]; // up to 32 different keys
};


class KeyboardHandler
{
public:

	//InstructionSet instructions;
	unsigned char keycode[256];
};


class Keys
{
private:

	int UP_CODE;
	int DOWN_CODE;
	int LEFT_CODE;
	int RIGHT_CODE;
	int JUMP_CODE;
	int ACTION_CODE;
	int FIRE_CODE;

public:

	void RedefineUP(int keycode)
	{
		UP_CODE = keycode;
	}
	void RedefineDOWN(int keycode)
	{
		DOWN_CODE = keycode;
	}
	void RedefineLEFT(int keycode)
	{
		LEFT_CODE = keycode;
	}
	void RedefineRIGHT(int keycode)
	{
		RIGHT_CODE = keycode;
	}
	void RedefineJUMP(int keycode)
	{
		JUMP_CODE = keycode;
	}
	void RedefineFIRE1(int keycode)
	{
		FIRE_CODE = keycode;
	}
	void RedefineACTION(int keycode)
	{
		ACTION_CODE = keycode;
	}

	Keys()
	{
		UP_CODE = VK_UP;
		DOWN_CODE = VK_DOWN;
		LEFT_CODE = VK_LEFT;
		RIGHT_CODE = VK_RIGHT;
		JUMP_CODE = VK_SPACE;
		ACTION_CODE = VK_SHIFT;
		FIRE_CODE = VK_CONTROL;
	}

	bool UpKey()
	{
		return keys[UP_CODE];
	}
	bool DownKey()
	{
		return keys[DOWN_CODE];
	}
	bool LeftKey()
	{
		return keys[LEFT_CODE];
	}
	bool RightKey()
	{
		return keys[RIGHT_CODE];
	}
	bool JumpKey()
	{
		return keys[JUMP_CODE];
	}
	bool Fire1Key()
	{
		return keys[FIRE_CODE];
	}
	bool ActionKey()
	{
		return keys[ACTION_CODE];
	}

	bool EscapeKey()
	{
		return keys[VK_ESCAPE];
	}

	bool F1Key()
	{
		return keys[VK_F1];
	}

	float keyDownTimer[256];
	bool keys[256];
};

#endif