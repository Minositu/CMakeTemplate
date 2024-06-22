#pragma once
#include <string>

void createWindow(std::string windowName, int posX = 0, int posY = 0, int width = 100, int height = 100);

bool processMessages();

void shutdownWindow();