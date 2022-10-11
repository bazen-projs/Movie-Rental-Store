#include "Movie.h"

/**
  * Default constructor initializes member variables to default values via setter functions.
  */
Movie::Movie() {

	setDirector("");
	setTitle("");
	setReleaseYear(0);
	setStock(0);
	setStartingStock(0);
}

/**
  * Constructor initializes movie member variables to parameter argument values via setter functions.
  *
  * @param movieDirector - The movie's director
  * @param movieTitle - The movie's title
  * @param movieReleaseYear - The movie's release year
  * @param stock - Number of copies of movie available in stock within associated store
  */
Movie::Movie(string movieDirector, string movieTitle, short int movieReleaseYear, int Stock) {

	setDirector(movieDirector);
	setTitle(movieTitle);
	setReleaseYear(movieReleaseYear);
	setStock(Stock);
	setStartingStock(Stock);
}

/**
  * Default destructor. Deallocates memory associated with object of class.
  */
Movie::~Movie() {}

/**
  * Sets the movie's director to parameter argument.
  *
  * @param Director - The movie's director to be set
  */
void Movie::setDirector(string Director) {

	director = Director;
}

/**
  * Sets the movie's title to parameter argument.
  *
  * @param Title - The movie's title to be set
  */
void Movie::setTitle(string Title) {

	title = Title;
}

/**
  * Sets the movie's release year to parameter argument.
  *
  * @param ReleaseYear - The movie's release year to be set
  */
void Movie::setReleaseYear(short int ReleaseYear) {

	releaseYear = ReleaseYear;
}

/**
  * Sets the movie's inventory stock to parameter argument.
  *
  * @param Stock - The movie's inventory stock to be set
  */
void Movie::setStock(int Stock) {

	stock = Stock;
}

/**
  * Sets the inventory stock the movie has at object creation.
  *
  * @param Stock - The movie's starting stock to be set
  */
void Movie::setStartingStock(int Stock) {

	startingStock = Stock;
}

/**
  * Gets the movie's director.
  *
  * @return The movie's director
  */
string Movie::getDirector() const {

	return director;
}

/**
  * Gets the movie's title.
  *
  * @return The movie's title
  */
string Movie::getTitle() const {

	return title;
}

/**
  * Gets the movie's release year.
  *
  * @return The movie's release year
  */
short int Movie::getReleaseYear() const {

	return releaseYear;
}

/**
  * Gets the movie's current stock.
  *
  * @return The movie's current stock
  */
int Movie::getStock() const {

	return stock;
}

/**
  * Gets the movie's initial stock.
  *
  * @return The movie's initial stock
  */
int Movie::getStartingStock() const {

	return startingStock;
}

/**
  * Increments the movie's current stock.
  *
  * @return The success status of the stock incrementation
  */
bool Movie::incrementStock() {

	// checks if stock is less than original stock to prevent adding 
	// non-existent stock.
	if(stock < startingStock) {

		stock += 1;
		return true;
	}
	return false;
}

/**
  * Decrements the movie's current stock.
  *
  * @return The success status of the stock decrementation
  */
bool Movie::decrementStock() {

	// checks if stock is greater than 0 to prevent negative stock values
	if(stock > 0) {

		stock -= 1;
		return true;
	}
	return false;
}

/**
  * Checks if the movie's member variables are all set to default values (an empty movie).
  *
  * @return The emptiness status of the movie
  */
bool Movie::isEmpty() const {

	return (director == "" && title == "" && releaseYear == 0 && stock == 0);
}

/**
  * Generates string representation of movie. Stock, director, title, and release year are printed.
  *
  * @return The string representation of the movie
  */
string Movie::toString() const {

	stringstream stringOutputStream;
	stringOutputStream << stock << ", " << director << ", " << title << ", " << releaseYear;
	string outputString;
	getline(stringOutputStream, outputString);
	return outputString;
}

/**
  * Default Comedy constructor invokes parent default "Movie" class constructor to initialize member variables.
  */
Comedy::Comedy(): Movie() {};

/**
  * Comedy constructor calls parent "Movie" class constructor to initialize member variables to parameter
  * arguments.
  */
Comedy::Comedy(short int year, string title, string director, int stock): Movie(director, title, year, stock) {
}

/**
  * Default destructor. Deallocates memory associated with object of class.
  */
Comedy::~Comedy(){};

/**
  * Gets the sorting criteria of the comedy movie (title followed by release year).
  *
  * @return The sorting criteria of the comedy movie
  */
string Comedy::getSortingCriteria() const {

	return getTitle() + ", " + to_string(getReleaseYear());
}

