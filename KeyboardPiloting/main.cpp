#include <Windows.h>
#include <stdio.h>

#define EXPORT extern "C" __declspec(dllexport)

float throttle = 1000.;
float yaw = 1500.;
float pitch = 1500;
float roll = 1500;

bool finish = false;

EXPORT float GetThrottle() {
	return throttle;
}

EXPORT float GetYaw() {
	return yaw;
}

EXPORT float GetPitch() {
	return pitch;
}

EXPORT float GetRoll() {
	return roll;
}

EXPORT void Stop() {
	finish = true;
}

EXPORT int Initialize(float sensibility,float minthrottle, float maxthrottle) {
	float res[4];
	res[0] = 1000;
	res[1] = res[2] = res[3] = 1500;
	finish = false;
	float factor = sensibility;

	while (!finish) {

		// throttle
		if (GetKeyState('W') & 0x8000/*check if high-order bit is set (1 << 15)*/)
		{
			if (res[0] + factor > maxthrottle) {
				res[0] = maxthrottle;
			}
			else {
				res[0] += factor;
			}
		}

		if (GetKeyState('S') & 0x8000/*check if high-order bit is set (1 << 15)*/)
		{
			if (res[0] - factor < minthrottle) {
				res[0] = minthrottle;
			}
			else {
				res[0] -= factor;
			}
		}

		// yaw
		if (GetKeyState('D') & 0x8000 || GetKeyState('A') & 0x8000)
		{
			if (GetKeyState('D') & 0x8000) {
				res[1] = 1;
			}
			else {
				res[1] = -1;
			}

		}
		else {
			res[1] = 0;
		}

		// pitch
		if (GetKeyState(VK_UP) & 0x8000 || GetKeyState(VK_DOWN) & 0x8000)
		{
			if (GetKeyState(VK_UP) & 0x8000) {
				res[2] = 1;
			}
			else {
				res[2] = -1;
			}

		}
		else {
			res[2] = 0;
		}

		// roll
		if (GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState(VK_LEFT) & 0x8000)
		{
			if (GetKeyState(VK_RIGHT) & 0x8000) {
				res[3] = 1;
			}
			else {
				res[3] = -1;
			}

		}
		else {
			res[3] = 0;
		}

		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			res[0] = -2;
			Stop();
		}

		throttle = res[0];
		yaw = res[1];
		pitch = res[2];
		roll = res[3];

		printf("%f %f %f %f\n", res[0], res[1], res[2], res[3]);
	}

	return 0;
}