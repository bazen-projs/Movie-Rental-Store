#include <iostream>

using namespace std;

// helper struct for holding information pertaining to whether a search in the BSTree was successful
// and what index within array the searched for item was found, if found.
struct E {

private:

	// Indicates whether a given searched item in the ArrayBasedBSTree has been found or not
	bool foundStatus;

	// Indicates the array index of the ArrayBasedBSTree a given searched item was found, if found
	int index;

public:

	/**
 	* Initializes found status of searched item and index location of found item
 	* 
 	* @param foundStatus - Whether the searched BST item was found
 	* @param index - The location of found item if found. The location insertion should occur if not found
 	*/
	E(bool foundStatus, int index) : foundStatus(foundStatus), index(index) {};

	/**
 	* Gets the success status of a BST item search
 	* 
 	* @return The BST search success status
 	*/
	bool isFound() {

		return foundStatus;
	}

	/**
 	* Gets the index of the found item in BST or index item ought to be placed if 
 	* not found
 	*
 	* @return The BST found index
 	*/
	int getIndex() {

		return index;
	}
};

// a binary search tree with an array based implementation as underlying data structure
// using implementation of 0-(n-1) range for array indices
template <typename MovieType>
class ArrayBasedBSTree {

private:

	// default maximum size for the movie inventory (may be expanded)
	int originalSize = 100;

	// BST array of movies
	MovieType *movies;

	// maximum size of movie inventory
	int movieInventoryMax;

	// number of movies stored in inventory
	int currentSize = 0;

	/**
 	 * Searches tree for movie argument starting from root, unless specified otherwise
 	 * 
 	 * @param movie - The movie to be searched
 	 * @param index - The array index to check for equality to movie argument
 	 *
 	 * @return An E object holding the status of whether the movie was found in 
 	 * the tree as well as at what index if found or what index ought to be inserted 
 	 * into if not found.
 	 */
	E searchTree(MovieType& movie, int index = 0) {

		if(movies[index] == movie) {

			E e(true, index);
 			return e;
 		}
 		else if(movies[index] > movie) {

			if(!movies[2 * index + 1].isEmpty()) {

				return searchTree(movie, 2 * index + 1);
			}
			else {

				E e(false, 2 * index + 1);
				return e;
			}
		}
		else {

			if(!movies[2 * index + 2].isEmpty()) {

				return searchTree(movie, 2 * index + 2);
			}
			else {

				E e(false, 2 * index + 2);
				return e;
			}
		}
	}

	/**
 	 * Starts and gets success status of tree search for given movie by calling 
	 * helper function "searchTree", implicitly starting search at root.
 	 * 
 	 * @param movie The movie to be searched
 	 * @return The success status of the search for argument movie
 	 */
	bool searchMediaInventory(MovieType& movie) {

		E e = searchTree(movie);
		return e.isFound();
	}

 	//bool searchAnother(MovieType &movie) {

 	//if() {
 	//}
 	//}

 	/**
 	 * Increases maximum capacity of underlying array of BST.
 	 *
 	 * @param additionalSpace - The number of elements to expand the underlying array size by
 	 * @return The success status of expansion
 	 */
	bool increaseInventorySize(int additionalSpace) {

		int newSize = movieInventoryMax + additionalSpace;
		if(newSize > 1000) {

			cout << "The requested new inventory size is above 1000. This is above the supported size: expansion failed." << endl;
			return false;
		}
		MovieType *expandedInventory = new MovieType[newSize];
		for(int i = 0; i < movieInventoryMax; i++) {

			expandedInventory[i] = movies[i];
		}
		delete[] movies;
		movies = expandedInventory;
		expandedInventory = nullptr;
		movieInventoryMax = newSize;
		return true;
	}

	/**
 	 * Attempts to inserts movie into tree. Gets status of insertion attempt: 0 if 
	 * movie exists in tree already, 1 if tree insertion successful, 2 if array index 
	 * needed for insertion was too high AND array expansion failed.
	 * 
	 * @param movie - Movie to be inserted
	 * @return Number representing particular circumstances surrounding insertion success/failure.
	 */
	char InsertHelper(MovieType& movie) {

		if(isFull()) {

			return -1;
		}
		else {

			E newIndex = searchTree(movie, 0);
			if(!(newIndex).isFound()) {

				int lastCurrentArrayIndex = movieInventoryMax - 1;
				if(newIndex.getIndex() > lastCurrentArrayIndex) {

					bool increasedSize = increaseInventorySize((newIndex.getIndex() - lastCurrentArrayIndex) * 5);
					if(!increasedSize) {

						return 2;
					}
				}
				movies[newIndex.getIndex()] = movie;
				return 1;
			}
			else {

				return 0;
			}
		}
	}

