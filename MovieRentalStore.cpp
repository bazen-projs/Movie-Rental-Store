#include "MovieRentalStore.h"

/**
  * Constructor calls functions to read files at directories specified by string arguments.
  *
  * @param movieFile - The directory of the movie file, listing all movies to be added to inventory
  * @param customerFile - The directory of the customer file, listing all customer to be added to database
  * @param commandFile - The directory of the command file, listing all commands to be acted on the database
  */
MovieRentalStore::MovieRentalStore(string movieFile, string customerFile, string commandFile) {

	// open and scan the movie file via it's directory, print error in failure
	if(!scanMovieFile(movieFile)) {

		cout << "Won't read customer and command files." << endl;
		return;
	}
	// open and scan the customer file via it's directory, print error in failure
	if(!scanCustomerFile(customerFile)) {

		cout << "Won't read command file." << endl;
		return;
	}
	// open and scan the command file via it's directory, print error in failure
	cout << "------------------------------Commands Begin------------------------------" << endl;
	scanCommandFile(commandFile);
}

/**
  * Destructor deallocates memory associated with object. Customer array and movie pointer array
  * for each customer in customer-movie borrow map are explicitly deleted.
  */
MovieRentalStore::~MovieRentalStore() {

	delete[] customers;
	clearCustMovieBorrowData();
}

/**
  * Generates hash code for given integer value and hash table size.
  * Hash function uses digit folding method. Used to generate hash value for
  * customer IDs.
  *
  * @param key - The value to be transformed into a hash key
  * @param hashTableSize - The size of the hash table
  *
  * @return The hash value for the key provided
  */
int MovieRentalStore::getHashCode(int key, int hashTableSize) {

	string keyString = to_string(key);
	int numberOfDigitsInTableSizeOneLess = log10(hashTableSize - 1) + 1;
	int hashCode = 0;
	int keyStringLength = keyString.length();
	int iterations = keyStringLength / numberOfDigitsInTableSizeOneLess;
	int index = 0;
	for(int i = 0; i < iterations; i++, index+=numberOfDigitsInTableSizeOneLess) {

		hashCode += stoi(keyString.substr(index, numberOfDigitsInTableSizeOneLess));
		if((index + numberOfDigitsInTableSizeOneLess)/numberOfDigitsInTableSizeOneLess >= iterations && (index + numberOfDigitsInTableSizeOneLess < keyStringLength)) {

			hashCode += stoi(keyString.substr(index+numberOfDigitsInTableSizeOneLess));
		}
	}
	if(iterations == 0) {

		hashCode += key;
	}
	return hashCode % hashTableSize;
}

/**
  * Adds customer to customer array. If hash value for customer is already occupied in hash table
  * add to seperate chained linked list at given index. Rejects customers with IDs matching
  * customer preexisting in database.
  *
  * @param customer - The customer to be added to array database
  */
void MovieRentalStore::addCustomer(Customer *customer) {

	int custIndex = getHashCode(customer->getCustomerID(), maxNumberofCustomers);
	if(customers[custIndex].isEmpty()) {

		customers[custIndex] = *customer;
		cout << "Customer added successfully (ID, First Name, Last Name): " << customers[custIndex].getCustomerID() << ", " << customers[custIndex].getFirstName() << ", " << customers[custIndex].getLastName() << endl;
		delete(customer);
	}
	else {

		Customer *nextCustomer = &customers[custIndex];
		while(nextCustomer->getNextCustomer() != nullptr) {

			if(*nextCustomer == *customer) {

				cout << "Customer with ID - " << nextCustomer->getCustomerID() << " is already in database." << endl;
				delete(customer);
				return;
			}
			nextCustomer = nextCustomer->getNextCustomer();
		}
		if(*nextCustomer == *customer) {

			cout << "Customer with ID - " << nextCustomer->getCustomerID() << " is already in database." << endl;
			delete(customer);
			return;
		}
		nextCustomer->setNextCustomer(customer);
		cout << "Customer added successfully (ID, First Name, Last Name): " << customer->getCustomerID() << ", " << customer->getFirstName() << ", " << customer->getLastName() << endl;
	}
}

/**
  * Searches for the argument customer in the customer array.
  *
  * @param custID - The customer ID of the customer to be searched for in database array
  *
  * @return The success status of the customer search
  */
bool MovieRentalStore::findCustomer(int custID) {

	// generates hash value for customer ID
	int custIndex = getHashCode(custID, maxNumberofCustomers);

	// checks if index for customer hash value in array is empty
	if(customers[custIndex].isEmpty()) {

		return false;
	}
	else {

		// search through the linked-list chain within taken customer index slot
		Customer *nextCustomer = &customers[custIndex];
		if(nextCustomer->getCustomerID() == custID) {

			return true;
		}
		while(nextCustomer->getNextCustomer() != nullptr) {

			if((nextCustomer->getNextCustomer())->getCustomerID() == custID) {

				return true;
			}
			nextCustomer = nextCustomer->getNextCustomer();
		}
		return false;
	}
}

