#pragma once
#include <string>

void __declspec(dllexport) CreateEngine();
void __declspec(dllexport) CreateWindow( unsigned int width, unsigned int height, const std::string& title );
void __declspec(dllexport) Run();
void __declspec(dllexport) DestroyEngine();
