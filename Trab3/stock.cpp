#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "stock.h"
// Importamos a biblioteca client.h para que o registro Product seja utilizado 
#include "client.h"
using namespace std;


// fun��o para expandir um vetor
Product* expandVector(Product* oldVector, unsigned short size) {

	// Criamos um novo vetor por aloca��o dinamica uma unidade maior que o antigo
	Product* newVector = new Product[size + 1];

	// Passamos todos os valores do antigo para o novo
	for (int i = 0; i < size; i++) {
		newVector[i] = oldVector[i];
	}

	// deletamos o antigo
	delete[] oldVector;

	// Retornamos o novo
	return newVector;
}

void toPascalCase(char name[]) {

	// criamos um ponteiro para manipular os caracteres atraves do seu endere�o de mem�ria
	// sendo esse ponteiro igual ao endere�o do primeiro caractere
	char* p = name;
	// O primeiro caractere ser� maiuscula
	*p = toupper(name[0]);
	for (int i = 1; i < strlen(name); i++)
		// Utilizando aritmetica de vetores atualizamos o endere�o de memoria de vetor e mudamos seu caractere atraves da fun��o tolower sem retornar nada no final
		*(p + i) = tolower(name[i]);
}


// Definindo uma fun��o de menu
char menu() {
	char option;
	cout << "Painal de controle" << endl;
	cout << "===================" << endl;
	cout << "(A)dicionar" << endl;
	cout << "(E)xcluir" << endl;
	cout << "(L)istar" << endl;
	cout << "(S)air" << endl;
	cout << "===================" << endl;
	cout << "Op��o: [ ]\b\b";
	cin >> option;
	return option;
}


// Lista os produtos no estoque
void list(Product p[], unsigned short size) {
	if (size == 0) {
		cout << "N�o h� produtos no estoque" << endl;
	}
	else {
		cout << "Listagem" << endl;
		cout << "--------" << endl;
		cout << fixed;
		cout.precision(2);
		for (int i = 0; i < size; i++) {
			cout << left; cout.width(7);
			cout << p[i].name << "- R$" << p[i].price << " - " << p[i].stock << " und." << endl;
		}
	}
	system("pause");
}

// fun��o chamada no arquivo main
void StockController() {
	
	// Inicializa��o das vari�veis complementares 
	Product* stock;
	ifstream fin;
	unsigned short capacity = 0;
	unsigned short numberOfProducts = 0;
	int position;

	fin.open("stock.dat", ios_base::in | ios_base::binary);
	// caso n�o exista o arquivo bin�rio, o veotr dinamico ir� receber nullptr
	if (!fin.is_open()) {
		stock = nullptr;
	}
	else {
		// caso o arquivo exista, passaremos o numero de registro para uma variavel e criamos o vetor dinamico
		fin.read((char *) & capacity, sizeof(unsigned short));
		// A principio, o numero de produtos ser� igual a capacidade do vetor
		numberOfProducts = capacity;
		stock = new Product[capacity];

		// Passando os produtos para o vetor de estoque
		for (unsigned short i = 0; i < capacity; i++) {
			fin.read((char *) &stock[i], sizeof(Product));
		}
	}

	fin.close();

	// lendo a primeira op��o do menu inicial
	char option = menu();
	
	while (tolower(option) != 's') {
		system("cls");
		// Retirando o \n do buffer
		cin.get();
		switch (tolower(option))
		{
		case 'a':
			// Lendo as informa��es do produto a ser adcionado no estoque
			cout << "Adicionar" << endl;
			cout << "---------" << endl;
			char newName[24];
			cout << "Produto: ";
			cin.getline(newName, 24);
			// Passando o nome para Pascal Case para ser adicionado 
			toPascalCase(newName);
			cout << "Pre�o: ";
			float newPrice;
			cin >> newPrice;
			cout << "Quantidade: ";
			unsigned newStock;
			cin >> newStock;

			position = -1;
			// Verificamos se o produto ja existe atrav�s de seu nome
			for (int i = 0; i < numberOfProducts; i++) {
				if (!strcmp(stock[i].name, newName)) {
					position = i;
				}
			}

			// caso n�o exista, iremos adcionar um novo produto
			if (position == -1) {
				// caso o n�mero de produtos no vetor seja igual a capacidade, precisamos aumentar a capacidade do vetor, para isso, chamamos a fun��o de expandir vetor e atualizamos a variavel capacidade
				if (numberOfProducts == capacity) {
					stock = expandVector(stock, capacity);
					++capacity;
				}
				// Por fim, adicionamos o produto no vetor e atualizamos o numero de produtos
				strcpy(stock[numberOfProducts].name, newName);
				stock[numberOfProducts].price = newPrice;
				stock[numberOfProducts].stock = newStock;
				++numberOfProducts;
			}
			else {
				// Caso o produto ja exista, iremos apenas atualizar o pre�o e aumentar o estoque
				stock[position].price = newPrice;
				stock[position].stock += newStock;
			}
			break;
		case 'e':
			if (numberOfProducts == 0) {
				cout << "N�o h� produtos no estoque para serem excluidos" << endl;
				system("pause");
			}
			else {
				// Menu de produtos disponiveis para serem exluidos
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
					// assim que o produto � excluido, deslocamos os produtos subsequentes uma unidade para tr�s
					for (int i = choice; i < numberOfProducts - 1; i++) {
						stock[i] = stock[i + 1];
					}

					// O �ltimo produto se torna vazio
					strcpy(stock[numberOfProducts - 1].name, " ");
					stock[numberOfProducts - 1].price = 0;
					stock[numberOfProducts - 1].stock = 0;
					// atualizamos o n�mero de produtos
					--numberOfProducts;
					break;
				case 'n':
					cout << "Item " << stock[choice].name << " n�o excluido" << endl;
					break;
				default:
					cout << "OP��O INV�LIDA!!!! Nada feito" << endl;
				}
			}
			break;
		case 'l':
			// chama a fun�ao listar
			list(stock, numberOfProducts);
			break;
		case 's':
			break;
		default:
			cout << "op��o inv�lida" << endl;
			system("pause");
		}

		system("cls");

		// chama o menu de novo para atualizar o la�o
		option = menu();
	}

	// Escrevendo o arquivo binario
	ofstream fout;
	fout.open("stock.dat", ios_base::out | ios_base::binary);


	// Passando o n�mero de produtos e os elementos do vetor de registros para o arquivo bin�rio, assim, atualizando o estoque
	fout.write((char *) &numberOfProducts, sizeof(unsigned short));

	for (unsigned short i = 0; i < numberOfProducts; ++i)
		fout.write((char*)& stock[i], sizeof(Product));

	fout.close();
	delete[] stock;
	
}