/**
  * Adds a customer transaction to the customer's (identified by their ID), vector list of transactions.
  *
  * @param transaction - The transaction to be added to customer vector list
  * @param custID - The ID of customer adding a transaction
  * 
  * @return The success status of the transaction insertion
  */
bool MovieRentalStore::addTransaction(string transaction, int custID) {

	// if customer exists, search for them through array and invoke their associated
        // "addTransaction" function
	if(findCustomer(custID)) {

		int custIndex = getHashCode(custID, maxNumberofCustomers);
		Customer *customer = &customers[custIndex];
		if(customer->getCustomerID() == custID) {

			customer->addTransaction(transaction);
		}
		else {

			while(customer->getNextCustomer() != nullptr) {

				if(customer->getNextCustomer()->getCustomerID() == custID) {

					customer->getNextCustomer()->addTransaction(transaction);
					return true;
				}
				customer = customer->getNextCustomer();
			}
			cout << "Transaction could not be logged for this customer. Customer not found." << endl;
		}
	}
	return false;
}

/**
  * Prints the vector list of transactions associated with the customer ID passed as argument.
  *
  * @param custID - The ID of the customer who's transactions are being printed
  *
  * @return The success status of the transaction output (only fails if customer not found)
  */
bool MovieRentalStore::printCustomerTransHistory(int custID) {

	int custIndex;
	if(findCustomer(custID)) {

		custIndex = getHashCode(custID, maxNumberofCustomers);
		if(customers[custIndex].getCustomerID() == custID) {

			cout << "Printing transactions of customer with cust ID: " << custID << endl;
			customers[custIndex].printCustomerTransactions();
			return true;
		}
		else {

			Customer *nextCustomer = &customers[custIndex];
			while(nextCustomer->getNextCustomer() != nullptr) {

				if(nextCustomer->getNextCustomer()->getCustomerID() == custID) {

					cout << "Printing transactions of customer with cust ID: " << custID << endl;
					nextCustomer->getNextCustomer()->printCustomerTransactions();
					return true;
				}
				nextCustomer = nextCustomer->getNextCustomer();
			}
		}
	}
	return false;
}

/**
  * Initializes the borrow list of a given argument customer to nullptr.
  *
  * @param custID - The ID of the customer who's having their borrow list initialized
  *
  * @return The success status of the borrow list initialization (only fails if customer not found)
  */
bool MovieRentalStore::initializeCustomerBorrowList(int custID) {

	if(!findCustomer(custID)) {

		return false;
	}
	Movie **customerMovieArray = new Movie*[defaultMaxCustMovieLimit];
	moviesBorrowedByCustomers[custID] = customerMovieArray;
	for(int i = 0; i < defaultMaxCustMovieLimit; i++) {

		moviesBorrowedByCustomers[custID][i] = nullptr;
	}
	return true;
}

/**
  * Add argument movie to customer borrow list.
  *
  * @param custID - The ID of the customer who's adding a movie to their borrow list
  *
  * @return The success status of the borrow list insertion (only fails if customer not found
  * or customer has already borrowed the max number of movies - 13)
  */
bool MovieRentalStore::addToCustomersBorrowList(Movie *movie, int custID) {

	if(moviesBorrowedByCustomers.find(custID) == moviesBorrowedByCustomers.end()) {

		if(!initializeCustomerBorrowList(custID)) {

			cout << "Customer with ID: " << to_string(custID) << " cannot borrow. They are not in the database." << endl;
			return false;
		}
	}
	for(int i = 0; i < defaultMaxCustMovieLimit; i++) {

		if(moviesBorrowedByCustomers[custID][i] == nullptr) {

			moviesBorrowedByCustomers[custID][i] = movie;
			return true;
		}
	}
	cout << "Customer with ID: " << custID << " has the max number of movies borrowed." << endl;
	return false;
}

/**
  * Verifies if customer borrow list is empty.
  *
  * @param custID - The ID of the customer who's borrow list is being evaluated
  *
  * @return The status of whether the borrow list is empty
  */
bool MovieRentalStore::customerBorrowListEmpty(int custID) {

	int counter = 0;
	for(int i = 0; i < defaultMaxCustMovieLimit; i++) {

		if(moviesBorrowedByCustomers[custID][i] == nullptr) {

			counter++;
		}
	}
	return (counter == defaultMaxCustMovieLimit);
}

/**
  * Remove argument movie from argument customer's borrow list.
  *
  * @param movie - The movie being removed from customer's borrow list
  * @param custID - The ID of the customer who's removing a movie from their borrow list
  *
  * @return The success status of the borrow list removal
  */
