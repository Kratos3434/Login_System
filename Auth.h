#ifndef AUTH_H
#define AUTH_H

#include "User.h"
#include <iostream>
#include <string>

class Auth {
	User** users;
	size_t num_users{0};

	bool verifyLogin(std::string email, std::string password) const {
		for (size_t i = 0; i < num_users; i++) {
			if (users[i]->getEmail() == email) {
				if (users[i]->getPassword() == password) {
					return true;
				}
			}
		}
		return false;
	}
public:
	Auth(User** users, size_t num_users) {
		this->users = users;
		this->num_users = num_users;
	}

	bool login() const {
		bool loginSuccess = false;
		std::cout << "=====================\n";
		std::cout << "Login\n";
		std::cout << "=====================\n";
		std::cout << "You can exit anytime by entering: y\n";
		std::string email;
		std::string password;

		do {
			std::cout << "Email: ";
			std::cin >> email;
			if (email == "y") return false;
			std::cout << "Password: ";
			std::cin >> password;
			std::cout << "\n";
			if (password == "y") return false;
			//todo: Check if email is valid and or password
			if (verifyLogin(email, password)) {
				loginSuccess = true;
			}
			else {
				std::cout << "Email or password is incorrect, please try again\n\n";
			}
		} while (!loginSuccess);

		return loginSuccess;
	}

	//todo: Implement signup
	bool signup() const {
		bool success = false;
		return success;
	}
};

#endif // !AUTH_H

