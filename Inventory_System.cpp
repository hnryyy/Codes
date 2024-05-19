#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <limits>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

// Product
struct Product{
	
	int id;
	string name;
	string category;
	float unit_price; 
	int quantity;
	float inventory_value;
	
};

bool isString(string input);
void loadProducts(Product*& products, string filename, int& id);
void add_record(Product*& products, int& id_, string filename);
void search_record(Product* products, int id_);
void display_records(Product* products, int id_, string filename);
void delete_record(string filename);
void exit_app();


int main(){
	
	Product* products = NULL;
	string filename = "products.txt";
	int choice;
	int id_ = 0;
	
	system("cls");

	do{

		loadProducts(products, filename, id_);

		while (true){

			system("cls");
			cout << "==============================================" << endl;
			cout << "    ByteHaven: Inventory Management System    " << endl;
			cout << "==============================================" << endl;
			cout << "1. Add New Product." << endl;
			cout << "2. Search for a Product." << endl;
			cout << "3. Display all Products." << endl;
			cout << "4. Delete Product Record." << endl;
			cout << "5. Exit." << endl;
			cout << "What would you like to do? ";
			
			if (cin >> choice){
				break;
			}

			else{
				system("cls");
				cout << "Invalid Input. Please only enter 1-5." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("pause");
			}

		}

		system("cls");

		switch(choice) {
			case 1:
				add_record(products, id_, filename);
				break;
			case 2:
				search_record(products, id_);
				break;
			case 3:
				display_records(products, id_, filename);
				break;
			case 4:
				delete_record(filename);
				break;
			case 5:
				exit_app();
				break;
			default:
				cout << "<!> Invalid Input. Please only enter 1-5. <!>" << endl;
				system("pause");
				break;
			}
			
	} while(choice != 5);

}

bool isString(string input){

	if (input.empty()){
		return false;
	}

	for (char c : input){
		if (!isalpha(c) && c != '_'){
			return false;
		}
	}

	return true;

}


void loadProducts(Product*& products, string filename, int& id) {

    ifstream file(filename);

    if (file.is_open()){

		id = 0;
        string line;
        int numProducts = 0;

        while (getline(file, line)) {
            numProducts++;
        }

        file.clear();
        file.seekg(0, ios::beg);

        products = new Product[numProducts];

        while (getline(file, line)) {

            stringstream iss(line);
            Product product;

            string item;
            getline(iss, item, ',');
            product.id = stoi(item);
            getline(iss, product.name, ',');
            getline(iss, product.category, ',');
            getline(iss, item, ',');
            product.unit_price = stof(item);
            getline(iss, item, ',');
            product.quantity = stoi(item);
            getline(iss, item, ',');
            product.inventory_value = stof(item);

            products[id] = product;
            id++;
        }

        file.close();
    } else {

        cerr << "Error: Unable to open file for reading." << endl;

    }

}

