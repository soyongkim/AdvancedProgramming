#include <iostream>
#include <string>
#include "Bibtexts.h"

int maxk = 13;
int c = 0;
void Database::save_Article(Article ar) {
	articles.push_back(ar);
}

void Database::save_Book(Book bk) {
	books.push_back(bk);
}

void Database::save_Inpro(Inproceedings in) {
	inps.push_back(in);
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
		if (articles.at(i).getKey() == c) {
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
	//std::cout.fill('+');
	std::cout << "size:" << articles.size() << endl;
	std::cout << "+-----------+" << endl;
	std::cout << "| ARTICLE";
	std::cout.width(maxk-9);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < articles.size(); i++) {
		if(articles.size() == 0)
			std::cout << "NoThing Data" << endl;
		pformatA(i);
	}
	std::cout << endl;
	std::cout << "+-----------+" << endl;
	std::cout << "| BOOK";
	std::cout.width(maxk - 6);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < books.size(); i++) {
		pformatB(i);
	}
	std::cout << endl;
	std::cout << "+--------------+" << endl;
	std::cout << "| INPROCEEDING";
	std::cout.width(2);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < inps.size(); i++) {
		pformatI(i);
	}
}

void Database::listSearch_DB(string att, string value) {
	int c;
	string v = std::string(value);
	//std::cout << "size:" << articles.size() << endl;
	std::cout << "+-----------+" << endl;
	std::cout << "| ARTICLE";
	std::cout.width(maxk - 9);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < articles.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getKey() == c) {
				pformatA(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getYear() == c) {
				pformatA(i);
			}
		}
		else if (att.compare("month") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getMonth() == c) {
				pformatA(i);
			}
		}
		else if (att.compare("chapter") == 0) {
			if (articles.at(i).getChapter().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (articles.at(i).getAuthor().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (articles.at(i).getTitle().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("journal") == 0) {
			if (articles.at(i).getJournal().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("volume") == 0) {
			c = stoi(string(value));
			if (articles.at(i).getVolume() == c) {
				pformatA(i);
			}
		}
		else if (att.compare("pages") == 0) {
			if (articles.at(i).getPages().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("edition") == 0) {
			if (articles.at(i).getEdition().compare(v) == 0) {
				pformatA(i);
			}
		}
		else if (att.compare("publisher") == 0) {
			if (articles.at(i).getPublisher().compare(v) == 0) {
				pformatA(i);
			}
		}

	}


	std::cout << endl;
	std::cout << "+-----------+" << endl;
	std::cout << "| BOOK";
	std::cout.width(maxk - 6);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < books.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (books.at(i).getKey() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("chapter") == 0) {
			c = stoi(string(value));
			if (books.at(i).getChapter() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (books.at(i).getYear() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("month") == 0) {
			c = stoi(string(value));
			if (books.at(i).getMonth() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("number") == 0) {
			c = stoi(string(value));
			if (books.at(i).getNumber() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("series") == 0) {
			c = stoi(string(value));
			if (books.at(i).getSeries() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("volume") == 0) {
			c = stoi(string(value));
			if (books.at(i).getVolume() == c) {
				pformatB(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (books.at(i).getTitle().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (books.at(i).getAuthor().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("editor") == 0) {
			if (books.at(i).getEditor().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("edition") == 0) {
			if (books.at(i).getEdition().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("booktitle") == 0) {
			if (books.at(i).getBooktitle().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("address") == 0) {
			if (books.at(i).getAddress().compare(v) == 0) {
				pformatB(i);
			}
		}
		else if (att.compare("publisher") == 0) {
			if (books.at(i).getPublisher().compare(v) == 0) {
				pformatB(i);
			}
		}
	}


	std::cout << endl;
	std::cout << "+--------------+" << endl;
	std::cout << "| INPROCEEDING";
	std::cout.width(2);
	std::cout << " |" << endl;
	std::cout << "+-----------------------------------------" << endl;
	for (int i = 0; i < inps.size(); i++) {
		if (att.compare("key") == 0) {
			c = stoi(string(value));
			if (inps.at(i).getKey() == c) {
				pformatI(i);
			}
		}
		else if (att.compare("year") == 0) {
			c = stoi(string(value));
			if (inps.at(i).getYear() == c) {
				pformatI(i);
			}
		}
		else if (att.compare("pages") == 0) {
			if (inps.at(i).getPages().compare(v) == 0) {
				pformatI(i);
			}
		}
		else if (att.compare("author") == 0) {
			if (inps.at(i).getAuthor().compare(v) == 0) {
				pformatI(i);
			}
		}
		else if (att.compare("title") == 0) {
			if (inps.at(i).getTitle().compare(v) == 0) {
				pformatI(i);
			}
		}
	}
}

void Database::delete_data_DB(int key) {
	for (int i = 0; i < articles.size(); i++) {
		if (articles.at(i).getKey() == key) {
			articles.erase(articles.begin() + i);
		std::cout << "> Delete Data" << endl;
			//std::cout << articles.at(i).getKey() << endl;
		}

	}
	for (int i = 0; i < books.size(); i++) {
		if (books.at(i).getKey() == key) {
			books.erase(books.begin() + i);
			std::cout << "> Delete Data" << endl;
			//std::cout << articles.at(i).getKey() << endl;
		}

	}
	for (int i = 0; i < inps.size(); i++) {
		if (inps.at(i).getKey() == key) {
			inps.erase(inps.begin() + i);
			std::cout << "> Delete Data" << endl;
			//std::cout << articles.at(i).getKey() << endl;
		}

	}
}


void Database::pformatA(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 4);
	std::cout << "| " << articles.at(i).getKey() << endl;
	std::cout << "| Author";
	std::cout.width(maxk - 7);
	std::cout << "| " << articles.at(i).getAuthor() << endl;
	std::cout << "| Title";
	std::cout.width(maxk - 6);
	std::cout << "| " << articles.at(i).getTitle() << endl;
	std::cout << "| Year";
	std::cout.width(maxk - 5);
	std::cout << "| " << articles.at(i).getYear() << endl;
	std::cout << "| Journal";
	std::cout.width(maxk - 8);
	std::cout << "| " << articles.at(i).getJournal() << endl;
	std::cout << "| Volume";
	std::cout.width(maxk - 7);
	std::cout << "| " << articles.at(i).getVolume() << endl;
	std::cout << "| Month";
	std::cout.width(maxk - 6);
	std::cout << "| " << articles.at(i).getMonth() << endl;
	std::cout << "| Publisher";
	std::cout.width(maxk - 10);
	std::cout << "| " << articles.at(i).getPublisher() << endl;
	std::cout << "| Chapter";
	std::cout.width(maxk - 8);
	std::cout << "| " << articles.at(i).getChapter() << endl;
	std::cout << "| Edition";
	std::cout.width(maxk - 8);
	std::cout << "| " << articles.at(i).getEdition() << endl;
	std::cout << "| Pages";
	std::cout.width(maxk - 6);
	std::cout << "| " << articles.at(i).getPages() << endl;
	std::cout << "+-----------------------------------------" << endl;
}

void Database::pformatB(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 4);
	std::cout << "| " << books.at(i).getKey() << endl;
	std::cout << "| Chapter";
	std::cout.width(maxk - 8);
	std::cout << "| " << books.at(i).getChapter() << endl;
	std::cout << "| Year";
	std::cout.width(maxk - 5);
	std::cout << "| " << books.at(i).getYear() << endl;
	std::cout << "| Month";
	std::cout.width(maxk - 6);
	std::cout << "| " << books.at(i).getMonth() << endl;
	std::cout << "| Series";
	std::cout.width(maxk - 7);
	std::cout << "| " << books.at(i).getSeries() << endl;
	std::cout << "| Volume";
	std::cout.width(maxk - 7);
	std::cout << "| " << books.at(i).getVolume() << endl;
	std::cout << "| Edition";
	std::cout.width(maxk - 8);
	std::cout << "| " << books.at(i).getEdition() << endl;
	std::cout << "| Booktitle";
	std::cout.width(maxk - 10);
	std::cout << "| " << books.at(i).getBooktitle() << endl;
	std::cout << "| Address";
	std::cout.width(maxk - 8);
	std::cout << "| " << books.at(i).getAddress() << endl;
	std::cout << "| Title";
	std::cout.width(maxk - 6);
	std::cout << "| " << books.at(i).getTitle() << endl;
	std::cout << "| Publisher";
	std::cout.width(maxk - 10);
	std::cout << "| " << books.at(i).getPublisher() << endl;
	std::cout << "| Author";
	std::cout.width(maxk - 7);
	std::cout << "| " << books.at(i).getAuthor() << endl;
	std::cout << "| Editor";
	std::cout.width(maxk - 7);
	std::cout << "| " << books.at(i).getEditor() << endl;
	std::cout << "+-----------------------------------------" << endl;
}

void Database::pformatI(int i) {
	std::cout << "| Key";
	std::cout.width(maxk - 4);
	std::cout << "| " << inps.at(i).getKey() << endl;
	std::cout << "| Year";
	std::cout.width(maxk - 5);
	std::cout << "| " << inps.at(i).getYear() << endl;
	std::cout << "| Title";
	std::cout.width(maxk - 6);
	std::cout << "| " << inps.at(i).getTitle() << endl;
	std::cout << "| Ins";
	std::cout.width(maxk - 4);
	std::cout << "| " << inps.at(i).getInstitution() << endl;
	std::cout << "| Author";
	std::cout.width(maxk - 7);
	std::cout << "| " << inps.at(i).getAuthor() << endl;
	std::cout << "| Pages";
	std::cout.width(maxk - 6);
	std::cout << "| " << inps.at(i).getPages() << endl;
	std::cout << "+-----------------------------------------" << endl;
}


void Database::setChangeA(int i , string att, string value) {
	int c;
	if (att.compare("month") == 0) {
		c = stoi(string(value));
		articles.at(i).setMonth(c);
		std::cout << ">Change Month" << endl;
	}
	else if (att.compare("year") == 0) {
		c = stoi(string(value));
		articles.at(i).setYear(c);
		std::cout << ">Change Year" << endl;
	}
	else if (att.compare("volume") == 0) {
		c = stoi(string(value));
		articles.at(i).setVolume(c);
		std::cout << ">Change Volume" << endl;
	}
	else if (att.compare("chapter") == 0) {
		articles.at(i).setChapter(value);
		std::cout << ">Change Chapter" << endl;
	}
	else if (att.compare("edition") == 0) {
		articles.at(i).setEdition(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("pages") == 0) {
		articles.at(i).setPages(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("publisher") == 0) {
		articles.at(i).setPublisher(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("author") == 0) {
		articles.at(i).setAuthor(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("title") == 0) {
		articles.at(i).setTitle(value);
		std::cout << ">Change Title" << endl;
	}
	else if (att.compare("journal") == 0) {
		articles.at(i).setJournal(value);
		std::cout << ">Change Journal" << endl;
	}
}

void Database::setChangeB(int i, string att, string value) {
	int c;
	if (att.compare("chapter") == 0) {
		c = stoi(string(value));
		books.at(i).setChapter(c);
		std::cout << ">Change Chapter" << endl;
	}
	else if (att.compare("year") == 0) {
		c = stoi(string(value));
		books.at(i).setYear(c);
		std::cout << ">Change Year" << endl;
	}
	else if (att.compare("month") == 0) {
		c = stoi(string(value));
		books.at(i).setMonth(c);
	}
	else if (att.compare("number") == 0) {
		c = stoi(string(value));
		books.at(i).setNumber(c);
		std::cout << ">Change Number" << endl;
	}
	else if (att.compare("series") == 0) {
		c = stoi(string(value));
		books.at(i).setSeries(c);
		std::cout << ">Change Series" << endl;
	}
	else if (att.compare("volume") == 0) {
		c = stoi(string(value));
		books.at(i).setVolume(c);
		std::cout << ">Change Volume" << endl;
	}
	else if (att.compare("author") == 0) {
		books.at(i).setAuthor(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("title") == 0) {
		books.at(i).setTitle(value);
		std::cout << ">Change Title" << endl;
	}
	else if (att.compare("publisher") == 0) {
		books.at(i).setPublisher(value);
		std::cout << ">Change Publisher" << endl;
	}
	else if (att.compare("editor") == 0) {
		books.at(i).setEditor(value);
		std::cout << ">Change Editor" << endl;
	}
	else if (att.compare("edition") == 0) {
		books.at(i).setEditor(value);
		std::cout << ">Change Edition" << endl;
	}
	else if (att.compare("booktitle") == 0) {
		books.at(i).setBooktitle(value);
		std::cout << ">Change BookTitle" << endl;

	}
	else if (att.compare("address") == 0) {
		books.at(i).setAddress(value);
		std::cout << ">Change Address" << endl;
	}

}

void Database::setChangeI(int i, string att, string value) {
	int c;
	if (att.compare("year") == 0) {
		c = stoi(string(value));
		inps.at(i).setYear(c);
		std::cout << ">Change Year" << endl;
	}
	else if (att.compare("author") == 0) {
		inps.at(i).setAuthor(value);
		std::cout << ">Change Author" << endl;
	}
	else if (att.compare("title") == 0) {
		inps.at(i).setTitle(value);
		std::cout << ">Change Title" << endl;
	}
	else if (att.compare("institution") == 0) {
		inps.at(i).setInstitution(value);
		std::cout << ">Change Institution" << endl;
	}
	else if (att.compare("pages") == 0) {
		inps.at(i).setPages(value);
		std::cout << ">Change Pages" << endl;
	}

}