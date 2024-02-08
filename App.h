#ifndef APP_H
#define APP_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "User.h"
#include "Auth.h"
#include <limits>

class App
{
	User **users{nullptr};
	Auth *auth{nullptr};
	size_t num_users{0};

	void loadUsers(const char *fileName)
	{
		deallocate();
		std::ifstream ifs(fileName);
		std::string line;
		while (std::getline(ifs, line))
		{
			num_users++;
		}

		ifs.close();
		ifs.open(fileName);
		users = new User *[num_users + 1];
		for (size_t i = 0; i < num_users; i++)
		{
			users[i] = nullptr;
		}
		std::vector<std::string> row;
		std::string word, temp;
		size_t cnt = 0;
		while (ifs)
		{
			row.clear();
			std::getline(ifs, line);
			std::stringstream s(line);
			while (std::getline(s, word, ','))
			{
				row.push_back(word);
			}
			if (row.size() > 0)
				users[cnt] = new User(row[0], row[1], row[2], row[3]);
			cnt++;
		}
		auth = new Auth(users, num_users);
	}

	void deallocate()
	{
		delete auth;
		auth = nullptr;
		for (size_t i = 0; i < num_users; i++)
		{
			delete users[i];
		}
		delete[] users;
		users = nullptr;
	}

public:
	App(const char *fileName)
	{
		loadUsers(fileName);
	}

	~App()
	{
		deallocate();
	}

	void run()
	{
		int choice = -1;
		do
		{
			bool successInput = false;
			std::cout << "Please enter a choice\n";
			std::cout << "=====================\n";
			std::cout << "1. Login\n";
			std::cout << "2. Register\n";
			std::cout << "0. Exit\n";
			std::cout << "=====================\n";
			do
			{
				std::cout << "> ";
				std::cin >> choice;
				if (std::cin)
				{
					successInput = true;
				}
				else
				{
					std::cout << "Invalid input, please try again\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			} while (!successInput);

			switch (choice)
			{
			case 1:
				std::cout << "You chose login\n";
				auth->login() ? std::cout << "Login successful\n" : std::cout << "Login failed\n";
				break;
			case 2:
				std::cout << "You chose Register\n";
				if (auth->signup())
				{
					loadUsers("users.csv");
					auth->login() ? std::cout << "Login successful\n" : std::cout << "Login failed\n";
				}
				else
				{
					std::cout << "Register Failed :(\n";
				}
				break;
			case 0:
				std::cout << "Exiting app..." << std::endl;
				break;
			default:
				std::cout << "Please enter a number between 0-2\n";
				break;
			}

		} while (choice != 0);
	}
	size_t numUsers() const
	{
		return num_users;
	}
};

#endif //! APP_H