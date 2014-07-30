//
// File:	Clock.h
// Desc:	Header of Clock
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_CLOCK_H__
#define __MK2014_CLASS_CLOCK_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

class CClock
{
	// Member Functions
public:
	CClock();
	~CClock();

	float GetGameTimeDeltaTick()const;  // in seconds
	float GetDeltaTimeTick()const; // in seconds

	void Initialise(); // Call before message loop.
	void Unpause(); // Call when unpaused.
	void Pause();  // Call when paused.
	void Tick();  // Call every frame.

protected:

private:
	CClock(const CClock& _kr);
	CClock& operator= (const CClock& _kr);

	// Member Variables
public:

protected:

private:
	double m_fSecondsPerCount;
	double m_fDeltaTime;

	__int64 m_iBaseTime;
	__int64 m_iPausedTime;
	__int64 m_iStopTime;
	__int64 m_iPreviousTime;
	__int64 m_iCurrentTime;

	bool m_isStopped;
};

#endif // __MK2014_CLASS_CLOCK_H__