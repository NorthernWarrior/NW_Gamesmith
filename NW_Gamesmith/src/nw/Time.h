#pragma once

#include <nw/CommonMacros.h>

namespace nw {

	class Gamesmith;

class NW_API Time
{
	friend class Gamesmith;

public:
	// Returns the current delta time
	inline static float GetDeltaTime() { return m_DeltaTime * m_TimeScale; }	
	
    // Returns the delta time irrespectively from the time scale
	inline static float GetDeltaTimeIrrespectively() { return m_DeltaTime; }
	inline static float GetTimeScale() { return m_TimeScale; }
	inline static void SetTimeScale(float timeScale) { m_TimeScale = timeScale; }

private:
	static float m_DeltaTime;
	static float m_TimeScale;
};

}