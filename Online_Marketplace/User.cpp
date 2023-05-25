#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Global.h"
#include "RatingSys.h"

using namespace std;
RatingSys sys;

void User::regestir(string type)
{
	User s;
	system("cls");

	cout << "Enter your name:";
	cin >> s.name;
	cout << endl;
	cout << "Enter your email:";
	cin >> s.email;
	cout << endl;
	cout << "Enter your phone number:";
	cin >> s.phone;
	cout << endl;
	cout << "Enter password:";
	cin >> s.password;
	cout << endl;

	s.id = autoid;
	//setting user type.
	s.type = type;

	system("cls");
	cout << "\t\t\t\t   Registraton succesful. congratulations!\n";
	cout << "\t\t\t\t\t\t Your ID is: " << autoid << "\n\n";

	user_list.push_back(s);

	autoid++;

	return;
}

void User::login(string type)
{
	User t;
	cout << "\t\tplease enter User Email and Password\n";
	cout << "User Email:";
	cin >> t.email;
	cout << endl;
	cout << "Password:";
	cin >> t.password;
	system("cls");


	if (t.id != 0 || t.password != "admin") //check if not an admin
	{
		for (auto i = user_list.begin(); i != user_list.end(); i++)//checking input id from regestered ids
		{
			User u = *i;
			if (u.email == t.email && u.password == t.password && u.type == type)//id found and it's of the same type of the user
			{
				current_user = &(*i);
				cout << "\t\t\t\t" << u.name << ", you logged in succesfully\n";
				if (u.type == "seller") {
					product p;
					p.productMenu();
				}
				else {

					buyerMenu();
				}
				return;
			}
		}
		cout << " login error!! Incorrect user id, password, or type\n\n";
		cout << "Try again. (y/n)" << endl;
		string choice2;
		cin >> choice2;
		system("cls");
		if (choice2 == "y" || choice2 == "Y" || choice2 == "yes" || choice2 == "YES") {
			login(type);
		}
	}
	else //admin login
	{
		system("cls");
		cout << "You're logged in as an admin!" << endl << endl;
		admin();
	}

}

void User::admin()
{
	int choice4, choice;
	char answer;

	system("cls");
	cout << "press 1 to search for id\n\n";
	cout << "press 2 to go back to main menu\n\n";
	cout << "please enter a choice:\n\n";
	cin >> choice;
	system("cls");
	if (choice == 1)
	{
		cout << "All regestered ID's: \n";

		for (auto it = user_list.begin(); it != user_list.end(); ++it) {
			cout << it->id + 1 << ")\tType: " << it->type << "User Name: " << it->name << endl;
		}

		cout << "\t\t------Choose the user you want from above(Or 0 to quit)------\n\n";
		cin >> choice4;
		system("cls");

		if (choice4 == 0) {
			return;
		}

		User u;

		for (auto j = user_list.begin(); j != user_list.end(); j++)
		{
			u = *j;

			if (u.id == choice4 - 1)
			{
				cout << endl;
				u.showpersonaldata(&u);
				cout << "Do you want to delete this user (y/n)";
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					user_list.erase(j);
					admin();
					return;
				}
				else {
					admin();
					return;
				}
			}

		}
		cout << "This id doesn't exist!" << endl;
	}
	return;
}

void User::selector_page(string type)
{
	char choice2;
	cout << "press 1 to login: \n\n";
	cout << "enter 2 to register \n\n";
	cout << "enter 3 if forget the password\n\n";
	cout << "enter 4 to exit \n\n";
	cout << "enter 0 to return to main menu\n\n";
	cout << "please enter choice:";
	cin >> choice2;


	switch (choice2)
	{
	case '1':
		system("cls");
		login(type);
		break;
	case '2':
		system("cls");
		regestir(type);
		break;
	case '3':
		system("cls");
		forgetpass();
		break;
	case '4':
		exit(0);
		break;
	case '0':
		system("cls");
		return;
	default:
		system("cls");
		cout << "\t\tplease enter choice from above choices." << endl;
		selector_page(type); // there might be an error.

	}
}

