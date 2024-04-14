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

Product* expandVector(Product*, unsigned short);

int main() {

	Product p;
	Product* stock;
	ifstream fin;
	unsigned short capacity = 0;
	unsigned short numberOfProducts = 0;

	fin.open("stock.dat", ios_base::in || ios_base::binary);
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
	cin >> option;
	while (tolower(option) != 's') {
		switch (tolower(option))
		{
		case 'a':
			cout << "Adicionar" << endl;
			cout << "---------" << endl;
			char newName[24];
			cout << "Produto: ";
			cin >> newName;
			cout << "Preço: ";
			float newPrice;
			cin >> newPrice;
			cout << "Quantidade: ";
			unsigned newStock;
			cin >> newStock;
			int position = -1;
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

				char confirmation;
				cout << "Deseja excluir " << stock[choice].name << " (S/N) ";
				cin >> confirmation;
				switch (tolower(confirmation))
				{
				case 's':
					for (int i = choice; i < numberOfProducts - 1; i++) {
						strcpy(stock[i].name, stock[i + i].name);
						stock[i].price = stock[i + 1].price;
						stock[i].stock = stock[i + 1].stock;
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
				for (int i = 0; i < numberOfProducts; i++) {
					cout << left; cout.width(7);
					cout << stock[i].name << "- R$" << stock[i].price << " - " << stock[i].stock << " und." << endl;
				}
			}
			break;
		case 's':
			break;
		default:
			cout << "opção inválida" << endl;
		}

		system("cls");

		cout << "Painal de controle" << endl;
		cout << "===================" << endl;
		cout << "(A)dicionar" << endl;
		cout << "(E)xcluir" << endl;
		cout << "(L)istar" << endl;
		cout << "(S)air" << endl;
		cout << "===================" << endl;
		cin >> option;
	}

	// Escrevendo o arquivo binario
	ofstream fout;
	fout.open("stock.dat", ios_base::out || ios_base::binary);

	fout.write((char *) &numberOfProducts, sizeof(unsigned short));

	for (unsigned short i = 0; i < numberOfProducts; ++i)
		fout.write((char*)& stock[i], sizeof(Product));

	fout.close();
	delete[] stock;
	return 0;
}

Product* expandVector(Product * oldVector, unsigned short size) {
	Product* newVector = new Product[size + 1];

	for (int i = 0; i < size; i++) {
		newVector[i] = oldVector[i];
	}

	delete[] oldVector;

	return newVector;
}