#pragma once
static const int SCR_W = 1920;
static const int SCR_H = 1080;

static const int RAT_W = 30;
static const int RAT_H = 90;

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};


