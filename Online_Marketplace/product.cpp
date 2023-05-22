#include <iostream>
#include "product.h"
#include "User.h"
#include "Global.h"
#include <fstream>
#include "RatingSys.h"

using namespace std;

RatingSys syss;

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
        cout << "1. Add product\n2. View products\n3. Update product\n4. Remove product\n5. Log out" << endl;
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
            cout << "1) Remove product from stock\n";
            cout << "2) Decrease product quantity\n";
            cout << "Enter the choice:\n";
            cin >> choice;

            if (choice == 2)
            {
                int qun;
                cout << "enter the name of product: \n";
                cin >> nameToRemove;
                cout << "enter the quantity you want to remove from stock: \n";
                cin >> qun;
                removeProduct(nameToRemove, qun);
            }
            else if (choice == 1) {
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

    //to get product category
    do {
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

    system("cls"); //clear screan
    cout << "\t\t\t\tProduct added successfully!" << endl;
}

void product::viewproduct() //view products
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

    auto it = stock.find(ProductName); // auto takes any data type
    if (it != stock.end() && (it->second.sellerId == current_user->id || current_user->type == "customer")) { //product found in stock and it's either the seller who owns this product or the buyer trying to access it
        if (c <= it->second.quantity)
        {
            it->second.quantity -= c;

        }
        else
        {
            cout << "No available quantity in stock\n";
        }


    }
    else {
        cout << "\t\t\t\tProduct with name " << ProductName << " was not found." << std::endl;
    }
}


//Customer methods

void product::make_categories()
{

    //    string name;
    User u;

    //we first clear category lists so it doesn't duplicate data 
    category_vector[0].clear(); //phones {iphone, galaxy, lenovo}
    category_vector[1].clear(); //electronics
    category_vector[2].clear(); //fashion
    category_vector[3].clear(); //others

    for (auto it = stock.begin(); it != stock.end(); ++it) {

        //phones
        if (it->second.category == "Phones") {
            category_vector[0].push_back(&it->second);

        }
        //Electronics
        else if (it->second.category == "Electronics") {
            category_vector[1].push_back(&it->second);
        }
        //Fashion
        else if (it->second.category == "Fashion") {
            category_vector[2].push_back(&it->second);
        }
        else {
            category_vector[3].push_back(&it->second);
        }

    }


}

void product::show_category()
{
    string choice;
    int index;
    do {
        cout << "Available Categories: 1)Phones\t2)Electronics\t3)Fashion\t4)Others\t0) Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");
        if (choice == "1") {
            cout << "Phones:\n";
            index = 0;
        }
        else if (choice == "2") {
            cout << "Electronics:\n";
            index = 1;
        }
        else if (choice == "3") {
            cout << "Fashion:\n";
            index = 2;
        }
        else if (choice == "4") {
            cout << "Others:\n";
            index = 3;
        }
        else if (choice == "0") {
            return;
        }
        else
            continue;

        for (int i = 0; i < category_vector[index].size(); i++) {
            cout << i + 1 << ") Name: " << category_vector[index][i]->name << "\tAverage Rate: " << category_vector[index][i]->avg_rate << "\t\tPrice: " << category_vector[index][i]->price << endl;
        }
        cout << "\t\t\t\t--------------------------------------------------------" << endl;
        cout << "choose product from above:\n(press 0 to Sort by Avg. Customer Review)\n\n";
        int answer;
        cin >> answer;
        system("cls");
        if (answer == 0) { // if answer is not a number of a product (0) then sort
            cout << "1) Asscending\n2) Descending\n";
            cin >> answer;
            system("cls");
            if (answer == 1) {
                syss.sorAsc(index);
                show_category();
                return;
            }
            else if (answer == 2) {
                syss.sorDesc(index);
                show_category();
                return;
            }
            else {
                cout << "Enter a valid choice!" << endl;
                continue;
            }
        }
        answer--; // making it zero indexed.
        if (answer >= category_vector[index].size() || answer < 0) {
            cout << "Enter a valid number" << endl;
            continue;
        }
        else {
            User u;
            u.search(category_vector[index][answer]->name);
        }

        break;
    } while (true);
}



