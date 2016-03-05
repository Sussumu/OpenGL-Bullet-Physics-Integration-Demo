#pragma once

#include <string>
#include <SDL/SDL.h>
#include <iostream>
#include <Windows.h>

extern void showMessage(std::string message);
extern void fatalError(std::string message);
extern void gotoxy(int x, int y);