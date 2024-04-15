#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

struct Product
{
	char name[24];
	float price;
	unsigned stock;
};

const unsigned DELIVERY_TAX = 6;

int findIndex(const char [], char, int);

const char menuOptions[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main() {
	ifstream stockFile;
	stockFile.open("stock.dat", ios_base::in | ios_base::binary);
	if (!stockFile.is_open()) {
		cout << "SINTO MUITO" << endl;
		cout << "Estamos sem estoque :(";
		exit(EXIT_FAILURE);
	}

	unsigned short numberOfProducts;

	stockFile.read((char*) &numberOfProducts, sizeof(unsigned short));
	unsigned* sells = new unsigned[numberOfProducts];
	Product* products = new Product[numberOfProducts];
	for (int i = 0; i < numberOfProducts; i++) {
		stockFile.read((char*) & products[i], sizeof(Product));
		sells[i] = 0;
	}

	stockFile.close();
	

	unsigned quantity;
	float totalToPay = 0;
	unsigned order = 0;
	ofstream fout;


	// Menu inicial
	char option, suboption;
	cout << " RapiZinho" << endl;
	cout << "===========" << endl;
	for (int i = 0; i < numberOfProducts; i++) {
		cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
	}
	cout << "(S) Sair" << endl;
	cout << "===========" << endl;
	cout << "Opção: [ ]\b\b";
	cin >> option;

	cout << fixed;
	cout.precision(2);

	system("cls");

	// Menu de pedido
	while (tolower(option) != 's') {
		suboption = option;
		while (tolower(suboption) != 's') {
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
				if (quantity < (sells[index] + products[index].stock)) {
					sells[index] += quantity;
					system("cls");
				}
				else {
					system("cls");
					cout << "SINTO MUITO" << endl;
					cout << "Nós só temos mais " << products[index].stock - sells[index] << " " << products[index].name << " em nosso estoque." << endl;
				}

			}

			

			// Menu atualizado com os pedidos feitos
			cout << " \nRapiZinho" << endl;
			cout << "===========" << endl;
			for (int i = 0; i < numberOfProducts; i++) {
				if (sells[i] != 0) {
					cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
				}
			}
			cout << "===========" << endl;
			for (int i = 0; i < numberOfProducts; i++) {
				cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
			}
			cout << "(S) Sair" << endl;
			cout << "===========" << endl;
			cout << "Opção: [ ]\b\b";
			cin >> suboption;

			system("cls");
		}


		// Quando sai do laço
		// Calculando as taxas
		cout << " RapiZinho " << endl;
		cout << "===========" << endl;
		for (int i = 0; i < numberOfProducts; i++) {
			if (sells[i] != 0) {
				cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
			}
		}
		cout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
		cout << "===========" << endl;
		for (int i = 0; i < numberOfProducts; i++) {
			totalToPay += sells[i] * products[i].price;
		}
		totalToPay += DELIVERY_TAX;
		cout << "Total = R$" << totalToPay << endl;

		cout << "\n[P] Pix" << endl;
		cout << "[C] Cartão " << endl;

		cout << "\nPagamento: [ ]\b\b";
		char payment;
		cin >> payment;

		float discount;
		unsigned discountPercentage;
		if (tolower(payment) == 'p')
			discountPercentage = 10;
		else
			discountPercentage = 5;

		discount = discountPercentage * totalToPay / 100;
		totalToPay -= discount;

		system("cls");
		// Confirmando pedido

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


		
		if (tolower(confirmOrder) == 's') {
			// Gerando recibo

			++order;
			cout << "Gerando recibo..." << endl;
			char fileTitle[30] = "pedido_";
			fileTitle[7] = 48 + order;
			strcat(fileTitle, ".txt");
			fout.open(fileTitle);
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

			// Atualizando estoque
			for (int i = 0; i < numberOfProducts; i++) {
				products[i].stock -= sells[i];
			}
			ofstream newStock;
			newStock.open("stock.dat", ios_base::out | ios_base::binary);
			newStock.write((char*)&numberOfProducts, sizeof(unsigned short));

			for (unsigned short i = 0; i < numberOfProducts; ++i)
				newStock.write((char*) & products[i], sizeof(Product));

			newStock.close();
		}
		else
			cout << "Pedido Cancelado";

		for (int i = 0; i < numberOfProducts; i++)
			sells[i] = 0;

		cout << " RapiZinho" << endl;
		cout << "===========" << endl;
		for (int i = 0; i < numberOfProducts; i++) {
			cout << "(" << menuOptions[i] << ") " << products[i].name << endl;
		}
		cout << "(S) Sair" << endl;
		cout << "===========" << endl;
		cout << "Opção: [ ]\b\b";
		cin >> option;
		system("cls");
	}
	
	delete[] sells;
	delete[] products;
	cout << "Obrigado";

	return 0;
}

int findIndex(const char vet[], char ch,int size) {
	for (int i = 0; i < size; i++) {
		if (vet[i] == ch)
			return i;
	}
	return -1;
}