#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "client.h"
using namespace std;


// Função para achar o indice do caractere do menu de opções
int findIndex(const char vet[], char ch, int size) {
	for (int i = 0; i < size; i++) {
		if (vet[i] == ch)
			return i;
	}
	return -1;
}

// Colorir o texto caso o produto esteja em falta no estoque
void redColor() {
	cout << "\033[0;31;40m";
}

// reseta a cor
void resetColor() {
	cout << "\033[m";
}

// Função principal chamada na main
void ClientInterface() {
	// Abrindo o binario to estoque para iniciar o programa
	ifstream stockFile;
	stockFile.open("stock.dat", ios_base::in | ios_base::binary);

	// Caso o arquivo binario não seja aberto, ele não existe, logo não tem estoque e o programa não é inicializado
	if (!stockFile.is_open()) {
		cout << "SINTO MUITO" << endl;
		cout << "Estamos sem estoque :(";
		exit(EXIT_FAILURE);
	}

	unsigned short numberOfProducts;

	// Lendo a quantidade de registros que existem no arquivo binário
	stockFile.read((char*) &numberOfProducts, sizeof(unsigned short));

	// iniciando o vetor dinamico para representar as vendas feitas durante um pedido
	unsigned* sells = new unsigned[numberOfProducts];

	// Criando o vetor dinamico de produtos com a quantidade de registros lindo anteriormente
	Product* products = new Product[numberOfProducts];

	// Passando os registros para o vetor dinamico
	for (int i = 0; i < numberOfProducts; i++) {
		stockFile.read((char*) & products[i], sizeof(Product));
		sells[i] = 0;
	}

	// Fechando o arquivo
	stockFile.close();
	

	// Iniciando variaveis complementares necessarias ao programa
	unsigned quantity;
	float totalToPay;
	unsigned order = 0;
	ofstream fout;

	//====================
	//     Menu inicial
	//====================
	char option, suboption;
	cout << " RapiZinho" << endl;
	cout << "===========" << endl;
	for (int i = 0; i < numberOfProducts; i++) {
		// Caso o estoque esteja zerado, o menu avisará ao usuário mostrando o texto vermelho
		if (products[i].stock != 0) {
			cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
		}
		else {
			redColor();
			cout << "(" << menuOptions[i] << ") " << products[i].name << " #ESGOTADO!!!";
			resetColor();
			cout << endl;
		}
	}
	cout << "(S) Sair" << endl;
	cout << "===========" << endl;
	cout << "Opção: [ ]\b\b";
	cin >> option;

	cout << fixed;
	cout.precision(2);

	system("cls");

	// =======================
	//      Menu de pedido
	// =======================
	while (tolower(option) != 's') {
		suboption = option;
		// option é a variavel utilizada para ler as informações do menu inicial do programa
		// suboption é a variavel utilizada para ler as informações do menu inicial do pedido
		while (tolower(suboption) != 's') {

			// Como não sabemos a quantidade exata de produtos no estoque
			// Criei um vetor com todas as letras do alfabeto com excessão do s, 
			// a função irá retornar o indice correspondente ao pedido, caso essa opção não exista ele irá retornar -1
			// A partir desse índice podemos trabalhar com a posição exato no vetor de produtos e vendas correspondente ao produto selecionado
			// O vetor menuOptions está no arquivo client.h
			int index = findIndex(menuOptions, toupper(suboption), 25);
			if (index == -1) {
				cout << "Opção inválida" << endl;
				system("pause");
			}
			else {
				cout << "Pedido" << endl;
				cout << "======" << endl;
				cout << products[index].name << endl;
				cout << "R$" << products[index].price << endl;
				cout << "======" << endl;
				cout << "Quantidade [ ]\b\b";
				cin >> quantity;
				// Verifica se o pedido corresponde ao estoque existente, caso contrario, não efetua o pedido
				if (quantity <= (sells[index] + products[index].stock)) {
					sells[index] += quantity;
					system("cls");
				}
				else {
					system("cls");
					cout << "SINTO MUITO" << endl;
					cout << "Nós só temos mais " << products[index].stock - sells[index] << " " << products[index].name << " em nosso estoque." << endl;
				}

			}

			
			// =======================================================================
			//       Menu atualizado com os pedidos feitos (produtos na cesta)
			// =======================================================================
			cout << " \nRapiZinho" << endl;
			cout << "===========" << endl;
			for (int i = 0; i < numberOfProducts; i++) {
				// Mostra os produtos contidos na cesta do cliente
				if (sells[i] != 0) {
					cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
				}
			}
			cout << "===========" << endl;
			for (int i = 0; i < numberOfProducts; i++) {
				if (products[i].stock != 0) {
					cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
				}
				else {
					redColor();
					cout << "(" << menuOptions[i] << ") " << products[i].name << " #ESGOTADO!!!";
					resetColor();
					cout << endl;
				}
			}
			cout << "(S) Sair" << endl;
			cout << "===========" << endl;
			cout << "Opção: [ ]\b\b";
			cin >> suboption;

			system("cls");
		}


		// QUANDO SAI DO LAÇO
		
		// =================================
		//        Calculando as taxas
		// =================================

		// Após finalizar o pedido, mostra o total a ser pago
		cout << " RapiZinho " << endl;
		cout << "===========" << endl;
		// Produtos na cesta
		for (int i = 0; i < numberOfProducts; i++) {
			if (sells[i] != 0) {
				cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
			}
		}
		cout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
		cout << "===========" << endl;
		totalToPay = 0;
		// total a pagar com os preços dos produtos vendidos
		for (int i = 0; i < numberOfProducts; i++) {
			totalToPay += sells[i] * products[i].price;
		}
		// acrescimo da taxa de delivery (ela foi definida no arquivo client.h por ser uma constante)
		totalToPay += DELIVERY_TAX;
		cout << "Total = R$" << totalToPay << endl;

		cout << "\n[P] Pix" << endl;
		cout << "[C] Cartão " << endl;

		cout << "\nPagamento: [ ]\b\b";
		char payment;
		cin >> payment;

		float discount;
		unsigned discountPercentage;

		// Pequeno tratamento de excessão caso o usuario não digite p ou c
		while (tolower(payment) != 'p' && tolower(payment) != 'c') {
			cout << "Opção inválida!!! Escolha novamente" << endl;
			cout << "\n[P] Pix" << endl;
			cout << "[C] Cartão " << endl;

			cout << "\nPagamento: [ ]\b\b";
			cin >> payment;
		}

		// Definindo o desconto conforme a opção de pagamento
		if (tolower(payment) == 'p')
			discountPercentage = 10;
		else
			discountPercentage = 5;

		discount = discountPercentage * totalToPay / 100;
		totalToPay -= discount;

		system("cls");

		// ==============================
		//       Confirmando pedido
		// ==============================
		cout << " \nRapiZinho " << endl;
		cout << "===========" << endl;
		for (int i = 0; i < numberOfProducts; i++) {
			if (sells[i] != 0) {
				cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
			}
		}
		cout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
		cout << "Desconto de " << discountPercentage << "% = R$" << discount << endl;
		cout << "===========" << endl;
		cout << "Total = R$" << totalToPay << endl;

		cout << "\nConfirmar Pedido (S/N): [ ]\b\b";
		char confirmOrder;
		cin >> confirmOrder;

		system("cls");

		// Leve tratamento de excessões do usuário
		while (tolower(confirmOrder) != 's' && tolower(confirmOrder) != 'n') {
			cout << "Por favor digite um valor válido" << endl;

			cout << "\nConfirmar Pedido (S/N): [ ]\b\b";
			cin >> confirmOrder;
			system("cls");
		}

		
		if (tolower(confirmOrder) == 's') {

			// ========================
			//     Gerando recibo
			// ========================

			//atualizando a variavel de pedido
			++order;
			cout << "Gerando recibo..." << endl;

			// Definindo o nome do arquivo com base no número do pedido
			char fileTitle[30] = "pedido_";
			// 48 pois a partir desse valor começam os digitos na tabela ASCII
			fileTitle[7] = 48 + order;
			strcat(fileTitle, ".txt");
			fout.open(fileTitle);

			// Gravando as informações em um arquivo texto
			fout << "Pedido #" << order << endl;
			fout << "--------------------------------------------------" << endl;
			fout << fixed;
			fout.precision(2);
			for (int i = 0; i < numberOfProducts; i++) {
				if (sells[i] != 0) {
					fout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
				}
			}
			fout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
			fout << "Desconto de " << discountPercentage << "% = R$" << discount << endl;
			fout << "--------------------------------------------------" << endl;
			fout << "Total = R$" << totalToPay << endl;
			fout.close();

			// =================================
			//        Atualizando estoque
			// =================================

			// Subtraindo o estoque com base nas vendas do produto
			for (int i = 0; i < numberOfProducts; i++) {
				products[i].stock -= sells[i];
			}
			ofstream newStock;

			// passando o numero de produtos e o vetor de registros atualizado para o arquivo binario que representa o estoque
			newStock.open("stock.dat", ios_base::out | ios_base::binary);
			newStock.write((char*)&numberOfProducts, sizeof(unsigned short));

			for (unsigned short i = 0; i < numberOfProducts; ++i)
				newStock.write((char*) & products[i], sizeof(Product));

			newStock.close();
		}
		else
			cout << "Pedido Cancelado";


		// =========================================================
		//        Mostrando o menu para recerber o próximo pedido
		// =========================================================
		for (int i = 0; i < numberOfProducts; i++)
			sells[i] = 0;

		cout << " RapiZinho" << endl;
		cout << "===========" << endl;
		for (int i = 0; i < numberOfProducts; i++) {
			if (products[i].stock != 0) {
				cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
			}
			else {
				redColor();
				cout << "(" << menuOptions[i] << ") " << products[i].name << " #ESGOTADO!!!";
				resetColor();
				cout << endl;
			}
		}
		cout << "(S) Sair" << endl;
		cout << "===========" << endl;
		cout << "Opção: [ ]\b\b";
		cin >> option;
		system("cls");
	}
	
	// Deletando os vetores dinamicos
	delete[] sells;
	delete[] products;
	cout << "Obrigado";
}