bool MovieRentalStore::removeFromCustomerList(Movie *movie, int custID) {

	// checks if movie is nullptr or empty (default constructed) movie. Also checks movie borrow map to evaluate if
        // customer borrowed any movies. If these conditions are true, return  false. Return false
        // if customer doesn't exist, didn't borrow the specific movie argument passed, or didn't
        // borrow any movies at all.
	if(movie != nullptr && !movie->isEmpty() && moviesBorrowedByCustomers.find(custID) != moviesBorrowedByCustomers.end()) {

		for(int i = 0; i < defaultMaxCustMovieLimit; i++) {

			if(moviesBorrowedByCustomers[custID][i] != nullptr) {

				if(moviesBorrowedByCustomers[custID][i]->getSortingCriteria() == movie->getSortingCriteria()) {

					delete(moviesBorrowedByCustomers[custID][i]);
					moviesBorrowedByCustomers[custID][i] = nullptr;
					while(i < defaultMaxCustMovieLimit - 1) {

						moviesBorrowedByCustomers[custID][i] = moviesBorrowedByCustomers[custID][i + 1];
						if(moviesBorrowedByCustomers[custID][i + 1] == nullptr) {

							break;
						}
						if(i + 1 == defaultMaxCustMovieLimit - 1) {

							moviesBorrowedByCustomers[custID][i + 1] = nullptr;
							break;
						}
						i++;
					}
					if(customerBorrowListEmpty(custID)) {

						delete[] moviesBorrowedByCustomers[custID];
						moviesBorrowedByCustomers.erase(custID);
					}
					return true;
				}
			}
		}
		cout << "Customer with ID: " << custID << " did not borrow this film (sorting criteria - " << movie->getSortingCriteria() << ")." << endl;
	}
	return false;
}

/**
  * Clear all customers borrow lists.
  */
void MovieRentalStore::clearCustMovieBorrowData() {

	map<int, Movie**>::iterator it;
	for(it = moviesBorrowedByCustomers.begin(); it != moviesBorrowedByCustomers.end(); it++) {

		for(int p = 0; p < defaultMaxCustMovieLimit; p++) {

			if(it->second[p] != nullptr) {

				delete(it->second[p]);
				it->second[p] = nullptr;
			}
		}
		delete[] it->second;
		it->second = nullptr;
	}
}

/**
  * Print to standard output the entirety of the store's movie inventory.
  * Print Comedies, then Dramas, then Classics.
  */
void MovieRentalStore::outputStoreInventory() {

	cout << "----------Comedy Movies----------" << endl;
	comedyMovieInventory.inorderTraversal();
	cout << "----------Drama Movies-----------" << endl;
	dramaMovieInventory.inorderTraversal();
	cout << "----------Classics Movies--------" << endl;
	classicsMovieInventory.inorderTraversal();
}

/**
  * Constructs a movie object from a given line from the movie file, passed as a stringstream argument.
  * This movie object is then added to the appropriate genre inventory. Function handles construction
  * of Drama and Comedy movies. Genre is specified by argument.
  *
  * @param movieParameters - The file line that holds the movie's information
  * @param genre - The genre of the movie
  *
  * @return The success state of the movie object insertion into inventory
  */
bool MovieRentalStore::DefaultMovieFactory(stringstream& movieParameters, char genre) {

        // holds a given comma delimited token of a parsed line from a movie file
	string movieParameter;

	// holds the token held by "movieParameter" excluding the first space character
	string cleanedParameter;

	// counts the number of movie variables parsed as tokens
	int parameterCounter = 1;

	// movie stock
	int stock;

	// movie director
	string director;

	// movie title
	string title;

	// movie release year
	short int releaseYear;

	// loop parses through movie line and assigns movie's parameters and constructs the
	// appropriate genre's movie object
	while(getline(movieParameters, movieParameter, ',')) {

		// get token removing starting space character
		cleanedParameter = movieParameter.substr(1);

		// depending on loop iteration, assign different movie parameters
		switch(parameterCounter) {

			case 1:
				break;

			case 2:
				stock = stoi(cleanedParameter);
				break;
			case 3:
				director = cleanedParameter;
				break;
			case 4:
				title = cleanedParameter;
				break;
			case 5:
				releaseYear = stoi(cleanedParameter);
				break;
			default:
				break;
		}
		parameterCounter++;
	}
	movieParameters.str("");

	// construct movie object according to genre parameter and add to corresponding inventory
	if(genre == 'F') {

		Comedy *comedyMovie = new Comedy(releaseYear, title, director, stock);
		if(comedyMovieInventory.Insert(*comedyMovie)) {

			delete(comedyMovie);
			return true;
		}
	}
	else if(genre == 'D') {

		Drama *dramaMovie = new Drama(director, title, releaseYear, stock);
		if(dramaMovieInventory.Insert(*dramaMovie)) {

			delete(dramaMovie);
			return true;
		}
		delete(dramaMovie);
	}
	return false;
}

