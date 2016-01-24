
#include "Secret.h"

void keyboardCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Keys[GLFW_KEY_W])
	{
		HasChange = true;
		Mob->MobLocation.X -= (float)(sin(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
		Mob->MobLocation.Z += (float)(cos(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
	}
if (Keys[GLFW_KEY_S])
{
	HasChange = true;
	Mob->MobLocation.X += (float)(sin(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
	Mob->MobLocation.Z -= (float)(cos(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
}
if (Keys[GLFW_KEY_A])
{
	HasChange = true;
	Mob->MobLocation.X += (float)(cos(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
	Mob->MobLocation.Z += (float)(sin(Mob->MobLocation.YRot) * Mob->Speed * FromLastTime);
}
if (Keys[GLFW_KEY_D])
{
	HasChange = true;
	Mob->MobLocation.X -= (float)(cos((Mob->MobLocation.YRot)) * Mob->Speed * FromLastTime);
	Mob->MobLocation.Z -= (float)(sin((Mob->MobLocation.YRot)) * Mob->Speed * FromLastTime);
}
}