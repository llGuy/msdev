#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <iostream>
#include <windows.h>
#include <chrono>

struct Timet
{
	int32_t hours;
	int32_t minutes;
	int32_t seconds;
};

class Timer
{
public:
	explicit Timer(const std::string&& title);
	void Run(void);
private:
	void Time(void);
	void Pause(void);
	void Resume(void);
	void Start(void);
	void End(void);
	void Quit(void);
	void Poll(const HANDLE& h);
	double Duration(void);

	const Timet CalculateTime(void);
private:
	std::string m_title;
	double m_total;
	bool m_running;
	bool m_paused;
	bool m_started;
	std::chrono::high_resolution_clock::time_point m_current;
};

#endif