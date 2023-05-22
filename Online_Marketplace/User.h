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
	vector<product> cart; 
	double total = 0;


	void login(string type);
	void admin();
	void selector_page(string type);
	void showpersonaldata(User* u);
	void regestir(string type);
	void forgetpass();

    //customer only methods

    void buyerMenu();
    void cartMenu();
    void addToCart(product item);
    void removeFromCart(int index);
    void updateCart(int index);
    void confirmBuying();
    void printCart();
    void search(string name);


	//rating system
	void addRating(product* prdct);
};

