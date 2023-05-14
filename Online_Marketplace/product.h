#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class product
{
public:
    int id;
    string name;
    string category;
    double price;
    int sellerId;
    int quantity;

    //construct
    product();

    //Methods
    
    //for seller

    void productMenu();
    void addProduct();
    void viewproduct();
    void updateProduct();
    void removeProduct(string ProductName);
    void removeProduct(string ProductName, int c);
    void categories();
};
