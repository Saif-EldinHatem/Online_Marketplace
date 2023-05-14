#pragma once
#include <vector>
#include <unordered_map>
#include "User.h"
#include "product.h"
#include <list>

using namespace std;

//file paths
inline string useerfile_Path = "Data/users.bin";
inline string productFile_Path = "Data/stock.bin";
inline fstream useerfile;
inline fstream productFile;

//global user
inline int autoid;

//list of users
inline list<User> user_list;

inline User* current_user;

//products stock
inline unordered_map<string, product> stock;

//category lists
inline vector <product*> phones;
inline vector <product*> electronics;
inline vector <product*> fashion;
inline vector <product*> others;



