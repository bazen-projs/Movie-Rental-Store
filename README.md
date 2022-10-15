This program has been tested in Linux. If running make file on Windows computer, it will be best to convert text files in "data_files" folder to be dos compatible.
All user generated input files should be placed in the "data_files" folder.

*****Movie file structure: each line contains a single movie. A movie consists of various information attributes that compose it. The information is dependent on genre. Three genres are accepted - Comedy, Drama, and Classics. Their line structure is as follows:

Comedy - F, Stock, Director, Title, Release Year
Drama - D, Stock, Director, Title, Release Year
Classics - C, Stock, Director, Title, [Major Actor First Name] [Major Actor Last Name] [Release Month] [Release Year]

As indicated above, Comedy and Drama movie have the same line structure, save for the presence of an
F or D that flags to the program what genre is being processed. Classics holds a different line
structure - rather than title followed by a comma then space and release year, it's structured as title followed
by comma then space and major actor first name, last name, release month, and release year, all seperated by spaces.
Brackets should not be in file, this is present above for readability purposes.

*****Customer file structure: each line contains a single customer. A customer consists of the following information: customer id, first name, and last name. The line structure is as follows:

[Customer ID] [Last Name] [First Name]

Example line: 3333 Witch Wicked


The line structure above begins with a unique customer ID, that is not duplicated in the file on another line,
if so, it will be rejected and discarded. A space must follow then the customer's last name is printed followed by another
space then finally their first name. Brackets should not be in file, this is present above for readability purposes.

*****Command file structure: each line contains a single command. Commands are actions that are executed on the data within the rental store. Commands are highly heterogenous, structure wise. These are the commands supported:

Inventory (prints all movies across all genres within the store inventory): I
History (prints all transactions conducted by a given customer to standard output): H [Customer ID]
Borrow (borrows a movie for a given customer, thereby decreasing stock): B [Customer ID] [Media Type] [Genre] [Movie's Sorting Criteria]
Return (returns a movie for a given customer, thereby increasing stock): R [Customer ID] [Media Type] [Genre] [Movie's Sorting Criteria]

For the borrow and return commands, "Media Type" represents the format the movie is in, i.e. DVD, VHS, etc. At the moment, only DVDs are supported, and they
are represented by the letter "D". Only D should be placed there, anything else be result in error and the line will be discarded. Genre is defined by the
letters presented in the movies structure section: C - Classics, F - Comedy, D - Drama. The single letters should be placed there rather than the full word
of the genre. The sorting criteria section is defined by the criteria that uniquely identifies a movie in the BST underlying storage data structure. In the case of
Drama, that is director followed by a space then title. Comedy is structured as title then space then year released. Classics is structured as release month
then space then release year then space then major actor first name then space then major actor last name.
Brackets should not be in file, this is present above for readability purposes.

Example files are presented in the "data_files" folder. The MovieRentalStore executable file in this repository is looking for the following file names:

Movie file: "data_files/data4movies.txt"
Customer file: "data_files/data4customers2.txt"
Command file: "data_files/data4commands2.txt"

If a user wants to create new files for each, then they should follow the above naming convention.
If a user wants different file names, then they should alter the file names in the main function in
"MovieRentalStore.cpp", and then run "makefile.sh".
