#include "timer.h"
#include <string>

Timer::Timer(const std::string&& title)
	: m_title(title), m_paused(false), m_started(false)
{
}
void Timer::Run(void) 
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	m_total = 0.0;
	m_running = true;
	while (m_running)
	{
		Poll(consoleHandle);
	}
}
void Timer::Poll(const HANDLE& h)
{
	std::string poll;
	SetConsoleTextAttribute(h, 10);
	std::cout << m_title << " > ";
	SetConsoleTextAttribute(h, 7);
	std::cin >> poll;
	SetConsoleTextAttribute(h, 12);

	char choice = poll[1];
	switch (choice)
	{
	case 's': Start(); break;
	case 'q': Quit(); break;
	case 't': Time(); break;
	case 'p': Pause(); break;
	case 'r': Resume(); break;
	case 'e': End(); break;
	}
	std::cout << std::endl;
}
void Timer::Time(void)
{
	if(m_started) m_total += Duration() / 1000000000;
	Timet t = CalculateTime();
	std::cout << t.hours << "h\t" << t.minutes << "m\t" << t.seconds << "s" << std::endl;
	m_current = std::chrono::high_resolution_clock::now();
}
void Timer::Pause(void)
{
	m_paused = true;
	m_total += Duration();
}
void Timer::Resume(void)
{
	m_current = std::chrono::high_resolution_clock::now();
	m_paused = false;
}
void Timer::Start(void)
{
	m_started = true;
	m_total = 0.0;
	m_current = std::chrono::high_resolution_clock::now();
}
void Timer::End(void)
{
	m_started = false;
	Time();
	m_total = 0.0;
}
void Timer::Quit(void)
{
	m_running = false;
}
double Timer::Duration(void)
{
	if (m_paused) return 0.0;
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = now - m_current;
	return d.count();
}
const Timet Timer::CalculateTime(void)
{
	Timet t;
	int32_t totalCasti32 = static_cast<int32_t>(m_total);
	t.seconds = totalCasti32 % 60;
	t.minutes = (totalCasti32 / 60) % 60;
	t.hours = totalCasti32 / (60 * 60);

	return t;
}