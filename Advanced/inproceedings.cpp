#include <iostream>
#include "Bibtexts.h"

//Set Function
void Inproceedings::setKey(int key) {
	this->key = key;
}
void Inproceedings::setYear(int year) {
	this->year = year;
}
void Inproceedings::setPages(string pages) {
	this->pages = pages;
}
void Inproceedings::setTitle(string title) {
	this->title = title;
}
void Inproceedings::setAuthor(string author) {
	this->author = author;
}
void Inproceedings::setInstitution(string institution) {
	this->institution = institution;
}

//Get Function
int Inproceedings::getKey() {
	return this->key;
}
int Inproceedings::getYear() {
	return this->year;
}
string Inproceedings::getPages() {
	return this->pages;
}
string Inproceedings::getTitle() {
	return this->title;
}
string Inproceedings::getAuthor() {
	return this->author;
}
string Inproceedings::getInstitution() {
	return this->institution;
}