/**
  * Constructs a classics movie object from a given line from the movie file, passed as a
  * stringstream argument. This movie object is then added to the appropriate genre inventory.
  *
  * @param movieParameters - The file line that holds the movie's information
  *
  * @return The success state of the movie object insertion into inventory
  */
bool MovieRentalStore::ClassicMovieFactory(stringstream& movieParameters) {

        // holds a given comma delimited token of a parsed line from a movie file
	string movieParameter;

	// holds the token held by "movieParameter" excluding the first space character
	string cleanedParameter;

	// counts the number of movie variables parsed as tokens
	int parameterCounter = 1;

	// movie stock
	int stock;

	// movie director
	string director;

	// movie title
	string title;

	// movie major actor
	string majorActor;

	// movie release month
	char releaseMonth;

	// movie release year
	int releaseYear;

	// loop parses through movie line and assigns movie's parameters and constructs the
	// appropriate genre's movie object
	while(getline(movieParameters, movieParameter, ',')) {

		// get token removing starting space character
		cleanedParameter = movieParameter.substr(1);

		// depending on loop iteration, assign different movie parameters
		switch(parameterCounter) {

			case 1:
				break;
			case 2:
				stock = stoi(cleanedParameter);
				break;
			case 3:
				director = cleanedParameter;
				break;
			case 4:
				title = cleanedParameter;
				break;
			case 5:
				{
				stringstream actorAndDate(cleanedParameter);
				string actorAndDateBuilder;

				// parses through the major actor and release date tokens, they are deliminted via space characters
				// and thus require their own loop
				while(getline(actorAndDate, actorAndDateBuilder, ' ')) {

					if(parameterCounter == 5) {

						majorActor = actorAndDateBuilder;
					}
					if(parameterCounter == 6) {

						majorActor += (" " + actorAndDateBuilder);
					}
					if(parameterCounter == 7) {

						releaseMonth = stoi(actorAndDateBuilder);
					}
					if(parameterCounter == 8) {

						releaseYear = stoi(actorAndDateBuilder);
					}
					parameterCounter++;
				}
				break;
				}
			default:
				break;
		}
		parameterCounter++;
	}
	movieParameters.str("");

	// construct classics movie object and add to corresponding inventory
	Classics *classicsMovie = new Classics(releaseYear, releaseMonth, majorActor, director, title, stock);
	if(classicsMovieInventory.Insert(*classicsMovie)) {

		delete(classicsMovie);
		return true;
	}
	delete(classicsMovie);
	return false;
}

/**
  * Constructs a classics movie object from a given line from the movie file, passed as a
  * stringstream argument. The classics movie is constructed from its sorting criteria exclusively.
  * The stock of the movie, if found, is decremented if a borrow command, or increments if a return command.
  * The borrow list for the given customer is also modified accordingly.
  * 
  * @param movieParameters - The file line that holds the borrow or return command's information
  * @param custID - The customer conducting a command
  * @param borrowOrReturn - Whether the command being processed is a movie borrow or return
  *
  * @return The success state of whether the classics movie specified in stringstream had it's stock changed appropriately and customer's borrow list was updated
  */
