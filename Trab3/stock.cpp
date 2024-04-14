#include <iostream>
#include <fstream>
using namespace std;

struct Product
{
	char name[24];
	float price;
	unsigned stock;
};

int main() {

	Product p;
	Product* stock;
	ifstream fin;

	fin.open("stock.dat", ios_base::in || ios_base::binary);
	if (!fin.is_open()) {
		stock = nullptr;
	}
	else {
		unsigned short size;
		fin.read((char *) & size, sizeof(unsigned short));
		stock = new Product[size];

		for (unsigned short i = 0; i < size; i++) {
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
			cout << "adiciona" << endl;
			break;
		case 'e':
			cout << "exclui" << endl;
			break;
		case 'l':
			cout << "lista" << endl;
			break;
		case 's':
			break;
		default:
			cout << "opção inválida" << endl;
		}

		cout << "Painal de controle" << endl;
		cout << "===================" << endl;
		cout << "(A)dicionar" << endl;
		cout << "(E)xcluir" << endl;
		cout << "(L)istar" << endl;
		cout << "(S)air" << endl;
		cout << "===================" << endl;
		cin >> option;
	}

	delete[] stock;
	return 0;
}