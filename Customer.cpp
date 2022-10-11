#include "Customer.h"

/**
 * Default constructor initializes customer ID, first name, last name, movies 
 * borrowed count, node pointer to next customer in linked list chain to default 
 * values.
 */
Customer::Customer() : customerID(0), firstName(""), lastName(""), movieBorrowCount(0), nextCustomer(nullptr) {}

/**
 * Initializes customer ID, first name, and last name to values specified in 
 * parameter arguments. Movies borrowed count and node pointer to next Customer in 
 * linked list chain assigned to default values, 0 and nullptr, respectively.
 * 
 * @param customerID - The unique integer identifying the customer
 * @param firstName - The first name of the customer
 * @param lastName - The last name of the customer
 */
Customer::Customer(int customerID, string firstName, string lastName) : customerID(customerID), firstName(firstName), lastName(lastName), movieBorrowCount(0), nextCustomer(nullptr) {}

/**
 * Destructor calls helper that deletes all Customer objects in linked chain 
 * pointed to by "nextCustomer".
 */
Customer::~Customer() {

	deletionHelper(nextCustomer);
}

/**
 * Deletes all Customer objects in linked chain pointed to by "nextCustomer".
 *
 * @param customer - Pointer to Customer object to be deleted
 */
void Customer::deletionHelper(Customer *customer) {

	if(customer != nullptr) {

		if(customer->getNextCustomer() == nullptr) {

			delete(customer);
			customer = nullptr;
			return;
		}
		else {

			deletionHelper(customer->getNextCustomer());
			delete(customer);
			customer = nullptr;
 		}
	}
}

/**
 * Gets the the customer's ID number.
 *
 * @return The customer's ID number
 */
int Customer::getCustomerID() {

	return customerID;
}

/**
 * Gets the customer's last name.
 *
 * @return The customer's last name
 */
string Customer::getLastName() {

	return lastName;
}

/**
 * Gets the customer's first name.
 * 
 * @return The customer's first name
 */
string Customer::getFirstName() {

	return firstName;
}

/**
 * Gets the status of whether the customer's member attributes have been 
 * initialized.
 *
 * @return The empty status of the customer's member attributes
 */
bool Customer::isEmpty() {

	return customerID == 0 && lastName == "" && firstName == "" && movieBorrowCount == 0 && nextCustomer == nullptr;
}

/**
 * Prints to standard output the list of all transactions made by the 
 * customer. Customer's transactions are all stored in member vector 
 * "customerTransactions".
 */
void Customer::printCustomerTransactions() {

	if(customerTransactions.begin() != customerTransactions.end()) {

		vector<string>::iterator it = customerTransactions.end();
		--it;
		for(; it != customerTransactions.begin(); --it) {

			cout << *it << endl;
		}
		cout << *it << endl;
	}
	else {

		cout << "This customer has made no transactions." << endl;
 	}
}

/**
 * Adds customer transaction to member string vector.
 *
 * @param transaction - The customer transaction to be added.
 */
void Customer::addTransaction(string transaction) {

	customerTransactions.push_back(transaction);
}

/**
 * Gets the number of movies borrowed by customer.
 * 
 * @return The number of movies borrowed by customer
 */
int Customer::getMovieBorrowCount() {

	return movieBorrowCount;
}

/**
 * Increments the customer movie borrow count.
 */
void Customer::incrementBorrowCount() {

	movieBorrowCount++;
}

/**
 * Decrements the customer movie borrow count.
 */
void Customer::decrementBorrowCount() {

	movieBorrowCount--;
}

/**
 * Assigns the member Customer pointer to next Customer object in the linked 
 * list chain.
 * 
 * @param nextCustomerInLine - A Customer pointer to the next Customer in linked list chain
 */
void Customer::setNextCustomer(Customer *nextCustomerInLine) {

	this->nextCustomer = nextCustomerInLine;
}

/**
 * Gets the next Customer in linked list chain.
 *
 * @return The next Customer in the linked list chain
 */
Customer* Customer::getNextCustomer() {

	return nextCustomer;
}

/**
 * Gets the equality status of the current Customer object ID and the 
 * parameter argument Customer object ID.
 * 
 * @param customer - The Customer object to be compared to.
 *
 * @return The equality status of the current Customer ID and the parameter argument Customer's Customer ID
 */
bool Customer::operator==(Customer &customer) {

	if(customerID == customer.customerID) {

		return true;
	}
	return false;
}