bool MovieRentalStore::borrowReturnCommandClassicsHelper(stringstream &movieParameters, int custID, bool borrowOrReturn) {

	// loop counter
	int counter = 0;

	// holds a token for the movie portion of a given borrow/return line
	string parameter;

	// holds the inputted movie data from borrow/return line
	int month;
	short int year;
	string majorActorFirstName;
	string majorActorLastName;
	string majorActor;

	// assigns classics movie constructor parameters holders to space delimited tokens
	// expected movie format: 3 1971 Katherine Hepburn (month, year, first name, last name)
	while(getline(movieParameters, parameter, ' ')) {

		switch(counter) {

			case 0:
				month = stoi(parameter);
				break;
			case 1:
				year = stoi(parameter);
				break;
			case 2:
				majorActorFirstName = parameter;
				break;
			case 3:
				majorActorLastName = parameter;
				break;
			default:
				break;
		}
		counter++;
	}
	majorActor = majorActorFirstName + " " + majorActorLastName;

	// generate classics movie object
	Classics *classicsMovie = new Classics(year, month, majorActor);

	// generate Movie type pointer to new movie for the purpose of passing as argument to customer borrow function ("addToCustomersBorrowList")
	Movie *classicsMoviePointer = classicsMovie;

	// if borrow command and inventory successfully decremented, else if return command and
	// inventory successfully incremented, else one of the inventory changes failed
	if(borrowOrReturn && classicsMovieInventory.changeMediaStock(*classicsMovie, false)) {

		// if failed to add to customer borrow list, then backtrack inventory change - increment stock
		if(!addToCustomersBorrowList(classicsMoviePointer, custID)) {

			cout << "Borrow failed...backtracking..." << endl;
			classicsMovieInventory.changeMediaStock(*classicsMovie, true);
			delete(classicsMoviePointer);
			classicsMoviePointer = nullptr;
			classicsMovie = nullptr;
			return false;
		}
		string transaction = "Borrowed classics DVD movie with sorting criteria: " + classicsMovie->getSortingCriteria();
		addTransaction(transaction, custID);
		return true;
	}
	else if(!borrowOrReturn && classicsMovieInventory.changeMediaStock(*classicsMovie, true)) {

		// if failed to remove from customer borrow list, then backtrack inventory change - decrement stock
		if(!removeFromCustomerList(classicsMoviePointer, custID)) {

			cout << "Return failed...backtracking..." << endl;
			classicsMovieInventory.changeMediaStock(*classicsMovie, false);
			delete(classicsMoviePointer);
			classicsMoviePointer = nullptr;
			classicsMovie = nullptr;
			return false;
		}
		string transaction = "Returned classics DVD movie with sorting criteria: " + classicsMovie->getSortingCriteria();
		delete(classicsMoviePointer);
		classicsMoviePointer = nullptr;
		classicsMovie = nullptr;
		addTransaction(transaction, custID);
		return true;
	}
	else {

		cout << "Could not execute command. Inventory stock not changed successfully!" << endl;
		delete(classicsMoviePointer);
		classicsMoviePointer = nullptr;
		classicsMovie = nullptr;
		return false;
	}
}

/**
  * Constructs a drama movie object from a given line from the movie file, passed as a
  * stringstream argument. The drama movie is constructed from its sorting criteria exclusively.
  * The stock of the movie, if found, is decremented if a borrow command, or increments if a return command.
  * The borrow list for the given customer is also modified accordingly.
  * 
  * @param movieParameters - The file line that holds the borrow or return command's information
  * @param custID - The customer conducting a command
  * @param borrowOrReturn - Whether the command being processed is a movie borrow or return
  *
  * @return The success state of whether the drama movie specified in stringstream had it's stock changed appropriately and customer's borrow list was updated
  */
bool MovieRentalStore::borrowReturnCommandDramaHelper(stringstream &movieParameters, int custID, bool borrowOrReturn) {

	// loop counter
	int counter = 0;

	// holds a token for the movie portion of a given borrow/return line
	string parameter;

	// holds the inputted movie data from borrow/return line
	string director;
	string title;

	// assigns drama movie constructor parameters holders to space delimited tokens
	// expected movie format: Gore Verbinski, Pirate of the Caribbean, (director, title)
	while(getline(movieParameters, parameter, ',')) {

		switch(counter) {

			case 0:
				director = parameter;
				break;
			case 1:
				title = parameter.substr(1);
				break;
			default:
				break;
		}
		counter++;
	}

	// generate drama movie object
	Drama *dramaMovie = new Drama(director, title);

	// generate Movie type pointer to new movie for the purpose of passing as argument to customer borrow function ("addToCustomersBorrowList")
	Movie *dramaMoviePointer = dramaMovie;

	// if borrow command and inventory successfully decremented, else if return command and
	// inventory successfully incremented, else one of the inventory changes failed
	if(borrowOrReturn && dramaMovieInventory.changeMediaStock(*dramaMovie, false)) {

		// if failed to add to customer borrow list, then backtrack inventory change - increment stock
		if(!addToCustomersBorrowList(dramaMoviePointer, custID)) {

			cout << "Borrow failed...backtracking..." << endl;
			dramaMovieInventory.changeMediaStock(*dramaMovie, true);
			delete(dramaMoviePointer);
			dramaMoviePointer = nullptr;
			dramaMovie = nullptr;
			return false;
		}
		string transaction = "Borrowed drama DVD movie with sorting criteria: " + dramaMovie->getSortingCriteria();
		addTransaction(transaction, custID);
		return true;
	}
	else if(!borrowOrReturn && dramaMovieInventory.changeMediaStock(*dramaMovie, true)) {

		// if failed to remove from customer borrow list, then backtrack inventory change - decrement stock
		if(!removeFromCustomerList(dramaMoviePointer, custID)) {

			cout << "Return failed...backtracking..." << endl;
			dramaMovieInventory.changeMediaStock(*dramaMovie, false);
			delete(dramaMovie);
			dramaMoviePointer = nullptr;
			dramaMovie = nullptr;
		}
		string transaction = "Returned drama DVD movie with sorting criteria: " + dramaMovie->getSortingCriteria();
		delete(dramaMoviePointer);
		dramaMoviePointer = nullptr;
		dramaMovie = nullptr;
		addTransaction(transaction, custID);
		return true;
	}
	else {

		cout << "Could not execute command. Inventory stock not changed successfully!" << endl;
		delete(dramaMoviePointer);
		dramaMoviePointer = nullptr;
		dramaMovie = nullptr;
		return false;
	}
}

