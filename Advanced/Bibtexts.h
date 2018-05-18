#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Article{
public:
	Article() {
		this->key = 0;
		this->year = 0;
		this->month = 0;
		this->volume = 0;
		this->pages = "";
		this->publisher = "";
		this->edition = "";
		this->author = "";
		this->title = "";
		this->journal = "";
	}

	//Set Function
	void setKey(int key);
	void setYear(int year);
	void setMonth(int month);
	void setVolume(int volume);
	void setChapter(string chapter);
	void setPages(string pages);
	void setEdition(string edition);
	void setAuthor(string author);
	void setTitle(string title);
	void setJournal(string journal);
	void setPublisher(string publisher);


	//Get Function
	int getKey();
	int getYear();
	int getMonth();
	int getVolume();
	string getChapter();
	string getPages();
	string getEdition();
	string getAuthor();
	string getTitle();
	string getJournal();
	string getPublisher();

private:
	int key;
	int year;
	int month;
	int volume;
	string publisher;
	string chapter;
	string edition;
	string pages;
	string author;
	string title;
	string journal;
};

class Book{
public:
	Book() {
		this->key = 0;
		this->chapter = 0;
		this->year = 0;
		this->title = "";
		this->publisher = "";
		this->author = "";
		this->editor = "";
	}

	//Set Function
	void setKey(int key);
	void setChapter(int chapter);
	void setYear(int year);
	void setTitle(string title);
	void setPublisher(string publisher);
	void setAuthor(string author);
	void setEditor(string editor);
	void setEdition(string edition);
	void setBooktitle(string booktitle);
	void setAddress(string address);
	void setMonth(int month);
	void setNumber(int number);
	void setSeries(int series);
	void setVolume(int volume);

	//Get Function
	int getKey();
	int getChapter();
	int getYear();
	int getMonth();
	int getNumber();
	int getSeries();
	int getVolume();
	string getTitle();
	string getPublisher();
	string getAuthor();
	string getEditor();
	string getEdition();
	string getBooktitle();
	string getAddress();
		

private:
	int key;
	int chapter;
	int year;
	int month;
	int number;
	int series;
	int volume;
	string edition;
	string booktitle;
	string address;
	string title;
	string publisher;
	string author;
	string editor;
};

class Inproceedings {
public:
	Inproceedings() {
		this->key = 0;
		this->year = 0;
		this->title = "";
		this->author = "";
		this->pages = "";
		this->institution = "";
	}

	//Set Function
	void setKey(int key);
	void setYear(int year);
	void setPages(string pages);
	void setInstitution(string institution);
	void setTitle(string title);
	void setAuthor(string author);

	//Get Function
	int getKey();
	int getYear();
	string getPages();
	string getInstitution();
	string getTitle();
	string getAuthor();

private:
	int key;
	int year;
	string pages;
	string institution;
	string author;
	string title;
};
class Database {
public :
	Database() {
		articles.reserve(500);
		books.reserve(500);
		inps.reserve(500);
	}

	void pformatA(int i);
	void pformatB(int i);
	void pformatI(int i);
	void setChangeA(int i, string att, string value);
	void setChangeB(int i, string att, string value);
	void setChangeI(int i, string att, string value);
	void listAll_DB();
	void listSearch_DB(string att, string value);
	void delete_data_DB(int key);
	void element_DB(string target, string att, string value);

	void save_Article(Article ar);
	void save_Book(Book bk);
	void save_Inpro(Inproceedings ip);

private :
	vector<Article> articles;
	vector<Book> books;
	vector<Inproceedings> inps;
};

class UI {
public :
	UI() {
		this->db = Database();
	}
	void delete_data(int key);
	void insert_article(Article ar);
	void insert_book(Book bk);
	void insert_inpro(Inproceedings in);
	void listAll();
	void listSearch(string att, string value);
	void element(string target, string att, string value);
private :
	Database db;
};