#pragma once
#include <fstream>
#include <iostream>
#include <vector>
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
    vector <float> ratings;
    float avg_rate = 0;
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
    void make_categories();
    void show_category();
};


