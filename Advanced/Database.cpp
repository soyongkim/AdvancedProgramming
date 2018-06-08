#include <iostream>
#include <algorithm>
#include <string>
#include "Bibtexts.h"

int maxk = 13;
int c = 0;
int directDB = 0;

//Year 정렬
bool cmpYear(Entity &a, Entity &b) {
	if (directDB == 0)
		return a.getYear() < b.getYear();
	else if(directDB == 1)
		return a.getYear() > b.getYear();
}

//Key 정렬
bool cmpKey(Entity &a, Entity &b) {
	if (directDB == 0)
		return a.getKey() < b.getKey();
	else if (directDB == 1)
		return a.getKey() > b.getKey();
}

//Author 정렬
bool cmpAuthor(Entity &a, Entity &b) {
	if (directDB == 0)
		return a.getAuthor() < b.getAuthor();
	else if (directDB == 1)
		return a.getAuthor() > b.getAuthor();
}

//Title 정렬
bool cmpTitle(Entity &a, Entity &b) {
	if (directDB == 0)
		return a.getTitle() < b.getTitle();
	else if (directDB == 1)
		return a.getTitle() > b.getTitle();
}



void Database::save_Article(Article ar) {
	articles.push_back(ar);
}

void Database::save_Book(Book bk) {
	books.push_back(bk);
}

void Database::save_Inpro(Inproceedings in) {
	inps.push_back(in);
}

void Database::sort_DB(string att, int direct) {
	directDB = direct;
	if (att.compare("key") == 0) {
		sort(articles.begin(), articles.end(), cmpKey);
		sort(books.begin(), books.end(), cmpKey);
		sort(inps.begin(), inps.end(), cmpKey);
	}
	else if (att.compare("year") == 0) {
		sort(articles.begin(), articles.end(), cmpYear);
		sort(books.begin(), books.end(), cmpYear);
		sort(inps.begin(), inps.end(), cmpYear);
	}
	else if (att.compare("author") == 0) {
		sort(articles.begin(), articles.end(), cmpAuthor);
		sort(books.begin(), books.end(), cmpAuthor);
		sort(inps.begin(), inps.end(), cmpAuthor);
	}
	else if (att.compare("title") == 0) {
		sort(articles.begin(), articles.end(), cmpTitle);
		sort(books.begin(), books.end(), cmpTitle);
		sort(inps.begin(), inps.end(), cmpTitle);
	}
	else {
		std::cout << "[Info]: Attribute is wrong. you have to insert Common attribute" << std::endl;
		return;
	}
	std::cout << "[Info]: Sort Complete" << std::endl;
}

void Database::element_DB(string target, string att, string value) {
	//아티클에서 찾기
	c = stoi(target);
	for (int i = 0; i < articles.size(); i++) {
		if (articles.at(i).getKey() == c) {
			setChangeA(i, att, value);
		}
	}

	//북에서 찾기
	for (int i = 0; i < books.size(); i++) {
		if (books.at(i).getKey() == c) {
			setChangeB(i, att, value);
		}	
	}

	//인프로시딩에서 찾기
	for (int i = 0; i < inps.size(); i++) {
		if (inps.at(i).getKey() == c) {
			setChangeI(i, att, value);
		}
	}
}

