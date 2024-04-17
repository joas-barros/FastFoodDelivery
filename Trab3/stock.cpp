#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "stock.h"
// Importamos a biblioteca client.h para que o registro Product seja utilizado 
#include "client.h"
using namespace std;


// função para expandir um vetor
Product* expandVector(Product* oldVector, unsigned short size) {

	// Criamos um novo vetor por alocação dinamica uma unidade maior que o antigo
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

	// criamos um ponteiro para manipular os caracteres atraves do seu endereço de memória
	// sendo esse ponteiro igual ao endereço do primeiro caractere
	char* p = name;
	// O primeiro caractere será maiuscula
	*p = toupper(name[0]);
	for (int i = 1; i < strlen(name); i++)
		// Utilizando aritmetica de vetores atualizamos o endereço de memoria de vetor e mudamos seu caractere atraves da função tolower sem retornar nada no final
		*(p + i) = tolower(name[i]);
}


// Definindo uma função de menu
char menu() {
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
	return option;
}


// Lista os produtos no estoque
void list(Product p[], unsigned short size) {
	if (size == 0) {
		cout << "Não há produtos no estoque" << endl;
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

// função chamada no arquivo main
void StockController() {
	
	// Inicialização das variáveis complementares 
	Product* stock;
	ifstream fin;
	unsigned short capacity = 0;
	unsigned short numberOfProducts = 0;
	int position;

	fin.open("stock.dat", ios_base::in | ios_base::binary);
	// caso não exista o arquivo binário, o veotr dinamico irá receber nullptr
	if (!fin.is_open()) {
		stock = nullptr;
	}
	else {
		// caso o arquivo exista, passaremos o numero de registro para uma variavel e criamos o vetor dinamico
		fin.read((char *) & capacity, sizeof(unsigned short));
		// A principio, o numero de produtos será igual a capacidade do vetor
		numberOfProducts = capacity;
		stock = new Product[capacity];

		// Passando os produtos para o vetor de estoque
		for (unsigned short i = 0; i < capacity; i++) {
			fin.read((char *) &stock[i], sizeof(Product));
		}
	}

	fin.close();

	// lendo a primeira opção do menu inicial
	char option = menu();
	
	while (tolower(option) != 's') {
		system("cls");
		// Retirando o \n do buffer
		cin.get();
		switch (tolower(option))
		{
		case 'a':
			// Lendo as informações do produto a ser adcionado no estoque
			cout << "Adicionar" << endl;
			cout << "---------" << endl;
			char newName[24];
			cout << "Produto: ";
			cin.getline(newName, 24);
			// Passando o nome para Pascal Case para ser adicionado 
			toPascalCase(newName);
			cout << "Preço: ";
			float newPrice;
			cin >> newPrice;
			cout << "Quantidade: ";
			unsigned newStock;
			cin >> newStock;

			position = -1;
			// Verificamos se o produto ja existe através de seu nome
			for (int i = 0; i < numberOfProducts; i++) {
				if (!strcmp(stock[i].name, newName)) {
					position = i;
				}
			}

			// caso não exista, iremos adcionar um novo produto
			if (position == -1) {
				// caso o número de produtos no vetor seja igual a capacidade, precisamos aumentar a capacidade do vetor, para isso, chamamos a função de expandir vetor e atualizamos a variavel capacidade
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
				// Caso o produto ja exista, iremos apenas atualizar o preço e aumentar o estoque
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
					// assim que o produto é excluido, deslocamos os produtos subsequentes uma unidade para trás
					for (int i = choice; i < numberOfProducts - 1; i++) {
						stock[i] = stock[i + 1];
					}

					// O último produto se torna vazio
					strcpy(stock[numberOfProducts - 1].name, " ");
					stock[numberOfProducts - 1].price = 0;
					stock[numberOfProducts - 1].stock = 0;
					// atualizamos o número de produtos
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
			// chama a funçao listar
			list(stock, numberOfProducts);
			break;
		case 's':
			break;
		default:
			cout << "opção inválida" << endl;
			system("pause");
		}

		system("cls");

		// chama o menu de novo para atualizar o laço
		option = menu();
	}

	// Escrevendo o arquivo binario
	ofstream fout;
	fout.open("stock.dat", ios_base::out | ios_base::binary);


	// Passando o número de produtos e os elementos do vetor de registros para o arquivo binário, assim, atualizando o estoque
	fout.write((char *) &numberOfProducts, sizeof(unsigned short));

	for (unsigned short i = 0; i < numberOfProducts; ++i)
		fout.write((char*)& stock[i], sizeof(Product));

	fout.close();
	delete[] stock;
	
}