/**
  * Constructs a comedy movie object from a given line from the movie file, passed as a
  * stringstream argument. The comedy movie is constructed from its sorting criteria exclusively.
  * The stock of the movie, if found, is decremented if a borrow command, or increments if a return command.
  * The borrow list for the given customer is also modified accordingly.
  * 
  * @param movieParameters - The file line that holds the borrow or return command's information
  * @param custID - The customer conducting a command
  * @param borrowOrReturn - Whether the command being processed is a movie borrow or return
  *
  * @return The success state of whether the comedy movie specified in stringstream had it's stock changed appropriately and customer's borrow list was updated
  */
bool MovieRentalStore::borrowReturnCommandComedyHelper(stringstream &movieParameters, int custID, bool borrowOrReturn) {

	// loop counter
	int counter = 0;

	// holds a token for the movie portion of a given borrow/return line
	string parameter;

	// holds the inputted movie data from borrow/return line
	string title;
	short int releaseYear;

	// assigns comedy movie constructor parameters holders to space delimited tokens
	// expected movie format: Pirate of the Caribbean, 2003 (title, release year)
	while(getline(movieParameters, parameter, ',')) {

		switch(counter) {

			case 0:
				title = parameter;
				break;
			case 1:
				releaseYear = stoi(parameter.substr(1));
				break;
			default:
				break;
		}
		counter++;
	}

	// generate comedy movie object
	Comedy *comedyMovie = new Comedy(releaseYear, title);

	// generate Movie type pointer to new movie for the purpose of passing as argument to customer borrow function ("addToCustomersBorrowList")
	Movie *comedyMoviePointer = comedyMovie;

	// if borrow command and inventory successfully decremented, else if return command and
	// inventory successfully incremented, else one of the inventory changes failed
	if(borrowOrReturn && comedyMovieInventory.changeMediaStock(*comedyMovie, false)) {

		// if failed to add to customer borrow list, then backtrack inventory change - increment stock
		if(!addToCustomersBorrowList(comedyMoviePointer, custID)) {

			cout << "Borrow failed...backtracking..." << endl;
			comedyMovieInventory.changeMediaStock(*comedyMovie, true);
			delete(comedyMovie);
			comedyMoviePointer = nullptr;
			comedyMovie = nullptr;
			return false;
		}
		string transaction = "Borrowed comedy DVD movie with sorting criteria: " + comedyMovie->getSortingCriteria();
		addTransaction(transaction, custID);
		return true;
	}
	else if(!borrowOrReturn && comedyMovieInventory.changeMediaStock(*comedyMovie, true)) {

		// if failed to remove from customer borrow list, then backtrack inventory change - decrement stock
		if(!removeFromCustomerList(comedyMoviePointer, custID)) {

			cout << "Return failed...backtracking..." << endl;
			comedyMovieInventory.changeMediaStock(*comedyMovie, false);
			delete(comedyMovie);
			comedyMoviePointer = nullptr;
			comedyMovie = nullptr;
			return false;
		}
		string transaction = "Returned comedy DVD movie with sorting criteria: " + comedyMovie->getSortingCriteria();
		delete(comedyMoviePointer);
		comedyMoviePointer = nullptr;
		comedyMovie = nullptr;
		addTransaction(transaction, custID);
		return true;
	}
	else {

		cout << "Could not execute command. Inventory stock not changed successfully!" << endl;
		delete(comedyMoviePointer);
		comedyMoviePointer = nullptr;
		comedyMovie = nullptr;
		return false;
	}
}

/**
  * Utilizes helper functions to process borrow and return commands. Borrow commands decrement a given movie's stock in
  * inventory. Return commands increment a given movie's stock in inventory. Determine genre of film via stringstream
  * and call appropriate helper function.
  * 
  * @param borrowReturnCommand - The borrow or return command line
  * @param borrowOrReturn - Whether the stringstream command represents a borrow or return (1 - borrow, 0 - return)
  *
  * @return The success state of the execution of the stringstream command
  */