/**
  * Gets the status of whether member variables are set to default values (i.e. an empty comedy movie).
  *
  * @return The emptiness status of the comedy movie
  */
bool Comedy::isEmpty() const {

	return (director == "" && title == "" && releaseYear == 0 && stock == 0);
}

/**
  * Gets the equality status of the associated Comedy movie object and the parameter argument Comedy
  * object (this == comedy parameter).
  *
  * @param movie - The comedy object being compared to
  *
  * @return The equality of the comedy movie to parameter argument comedy movie
  */
bool Comedy::operator==(Comedy &movie) {

	// equality of title and then release year, as a secondary sorting criteria, is used to evaluate
        // equality.
	return title == movie.title && releaseYear == movie.releaseYear;
}

/**
  * Determines if the associated Comedy movie object is greater than the parameter argument Comedy
  * object (this > comedyParameter).
  *
  * @param movie - The comedy object being compared to
  *
  * @return Whether the associated comedy object is greater than the parameter argument comedy object
  */
bool Comedy::operator>(Comedy &movie) {

	// checks if title is greater than parameter argument title; if equal
        // than check if release year is greater.
	if(title == movie.getTitle()) {

		return releaseYear > movie.getReleaseYear();
	}
	return title > movie.getTitle();
}

/**
  * Determines if the associated Comedy movie object is less than the parameter argument Comedy
  * object (this < comedyParameter).
  *
  * @param movie - The comedy object being compared to
  *
  * @return Whether the associated comedy object is lesser than the parameter argument comedy object
  */
bool Comedy::operator<(Comedy &movie) {

	// checks if title is less than parameter argument title; if equal
        // than check if release year is lesser.
	if(title == movie.getTitle()) {

		return releaseYear < movie.getReleaseYear();
	}
	return title < movie.getTitle();
}

/**
  * Default constructor for Drama movie object. Invokes parent default "Movie" constructor to assign member variables default values.
  */
Drama::Drama(): Movie(){};

/**
  * Constructor for Drama movie object invokes parent "Movie" constructor assigning member variables to parameter argument values.
  * 
  * @param director - The director for the movie
  * @param title - The title for the movie
  * @param year - The year for the movie
  * @param stock - The stock for the movie
  */
Drama::Drama(string director, string title, short int year, int stock): Movie(director, title, year, stock) {
}

/**
  * Destructor for Drama movie object. Deallocates memory associated with object of class.
  */
Drama::~Drama(){};

/**
  * Gets the sorting criteria of the drama movie (director followed by title).
  *
  * @return The sorting criteria of the drama movie
  */
string Drama::getSortingCriteria() const {

	return getDirector() + ", " + getTitle() + ",";
}

/**
  * Gets the status of whether member variables are set to default values (i.e. an empty drama movie).
  *
  * @return The emptiness status of the drama movie
  */
bool Drama::isEmpty() const {

	return (director == "" && title == "" && releaseYear == 0 && stock == 0);
}

/**
  * Gets the equality status of the associated Drama movie object and the parameter argument Drama
  * object (this == drama parameter).
  *
  * @param movie - The drama object being compared to
  *
  * @return The equality of the drama movie to parameter argument drama movie
  */
bool Drama::operator==(Drama &movie) {

        // check if director and title are identical to corresponding argument values, if so movies
        // are identical.
	return director == movie.director && title == movie.title;
}

/**
  * Determines if the associated Drama movie object is greater than the parameter argument Drama
  * object (this > drama parameter).
  *
  * @param movie - The drama object being compared to
  *
  * @return Whether the associated drama object is greater than the parameter argument drama object
  */
bool Drama::operator>(Drama &movie) {

        // if the director is greater than the argument's director, then the movie object is greater.
        // if the directors are equal, evaluate if title is greater than argument title, if so,
        // then movie object is greater.
	if(director == movie.getDirector()) {

		return title > movie.getTitle();
	}
	return director > movie.getDirector();
}

/**
  * Determines if the associated Drama movie object is less than the parameter argument Drama
  * object (this < drama parameter).
  *
  * @param movie - The drama object being compared to
  *
  * @return Whether the associated drama object is lesser than the parameter argument drama object
  */
bool Drama::operator<(Drama &movie) {

	// if the director is less than the argument's director, then the movie object is lesser.
        // if the directors are equal, evaluate if title is lesser than argument title, if so,
        // then movie object is lesser.
	if(director == movie.getDirector()) {

		return title < movie.getTitle();
	}
	return director < movie.getDirector();
}

/**
  * Default Classics constructor invokes default parent Movie to initialize member variables. Classics
  * exclusive member variables assigned to default values in body.
  */
Classics::Classics(): Movie() {

	releaseMonth = 0;
	majorActor = "";
};