void add_record(Product*& products, int& id_, string filename){
	
	string choice;
	
	do {

		Product* temp = new Product[id_ + 1];

		for (int i = 0; i < id_; i++){
			temp[i] = products[i];
		}
		
		system("cls");
		cout << "----------------------------------------------" << endl;				
		cout << "\t\tAdd New Product				 \n";
		cout << "----------------------------------------------" << endl;
		cout << endl;

		temp[id_].id = id_;

		cout << "Product Name: ";
		cin.ignore();
		getline(cin, temp[id_].name);

		do {
			cout << "Category: ";
			getline(cin, temp[id_].category);

			if (!isString(temp[id_].category)){
				cout << "Invalid Input. Please enter a string only." << endl;
			}

		} while (!isString(temp[id_].category));

		while (true) {

			cout << "Unit Price: PHP ";

			if (cin >> temp[id_].unit_price) {
				if (temp[id_].unit_price > 0) {
					break;
				}
				else {
					cout << "Price should be more than 0.\n";
				}
			}
			else {
				cout << "Invalid. Please enter a positive integer only.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}

		while (true){

				cout << "Quantity: ";
			if (cin >> temp[id_].quantity) {
				if (temp[id_].quantity > 0) {
					break;
				}
				else {
					cout << "Quantity should be more than 0.\n";
				}
			}
			else {
				cout << "Invalid. Please enter a positive integer only.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}



		temp[id_].inventory_value = temp[id_].unit_price * temp[id_].quantity;

		ofstream file(filename, ios::app);

		if (file.is_open()) {
			file << temp[id_].id << "," << temp[id_].name << "," << temp[id_].category << "," << temp[id_].unit_price << "," << temp[id_].quantity << "," << temp[id_].inventory_value << endl;
			cout << "Product added successfully."; 
		}
		else {
			cerr << "Error: Unable to open the file.";
		}

		delete [] products;

		products = temp;

		id_++;

		do{
			cout << "\nDo you want to add another product? (Y/N) ";
			cin >> choice;

			if (!isString(choice)){
				cout << "Invalid Input. Please enter a string only." << endl;
			}

		} while (!isString(choice));
	} while (choice != "N" && choice != "n");	
	
}

void search_record(Product* products, int id_){
	
	system("cls");

	int choice;
	int id_input;
	string name_input;
	string category_input;
	
	do{	
		bool found = false;

		while (true){
			system("cls");
			cout << "----------------------------------------------" << endl;				
			cout << "\t    Search for a Product		 \n";
			cout << "----------------------------------------------" << endl;
			cout << "[1] ID" << endl;
			cout << "[2] Name" << endl;
			cout << "[3] Category" << endl;
			cout << "[4] Back to Main Menu." << endl;
			cout << "Search for: ";
			if (cin >> choice){
				break;
			}
			else{
				system("cls");
				cout << "Invalid Input. Please only enter 1-4." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("pause");
			}
		}

		system("cls");
		cout << "----------------------------------------------" << endl;				
		cout << "\t    Search for a Product		 \n";
		cout << "----------------------------------------------" << endl;

		switch(choice){
			case 1:
				while (true){
					cout << "Enter ID: ";
					if (cin >> id_input){
						break;
					}
					else{
						cout << "Invalid. Please enter a positive integer only.\n";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}

				system("cls");
				cout << "----------------------------------------------" << endl;				
				cout << "\t    Search for a Product		 \n";
				cout << "----------------------------------------------" << endl;
				cout << setw(5) << "ID" << setw(20) << "NAME" << setw(20) << "CATEGORY" << setw(20) << "UNIT PRICE" << setw(15) << "QUANTITY" << setw(20) << "INVENTORY VALUE" << endl;
				for (int i = 0; i < id_; i++){
					if (products[i].id == id_input){
						
						cout << setw(5)  << products[i].id << setw(20) << products[i].name << setw(20) << products[i].category << setw(20) << fixed << setprecision(2) << products[i].unit_price << setw(15) << products[i].quantity << setw(20) << products[i].inventory_value << endl;
						found = true;
						}
				}
				if (found == false){
					cout << "\nNo Product Found" << endl;
				}
				system("pause");
				break;

			case 2:
				cin.ignore();
				cout << "Enter Name: ";
				getline(cin, name_input);

				system("cls");
				cout << "----------------------------------------------" << endl;				
				cout << "\t    Search for a Product		 \n";
				cout << "----------------------------------------------" << endl;
				cout << setw(5) << "ID" << setw(20) << "NAME" << setw(20) << "CATEGORY" << setw(20) << "UNIT PRICE" << setw(15) << "QUANTITY" << setw(20) << "INVENTORY VALUE" << endl;
				for (int i = 0; i < id_; i++){
					if (products[i].name == name_input){
					
						cout << setw(5)  << products[i].id << setw(20) << products[i].name << setw(20) << products[i].category << setw(20) << fixed << setprecision(2) << products[i].unit_price << setw(15) << products[i].quantity << setw(20) << products[i].inventory_value << endl;
						found = true;
						}

				}
				if (found == false){
					cout << "\nNo Product Found" << endl;
				}
				system("pause");
				break;

			case 3:
				do{
					cin.clear();
					cin.ignore(10000,'\n');
					cout << "Enter Category: ";
					getline(cin, category_input);
	
					if (!isString(category_input)){
						cout << "Invalid Input. Please enter a string only." << endl;
					}

				} while (!isString(category_input));

				system("cls");
				cout << "----------------------------------------------" << endl;				
				cout << "\t    Search for a Product		 \n";
				cout << "----------------------------------------------" << endl;
				cout << setw(5) << "ID" << setw(20) << "NAME" << setw(20) << "CATEGORY" << setw(20) << "UNIT PRICE" << setw(15) << "QUANTITY" << setw(20) << "INVENTORY VALUE" << endl;
				for (int i = 0; i < id_; i++){
					if (products[i].category == category_input){
						cout << setw(5)  << products[i].id << setw(20) << products[i].name << setw(20) << products[i].category << setw(20) << fixed << setprecision(2) << products[i].unit_price << setw(15) << products[i].quantity << setw(20) << products[i].inventory_value << endl;
						found = true;
						}
				}

				if (found == false){
					cout << "\nNo Product Found" << endl;
				}
				system("pause");
				break;

			case 4:
				break;

			default:
				cout << "<!> Invalid Input. Please only enter 1-4. <!>" << endl;
				system("pause");
				break;
			
		};
				
	}while(choice != 4);

	
}

void display_records(Product* products, int id_, string filename){
	
    cout << "==============================================" << endl;
    cout << "          Displaying All Products            " << endl;
    cout << "==============================================" << endl;

	cout << setw(5) << "ID" << setw(20) << "NAME" << setw(20) << "CATEGORY" << setw(20) << "UNIT PRICE" << setw(15) << "QUANTITY" << setw(20) << "INVENTORY VALUE" << endl;

    for (int i = 0; i < id_; i++) {
        cout << setw(5)  << products[i].id << setw(20) << products[i].name << setw(20) << products[i].category << setw(20) << fixed << setprecision(2) << products[i].unit_price << setw(15) << products[i].quantity << setw(20) << products[i].inventory_value << endl;
	}

	system("pause");

}

void delete_record(string filename){
	
	ifstream inFile(filename);

	int id;

	while (true){
			cout << "Enter the ID that you want to remove: ";

			if (cin >> id){
				cout << "Product removed successfully.";
				break;
			}
			else{
				cout << "Invalid. Please enter a positive integer only.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

	string line;

	Product product;

	vector<string> lines;

	while (getline(inFile, line)){

		lines.push_back(line);

	}

	inFile.close();

	ofstream outFile(filename);

	for (int i = 0; i < lines.size(); i++){
		if (i != id){
			outFile << lines[i] << endl;
		}
	}

}

void exit_app(){
	
	cout << "==============================================" << endl;
	cout << "    ByteHaven: Inventory Management System    "<< endl;
	cout << "==============================================" << endl;
	cout << "Members:" << endl;
	cout << "Suntay, Christian Jacob D. (L)" << endl;
	cout << "Garcia, Wayne Andrei (A)" << endl;
	cout << "Asunio, Daniah G." << endl;
	cout << "Dacalan, Paul Henry M." << endl;
	cout << "Pastorfide, Johan C." << endl;

}
