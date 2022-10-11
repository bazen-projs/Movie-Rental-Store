#include <iostream>
#include <vector>

using namespace std;

class Customer {

private:

	// unique identifier for a customer
	int customerID;

	// customer's first name
	string firstName;

	// customer's last name
	string lastName;

	// vector list of all transactions made by customer
	vector<string> customerTransactions;

	// number of movies customer has borrowed
	int movieBorrowCount;

	// pointer to next customer at a given index within customer hash table via seperate chaining,
	// if new customer hashed to identical index in table.
	Customer *nextCustomer;

public:

	// Customer default constructor
	Customer();

	// Customer constructor assigns members fields to parameter values
	Customer(int customerID, string firstName, string lastName);

	// Customer destructor - deletes all customers in chain
	~Customer();

	// helper function aids in deletion of all customers in linked-list chain
	void deletionHelper(Customer*);

	// getter for customer ID
	int getCustomerID();

	// getter for customer last name
	string getLastName();

	// getter for customer first name
	string getFirstName();

	// add customer transaction to customer transaction vector list
	void addTransaction(string transaction);

	// print all customer transactions conducted thus far
	void printCustomerTransactions();

	// evaluates whether the Customer object is "empty" (constructed via default constructor, with all member field values still set to default values)
	bool isEmpty();

	// getter for customer movie borrow count
	int getMovieBorrowCount();

	// increments the borrow count for customer
	void incrementBorrowCount();

	// decrements the borrow count for customer
	void decrementBorrowCount();

	// setter for the next customer in the linked-list hash table chain
	void setNextCustomer(Customer*);

	// getter for the next customer pointer in linked-list seperate chaining hash table chain
	Customer* getNextCustomer();

	// evaluates the equality of the current Customer object with the parameter Customer object
	bool operator==(Customer&);
};