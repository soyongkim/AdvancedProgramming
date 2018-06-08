#include <iostream>
#include "Bibtexts.h"

//Set Variable
void Article::setKey(int key) {
	this->key = key;
}
void Article::setYear(int year) {
	this->year = year;
}
void Article::setMonth(int month) {
	this->month = month;
}
void Article::setPages(string pages) {
	this->pages = pages;
}
void Article::setVolume(int volume) {
	this->volume = volume;
}
void Article::setAuthor(string author) {
	this->author = author;
}
void Article::setPublisher(string publisher) {
	this->publisher = publisher;
}
void Article::setTitle(string title) {
	this->title = title;
}
void Article::setJournal(string journal) {
	this->journal = journal;
}
void Article::setChapter(int chapter) {
	this->chapter = chapter;
}
void Article::setEdition(string edition) {
	this->edition = edition;
}

//Get Variable
int Article::getKey() {
	return this->key;
}

int Article::getYear() {
	return this->year;
}

int Article::getMonth() {
	return this->month;
}

int Article::getVolume() {
	return this->volume;
}

int Article::getChapter() {
	return this->chapter;
}

string Article::getPages() {
	return this->pages;
}

string Article::getAuthor() {
	return this->author;
}

string Article::getTitle() {
	return this->title;
}

string Article::getPublisher() {
	return this->publisher;
}

string Article::getJournal() {
	return this->journal;
}

string Article::getEdition() {
	return this->edition;
}
