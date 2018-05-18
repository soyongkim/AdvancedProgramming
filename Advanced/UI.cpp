#include <iostream>
#include "Bibtexts.h"

void UI::insert_article(Article ar) {
	//std::cout << ">called insert_article()" << endl;
	db.save_Article(ar);
}

void UI::insert_book(Book bk) {
	//std::cout << ">called in_book()" << endl;
	db.save_Book(bk);
}

void UI::insert_inpro(Inproceedings in) {
	//std::cout << ">called in_inpro()" << endl;
	db.save_Inpro(in);
}

void UI::listAll() {
	//std::cout << ">called listAll()" << endl;
	db.listAll_DB();
}

void UI::listSearch(string att, string value) {
	//std::cout << ">called search" << endl;
	db.listSearch_DB(att, value);
}

void UI::element(string target, string att, string value) {
	//std::cout << ">called up_i()" << endl;
	db.element_DB(target, att, value);
}

void UI::delete_data(int key) {
	//std::cout << ">called up_i()" << endl;
	db.delete_data_DB(key);
}