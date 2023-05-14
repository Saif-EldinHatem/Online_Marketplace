#include <iostream>
#include "product.h"
#include "User.h"
#include "Global.h"
#include <fstream>

using namespace std;


//construct
product::product()
{
    id = 0;
    name = "";
    price = 0;
    quantity = 0;
    sellerId = 0;
    category = "";
}

//seller methods
void product::productMenu()
{
    string nameToRemove;
    int choice;
    while (true) {
        cout << endl << "\t\t-----------------------------------------------------------------------" << endl;
        cout << "1. Add product\n2. View product\n3. Update product\n4. Remove product\n5. Log out" << endl;
        cout << "Enter your choice: " << endl;

        cin >> choice;
        system("cls");
        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            viewproduct();
            break;
        case 3:
            updateProduct();
            break;
        case 4:
            int choice;
            cout << "1) Decrease product quantity\n";
            cout << "2) Remove product from stock\n";
            cout << "Enter the choice:\n";
            cin >> choice;
        
            if (choice == 1)
            {
                int qun;
                cout << "enter the name of product: \n";
                cin >> nameToRemove;
                cout << "enter the quantity you want to remove from stock: \n";
                cin >> qun;
                removeProduct(nameToRemove , qun);
            }
            else if (choice == 2){
                cout << "Enter product name you want to remove:\n";
                cin >> nameToRemove;
                removeProduct(nameToRemove);
            }
            else 
                "invalid choice";
            break;
        case 5:
            return;
        default:
            cout << "\t\t\t\t\tInvalid choice! Try again." << endl;
        }
    }
}

void product::addProduct()
{
    product newProduct;
    
    cout << "Enter product ID: ";
    cin >> newProduct.id;
    
    cout << "Enter product name: ";
    cin >> newProduct.name;
    
    cout << "Enter product price: ";
    cin >> newProduct.price;
    
    cout << "Enter product quantity: ";
    cin >> newProduct.quantity;

    do{
        string choice;
        cout << "Available Categories: 1)Phones\t2)Electronics\t3)Fashion\t4)Others" << endl;
        cout << "Enter product category: ";
        cin >> choice;
        
        if (choice == "1")
            newProduct.category = "Phones";
        else if (choice == "2")
            newProduct.category = "Electronics";
        else if (choice == "3")
            newProduct.category = "Fashion";
        else if (choice == "4")
            newProduct.category = "Others";
        else
            continue;
        
        break;
    } while (true);

    newProduct.sellerId = current_user->id;
    stock[newProduct.name] = newProduct; 

    system("cls");
    cout << "\t\t\t\tProduct added successfully!" << endl;
}

void product::viewproduct()
{
    system("cls");
    cout << "Product ID\tProduct Name\tProduct Price\tProduct Category\tProduct Quantity\tSeller ID" << endl;
    for (auto it = stock.begin(); it != stock.end(); it++) // get firts of map then iterate until we reach end on map 
    {
        if (current_user->id == it->second.sellerId) { //To only view products of the specified seller.
            cout << it->second.id << "\t\t" << it->second.name << "\t\t" << it->second.price << "\t\t" << it->second.category << "\t\t\t" << it->second.quantity << "\t\t\t" << it->second.sellerId << endl;
        }
    } // second is the value , first is the key , so second contains info ely fel struct 

}

void product::updateProduct()
{
    string name;

    cout << "Enter product name to update: ";
    cin >> name;

    auto it = stock.find(name);
    if (it != stock.end() && it->second.sellerId == current_user->id) { //product name found and product belongs to the current seller

        //product name found: 3malna object of product w3malna copy mn el id bta3 el original product to the object b3daha msa7na el original wda5alna el data el gdeda fel update lel object b3den defna el object to the stock map.

        int choice;
        cout << "1) Edit quantty. \n2) Edit all product info." << endl;
        cin >> choice;
        system("cls");
        if (choice == 1) {
            cout << "Enter the new quantity: ";
            cin >> it->second.quantity;
            cout << "product " << it->second.name << " quantity is: " << it->second.quantity << endl;
        }
        else {
            product p1;
            p1.id = it->second.id;
            stock.erase(it);

            cout << "Enter new product name: ";
            cin >> p1.name;

            cout << "Enter new product price: ";
            cin >> p1.price;

            cout << "Enter new product quantity: ";
            cin >> p1.quantity;

            do {
                string choice;
                cout << "Available Categories: 1)Phones\t2)Electronics\t3)Fashion\t4)Others" << endl;
                cout << "Enter product category: ";
                cin >> choice;

                if (choice == "1")
                    p1.category = "Phones";
                else if (choice == "2")
                    p1.category = "Electronics";
                else if (choice == "3")
                    p1.category = "Fashion";
                else if (choice == "4")
                    p1.category = "Others";
                else
                    continue;

                break;
            } while (true);

            p1.sellerId = current_user->id;

            stock[p1.name] = p1;

            system("cls");
        }

        cout << "\t\t\t\tProduct updated successfully." << endl;

    }
    else {
        system("cls");
        cout << "\t\t\t\tProduct with name " << name << " not found." << endl;
    }
}

void product::removeProduct(string ProductName)
{
    system("cls");

    auto it = stock.find(ProductName);
    if (it != stock.end() && it->second.sellerId == current_user->id) {

        stock.erase(it);
        cout << "\t\t\t\tProduct with name " << ProductName << " has been removed." << std::endl;
    }
    else {
        cout << "\t\t\t\tProduct with name " << ProductName << " was not found." << std::endl;
    }

}

void product::removeProduct(string ProductName, int c)
{

    auto it = stock.find(ProductName);
    if (it != stock.end() && (it->second.sellerId == current_user->id || current_user->type == "customer")) { //product found in stock and it's either the seller who owns this product or the buyer trying to access it
        if (c <= it->second.quantity)
        {
            it->second.quantity -= c;
        }
        else
        {
            cout << "No available quantity in stock\n";
        }

        //print the current quantity
        cout << "\t\t\t\t" << ProductName << " new quantity : " << it->second.quantity << endl;

    }
    else {
        cout << "\t\t\t\tProduct with name " << ProductName << " was not found." << std::endl;
    }
}
   

//Customer methods

void product::categories()
{

    string name;
    User u;
    phones.clear();
    electronics.clear();
    fashion.clear();
    others.clear();
    //check here!
    for (auto it = stock.begin(); it != stock.end(); ++it) {

        //phones
        if (it->second.category == "Phones") {
            phones.push_back(&it->second);

        }
        //Electronics
        else if (it->second.category == "Electronics") {
            electronics.push_back(&it->second);
        }
        //Fashion
        else if (it->second.category == "Fashion") {
            fashion.push_back(&it->second);
        }
        else {
            others.push_back(&it->second);
        }

    }

    cout << "[Phones]:" << endl;
    for (int i = 0; i < phones.size(); i++) {
        cout << phones[i]->name << endl;
    }

    cout << endl << endl << endl << "[Electroins]:" << endl;
    for (int i = 0; i < electronics.size(); i++) {
        cout << electronics[i]->name << endl;
    }
    cout << endl << endl << endl << "[Fashion]:" << endl;
    for (int i = 0; i < fashion.size(); i++) {
        cout << fashion[i]->name << endl;
    }
    cout << endl << endl << endl << "[Others]:" << endl;
    for (int i = 0; i < others.size(); i++) {
        cout << others[i]->name << endl;
    }
   cout <<"\n\n\nplease enter the product name from above:\n";
    cin >> name;
    u.search(name);
    
}