bool MovieRentalStore::handleBorrowReturnCommand(stringstream& borrowReturnCommand, bool borrowOrReturn) {

	// holds a token for the movie portion of a given borrow/return line
	string parameter;

	// loop counter
	int counter = 0;

	// holds the inputted data/parameters from borrow/return line
	int custID;

	// holds the media type (DVD - D is the only type supported currently)
	char videoCode;
	char genre;

	// parse through tokens of the borrow/return command and assign parameter variables of command to tokens
	while(getline(borrowReturnCommand, parameter, ' ')) {

		switch(counter) {

			case 0:
				custID = stoi(parameter);
				if(!findCustomer(custID)) {

					cout << "Customer ID was invalid. No customer found with ID: " << parameter << "." << endl;
					return false;
				}
				break;
			case 1:
				videoCode = parameter.at(0);
				if(videoCode != 'D') {

					string videoCodeString(1, videoCode);
					cout << "Invalid video code provided. Do not recognize video code: " << videoCodeString << endl;
					return false;
				}
				break;
			case 2:

				// based on genre specified, call designated helper function for command processing
				genre = parameter.at(0);
				switch(genre) {

					case 'F':
						return borrowReturnCommandComedyHelper(borrowReturnCommand, custID, borrowOrReturn);
					case 'D':
						return borrowReturnCommandDramaHelper(borrowReturnCommand, custID, borrowOrReturn);
					case 'C':
						return borrowReturnCommandClassicsHelper(borrowReturnCommand, custID, borrowOrReturn);
					default:
						string genreString(1, genre);
						cout << "The genre code was invalid. Do not recognize code: " << genreString << "." << endl;
						return false;
				}
			default:
				if(borrowOrReturn) {

					cout << "Undefined error occured processing borrow command." << endl;
					return false;
				}
				cout << "Undefined error occured processing return command." << endl;
				return false;
		}
		counter++;
	}
	if(borrowOrReturn) {

		cout << "Undefined error occured processing borrow command." << endl;
		return false;
	}
	cout << "Undefined error occured processing return command." << endl;
	return false;
}

/**
  * Scans the movie inventory file, holding the list of all movies. Add each valid movie (one of the 3 supported genres: Comedy, Drama, Classics)
  * to the corresponding inventory.
  *
  * @param movieFile - The directory of the movie inventory file
  *
  * @return Whether the file was successfully read
  */
bool MovieRentalStore::scanMovieFile(string movieFile) {

	// ifstream reads the movie inventory file
	ifstream readFile;

	// holds a given line parsed within ifstream
	string line;

	// ifstream opens movie inventory file
	readFile.open(movieFile);

	// if file has not successfully opened, terminate function, return false, and notify user
	if(readFile) {

		cout << "-----------------Movie file read successfully-----------------!" << endl << endl;
	}
	else {

		cout << "Movie file failed to be read successfully!" << endl << endl;
		return false;
	}
	char genre;

	// read each line of movie inventory file, construct movie object via designated helper functions, then add to inventory
	while(readFile) {

		// reads and stores line in variable "line" then creates a stringstream out of it
		getline(readFile, line);
		if(line == "") {

			continue;
		}
		stringstream movieParameters(line);

		// gets the genre and creates the designated movie object
		genre = line.at(0);
		if(genre != 'C' && genre != 'D' && genre != 'F') {

			cout << "Invalid genre code provided: No genre associated with code '" << genre << "'" << ". Movie was not added to inventory: " << line << endl;
		}
		else if(genre == 'D' || genre == 'F') {

			// constructs comedy and drama movies
			DefaultMovieFactory(movieParameters, genre);
		}
		else if(genre == 'C') {

			// constructs classics movies
			ClassicMovieFactory(movieParameters);
		}
	}

	// close ifstream and return true indicating all present valid movie lines were read and added to inventory
	readFile.close();
	return true;
}

/**
  * Scans the customer file, holding the list of all customers. Add each customer (with formatting: custID, last name, first name)
  * to the customer hash table via helper function.
  *
  * @param customerFile - The directory of the customer file
  *
  * @return Whether the file was successfully read
  */
bool MovieRentalStore::scanCustomerFile(string customerFile) {

	// ifstream reads the customer list file
	ifstream readFile;

	// holds a given line holding customer information parsed within ifstream
	string line;

	// ifstream opens customer list file and line to cout printed for formatting purposes
	readFile.open(customerFile);
	cout << endl;

	// if file has not successfully opened, terminate function, return false, and notify user in console
	if(readFile) {

		cout << "----------------Customer file read successfully!-----------------" << endl << endl;
	}
	else {

		cout << "Customer file failed to be read successfully!" << endl << endl;
		return false;
	}

	// read each line of customer list file, construct customer object then invoke helper function to add to customer hash table
	while(readFile) {

		// reads and stores line in variable "line" then creates a stringstream out of it
		getline(readFile, line);
		if(line == "") {

			continue;
		}
		stringstream customerParameters(line);

		// holds a particular parameter for the customer in the loop parsing
		string customerParameter;

		// holds the various customer parameters
		int custID;
		string firstName;
		string lastName;

		// loop counter
		int counter = 0;

		// parse each parameter token of the customer line
		while(getline(customerParameters, customerParameter, ' ')) {

			if(counter == 0) {

				custID = stoi(customerParameter);
			}
			else if(counter == 1) {

				lastName = customerParameter;
			}
			else if(counter == 2) {

				firstName = customerParameter;
			}
			counter++;
		}
		if(line != "") {

			// generate customer object then add it to the customer hash table
			Customer *customer = new Customer(custID, firstName, lastName);
			addCustomer(customer);
		}
	}

	// close ifstream, print for aesthetic formatting purposes, then return true to indicate file read successfully
	readFile.close();
	cout << endl;
	return true;
}

