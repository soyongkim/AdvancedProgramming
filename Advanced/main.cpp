#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
#include "Bibtexts.h"

using namespace std;

#define PROGRAM_NAME "ReferenceManagement"

#define PROGRAM_VERSION 2.0
#define ARGUMENT_AMOUNT 100
#define BUF_SIZE 1024


void usage();
void openFile(char* path, int flag);
string truncData(string data);
int createData(vector<string> buf);
void insertData(int i, int k);
char* changeAPath(char* arg);

Article aobj;
Book bobj;
Inproceedings iobj;
UI ui = UI();

int chk = 0;
int key = 0;

	int main()
	{
		// Print program name and version
		std::string program_name = "ReferenceManagement";
		std::cout << program_name << " Version: " << PROGRAM_VERSION << std::endl;
		usage();

		int argc;
		char arg[ARGUMENT_AMOUNT][BUF_SIZE] = { 0, };

		while (1) {
			argc = 1;
			std::cout << "[Order]: ";
			rewind(stdin);
			fgets(arg[0], BUF_SIZE, stdin);
			int string_size = strlen(arg[0]);

			while (1) {
				//"" 문자열 길이
				int size = 0;
				if (arg[0][size] == '\"') {
					size++;
					while (1) {
						if (arg[0][size] == '\"')
							break;
						size++;
					}
					size++;

					//"" 문자열 복사
					for (int j = 0; j < size - 2; j++) 
						arg[argc][j] = arg[0][j+1];
				}
				else {
					//문자열 길이
					while (1) {
						if (arg[0][size] == ' ' || arg[0][size] == '\n')
							break;
						size++;
					}
					//문자열 복사
					for (int j = 0; j < size; j++) 
						arg[argc][j] = arg[0][j];
				}

				//다 읽을때의 조건
				if (arg[0][size] == '\n') {
					//arg[argc][size] = 0;
					break;
				}
				//원본 문자열 재배치
				for (int j = 0; j < string_size; j++) {
					if (arg[0][size] == '\n')
						break;
					arg[0][j] = arg[0][j + size + 1];
					arg[0][j + size + 1] = 0;
				}
				argc++;
			}
			//명령 수행 구간
			while (1) {
				if (std::string(strlwr(arg[1])) == "--input") {
					if (argc < 2) {
						std::cerr << "[Usage]: --input [File1] [File2] [File3] [...]" << std::endl;
						break;
					}
					//--input 명령 수행
					for (int i = 2; i <= argc; i++) {
						//절대 경로 변환
						char* path = changeAPath(arg[i]);

						char txtpath[10][BUF_SIZE] = { 0, };
						if (strstr(path, ".txt") != NULL) {
							ifstream inFile(path);
							if (!inFile.is_open()) {
								perror("[Error]");
								break;
							}
							for (int i = 0;!inFile.eof();i++) {
								inFile.getline(txtpath[i], BUF_SIZE);
								std::cout << "[Text File Path]: " << txtpath[i] << endl;
								openFile(txtpath[i], 0);
							}
							inFile.close();
						}
						else {
							openFile(arg[i], 0);
						}
					//for end
					}
					break;

				}
				else if (std::string(strlwr(arg[1])) == "--list") {
					// --list 명령 수행
					if (argc == 2) {
						if (strcmp(strlwr(arg[2]), "all") == 0)
							ui.listAll();
						else
							std::cerr << "[Usage]: --list all or [Attribute] [\"Value\"]" << std::endl;
					}
					else if (argc == 3) {
						ui.listSearch(string(strlwr(arg[2])), string(arg[3]));
					}
					else {
						std::cerr << "[Usage]: --list all or [Attribute] [\"Value\"]" << std::endl;
						break;
					}
					break;
				}
				else if (std::string(strlwr(arg[1])) == "--update") {
					//--update 명령 수행
					if(argc == 3) {
						int k;
						if (string(arg[2]).find_first_not_of("0123456789") == string::npos) 
							k = stoi(string(arg[2]));
						else {
							std::cout << "[Error]: Insert Key Number not Character" << endl;
							break;
						}
						char* path = changeAPath(arg[3]);
						if (k > key) {
							std::cout << "[Error]: This key number is not exist" << endl;
							break;
						}
						openFile(path, 1);
						ui.delete_data(k);
						insertData(chk, k);
					}
					else
						std::cerr << "[Usage]: --update [Key] [.bib File]" << std::endl;
					break;
				}
				else if (std::string(strlwr(arg[1])) == "--element") {
					//--element 명령 수행
					if (argc == 4) {
						string key_value = string(arg[2]);
						string att = string(strlwr(arg[3]));
						string newdata = string(arg[4]);
						if (key_value.find_first_not_of("0123456789") == string::npos) {
							if(att.compare("key") == 0)
								std::cout << "[Error]: Key value is not changed" << endl;
							else
								ui.element(key_value, att, newdata);
						}
						else
							std::cout << "[Error]: Insert Key Number not Character" << endl;
					}
					else
						std::cerr << "[Usage]: --element [Key] [Attribute] [\"Value\"]" << std::endl;
					break;
				}
				else if (std::string(strlwr(arg[1])) == "--sort") {
					//--sort 명령 수행
					if (argc == 3) {
						string att = string(arg[2]);
						string order = string(strlwr(arg[3]));
						ui.sort_data(att, order);
					}
					else
						std::cerr << "[Usage]: --sort [Attribute] [asc or desc]" << std::endl;
					break;
				}
				else if (std::string(strlwr(arg[1])) == "--exit") {
					// End of Program
					return 0;
				}
				else {
					usage();
					break;
				}
			}
			for (int i = 0; i <= argc; i++) {
				memset(arg[i], 0, BUF_SIZE);
			}
		}
		// End of Program
		return 0;
	}

	void openFile(char* path, int flag) {
		char inputstring[BUF_SIZE];
		int exception = 1;
		vector<string> v;
		ifstream inFile(path);
		if (!inFile.is_open()) {
			perror("[Error]");
			return;
		}
		while (!inFile.eof()) {
			inFile.getline(inputstring, BUF_SIZE);
			v.push_back(string(inputstring));
			if (strcmp(inputstring, "") == 0) {
				if (v.at(0).find("@", 0) != std::string::npos) {
					if (v.at(0).find("Preamble") != std::string::npos || v.at(0).find("Comment") != std::string::npos) {
						v.clear();
						continue;
					}
					try {
						if (v.at(0).find("}") != std::string::npos)	 throw exception;
					}
					catch (int exception) {
						std::cout << "[Error]: Wrong format data" << std::endl;
						return;
					}
					chk = createData(v);
					if (flag == 0) 
						insertData(chk, 0);
				}
				v.clear();
			}
		}
		inFile.close();
		std::cout << "[Info]: Input Complete" << std::endl;
	}

	string truncData(string data) {
		data.erase(std::remove(data.end() - 1, data.end(), ','), data.end());
		data.erase(std::remove(data.begin(),data.end(),'{'), data.end());
		data.erase(std::remove(data.begin(), data.end(), '}'), data.end());
		return data;
	}


	char* changeAPath(char* arg) {
		// 절대경로로 만들기
		char repath[MAX_PATH] = { 0, };
		GetModuleFileName(NULL, repath, MAX_PATH);
		//printf("re:%s\n", repath);
		char path[BUF_SIZE] = { 0, };
		int size = 0;
		int t = 0;
		while (repath[size] != 0) {
			if (repath[++size] == '\\') {
				t = size;
				for (int m = 0; m < t; m++)
					path[m] = repath[m];
				path[t] = 0;
			}
			if (repath[size] == 0) {
				break;
			}
		}
		int j = -1;
		path[t++] = '\\';
		while (1) {
			path[t++] = arg[++j];
			if (arg[j] == 0)
				break;
		}
		strcpy(arg, path);
		return arg;
	}

	void insertData(int chk, int k) {
		if (chk == 1) {
			if (k > 0) 
				aobj.setKey(k);
			else
				aobj.setKey(key++);
			ui.insert_article(aobj);
		}
		else if (chk == 2) {
			if (k > 0)
				bobj.setKey(k);
			else
				bobj.setKey(key++);
			ui.insert_book(bobj);
		}
		else if (chk == 3) {
			if (k > 0)
				iobj.setKey(k);
			else
				iobj.setKey(key++);
			ui.insert_inpro(iobj);
		}
	}

	void usage() {
		std::cout << "[Usage]" << std::endl
			<< "1. Input File     : --input [File1] [File2] [File3] [...]" << std::endl
			<< "2. Show List      : --list all or [Attribute] [\"Value\"]" << std::endl
			<< "3. Update File    : --update [Key] [.bib File]" << std::endl
			<< "4. Update Element : --element [Key] [Attribute] [\"Value\"]" << std::endl
			<< "5. Sort Table     : --sort [Attribute] [asc or desc]" << std::endl
			<< "6. Program Exit   : --exit" << std::endl << std::endl;
	}

	int createData(vector<string> buf) {
		//파일 읽기
		string att;
		string value;
		int pos;
		for (int i = 0;i < buf.size();i++) {
			// 객체 만들기
			if (buf.at(i).find("@") != std::string::npos) {
				if (buf.at(i).find("article", 0) != std::string::npos) {
					//puts("-----aritcle ----");
					aobj = Article();
					chk = 1;
				}
				else if (buf.at(i).find("book", 0) != std::string::npos) {
					bobj = Book();
					chk = 2;
				}
				else if (buf.at(i).find("inproceedings", 0) != std::string::npos) {
					iobj = Inproceedings();
					chk = 3;
				}
			} // 인자 넣기
			if ((pos = buf.at(i).find("=")) != std::string::npos) {
				//std::cout << "pos:" << pos << endl;
				int j = 0;
				for (j = 0; buf.at(i).at(j) != '='; j++);
				pos = j;
				att = buf.at(i).substr(0, pos - 1);
				value = buf.at(i).substr(pos + 2, buf.at(i).length());
				value = truncData(value);
				//데이터 매칭
				// 아티클 케이스
				if (chk == 1) {
					if (att.compare("author") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos){
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setAuthor(std::string(value));
					}
					else if (att.compare("year") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						aobj.setYear(c);
					}
					else if (att.compare("month") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						aobj.setMonth(c);
					}
					else if (att.compare("volume") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c;
						try {
							c = stoi(value);
							aobj.setVolume(c);
						}
						catch (std::invalid_argument&) {
							aobj.setVolume(0);
						}		
					}
					else if (att.compare("chapter") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c;
						try {
							c = stoi(value);
							aobj.setChapter(c);
						}
						catch (std::invalid_argument&) {
							aobj.setChapter(0);
						}
					}
					else if (att.compare("journal") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setJournal(value);
					}
					else if (att.compare("title") == 0) {
						int j = i;
						while (buf.at(++j).find("=", 0) == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setTitle(value);
					}
					else if (att.compare("pages") == 0) {
						int j = i;
						while (buf.at(++j).find("=", 0) == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setPages(value);
					}
					else if (att.compare("edition") == 0) {
						int j = i;
						while (buf.at(++j).find("=", 0) == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setEdition(value);
					}
					else if (att.compare("publisher") == 0) {
						int j = i;
						while (buf.at(++j).find("=", 0) == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setPublisher(value);
					}
				}
				// 북 케이스
				if (chk == 2) {
					if (att.compare("year") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						bobj.setYear(c);
					}
					else if (att.compare("chapter") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						bobj.setChapter(c);
					}
					else  if (att.compare("month") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						bobj.setMonth(c);
					}
					else  if (att.compare("number") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						bobj.setNumber(c);
					}
					else  if (att.compare("series") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						bobj.setSeries(c);
					}
					else  if (att.compare("volume") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c;
						try {
							c = stoi(value);
							bobj.setVolume(c);
						}
						catch (std::invalid_argument&) {
							bobj.setVolume(0);
						}
						bobj.setVolume(c);
					}
					else if (att.compare("author") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setAuthor(value);
					}
					else if (att.compare("editor") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setEditor(value);
					}
					else if (att.compare("edition") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setEdition(value);
					}
					else if (att.compare("booktitle") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setBooktitle(value);
					}
					else if (att.compare("address") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setAddress(value);
					}
					else if (att.compare("publisher") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setPublisher(value);
					}
					else if (att.compare("title") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						bobj.setTitle(value);
					}
				}
				// 인프로시딩 케이스
				if (chk == 3) {
					if (att.compare("year") == 0) {
						value.erase(std::remove(value.end() - 1, value.end(), ','), value.end());
						int c = stoi(value);
						iobj.setYear(c);
					}
					else if (att.compare("pages") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						iobj.setPages(value);
					}
					else if (att.compare("institution") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						iobj.setInstitution(value);
					}
					else if (att.compare("title") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						iobj.setTitle(value);
					}
					else if (att.compare("author") == 0) {
						int j = i;
						while (buf.at(++j).find('=') == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						iobj.setAuthor(value);
					}
				}

			}		

		}
		return chk;
	}