void Database::listAll_DB() {
	string con;
	bool bcon = false;
	if (articles.size() == 0)
		std::cout << "[Info]: Nothing Data in Articles" << endl;
	else {
		std::cout << "+-----------+" << endl;
		std::cout << "| ARTICLE";
		std::cout.width(maxk - 9);
		std::cout << " |" << endl;
		std::cout << "+-----------+" << endl;
		for (int i = 0; i < articles.size(); i++) {
			if (i % 100 == 0 && i != 0) {
				std::cout << "[Info]: Do yon want to show more ? (y or n)" << endl;
				std::cout << "[Order]: ";
				std::cin >> con;
				if (con.compare("n") == 0)
					bcon = true;
			}
			if (bcon == true)
				break;
			pformatA(i);
		}
		//std::cout << endl;
	}
	if(books.size() == 0)
		std::cout << "[Info]: Nothing Data in Books" << endl;
	else {
		if (bcon == false) {
			std::cout << "+-----------+" << endl;
			std::cout << "| BOOK";
			std::cout.width(maxk - 6);
			std::cout << " |" << endl;
			std::cout << "+-----------+" << endl;
			for (int i = 0; i < books.size(); i++) {
				if (i % 100 == 0 && i != 0) {
					std::cout << "[Info]: Do yon want to show more ? (y or n)" << endl;
					std::cout << "[Order]: ";
					std::cin >> con;
					if (con.compare("n") == 0)
						bcon = true;
				}
				if (bcon == true)
					break;
				pformatB(i);
			}
			//std::cout << endl;
		}
	}
	if(inps.size() == 0)
		std::cout << "[Info]: Nothing Data in Inproceedings" << endl;
	else {
		if (bcon == false) {
			std::cout << "+--------------+" << endl;
			std::cout << "| INPROCEEDING";
			std::cout.width(2);
			std::cout << " |" << endl;
			std::cout << "+--------------+" << endl;
			for (int i = 0; i < inps.size(); i++) {
				if (i % 100 == 0 && i != 0) {
					std::cout << "[Info]: Do yon want to show more ? (y or n)" << endl;
					std::cout << "[Order]: ";
					std::cin >> con;
					if (con.compare("n") == 0)
						bcon = true;
				}
				if (bcon == true)
					break;
				pformatI(i);
			}
		}
	}
	std::cout << "[Total size]: " << articles.size() + books.size() + inps.size() << std::endl << std::endl;
}