/**
  * Scans the command file, holding the list of all commands executed on the store. 
  *
  * @param commandFile - The directory of the command file
  *
  * @return Whether the file was successfully read
  */
bool MovieRentalStore::scanCommandFile(string commandFile) {

	// the input file stream (reads a file)
	ifstream readFile;

	// holds an individual line read from the ifstream
	string line;

	// opens file
	readFile.open(commandFile);

	// verifies file opened successfully, if fails notify user and terminate function
	if(readFile) {

		cout << "Command file read successfully!" << endl << endl;
	}
	else {

		cout << "Command file failed to be read successfully!" << endl << endl;
		return false;
	}

	// processes each command line
	while(readFile) {

		// reads the current line of ifstream and stores it in string "line", increments cursor to next line
		getline(readFile, line);

		// generates a stringstream of the line to allow the parsing of tokens
		stringstream commandParameters(line);

		// holds tokens from a given line
		string commandParameter;

		// cutomer id
		int custID;

		// command type
		char action;

		// loop counter
		int counter = 0;

		// iterates through a given command line
		while(getline(commandParameters, commandParameter, ' ')) {

			// read the first character indicating the command type, execute command, then exit loop
			if(counter == 0) {

				// holds the char that represents the command indicated by the character read
                                // from the first letter of command line
				action = commandParameter.at(0);

				// determine which command to execute based on value of variable "action"
				switch(action) {

					// movie borrow command selected
					case 'B':
						if(!handleBorrowReturnCommand(commandParameters, 1)) {

							cout << "The following command failed: " << line << "."<< endl;
							cout << endl;
						}
						break;

					// movie return command selected
					case 'R':
						if(!handleBorrowReturnCommand(commandParameters, 0)) {

							cout << "The following command failed: " << line << "."<< endl;
							cout << endl;
						}
						break;

					// customer transaction history command selected - gets transaction history for specific customer indicated
					case 'H':
						getline(commandParameters, commandParameter, ' ');
						custID = stoi(commandParameter);
						printCustomerTransHistory(custID);
						cout << endl;
						break;

					// movie inventory print command selected
					case 'I':
						outputStoreInventory();
						cout << endl;
						break;

					// action not recognized. error printing occurs to cout.
					default:
						string actionString(1, action);
						cout << "The action code provided was invalid. Do not recognize: " << actionString << ". Command terminated." << endl;
						cout << "The following command failed: " << line << "."<< endl;
						cout << endl;
				}
			}
			else {

				break;
			}
			counter++;
		}
	}
	// close opened file and return true, indicating file was succesfully read
	readFile.close();
	return true;
}

/**
  * Prints all movies a given customer, specified in argument via custID, has currently borrowed.
  * 
  * @param custID - The customer ID of the customer to have their borrow list printed
  * 
  * @return The success state of whether the indicated customer's borrow list was printed (only fails if customer not found)
  */
bool MovieRentalStore::printCustomerBorrowList(int custID) {

	// if customer found proceed with customer borrow list print
	if(findCustomer(custID)) {

		// verify the customer has a borrow list, by evaluating the presence of the customer ID in the customer borrow list map
		if(moviesBorrowedByCustomers.find(custID) != moviesBorrowedByCustomers.end()) {

			cout << "Customer ID - " << custID << ": ";
			for(int i = 0; i < defaultMaxCustMovieLimit; i++) {

				if(moviesBorrowedByCustomers[custID][i] != nullptr) {

					cout << moviesBorrowedByCustomers[custID][i]->getSortingCriteria() << "--";
				}
				
			}
			cout << endl;
		}
		else {

			cout << "Customer with ID - " << custID << " has no borrowed items." << endl;
		}
		return true;
	}
	cout << "Customer with ID - " << custID << " does not exist." << endl;
	return false;
}

int main() {

	cout << "-------------------------------Movie Rental Store-------------------------------" << endl << endl;
	string movieFile = "data_files/data4movies.txt";
	string customerFile = "data_files/data4customers2.txt";
	string commandFile = "data_files/data4commands2.txt";
	MovieRentalStore store(movieFile, customerFile, commandFile);
}