#include <iostream>
#include "User.h"
#include "Global.h"
#include "product.h"
#include <fstream>
using namespace std;

void Read_File();
void Write_File();

int main()
{
	Read_File();
	int choice1;
	User u1;
	
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
			u1.info("customer");
			//	system("cls");
		}
		else if (choice1 == 2)
		{
			u1.info("seller");
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
	user_list.clear();
	stock.clear();

	//--------------------------------------------userfile---------------------------------------//

	//Open file
	useerfile.open(useerfile_Path, ios::app | ios::in | ios::out | ios::binary | ios::ate);

	//Take the size of the Seller File and put it into a variable
	streampos userfile_size = useerfile.tellg();

	//create an array of strings with the size of the Seller File
	char* userfile_memblock = new char[userfile_size];

	//move the pointer to the begining of the Seller File
	useerfile.seekg(0, ios::beg);

	//put the data in memblock array 
	useerfile.read(userfile_memblock, userfile_size);

	//loop in the Seller File and push Data in the seller_vector
	long long userfile_byteindex = 0;
	while (userfile_byteindex < userfile_size)
	{
		User* u = (User*)(userfile_memblock + userfile_byteindex);
		user_list.push_back(*u);

		userfile_byteindex += sizeof(User);
	}

	useerfile.close();



	//intializing the static variable of autoid with the next available id.
	autoid = user_list.size();

	//---------------------------------------------productFile---------------------------------//
	//Open file
	productFile.open(productFile_Path, ios::app | ios::in | ios::out | ios::binary | ios::ate);

	//Take the size of the Seller File and put it into a variable
	streampos productFile_size = productFile.tellg();

	//create an array of strings with the size of the Seller File
	char* productFile_memblock = new char[productFile_size];

	//move the pointer to the begining of the Seller File
	productFile.seekg(0, ios::beg);

	//put the data in memblock array 
	productFile.read(productFile_memblock, productFile_size);

	//loop in the Seller File and push Data in the seller_vector
	long long productFile_byteindex = 0;
	product *p;
	while (productFile_byteindex < productFile_size)
	{
		p = (product*)(productFile_memblock + productFile_byteindex);
		stock[p->name] = *p;
		productFile_byteindex += sizeof(product);
	}
	productFile.close();
}

void Write_File()
{

	//Write user data
	useerfile.open(useerfile_Path, ios::out | ios::binary);
	for (auto it = user_list.begin(); it != user_list.end(); ++it) {
		useerfile.write((char*)& (*it), sizeof(*it));
	}
	useerfile.close();

	//write product data
	productFile.open(productFile_Path, ios::out | ios::binary);
	for (auto it = stock.begin(); it != stock.end(); ++it) {
		productFile.write((char*)&(it->second), sizeof(it->second));
	}
	productFile.close();

}


