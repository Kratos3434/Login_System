#ifndef AUTH_H
#define AUTH_H

#include "User.h"
#include <iostream>
#include <string>
#include <limits>

class Auth
{
	User **users;
	size_t num_users{0};

	bool verifyLogin(std::string email, std::string password) const
	{
		for (size_t i = 0; i < num_users; i++)
		{
			if (users[i]->getEmail() == email)
			{
				if (users[i]->getPassword() == password)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool saveUser(std::string firstName, std::string lastName, std::string email, std::string password) const
	{
		std::ofstream ofs("users.csv", std::ios::out | std::ios::app);
		ofs << firstName << "," << lastName << "," << email << "," << password << std::endl;
		return true;
	}

	bool exitor(std::string var) const
	{
		if (var == "y")
		{
			return true;
		}
		return false;
	}

public:
	Auth(User **users, size_t num_users)
	{
		this->users = users;
		this->num_users = num_users;
	}

	bool login() const
	{
		bool loginSuccess = false;
		std::cout << "\n=====================\n";
		std::cout << "Login\n";
		std::cout << "=====================\n";
		std::cout << "You can exit anytime by entering: y\n";
		std::string email;
		std::string password;

		do
		{
			std::cout << "Email: ";
			std::cin >> email;
			if (email == "y")
				return false;
			std::cout << "Password: ";
			std::cin >> password;
			std::cout << "\n";
			if (password == "y")
				return false;
			if (verifyLogin(email, password))
			{
				loginSuccess = true;
			}
			else
			{
				std::cout << "Email or password is incorrect, please try again\n\n";
			}
		} while (!loginSuccess);

		return loginSuccess;
	}

	// todo: Implement signup
	bool signup() const
	{
		bool success = false;
		do
		{
			std::string firstName, lastName, email, password, password2;
			std::cout << "\n====================\n";
			std::cout << "Register\n";
			std::cout << "====================\n";
			std::cout << "Enter \'y\' to abort anytime\n";
			std::cout << "====================\n";
			std::cout << "First Name: ";
			std::cin >> firstName;
			if (exitor(firstName))
				return false;
			std::cout << "Last Name: ";
			std::cin >> lastName;
			if (exitor(lastName))
				return false;
			std::cout << "Email: ";
			std::cin >> email;
			if (exitor(email))
				return false;
			std::cout << "Password: ";
			std::cin >> password;
			if (exitor(password))
				return false;
			do
			{
				std::cout << "Confirm Password: ";
				std::cin >> password2;
				if (exitor(password2))
					return false;
				if (password2 != password)
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Passwords do not match\n";
				}
			} while (password2 != password);
			success = true;
			if (success)
			{
				saveUser(firstName, lastName, email, password);
			}
		} while (!success);
		return success;
	}
};

#endif // !AUTH_H