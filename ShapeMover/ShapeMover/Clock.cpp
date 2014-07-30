// 
// File: Clock.cpp
// Desc: Implementation of Clock
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <Windows.h>

// Local Includes

// This Include
#include "Clock.h"

// Static Variables


CClock::CClock()
: m_fSecondsPerCount(0.0)
, m_fDeltaTime(-1.0)
, m_iBaseTime(0)
, m_iPausedTime(0)
, m_iPreviousTime(0)
, m_iCurrentTime(0)
, m_isStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_fSecondsPerCount = 1.0 / (double)countsPerSec;
}

CClock::~CClock()
{
}

// Returns the total time elapsed since Initialise() was called, NOT counting any
// time when the clock is stopped.
float CClock::GetGameTimeDeltaTick()const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	//
	// ----*---------------*------------------------------*------> time
	//  m_iBaseTime       m_iStopTime                      m_iCurrentTime

	if(m_isStopped)
		return (float)((m_iStopTime - m_iBaseTime)*m_fSecondsPerCount);

	// The distance m_iCurrentTime - m_iBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from m_iCurrentTime:  
	//
	//  (m_iCurrentTime - m_iPausedTime) - m_iBaseTime 
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------*------> time
	//  m_iBaseTime       m_iStopTime        startTime     m_iCurrentTime

	return (float)(((m_iCurrentTime - m_iPausedTime) - m_iBaseTime) * m_fSecondsPerCount);
}

float CClock::GetDeltaTimeTick()const
{
	return (float)m_fDeltaTime;
}

void CClock::Initialise()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_iBaseTime = currTime;
	m_iPreviousTime = currTime;
	m_iStopTime = 0;
	m_isStopped  = false;
}

void CClock::Unpause()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  m_iBaseTime       m_iStopTime        startTime     

	if( m_isStopped )
	{
		m_iPausedTime += (startTime - m_iStopTime);	

		m_iPreviousTime = startTime;
		m_iStopTime = 0;
		m_isStopped  = false;
	}
}

void CClock::Pause()
{
	if( !m_isStopped )
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_iStopTime = currTime;
		m_isStopped = true;
	}
}

void CClock::Tick()
{
	if( m_isStopped )
	{
		m_fDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_iCurrentTime = currTime;

	// Time difference between this frame and the previous.
	m_fDeltaTime = (m_iCurrentTime - m_iPreviousTime) * m_fSecondsPerCount;

	// Prepare for next frame.
	m_iPreviousTime = m_iCurrentTime;

	// Force nonnegative.
	if(m_fDeltaTime < 0.0)
		m_fDeltaTime = 0.0;
}