void User::showpersonaldata(User* u)
{
	cout << "ID:   \t" << u->id << endl;
	cout << "Name: \t" << u->name << endl;
	cout << "Phone:\t" << u->phone << endl;
	cout << "Email:\t" << u->email << endl;
	cout << "Type: \t" << u->type << endl << endl;

}

void User::forgetpass()
{
	User w;
	int option;
	system("cls");
	cout << "\t\t you forget your password don't worry \n\n";
	cout << "press 1 to search your pasword by your user id \n\n";
	cout << "press 2 to go back to main menu\n\n";
	cout << "enter your choice \n\n";
	cin >> option;


	switch (option)
	{
	case 1:
	{
		int count2 = 0;
		cout << "enter your user id \n";
		cin >> w.id;

		for (auto j = user_list.begin(); j != user_list.end(); j++)
		{
			User u = *j;

			if (u.id == w.id)
			{
				cout << "\n\n your accout is found! \n";
				cout << "your password is:" << u.password << endl;
				system("pause");
				system("cls");
				return;
			}

		}


		cout << "sorry your account is not found \n";
		return;
		break;

	}
	case 2:
	{
		return;
		break;
	}
	default:
		cout << "wrong choice !! please try again\n";
		forgetpass();
		break;
	}
}

//customer-only methods

void User::buyerMenu()
{
	int choice;
	string name;
	product p;

	// we devide categories once the buyer logs in.
	p.make_categories();

	while (true) {
		cout << endl << "\t\t-----------------------------------------------------------------------" << endl;
		cout << "1. Search by name\n2. Categories\n3. View Cart\n4. Log out" << endl;
		cout << "Enter your choice: " << endl;

		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:

			//show whole stock.
			for (auto it = stock.begin(); it != stock.end(); ++it) {
				cout << "Name: " << it->second.name << "\t\tAverage Rate : " << it->second.avg_rate << "\t\tPrice: " << it->second.price << endl;
			
			}

			cout << "\nEnter Name of product: ";
			cin >> name;
			search(name);
			break;
		case 2:
			p.show_category();
			break;
		case 3:
			cartMenu();
			break;
		case 4:
			return;
			break;
		default:
			cout << "\t\t\t\t\tInvalid choice. Try again." << endl;
		}
	}
}

void User::cartMenu()
{
	int choice;
	string name;
	product p;
	int index;

	while (true) {

		//check if cart is empty.
		if (current_user->cart.empty()) {
			cout << "\t\t\t\t\t\tCart is empty." << endl;
			return;
		}

		cout << endl << "\t\t-----------------------------------------------------------------------" << endl;
		printCart();
		cout << "1. Change items quantities\n2. Remove an item from cart\n3. Empty cart\n4. Confirm buying\n0. Back to main menu" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;
		system("cls");
		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			printCart();
			cout << "Choose item number from above: ";
			cin >> index;
			if (index < 1 && index > current_user->cart.size()) { //validate user input
				cout << "Invalid choice!";
				break;
			}

			updateCart(index - 1);
			break;
		case 2:
			printCart();
			cout << "Choose item number from above: ";
			cin >> index;
			system("cls");
			if (index < 1 && index > current_user->cart.size()) { //validate user input
				cout << "Invalid choice!";
				break;
			}

			removeFromCart(index - 1);
			break;
		case 3:
			current_user->cart.clear();
			break;
		case 4:
			confirmBuying();
			break;
		default:
			cout << "\t\t\t\t\tInvalid choice. Try again." << endl;
		}
	}

}

