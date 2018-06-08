#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Entity {
	public:
		virtual int getKey() = 0;
		virtual int getYear() = 0;
		virtual string getAuthor() = 0;
		virtual string getTitle() = 0;

		virtual void setKey(int key) = 0;
		virtual void setYear(int year) = 0;
		virtual void setAuthor(string author) = 0;
		virtual void setTitle(string title) = 0;

	protected:
		int key;
		int year;
		string author;
		string title;
};

class Article : public Entity {
	public:
		Article() {
			this->key = 0;
			this->year = 0;
			this->month = 0;
			this->volume = 0;
			this->chapter = 0;
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
		void setChapter(int chapter);
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
		int getChapter();
		string getPages();
		string getEdition();
		string getAuthor();
		string getTitle();
		string getJournal();
		string getPublisher();

	private:
		int month;
		int volume;
		int chapter;
		string publisher;
		string edition;
		string pages;
		string journal;
};

class Book : public Entity {
public:
	Book() {
		this->key = 0;
		this->chapter = 0;
		this->year = 0;
		this->month = 0;
		this->number = 0;
		this->series = 0;
		this->volume = 0;
		this->title = "";
		this->publisher = "";
		this->author = "";
		this->editor = "";
		this->edition = "";
		this->booktitle = "";
		this->address = "";
	}

	//Set Function
	void setKey(int key);
	void setChapter(int chapter);
	void setYear(int year);
	void setMonth(int month);
	void setNumber(int number);
	void setSeries(int series);
	void setVolume(int volume);
	void setTitle(string title);
	void setPublisher(string publisher);
	void setAuthor(string author);
	void setEditor(string editor);
	void setEdition(string edition);
	void setBooktitle(string booktitle);
	void setAddress(string address);

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
		
//chapter month number
private:
	int chapter; 
	int month; 
	int number; 
	int series;
	int volume; 
	string edition; 
	string booktitle; 
	string address; 
	string publisher; 
	string editor; 
};
//page
class Inproceedings : public Entity {
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
	string pages;
	string institution;
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
	void sort_DB(string att, int direct);

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
	void sort_data(string att, string order);
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
