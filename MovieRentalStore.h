#include "BSTArray.h"
#include "Movie.h"
#include "Customer.h"

using namespace std;

// A movie rental store system
class MovieRentalStore {

public:

	// map containing an array of Movie pointers for each customer ID associated with
	// a customer that borrowed one or more movies
	map<int, Movie**> moviesBorrowedByCustomers;

	// the maximum number of customers currently supported by the movie rental store
	const int maxNumberofCustomers = 5000;

	// the customer hash table
	Customer *customers = new Customer[maxNumberofCustomers];

	// the maximum number of borrowed movies allowed for a given customer at a given point of time
	const int defaultMaxCustMovieLimit = 13;

	// movie inventories for each of the genres supported/carried
	ArrayBasedBSTree<Comedy> comedyMovieInventory;
	ArrayBasedBSTree<Drama> dramaMovieInventory;
	ArrayBasedBSTree<Classics> classicsMovieInventory;

	// generates a hash code (via digit folding) for a given customer ID passed as first argument
	int getHashCode(int, int);

	// adds a customer to the customer hash table
	void addCustomer(Customer *);

	// finds a customer given customer, via their customer id
	bool findCustomer(int);

	// adds a customer transaction to their customer transaction history
	bool addTransaction(string, int);

	// prints all transactions a given customer (via their ID) has executed
	bool printCustomerTransHistory(int);

	// initialize a customer's (via their ID) borrow list. generates an entry in the map for the
	// customer and allocates movie pointer array of size "defaultMaxCustMovieLimit"
	bool initializeCustomerBorrowList(int);

	// add to customer's (via their ID) borrow list in the event they execute a borrow command
	bool addToCustomersBorrowList(Movie *, int);

	// evaluates whether a given customer's (via their ID) borrow list is empty
	bool customerBorrowListEmpty(int);

	// remove from customer's (via their ID) borrow list in the event they execute a return command
	bool removeFromCustomerList(Movie *, int);

	// clear customer's (via their ID) borrow list
	void clearCustMovieBorrowData();

	// prints to cout each genre's movie inventory - executed when "I"/Inventory command is executed
	void outputStoreInventory();

	// constructs a movie of Comedy and Drama type from stringstream parameters
	bool DefaultMovieFactory(stringstream&, char);

	// constructs a movie of Classics type from stringstream parameters
	bool ClassicMovieFactory(stringstream&);

	// fills the customer hash table with all existing customers as listed from customer text file.
	// argument is directory to customer text file.
	bool scanCustomerFile(string);

	// fills the movie BSTree with all valid movies as listed within movie text file.
	// argument is directory to movie text file.
	bool scanMovieFile(string);

	// executes valid commands on database (MovieRentalStore data) as listed in command text file.
	// argument is directory to command text file.
	bool scanCommandFile(string);

	// helper function for borrow/return commands - initiates modification of inventory/borrow list (specifically for Classics movies)
	bool borrowReturnCommandClassicsHelper(stringstream &, int, bool);

	// helper function for borrow/return commands - initiates modification of inventory/borrow list (specifically for Drama movies)
	bool borrowReturnCommandDramaHelper(stringstream &, int, bool);

	// helper function for borrow/return commands - initiates modification of inventory/borrow list (specifically for Comedy movies)
	bool borrowReturnCommandComedyHelper(stringstream &, int, bool);

	// executes borrow/return command when invoked by command handling function
	bool handleBorrowReturnCommand(stringstream&, bool);

	// prints all movies borrowed by a given customer (via their ID)
	bool printCustomerBorrowList(int);

public:

	// MovieRentalStore constructor - calls the three file processing functions to set up database
	// and execute commands on said database
	MovieRentalStore(string, string, string);

	// MovieRentalStore destructor - deletes customer hash table and borrow lists within map if present
	~MovieRentalStore();
};