void User::addToCart(product item)
{
	int choice;
	int amount;
	int cart_Item_ID = -1;
	product prdct;


	// check if item already exists in cart
	for (int i = 0; i < current_user->cart.size(); i++) {
		if (current_user->cart[i].id == item.id) {
			cart_Item_ID = i;
			break;
		}
	} 
	

	cout << "Available quantity in stock: " << item.quantity << endl << endl;
	cout << "Enter quantity you want to add to cart: ";
	cin >> amount;
	system("cls");

	//check if user enters quantity of 0
	if (amount == 0) {
		return;
	}

	//if item already exists sum new quantity to its already existing amount.
	if (cart_Item_ID != -1) {
		amount += current_user->cart[cart_Item_ID].quantity;
		current_user->cart[cart_Item_ID].quantity = amount;
	}

	//check if entered quantity bigger than quantity in stock.
	if (amount > item.quantity) {
		cout << "\t\t\t\tNot enough quantity in stock." << endl;
		return;
	}

	if (cart_Item_ID == -1) { //if product is new to cart.
		prdct.id = item.id;
		prdct.name = item.name;
		prdct.category = item.category;
		prdct.price = item.price;
		prdct.sellerId = item.sellerId;
		prdct.quantity = amount;
		current_user->cart.push_back(prdct);
	}


	cout << "Item added to cart" << endl
		<< "1)Confirm buying" << endl
		<< "2)Continue shopping.." << endl;
	cin >> choice;
	system("cls");

	if (choice == 1) {
		confirmBuying();
	}
	else if (choice == 2) {
		return;
	}
	else {
		cout << "Invalid choice";
	}
}

void User::removeFromCart(int index)
{
	current_user->cart.erase(current_user->cart.begin() + index);
}

void User::updateCart(int index)
{
	int count;
	cout << "Item quantity in cart: " << current_user->cart[index].quantity << endl;

	auto it = stock.find(current_user->cart[index].name);
	if (it != stock.end()) {
		cout << "Enter amount you want to update (from 0 to " << it->second.quantity << "): " << endl;
		cin >> count;
		system("cls");
		if (count > it->second.quantity) { //if quantity user enters is bigger than quantity in stock.
			cout << "No enough quantity in stock" << endl << endl;
			updateCart(index);
		}
		else { //amount maybe is correct

			current_user->cart[index].quantity = count;

			if (current_user->cart[index].quantity == 0) { //if amount of product in cart is 0 then remove it from cart.
				removeFromCart(index);
				cout << "Item removed from cart!" << endl;
				return;
			}
			cout << current_user->cart[index].name << " new quantity in cart: " << current_user->cart[index].quantity << endl;
		}
	}
	else
		cout << "Item not found in stock!" << endl;

}

void User::confirmBuying()
{
	string answer;
	product p;

	printCart();

	cout << "Buy (y/n)" << endl;
	cin >> answer;
	system("cls");

	if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
		//removes from stock
		for (int i = 0; i < current_user->cart.size(); i++)
		{
			p.removeProduct(current_user->cart[i].name, current_user->cart[i].quantity);
		}
		
		//empty cart.
		current_user->cart.clear();
	}
	else if (answer == "n" || answer == "N" || answer == "no" || answer == "No") {
		return;
	}
	else {
		confirmBuying();
	}
}

void User::printCart()
{
	current_user->total = 0;

	for (int i = 0; i < current_user->cart.size(); i++)
	{
		cout << i + 1 << ") Item: " << current_user->cart[i].name << "\t Price: " << current_user->cart[i].price << "\t Quantity: " << current_user->cart[i].quantity << endl;
		current_user->total += (current_user->cart[i].price * current_user->cart[i].quantity); //multiplied by quantity to give correct price.
	}
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Total price: " << current_user->total << endl << endl;

}

void User::search(string name)
{
	system("cls");
	string choice;
	auto it = stock.find(name);
	if (it != stock.end()) {
		cout << "Name: " << it->second.name << endl;
		cout << "Category: " << it->second.category << endl;
		cout << "Price: " << it->second.price << endl;
		cout << "Available Quantity: " << it->second.quantity << endl;
		cout << "Seller ID: " << it->second.sellerId << endl;

		cout << endl << endl;

		cout << "1) Add to cart\n2) Rate product\n3) continue shopping\n ";
		cin >> choice;
		system("cls");
		if (choice == "1")
		{
			addToCart(it->second);
		}
		else if (choice == "2") {
			addRating(&it->second);
			sys.avg_ratings(&it->second);
		}
		else
			return;
	}
	else
		cout << "Product Not Found!" << endl;


}

void User::addRating(product* prdct)
{
	float rating;

	while (true) {

		cout << "Enter rating for product '" << prdct->name << "' (out of 5): ";
		cin >> rating;

		if (rating >= 0 && rating <= 5) {
			prdct->ratings.push_back(rating);
			break;
		}
		else {
			cout << "Invalid rate, try again!" << endl;
		}

	}
}