void Database::listSearch_DB(string att, string value) {
	int c;
	vector<int> filter;

	for (int i = 0; i < articles.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getKey() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getYear() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("month") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getMonth() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("chapter") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getChapter() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (articles.at(i).getAuthor().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (articles.at(i).getTitle().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("journal") == 0) {
			if (articles.at(i).getJournal().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("volume") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getVolume() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("pages") == 0) {
			if (articles.at(i).getPages().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("edition") == 0) {
			if (articles.at(i).getEdition().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("publisher") == 0) {
			if (articles.at(i).getPublisher().compare(value) == 0) {
				filter.push_back(i);
			}
		}

	}


	if (filter.empty() == true) 
		std::cout << "[Info]: Not found in Articles" << endl;
	else {
		std::cout << "+-----------+" << endl;
		std::cout << "| ARTICLE";
		std::cout.width(maxk - 9);
		std::cout << " |" << endl;
		std::cout << "+-----------+" << endl;
		for (int i = 0; i < filter.size(); i++) {
			pformatA(filter.at(i));
		}
		filter.clear();
		//std::cout << endl;
	}


	for (int i = 0; i < books.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (books.at(i).getKey() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("chapter") == 0) {
			c = stoi(string(value));
			if (books.at(i).getChapter() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (books.at(i).getYear() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("month") == 0) {
			c = stoi(string(value));
			if (books.at(i).getMonth() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("number") == 0) {
			c = stoi(string(value));
			if (books.at(i).getNumber() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("series") == 0) {
			c = stoi(string(value));
			if (books.at(i).getSeries() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("volume") == 0) {
			c = stoi(string(value));
			if (books.at(i).getVolume() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (books.at(i).getTitle().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (books.at(i).getAuthor().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("editor") == 0) {
			if (books.at(i).getEditor().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("edition") == 0) {
			if (books.at(i).getEdition().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("booktitle") == 0) {
			if (books.at(i).getBooktitle().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("address") == 0) {
			if (books.at(i).getAddress().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("publisher") == 0) {
			if (books.at(i).getPublisher().compare(value) == 0) {
				filter.push_back(i);
			}
		}
	}

	if(filter.empty() == true)
		std::cout << "[Info]: Not found in Books" << endl;
	else {
		std::cout << "+-----------+" << endl;
		std::cout << "| BOOK";
		std::cout.width(maxk - 6);
		std::cout << " |" << endl;
		std::cout << "+-----------+" << endl;
		for (int i = 0; i < filter.size(); i++) {
			pformatB(filter.at(i));
		}
		filter.clear();
		//std::cout << endl;
	}	
	
	for (int i = 0; i < inps.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (inps.at(i).getKey() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (inps.at(i).getYear() == c) {
				filter.push_back(i);
			}
		}
		else if (att.compare("pages") == 0) {
			if (inps.at(i).getPages().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (inps.at(i).getAuthor().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (inps.at(i).getTitle().compare(value) == 0) {
				filter.push_back(i);
			}
		}
		else if (att.compare("ins") == 0) {
			if (inps.at(i).getInstitution().compare(value) == 0) {
				filter.push_back(i);
			}
		}
	}

	if (filter.empty() == true)
		std::cout << "[Info]: Not found in Inproceedings" << endl;
	else {
		std::cout << "+--------------+" << endl;
		std::cout << "| INPROCEEDING";
		std::cout.width(2);
		std::cout << " |" << endl;
		std::cout << "+--------------+" << endl;
		for (int i = 0; i < filter.size(); i++) {
			pformatI(filter.at(i));
		}
	}
	std::cout << endl;
}

void Database::delete_data_DB(int key) {
	for (int i = 0; i < articles.size(); i++) {
		if (articles.at(i).getKey() == key) {
			articles.erase(articles.begin() + i);
		}

	}
	for (int i = 0; i < books.size(); i++) {
		if (books.at(i).getKey() == key) {
			books.erase(books.begin() + i);
		}

	}
	for (int i = 0; i < inps.size(); i++) {
		if (inps.at(i).getKey() == key) {
			inps.erase(inps.begin() + i);
		}

	}
}

void Database::pformatA(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 4);
	std::cout << "| " << articles.at(i).getKey() << endl;
	if (articles.at(i).getAuthor().compare("") != 0) {
		std::cout << "| Author";
		std::cout.width(maxk - 7);
		std::cout << "| " << articles.at(i).getAuthor() << endl;
	}
	if (articles.at(i).getTitle().compare("") != 0) {
		std::cout << "| Title";
		std::cout.width(maxk - 6);
		std::cout << "| " << articles.at(i).getTitle() << endl;
	}
	if (articles.at(i).getYear() != 0) {
		std::cout << "| Year";
		std::cout.width(maxk - 5);
		std::cout << "| " << articles.at(i).getYear() << endl;
	}
	if (articles.at(i).getJournal().compare("") != 0) {
		std::cout << "| Journal";
		std::cout.width(maxk - 8);
		std::cout << "| " << articles.at(i).getJournal() << endl;
	}
	if (articles.at(i).getVolume() != 0) {
		std::cout << "| Volume";
		std::cout.width(maxk - 7);
		std::cout << "| " << articles.at(i).getVolume() << endl;
	}
	if (articles.at(i).getMonth() != 0) {
		std::cout << "| Month";
		std::cout.width(maxk - 6);
		std::cout << "| " << articles.at(i).getMonth() << endl;
	}
	if (articles.at(i).getPublisher().compare("") != 0) {
		std::cout << "| Publisher";
		std::cout.width(maxk - 10);
		std::cout << "| " << articles.at(i).getPublisher() << endl;
	}
	if (articles.at(i).getChapter() != 0) {
		std::cout << "| Chapter";
		std::cout.width(maxk - 8);
		std::cout << "| " << articles.at(i).getChapter() << endl;
	}
	if (articles.at(i).getEdition().compare("") != 0) {
		std::cout << "| Edition";
		std::cout.width(maxk - 8);
		std::cout << "| " << articles.at(i).getEdition() << endl;
	}
	if (articles.at(i).getPages().compare("") != 0) {
		std::cout << "| Pages";
		std::cout.width(maxk - 6);
		std::cout << "| " << articles.at(i).getPages() << endl;
	}
	//std::cout << "+-----------------------------------------" << endl;
	std::cout << "+-----------+" << endl;
}

void Database::pformatB(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 4);
	std::cout << "| " << books.at(i).getKey() << endl;
	if (books.at(i).getChapter() != 0) {
		std::cout << "| Chapter";
		std::cout.width(maxk - 8);
		std::cout << "| " << books.at(i).getChapter() << endl;
	}
	if (books.at(i).getYear() != 0) {
		std::cout << "| Year";
		std::cout.width(maxk - 5);
		std::cout << "| " << books.at(i).getYear() << endl;
	}
	if (books.at(i).getMonth() != 0) {
		std::cout << "| Month";
		std::cout.width(maxk - 6);
		std::cout << "| " << books.at(i).getMonth() << endl;
	}
	if (books.at(i).getSeries() != 0) {
		std::cout << "| Series";
		std::cout.width(maxk - 7);
		std::cout << "| " << books.at(i).getSeries() << endl;
	}
	if (books.at(i).getVolume() != 0) {
		std::cout << "| Volume";
		std::cout.width(maxk - 7);
		std::cout << "| " << books.at(i).getVolume() << endl;
	}
	if (books.at(i).getNumber() != 0) {
		std::cout << "| Number";
		std::cout.width(maxk - 7);
		std::cout << "| " << books.at(i).getNumber() << endl;
	}
	if (books.at(i).getEdition().compare("") != 0) {
		std::cout << "| Edition";
		std::cout.width(maxk - 8);
		std::cout << "| " << books.at(i).getEdition() << endl;
	}
	if (books.at(i).getBooktitle().compare("") != 0) {
		std::cout << "| Booktitle";
		std::cout.width(maxk - 10);
		std::cout << "| " << books.at(i).getBooktitle() << endl;
	}
	if (books.at(i).getAddress().compare("") != 0) {
		std::cout << "| Address";
		std::cout.width(maxk - 8);
		std::cout << "| " << books.at(i).getAddress() << endl;
	}
	if (books.at(i).getTitle().compare("") != 0) {
		std::cout << "| Title";
		std::cout.width(maxk - 6);
		std::cout << "| " << books.at(i).getTitle() << endl;
	}
	if (books.at(i).getPublisher().compare("") != 0) {
		std::cout << "| Publisher";
		std::cout.width(maxk - 10);
		std::cout << "| " << books.at(i).getPublisher() << endl;
	}
	if (books.at(i).getAuthor().compare("") != 0) {
		std::cout << "| Author";
		std::cout.width(maxk - 7);
		std::cout << "| " << books.at(i).getAuthor() << endl;
	}
	if (books.at(i).getEditor().compare("") != 0) {
		std::cout << "| Editor";
		std::cout.width(maxk - 7);
		std::cout << "| " << books.at(i).getEditor() << endl;
	}
	std::cout << "+-----------+" << endl;
}

void Database::pformatI(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 1);
	std::cout << "| " << inps.at(i).getKey() << endl;
	if (inps.at(i).getYear() != 0) {
		std::cout << "| Year";
		std::cout.width(maxk - 2);
		std::cout << "| " << inps.at(i).getYear() << endl;
	}
	if (inps.at(i).getTitle().compare("") != 0) {
		std::cout << "| Title";
		std::cout.width(maxk - 3);
		std::cout << "| " << inps.at(i).getTitle() << endl;
	}
	if (inps.at(i).getInstitution().compare("") != 0) {
		std::cout << "| Ins";
		std::cout.width(maxk - 1);
		std::cout << "| " << inps.at(i).getInstitution() << endl;
	}
	if (inps.at(i).getAuthor().compare("") != 0) {
		std::cout << "| Author";
		std::cout.width(maxk - 4);
		std::cout << "| " << inps.at(i).getAuthor() << endl;
	}
	if (inps.at(i).getPages().compare("") != 0) {
		std::cout << "| Pages";
		std::cout.width(maxk - 3);
		std::cout << "| " << inps.at(i).getPages() << endl;
	}
	std::cout << "+--------------+" << endl;
}

void Database::setChangeA(int i , string att, string value) {
	int c;
	if (att.compare("month") == 0) {
		c = stoi(string(value));
		articles.at(i).setMonth(c);
		std::cout << "<Change Month>" << endl;
	}
	else if (att.compare("year") == 0) {
		c = stoi(string(value));
		articles.at(i).setYear(c);
		std::cout << "<Change Year>" << endl;
	}
	else if (att.compare("volume") == 0) {
		c = stoi(string(value));
		articles.at(i).setVolume(c);
		std::cout << "<Change Volume>" << endl;
	}
	else if (att.compare("chapter") == 0) {
		c = stoi(string(value));
		articles.at(i).setChapter(c);
		std::cout << "<Change Chapter>" << endl;
	}
	else if (att.compare("edition") == 0) {
		articles.at(i).setEdition(value);
		std::cout << "<Change Author>" << endl;
	}
	else if (att.compare("pages") == 0) {
		articles.at(i).setPages(value);
		std::cout << "<Change Pages>" << endl;
	}
	else if (att.compare("publisher") == 0) {
		articles.at(i).setPublisher(value);
		std::cout << "<Change Publisher>" << endl;
	}
	else if (att.compare("author") == 0) {
		articles.at(i).setAuthor(value);
		std::cout << "<Change Author>" << endl;
	}
	else if (att.compare("title") == 0) {
		articles.at(i).setTitle(value);
		std::cout << "<Change Title>" << endl;
	}
	else if (att.compare("journal") == 0) {
		articles.at(i).setJournal(value);
		std::cout << "<Change Journal>" << endl;
	}
}

void Database::setChangeB(int i, string att, string value) {
	int c;
	if (att.compare("chapter") == 0) {
		c = stoi(string(value));
		books.at(i).setChapter(c);
		std::cout << "<Change Chapter>" << endl;
	}
	else if (att.compare("year") == 0) {
		c = stoi(string(value));
		books.at(i).setYear(c);
		std::cout << "<Change Year>" << endl;
	}
	else if (att.compare("month") == 0) {
		c = stoi(string(value));
		books.at(i).setMonth(c);
		std::cout << "<Change Month>" << endl;
	}
	else if (att.compare("number") == 0) {
		c = stoi(string(value));
		books.at(i).setNumber(c);
		std::cout << "<Change Number>" << endl;
	}
	else if (att.compare("series") == 0) {
		c = stoi(string(value));
		books.at(i).setSeries(c);
		std::cout << "<Change Series>" << endl;
	}
	else if (att.compare("volume") == 0) {
		c = stoi(string(value));
		books.at(i).setVolume(c);
		std::cout << "<Change Volume>" << endl;
	}
	else if (att.compare("author") == 0) {
		books.at(i).setAuthor(value);
		std::cout << "<Change Author>" << endl;
	}
	else if (att.compare("title") == 0) {
		books.at(i).setTitle(value);
		std::cout << "<Change Title>" << endl;
	}
	else if (att.compare("publisher") == 0) {
		books.at(i).setPublisher(value);
		std::cout << "<Change Publisher>" << endl;
	}
	else if (att.compare("editor") == 0) {
		books.at(i).setEditor(value);
		std::cout << "<Change Editor>" << endl;
	}
	else if (att.compare("edition") == 0) {
		books.at(i).setEdition(value);
		std::cout << "<Change Edition>" << endl;
	}
	else if (att.compare("booktitle") == 0) {
		books.at(i).setBooktitle(value);
		std::cout << "<Change BookTitle>" << endl;

	}
	else if (att.compare("address") == 0) {
		books.at(i).setAddress(value);
		std::cout << "<Change Address>" << endl;
	}

}

void Database::setChangeI(int i, string att, string value) {
	int c;
	if (att.compare("year") == 0) {
		c = stoi(string(value));
		inps.at(i).setYear(c);
		std::cout << "<Change Year>" << endl;
	}
	else if (att.compare("author") == 0) {
		inps.at(i).setAuthor(value);
		std::cout << "<Change Author>" << endl;
	}
	else if (att.compare("title") == 0) {
		inps.at(i).setTitle(value);
		std::cout << "<Change Title>" << endl;
	}
	else if (att.compare("ins") == 0) {
		inps.at(i).setInstitution(value);
		std::cout << "<Change Institution>" << endl;
	}
	else if (att.compare("pages") == 0) {
		inps.at(i).setPages(value);
		std::cout << "<Change Pages>" << endl;
	}

}