	/**
 	 * Traverses the BST via inorder traversal.
 	 *
 	 * @param index - The current index being visited within the BST.
 	 */
 	void inorderTraversalHelper(int index) {

		if(2 * index + 1 < movieInventoryMax && !movies[2 * index + 1].isEmpty()) {

			inorderTraversalHelper(2 * index + 1);
		}
		if(index < movieInventoryMax && !movies[index].isEmpty()) {

			cout << movies[index] << endl;
		}
		if(2 * index + 2 < movieInventoryMax && !movies[2 * index + 2].isEmpty()) {

			inorderTraversalHelper(2 * index + 2);
		}
	}

public:

	/**
 	 * Constructor initializes and instantiates BST movie array and max size of BST.
 	 */
 	ArrayBasedBSTree() {

		movies = new MovieType[originalSize];
		movieInventoryMax = originalSize;
	}

 	/**
 	 * Delete BST array and set to nullptr.
 	 */
 	~ArrayBasedBSTree() {

 		delete[] movies;
 		movies = nullptr;
 	}

 	/**
 	 * Gets the fullness status of BST. True if full, false if not.
 	 *
 	 * @return State of whether the BST is full
 	 */
 	bool isFull() {

 		int size = 0;
 		for(int i = 0; i < movieInventoryMax; i++) {

 			if(!movies[i].isEmpty()) {

 				size++;
 				continue;
 			}
 			break;
 		}
 		return size == movieInventoryMax;
 	}

 	/**
 	 * Change stock of a given argument movie in BST.
 	 * 
 	 * @param movie - The movie having its stock altered.
 	 * @param incOrDec - The direction stock ought change (true if decrementing, false if incrementing)
 	 *
 	 * @return The success status of the specified stock change
 	 */
 	bool changeMediaStock(MovieType &movie, bool incOrDec) {

		E e = searchTree(movie, 0);
		if(e.isFound()) {

			MovieType *foundMovie = &movies[e.getIndex()];
 			if(incOrDec) {

 				if(foundMovie->incrementStock()) {

 					return true;
 				}
 				cout << "Return failed: stock for this movie is already at maximum." << endl;
 				return false;
 			}
 			else {

 				if(foundMovie->decrementStock()) {

 					return true;
 				}
 				cout << "Borrow failed for movie with sorting criteria - " << movie.getSortingCriteria() << ": there is no stock for this movie at the moment." << endl;
 				return false;
 			}
 		}
 		cout << "The movie with sorting criteria: " << movie.getSortingCriteria() << " was not found within the inventory." << endl;
 		return false;
 	}

 	/**
 	 * Inserts movie into BST using helper function: InsertHelper. If root is not 
	 * empty, invoke helper, if so, assign value to argument movie. Print out 
	 * circumstances of search, if helper invoked.
 	 * @param movie - The movie to be inserted into BST
 	 *
 	 * @return The success status of the insertion
 	 */
 	bool Insert(MovieType& movie) {

 		if(!movies[0].isEmpty()) {

 			char insertSucceeded = InsertHelper(movie);
 			switch(insertSucceeded) {

 				case -1:
 					cout << "Insertion failed: The inventory is full." << endl;
 					return false;
 				case 0:
 					cout << "This movie is already in the inventory." << endl;
 					return false;
 				case 1:
 					cout << "Successfully added movie to the inventory. Sorting criteria is: " << movie.getSortingCriteria() << endl;
 					currentSize++;
 					return true;
 				case 2:
 					cout << "Insertion failed: This insertion would require expanding internal container for this genre beyond maximum size.\n" << "Movie was: " << 
					movie.toString() << endl;
 					return false;
 				default:
 					cout << "Undefined error occured" << endl;
 					return false;
 			}
 		}
 		else {

 			movies[0] = movie;
 			currentSize++;
 			return true;
 		}
 	}

 	/**
 	 * Gets the number of movies stored in BST at point called.
 	 *
 	 *@return The number of movies stored in BST
 	 */
 	int getSize() {

 		return currentSize;
 	}

	/**
	 * Prints every existing media item inserted into the tree by parsing through
	 * the underlying array.
	 */
 	void printTreeContents() {

 		for(int i = 0; i < movieInventoryMax; i++) {

 			if(!movies[i].isEmpty()) {

 				cout << movies[i].toString() << endl;
 			}
 		}
 	}

 	/**
 	 * Initiates inorder traversal of BST utilizing helper function, providing index to originate search (root)
 	 */
 	void inorderTraversal() {

 		inorderTraversalHelper(0);
 	}
};
