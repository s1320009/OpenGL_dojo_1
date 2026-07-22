#pragma once

void FontBegin();
void FontEnd();

void FontSetPosition(float _x, float _y);
void FontSetSize(float _size);
void FontSetColor(unsigned char _red, unsigned char _green, unsigned char _blue);
void FontDraw(const char* _format, ...);