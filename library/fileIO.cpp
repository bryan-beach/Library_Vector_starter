#include "../includes_usr/fileIO.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();

	ifstream myInputFile;
	myInputFile.open(filename, ios::in);

	if (myInputFile.is_open()) {

		std::string line;
		vector <string> tokens;
		int i = 0;

		while (!myInputFile.eof()) {

			getline(myInputFile, line);

			tokens.clear();
			stringstream check1(line);
			string intermediate;

			while(getline(check1, intermediate, ','))
			{
				tokens.push_back(intermediate);
			}

			if (tokens.size() >= 1) {
				int bookId = atoi(tokens[0].c_str());
				books.push_back(book());
				books[i].book_id = bookId;
				books[i].title = tokens[1];
				books[i].author = tokens[2];
				int value = atoi(tokens[3].c_str());
				switch (value)
				{
				case 0:
					books[i].state = UNKNOWN;
					break;
				case 1:
					books[i].state = IN;
					break;
				case 2:
					books[i].state = OUT;
				}
				int id = atoi(tokens[4].c_str());
				books[i].loaned_to_patron_id = id;
			}

			i++;

		}

		myInputFile.close();

		if (books.size() < 1) {
			return NO_BOOKS_IN_LIBRARY;
		}

		return SUCCESS;

	} else {

		return COULD_NOT_OPEN_FILE;

	}

}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{

	if (books.size() < 1) {
		return NO_BOOKS_IN_LIBRARY;
	}

	ofstream myOutputFile;
	myOutputFile.open(filename);

	if (myOutputFile.is_open()) {

		for (book page : books) {
			myOutputFile << page.book_id;
			myOutputFile << ",";

			myOutputFile << page.title;
			myOutputFile << ",";

			myOutputFile << page.author;
			myOutputFile << ",";

			myOutputFile << page.state;
			myOutputFile << ",";

			myOutputFile << page.loaned_to_patron_id;
			myOutputFile << "\n";
		}

	} else {
		return COULD_NOT_OPEN_FILE;
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{

	patrons.clear();

	ifstream myInputFile;
		myInputFile.open(filename, ios::in);

		if (myInputFile.is_open()) {

			std::string line;
			vector <string> tokens;
			int i = 0;

			while (!myInputFile.eof()) {

				getline(myInputFile, line);

				tokens.clear();
				stringstream check1(line);
				string intermediate;

				while(getline(check1, intermediate, ','))
				{
					tokens.push_back(intermediate);
				}

				if (tokens.size() >= 1) {
					patrons.push_back(patron());

					int patronId = atoi(tokens[0].c_str());
					patrons[i].patron_id = patronId;
					patrons[i].name = tokens[1];
					int numBooks = atoi(tokens[2].c_str());
					patrons[i].number_books_checked_out = numBooks;

				}

				i++;

			}

			myInputFile.close();

			if (patrons.size() < 1) {
				return NO_PATRONS_IN_LIBRARY;
			}

			return SUCCESS;

		} else {

			return COULD_NOT_OPEN_FILE;

		}

}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if (patrons.size() < 1) {
			return NO_BOOKS_IN_LIBRARY;
		}

		ofstream myOutputFile;
		myOutputFile.open(filename);

		if (myOutputFile.is_open()) {

			for (patron person : patrons) {
				myOutputFile << person.patron_id;
				myOutputFile << ",";

				myOutputFile << person.name;
				myOutputFile << ",";

				myOutputFile << person.number_books_checked_out;
				myOutputFile << "\n";
			}

		} else {
			return COULD_NOT_OPEN_FILE;
		}

		return SUCCESS;
}