/**
  * Classics constructor invokes parent "Movie" constructor initializing member variables to parameter
  * argument values. Classics exclusive member variables assigned to argument values in body.
  */
Classics::Classics(short int year, int month, string actor, string director, string title, int stock): Movie(director, title, year, stock) {

	releaseMonth = month;
	majorActor = actor;
}

/**
  * Default Classics constructor calls parent default "Movie" class constructor to initialize member variables.
  */
Classics::~Classics() {};

/**
  * Gets the sorting criteria of the classics movie (release date followed by major actor).
  *
  * @return The sorting criteria of the classics movie
  */
string Classics::getSortingCriteria() const {

	return getReleaseDate() + " " + getMajorActor();
}

/**
  * Gets the status of whether member variables are set to default values (i.e. an empty classics movie).
  *
  * @return The emptiness status of the classics movie
  */
bool Classics::isEmpty() const {

	return (director == "" && title == "" && releaseYear == 0 && stock == 0 && releaseMonth == 0 && majorActor == "");
}

/**
  * Gets the release date of the movie (composed of release month followed by release year).
  * 
  * @return The movie's release date
  */
string Classics::getReleaseDate() const {

	return (to_string(releaseMonth) + " " + to_string(releaseYear));
}

/**
  * Gets the release month of the movie.
  * 
  * @return The movie's release month
  */
int Classics::getReleaseMonth() const {

	return releaseMonth;
}

/**
  * Gets the major actor of the movie.
  * 
  * @return The movie's major actor
  */
string Classics::getMajorActor() const {

	return majorActor;
}

/**
  * Generates string representation of Classics movie. Stock, director, title, major actor,
  * release month, and release year are printed.
  *
  * @return The string representation of the Classics movie
  */
string Classics::toString() const {

	stringstream stringOutputStream;
	stringOutputStream << stock << ", " << director << ", " << title << ", " << majorActor << " " << releaseMonth << " " << releaseYear;
	string outputString;
	getline(stringOutputStream, outputString);
	return outputString;
}

/**
  * Gets the equality status of the associated Classics movie object and the parameter argument Classics
  * object (this == classics parameter).
  *
  * @param movie - The classics object being compared to
  *
  * @return The equality of the classics movie to parameter argument classics movie
  */
bool Classics::operator==(Classics &movie) {

        // checks if objects release date and major actor are identical, if so, then objects are equal
	return getReleaseDate() == movie.getReleaseDate() && getMajorActor() == movie.getMajorActor();
}

/**
  * Determines if the associated Classics movie object is greater than the parameter argument Classics
  * object (this > classics parameter).
  *
  * @param movie - The classics object being compared to
  *
  * @return Whether the associated classics object is greater than the parameter argument classics object
  */
bool Classics::operator>(Classics &movie) {

	// if release date is greater than argument release date, then movie is greater
        // if release date is equal to argument release date, then check if major actor
        // is greater - if so, movie object is greater.
	if(getReleaseDate() == movie.getReleaseDate()) {

		return majorActor > movie.getMajorActor();
	}
	if(getReleaseYear() == movie.getReleaseYear()) {

		return getReleaseMonth() > movie.getReleaseMonth();
	}
	return getReleaseYear() > movie.getReleaseYear();
}

/**
  * Determines if the associated Classics movie object is less than the parameter argument Classics
  * object (this < classics parameter).
  *
  * @param movie - The classics object being compared to
  *
  * @return Whether the associated classics object is lesser than the parameter argument classics object
  */
bool Classics::operator<(Classics &movie) {

	// if not greater than argument movie nor equal to, the movie is lesser than argument movie object.
	return !(*this > movie) && !(*this == movie);
}

/**
  * Gets the output stream that holds the string representation of a Comedy object.
  *
  * @param out - The ostream being inputted into
  * @param f - The comedy object having its toString output put into output stream
  *
  * @return Reference to argument output stream
  */
ostream& operator<<(ostream &out, const Comedy&f)
{

    out << f.toString() << endl;
    return out;
}

/**
  * Gets the output stream that holds the string representation of Drama object.
  *
  * @param out - The ostream being inputted into
  * @param d - The Drama object having its toString output put into output stream
  *
  * @return Reference to argument output stream
  */
ostream& operator<<(ostream &out, const Drama&d)
{

    out << d.toString() << endl;
    return out;
}

/**
  * Gets the output stream that holds the string representation of Classics object.
  *
  * @param out - The ostream being inputted into
  * @param c - The Classics object having its toString output put into output stream
  *
  * @return Reference to argument output stream
  */
ostream& operator<<(ostream &out, const Classics&c)
{

    out << c.toString() << endl;
    return out;
}