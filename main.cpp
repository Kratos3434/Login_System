#include <iostream>
#include "User.h"
#include "App.h"
using namespace std;

int main() {
	cout << "Welcome to Login/Register App" << endl;
	cout << "=============================" << endl;
	cout << "Loading..." << endl;
	cout << "=============================" << endl;
	App app("users.csv");
	cout << "Number of users: " << app.numUsers() << endl;
	cout << "=============================" << endl;
	cout << "Running app..." << endl;
	cout << "=============================" << endl;
	app.run();
	return 0;
}