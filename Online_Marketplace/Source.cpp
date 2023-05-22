#include <iostream>
#include "User.h"
#include "Global.h"
#include "product.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
void Read_File();
void Write_File();


int main()
{

	Read_File();
	int choice1;
	User u1;

	//intializing categories vector.
	vector<product*> category;
	category_vector.push_back(category); //phones
	category_vector.push_back(category); //electornics
	category_vector.push_back(category); //fashion
	category_vector.push_back(category); //others


	while (true) {
		cout << "\t\t\t\t--------------------------------------------------\n\n\n";
		cout << "\t\t\t\t                      welcome                      \n\n\n";
		cout << "\t\t\t\t--------------------------------------------------\n\n";
		cout << "press 1 to enter as a customer-> \n\n";
		cout << "press 2 to enter as a seller-> \n\n";
		cout << "press 3 to exit-> \n\n";
		cout << "please enter your choice: ";
		cin >> choice1;
		system("cls");
		cout << endl;

		if (choice1 == 1)
		{
			u1.selector_page("customer");
			//	system("cls");
		}
		else if (choice1 == 2)
		{
			u1.selector_page("seller");
			//	system("cls");
		}
		else if (choice1 == 3)
		{
			break;
		}
		else
			cout << "wrong choice please try again\n\n";

	}
	Write_File();

	return 0;
}

void Read_File()
{
	//make sure data structure are empty.
	user_list.clear();
	stock.clear();

	//--------------------------------------------userFile--------------------------------------------//

	nlohmann::json json_useerfile;

	useerfile.open(useerfile_Path, ios::in);

	if (!useerfile) { //if file doesn't exist for example: do not read and continue to program.
		return;
	}

	string users_content((istreambuf_iterator<char>(useerfile)), istreambuf_iterator<char>());
	json_useerfile = nlohmann::json::parse(users_content);


	for (auto json_user = json_useerfile.begin(); json_user != json_useerfile.end(); ++json_user) {

		User u; //create an instance of type User to fill its data and push it back to the user_list.

		u.id = (*json_user)["id"];
		u.name = (*json_user)["name"];
		u.password = (*json_user)["password"];
		u.email = (*json_user)["email"];
		u.type = (*json_user)["type"];
		u.phone = (*json_user)["phone"];
		u.total = (*json_user)["total"];
		u.address = (*json_user)["address"];

		for (auto json_product = (*json_user)["cart"].begin(); json_product != (*json_user)["cart"].end(); ++json_product) {
			product p; //create an instance of type product to fill its data and push it back to the cart.
			p.id = (*json_product)["id"];
			p.name = (*json_product)["name"];
			p.category = (*json_product)["category"];
			p.price = (*json_product)["price"];
			p.sellerId = (*json_product)["sellerId"];
			p.quantity = (*json_product)["quantity"];
			p.avg_rate = (*json_product)["avg_rate"];

			for (auto json_rating = (*json_product)["ratings"].begin(); json_rating != (*json_product)["ratings"].end(); ++json_rating) {
				p.ratings.push_back(*json_rating); // pushing every rating to the rating vector of product p.
			}

			u.cart.push_back(p); // pushing every product to the cart vector of user u.
		}

		user_list.push_back(u); //pushing the new user to user_list.
	}

	useerfile.close();

	//intializing the static variable of autoid with the next available id.
	autoid = user_list.size();




	//---------------------------------------------productFile---------------------------------//

	nlohmann::json json_productFile;
	productFile.open(productFile_Path, ios::in);

	if (!productFile) {

		return;
	}

	string products_content((istreambuf_iterator<char>(productFile)), istreambuf_iterator<char>());
	json_productFile = nlohmann::json::parse(products_content);

	for (auto json_product = json_productFile.begin(); json_product != json_productFile.end(); ++json_product) {
		product p;
		p.id = (*json_product)["id"];
		p.name = (*json_product)["name"];
		p.category = (*json_product)["category"];
		p.price = (*json_product)["price"];
		p.sellerId = (*json_product)["sellerId"];
		p.quantity = (*json_product)["quantity"];
		p.avg_rate = (*json_product)["avg_rate"];

		for (auto json_rating = (*json_product)["ratings"].begin(); json_rating != (*json_product)["ratings"].end(); ++json_rating) {
			p.ratings.push_back(*json_rating); // pushing every rating to the rating vector of product p.
		}

		stock[p.name] = p;

	}
	productFile.close();

}

void Write_File()
{

	//------------------------------------------ WRITE USER DATA ---------------------------------------------//

	//created a json object to handle writing vectors like "cart" and "ratings" proberly.
	nlohmann::json json_useerfile_data;

	for (auto it = user_list.begin(); it != user_list.end(); ++it) {
		nlohmann::json user_json;
		user_json["id"] = it->id;
		user_json["name"] = it->name;
		user_json["password"] = it->password;
		user_json["email"] = it->email;
		user_json["type"] = it->type;
		user_json["address"] = it->address;                       //add it later.
		user_json["phone"] = it->phone;


		// Convert the cart vector of objects to a JSON array
		nlohmann::json cart_array;
		for (auto product = it->cart.begin(); product != it->cart.end(); ++product) {
			nlohmann::json product_json;

			product_json["id"] = product->id;
			product_json["name"] = product->name;
			product_json["category"] = product->category;
			product_json["price"] = product->price;
			product_json["sellerId"] = product->sellerId;
			product_json["quantity"] = product->quantity;
			product_json["ratings"] = product->ratings;
			product_json["avg_rate"] = product->avg_rate;
			cart_array.push_back(product_json);
		}

		user_json["cart"] = cart_array;
		user_json["total"] = it->total;

		json_useerfile_data.push_back(user_json);
	}

	useerfile.open(useerfile_Path, ios::out);

	if (!useerfile.is_open()) {
		cout << "Couldn't store data";
		useerfile.close();
		return;
	}

	useerfile << json_useerfile_data.dump(4);
	useerfile.close();

	//------------------------------------------ WRITE PRODUCT DATA ---------------------------------------------//

	//created a json object to handle writing vectors like "cart" and "ratings" proberly.
	nlohmann::json json_productFile;

	for (auto product = stock.begin(); product != stock.end(); ++product) {
	//create a json object to serialize every product from stock	
		nlohmann::json product_json;
		product_json["id"] = product->second.id;
		product_json["name"] = product->second.name;
		product_json["category"] = product->second.category;
		product_json["price"] = product->second.price;
		product_json["sellerId"] = product->second.sellerId;
		product_json["quantity"] = product->second.quantity;
		product_json["ratings"] = product->second.ratings;
		product_json["avg_rate"] = product->second.avg_rate;

		//push every new product to the json productfile data obj.
		json_productFile.push_back(product_json);
	}

	productFile.open(productFile_Path, ios::out);

	if (!productFile.is_open()) {
		cout << "Couldn't store data";
		productFile.close();
		return;
	}

	productFile << json_productFile.dump(4);
	productFile.close();

}


