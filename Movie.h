#include<bits/stdc++.h>
#include <iostream>
#include <map>
#include <iterator>

using namespace std;

// class represents a Movie with a series of parameters
class Movie {

protected:

	string director;
	string title;
	short int releaseYear;
	int stock;
	int startingStock;

public:
	// default constructor
	Movie();

	// constructor sets member fields to parameter arguments
	Movie(string movieDirector, string movieTitle, short int movieReleaseYear, int Stock);

	// destructor
	virtual ~Movie();

	// getter for director
	string getDirector() const;

	// getter for title
	string getTitle() const;

	// getter for release year
	short int getReleaseYear() const;

	// getter for stock
	int getStock() const;

	// getter for starting stock (the stock at object creation)
	int getStartingStock() const;

	// verifies the emptiness of all the object field members (set to default values?)
	bool isEmpty() const;

	// a string representation of the movie object (prints all members of movie object)
	virtual string toString() const;

	// string representation of sorting criteria
	virtual string getSortingCriteria() const = 0;

	// increments the stock
	bool incrementStock();

	// decrements the stock
	bool decrementStock();

private:
	// setter for stock
	void setStock(int Stock);

	// setter for starting stock (the initial stock at object creation)
	void setStartingStock(int Stock);

	// setter for director
	void setDirector(string Director);

	// setter for title
	void setTitle(string Title);

	// setter for release year
	void setReleaseYear(short int ReleaseYear);
};

// class represents a Comedy movie with a series of parameters and its own sorting criteria
class Comedy: public Movie {

public:

	// Comedy movie default constructor
	Comedy();

	// Comedy constructor sets member fields to parameter arguments
	Comedy(short int year, string title, string director = "", int stock = 0);

	// Comedy destructor
	~Comedy();

	// gets the string representation of the sorting criteria of the Comedy movie (title, year)
	string getSortingCriteria() const;

	// verifies the emptiness of all the object field members (set to default values?)
	bool isEmpty() const;

	// evaluates if the current Comedy object is equal to parameter Comedy object (equal title and year)
	bool operator==(Comedy &movie);

	// evaluates if the current Comedy object is greater than parameter Comedy object (greater title, then year if equal)
	bool operator>(Comedy &movie);

	// evaluates if the current Comedy object is lesser than parameter Comedy object (lesser title, then year if equal)
	bool operator<(Comedy &movie);

	// stream insertion operator for Comedy movies, utilizes output of toString function as string inserted into stream
	friend ostream& operator<<(ostream &out, const Comedy&f);
};

// class represents a Drama movie with a series of parameters and its own sorting criteria
class Drama: public Movie {

public:

	// Drama movie default constructor
	Drama();

	// Drama constructor sets member fields to parameter arguments
	Drama(string director, string title, short int year = 0, int stock = 0);

	// Drama destructor
	~Drama();

	// gets the string representation of the sorting criteria of the Drama movie (director, title,)
	string getSortingCriteria() const;

	// verifies the emptiness of all the object field members (set to default values?)
	bool isEmpty() const;

	// evaluates if the current Drama object is equal to parameter Drama object (director and title)
	bool operator==(Drama &movie);

	// evaluates if the current Drama object is greater than parameter Drama object (greater director, then title if equal)
	bool operator>(Drama &movie);

	// evaluates if the current Drama object is lesser than parameter Drama object (lesser director, then title if equal)
	bool operator<(Drama &movie);

	// stream insertion operator for Drama movies, utilizes output of toString function as string inserted into stream
	friend ostream& operator<<(ostream &out, const Drama&d);
};

// class represents a Classics movie with a series of unique and inherited parameters
// as well as its own sorting criteria
class Classics: public Movie {

private:

	// unique member variables of Classics movie object: the month the movie released, and the
	// associated major actor featuring in the movie
	int releaseMonth;
	string majorActor;

public:

	// Classics movie default constructor
	Classics();

	// Classics constructor sets member fields to parameter arguments
	Classics(short int year, int month, string actor, string director = "", string title = "", int stock = 0);

	// Classics destructor
	~Classics();

	// gets the string representation of the sorting criteria of the Classics movie (release date *space* major actor)
	string getSortingCriteria() const;

	// verifies the emptiness of all the object field members (set to default values?)
	bool isEmpty() const;

	// getter for release date (constructed internally from release month and release year exp. 9 1939)
	string getReleaseDate() const;

	// getter for release month
	int getReleaseMonth() const;

	// getter for major actor
	string getMajorActor() const;

	// a string representation of the Classics object (prints all members of Classics object)
	string toString() const;

	// evaluates if the current Classics object is equal to parameter Classics object (release date and major actor)
	bool operator==(Classics &movie);

	// evaluates if the current Classics object is greater than parameter Classics object (greater release date, then major actor if equal)
	bool operator>(Classics &movie);

	// evaluates if the current Classics object is lesser than parameter Classics object (lesser release date, then major actor if equal)
	bool operator<(Classics &movie);

	// stream insertion operator for Classics movies, utilizes output of toString function as string inserted into stream
	friend ostream& operator<<(ostream &out, const Classics&c);
};