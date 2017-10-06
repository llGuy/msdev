#include "EntryManager.h"



EntryManager::EntryManager()
{
}

bool EntryManager::Introduction()
{
	int _decision;
	cout << "~add(1)\n~check(!1)\n\n";
	cin >> _decision;
	if(_decision == 1) return true;
	else return false;
}

void EntryManager::Compile()
{
	if(Introduction() == true)
	{
		Add();
	}
	else
	{
		
	}
}

void EntryManager::Add() 
{
	
}

EntryManager::~EntryManager()
{
}
