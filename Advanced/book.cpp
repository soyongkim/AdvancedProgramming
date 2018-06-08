#include <iostream>
#include "Bibtexts.h"

//Set Function
void Book::setKey(int key) {
	this->key = key;
}
void Book::setChapter(int chapter) {
	this->chapter = chapter;
}
void Book::setYear(int year) {
	this->year = year;
}
void Book::setMonth(int month) {
	this->month = month;
}
void Book::setNumber(int number) {
	this->number = number;
}
void Book::setSeries(int series) {
	this->series = series;
}
void Book::setVolume(int volume) {
	this->volume = volume;
}
void Book::setTitle(string title) {
	this->title = title;
}
void Book::setPublisher(string publisher) {
	this->publisher = publisher;
}
void Book::setAuthor(string author) {
	this->author = author;
}
void Book::setEditor(string editor) {
	this->editor = editor;
}
void Book::setEdition(string edition) {
	this->edition = edition;
}
void Book::setBooktitle(string booktitle) {
	this->booktitle = booktitle;
}
void Book::setAddress(string address) {
	this->address = address;
}
//첨부+


//Get Function
int Book::getKey() {
	return this->key;
}
int Book::getChapter() {
	return this->chapter;
}
int Book::getYear() {
	return this->year;
}
int Book::getMonth() {
	return this->month;
}
int Book::getNumber() {
	return this->number;
}
int Book::getSeries() {
	return this->series;
}
int Book::getVolume() {
	return this->volume;
}
string Book::getTitle() {
	return this->title;
}
string Book::getPublisher() {
	return this->publisher;
}
string Book::getAuthor() {
	return this->author;
}
string Book::getEditor() {
	return this->editor;
}
string Book::getEdition() {
	return this->edition;
}
string Book::getBooktitle() {
	return this->booktitle;
}
string Book::getAddress() {
	return this->address;
}
