#include <iostream>
#include <cstring>
#include "stock.h"
#include "client.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc == 1)
		ClientInterface();
	else {
		if (strcmp(argv[1], "-c") == 0) {
			StockController();
		}
		else {
			cout << "Opção inválida";
		}
	}
	return 0;
}