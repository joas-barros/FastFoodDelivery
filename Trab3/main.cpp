#include <iostream>
#include <cstring>
#include "stock.h"
#include "client.h"
using namespace std;

// ================================
//  arquivo principal do programa
// ================================
int main(int argc, char** argv) {
	// caso s� seja passado o nome do executavel no prompt deve-se abrir a intercae de pedido do cliente
	if (argc == 1)
		ClientInterface();
	else {
		// caso o argumento ap�s o nome do executavel seja -c, devemos abrir o controlador do estoque
		if (strcmp(argv[1], "-c") == 0) {
			StockController();
		}
		else {
			//caso nenhuma condi��o seja satisfeita, deve mostrar op��o inv�lida
			cout << "Op��o inv�lida";
		}
	}
	return 0;
}