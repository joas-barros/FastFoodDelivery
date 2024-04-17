#include <iostream>
#include <cstring>
#include "stock.h"
#include "client.h"
using namespace std;

// ================================
//  arquivo principal do programa
// ================================
int main(int argc, char** argv) {
	// caso só seja passado o nome do executavel no prompt deve-se abrir a intercae de pedido do cliente
	if (argc == 1)
		ClientInterface();
	else {
		// caso o argumento após o nome do executavel seja -c, devemos abrir o controlador do estoque
		if (strcmp(argv[1], "-c") == 0) {
			StockController();
		}
		else {
			//caso nenhuma condição seja satisfeita, deve mostrar opção inválida
			cout << "Opção inválida";
		}
	}
	return 0;
}