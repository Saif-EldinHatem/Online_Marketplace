#pragma once
#include <fstream>
#include "product.h"
#include <vector>

using namespace std;


class User
{
public:
	int id;
	string name;
	string password;
	string email;
	string type;
    string address = "address";//for customer only
	int phone;

	//cart related
	double total =0 ;
	vector<product> cart;

	void login(string type);
	void admin();
	void info(string type);
	void showpersonaldata(User* u);
	void regestir(string type);
	void forgetpass();
    //customer only
    void buyerMenu();
    void cartMenu();
    void addToCart(product item);
    void removeFromCart(int index);
    void updateCart(int index);
    void confirmBuying();
    void printCart();
    void search(string name);

};


