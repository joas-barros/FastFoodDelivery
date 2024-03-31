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

int main() {
	Product products[] = {
		{"Pastel", 5.50, 0},
		{"Bolo", 6, 0},
		{"Pizza", 30.00, 0},
		{"Suco", 4, 0}
	};

	unsigned sells[4] = { 0 };
	unsigned quantity;
	float totalToPay = 0;
	ofstream fout;

	char option;
	cout << " RapiZinho" << endl;
	cout << "===========" << endl;
	cout << "(A) " << products[0].name << endl;
	cout << "(B) " << products[1].name << endl;
	cout << "(C) " << products[2].name << endl;
	cout << "(D) " << products[3].name << endl;
	cout << "(S) Sair" << endl;
	cout << "===========" << endl;
	cout << "Opção: [ ]\b\b";
	cin >> option;

	cout << fixed;
	cout.precision(2);

	system("cls");

	while (tolower(option) != 's') {
		cout << "Pedido" << endl;
		cout << "======" << endl;
		switch (tolower(option))
		{
		case 'a':
			cout << products[0].name << endl;
			cout << "R$" << products[0].price << endl;
			cout << "======" << endl;
			cout << "Quantidade [ ]\b\b";
			
			cin >> quantity;
			sells[0] += quantity;
			break;
		case 'b':
			cout << products[1].name << endl;
			cout << "R$" << products[1].price << endl;
			cout << "======" << endl;
			cout << "Quantidade [ ]\b\b";
			
			cin >> quantity;
			sells[1] += quantity;
			break;
		case 'c':
			cout << products[2].name << endl;
			cout << "R$" << products[2].price << endl;
			cout << "======" << endl;
			cout << "Quantidade [ ]\b\b";
			
			cin >> quantity;
			sells[2] += quantity;
			break;
		case 'd':
			cout << products[3].name << endl;
			cout << "R$" << products[3].price << endl;
			cout << "======" << endl;
			cout << "Quantidade [ ]\b\b";
			
			cin >> quantity;
			sells[3] += quantity;
			break;
		default:
			cout << "Opção inválida" << endl;
		}

		system("cls");

		cout << " \nRapiZinho" << endl;
		cout << "===========" << endl;
		for (int i = 0; i < 4; i++) {
			if (sells[i] != 0) {
				cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
			}
		}
		cout << "===========" << endl;
		cout << "(A) " << products[0].name << endl;
		cout << "(B) " << products[1].name << endl;
		cout << "(C) " << products[2].name << endl;
		cout << "(D) " << products[3].name << endl;
		cout << "(S) Sair" << endl;
		cout << "===========" << endl;
		cout << "Opção: [ ]\b\b";
		cin >> option;

		system("cls");
	}
	cout << " RapiZinho " << endl;
	cout << "===========" << endl;
	for (int i = 0; i < 4; i++) {
		if (sells[i] != 0) {
			cout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
		}
	}
	cout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
	cout << "===========" << endl;
	for (int i = 0; i < 4; i++) {
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

	cout << " \nRapiZinho " << endl;
	cout << "===========" << endl;
	for (int i = 0; i < 4; i++) {
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
		cout << "Gerando recibo...";
		fout.open("pedido_1.txt");
		fout << "Pedido #1" << endl;
		fout << "--------------------------------------------------" << endl;
		for (int i = 0; i < 4; i++) {
			if (sells[i] != 0) {
				fout << sells[i] << " X " << products[i].name << " de R$" << products[i].price << " = R$" << sells[i] * products[i].price << endl;
			}
		}
		fout << "Taxa de entrega = R$" << DELIVERY_TAX << endl;
		fout << "Desconto de " << discountPercentage << "% = R$" << discount << endl;
		fout << "--------------------------------------------------" << endl;
		fout << "Total = R$" << totalToPay << endl;
		fout.close();
	}
	else
		cout << "Pedido Cancelado";


	return 0;
}