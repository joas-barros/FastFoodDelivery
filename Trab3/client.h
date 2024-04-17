#pragma once

// ===================================
//    arquivo de cabeçalho do client
// ===================================

struct Product
{
	char name[24];
	float price;
	unsigned stock;
};

// valor da taxa de delivery
const unsigned DELIVERY_TAX = 6;

int findIndex(const char[], char, int);

void redColor();

void resetColor();

// vetor representando as opções de menu
const char menuOptions[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

void ClientInterface();
