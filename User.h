#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
	std::string firstName;
	std::string lastName;
	std::string email;
	std::string password;
public:
	User() {};

	User(std::string firstName, std::string lastName, std::string email, std::string password) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->email = email;
		this->password = password;
	}

	std::string getEmail() const {
		return email;
	}

	std::string getPassword() const {
		return password;
	}

	void setFirstName(std::string firstName) {
		this->firstName = firstName;
	}

	void setLastName(std::string lastName) {
		this->lastName = lastName;
	}

	void setEmail(std::string email) {
		this->email = email;
	}

	void setPassword(std::string password) {
		this->password = password;
	}

	void display(std::ostream& os) const {
		os << "First Name: " << firstName << std::endl;
		os << "Last Name: " << lastName << std::endl;
		os << "Email: " << email << std::endl;
	}
};

#endif //!USER_H
