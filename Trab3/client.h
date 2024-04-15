#pragma once

struct Product
{
	char name[24];
	float price;
	unsigned stock;
};

const unsigned DELIVERY_TAX = 6;

int findIndex(const char[], char, int);

void redColor();

void resetColor();

const char menuOptions[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

void ClientInterface();
