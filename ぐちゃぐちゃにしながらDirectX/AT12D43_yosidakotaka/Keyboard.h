#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

void KayboadUpdate();

bool IsKeyPress(int nVirtKey);
bool IsKeyTrigger(int nVirtKey);
bool IsKeyRelease(int nVirtKey);

#endif // !_KEYBOARD_H_

