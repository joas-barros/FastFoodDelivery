#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "stock.h"
using namespace std;

Product* expandVector(Product* oldVector, unsigned short size) {
	Product* newVector = new Product[size + 1];

	for (int i = 0; i < size; i++) {
		newVector[i] = oldVector[i];
	}

	delete[] oldVector;

	return newVector;
}

void toPascalCase(char name[]) {

	// criamos um ponteiro para manipular os caracteres atraves do seu endereço de memória
	// sendo esse ponteiro igual ao endereço do primeiro caractere
	char* p = name;
	*p = toupper(name[0]);
	for (int i = 1; i < strlen(name); i++)
		// Utilizando aritmetica de vetores atualizamos o endereço de memoria de vetor e mudamos seu caractere atraves da função toupper sem retornar nada no final
		*(p + i) = tolower(name[i]);
}

void StockController() {

	
	Product* stock;
	ifstream fin;
	unsigned short capacity = 0;
	unsigned short numberOfProducts = 0;
	int position;

	fin.open("stock.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open()) {
		stock = nullptr;
	}
	else {
		
		fin.read((char *) & capacity, sizeof(unsigned short));
		numberOfProducts = capacity;
		stock = new Product[capacity];

		for (unsigned short i = 0; i < capacity; i++) {
			fin.read((char *) &stock[i], sizeof(Product));
		}
	}

	fin.close();

	char option;
	cout << "Painal de controle" << endl;
	cout << "===================" << endl;
	cout << "(A)dicionar" << endl;
	cout << "(E)xcluir" << endl;
	cout << "(L)istar" << endl;
	cout << "(S)air" << endl;
	cout << "===================" << endl;
	cout << "Opção: [ ]\b\b";
	cin >> option;
	
	while (tolower(option) != 's') {
		system("cls");
		switch (tolower(option))
		{
		case 'a':
			cout << "Adicionar" << endl;
			cout << "---------" << endl;
			char newName[24];
			cout << "Produto: ";
			cin >> newName;
			toPascalCase(newName);
			cout << "Preço: ";
			float newPrice;
			cin >> newPrice;
			cout << "Quantidade: ";
			unsigned newStock;
			cin >> newStock;
			position = -1;
			for (int i = 0; i < numberOfProducts; i++) {
				if (!strcmp(stock[i].name, newName)) {
					position = i;
				}
			}
			if (position == -1) {
				if (numberOfProducts == capacity) {
					stock = expandVector(stock, capacity);
					++capacity;
				}
				strcpy(stock[numberOfProducts].name, newName);
				stock[numberOfProducts].price = newPrice;
				stock[numberOfProducts].stock = newStock;
				++numberOfProducts;
			}
			else {
				stock[position].price = newPrice;
				stock[position].stock += newStock;
			}
			break;
		case 'e':
			if (numberOfProducts == 0) {
				cout << "Não há produtos no estoque para serem excluidos" << endl;
				system("pause");
			}
			else {
				cout << "Excluir" << endl;
				cout << "-------" << endl;
				for (int i = 0; i < numberOfProducts; i++) {
					cout << i + 1 << ")  " << stock[i].name << endl;
				}

				int choice;
				cout << "\nProduto: [ ]\b\b";
				cin >> choice;

				--choice;

				char confirmation;
				cout << "Deseja excluir " << stock[choice].name << " (S/N) ";
				cin >> confirmation;
				switch (tolower(confirmation))
				{
				case 's':
					//Product temp;
					for (int i = choice; i < numberOfProducts - 1; i++) {
						stock[i] = stock[i + 1];
						/*strcpy(stock[i].name, stock[i + i].name);
						stock[i].price = stock[i + 1].price;
						stock[i].stock = stock[i + 1].stock;*/
					}
					strcpy(stock[numberOfProducts - 1].name, " ");
					stock[numberOfProducts - 1].price = 0;
					stock[numberOfProducts - 1].stock = 0;
					--numberOfProducts;
					break;
				case 'n':
					cout << "Item " << stock[choice].name << " não excluido" << endl;
					break;
				default:
					cout << "OPÇÃO INVÁLIDA!!!! Nada feito" << endl;
				}
			}
			break;
		case 'l':
			if (numberOfProducts == 0) {
				cout << "Não há produtos no estoque" << endl;
			}
			else {
				cout << "Listagem" << endl;
				cout << "--------" << endl;
				cout << fixed;
				cout.precision(2);
				for (int i = 0; i < numberOfProducts; i++) {
					cout << left; cout.width(7);
					cout << stock[i].name << "- R$" << stock[i].price << " - " << stock[i].stock << " und." << endl;
				}
			}
			system("pause");
			break;
		case 's':
			break;
		default:
			cout << "opção inválida" << endl;
			system("pause");
		}

		system("cls");

		cout << "Painal de controle" << endl;
		cout << "===================" << endl;
		cout << "(A)dicionar" << endl;
		cout << "(E)xcluir" << endl;
		cout << "(L)istar" << endl;
		cout << "(S)air" << endl;
		cout << "===================" << endl;
		cout << "Opção: [ ]\b\b";
		cin >> option;
	}

	// Escrevendo o arquivo binario
	ofstream fout;
	fout.open("stock.dat", ios_base::out | ios_base::binary);

	fout.write((char *) &numberOfProducts, sizeof(unsigned short));

	for (unsigned short i = 0; i < numberOfProducts; ++i)
		fout.write((char*)& stock[i], sizeof(Product));

	fout.close();
	delete[] stock;
	
}

