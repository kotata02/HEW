#include"Keyboard.h"
#include<Windows.h>

BYTE g_keyTable[256];
BYTE g_oldKeyTable[256];

void KayboadUpdate()
{
	memcpy(g_oldKeyTable, g_keyTable, sizeof(g_oldKeyTable));
	GetKeyboardState(g_keyTable);
}
bool IsKeyPress(int nVirtKey) 
{
	return g_keyTable[nVirtKey] & 0x80;
}
bool IsKeyTrigger(int nVirtKey)
{
	return (g_keyTable[nVirtKey] ^ g_oldKeyTable[nVirtKey])&g_keyTable[nVirtKey] & 0x80;
}
bool IsKeyRelease(int nVirtKey)
{
	return (g_keyTable[nVirtKey] ^ g_oldKeyTable[nVirtKey])&g_oldKeyTable[nVirtKey] & 0x80;
}