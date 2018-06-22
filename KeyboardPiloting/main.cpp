#include <Windows.h>
#include <stdio.h>

#define EXPORT extern "C" __declspec(dllexport)

float throttle = 1000.;
float yaw = 1500.;
float pitch = 1500;
float roll = 1500;

bool finish = false;

/// <summary>
/// Exported funciton to receive the throttle value
/// </summary>
/// <returns>throttle</returns>
EXPORT float GetThrottle() {
	return throttle;
}

/// <summary>
/// Exported funciton to receive the yaw value
/// </summary>
/// <returns>yaw</returns>
EXPORT float GetYaw() {
	return yaw;
}

/// <summary>
/// Exported funciton to receive the pitch value
/// </summary>
/// <returns>pitch</returns>
EXPORT float GetPitch() {
	return pitch;
}

/// <summary>
/// Exported funciton to receive the roll value
/// </summary>
/// <returns>roll</returns>
EXPORT float GetRoll() {
	return roll;
}

/// <summary>
/// Exported funciton stop the program externally
/// </summary>
EXPORT void Stop() {
	finish = true;
}

/// <summary>
/// Initializes the program to catch the pressed keys
/// </summary>
/// <param name="sensitivity">throttle shift based on cps </param>
/// <param name="minthrottle">minimun allowed throttle</param>
/// <param name="maxthrottle">maximum allowed throttle</param>
/// <returns>0 when finish</returns>
EXPORT int Initialize(float sensitivity,float minthrottle, float maxthrottle) {
	float res[4];
	res[0] = 1000;
	res[1] = res[2] = res[3] = 1500;
	finish = false;
	float factor = sensitivity;

	while (!finish) {

		// throttle
		if (GetKeyState('W') & 0x8000)
		{
			if (res[0] + factor > maxthrottle) {
				res[0] = maxthrottle;
			}
			else {
				res[0] += factor;
			}
		}

		if (GetKeyState('S') & 0x8000)
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