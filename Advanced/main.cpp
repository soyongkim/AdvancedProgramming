#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
#include "Bibtexts.h"

using namespace std;

#define PROGRAM_NAME "ReferenceManagement"
const double Version = 0.1;

#define PROGRAM_VERSION 0.1
#define ARGUMENT_AMOUNT 100
#define BUF_SIZE 1024

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

		int argc = 1;
		char arg[ARGUMENT_AMOUNT][BUF_SIZE] = { 0, };

		while (1) {
			argc = 1;
			fgets(arg[0], BUF_SIZE, stdin);

			while (1) {
				//문자열 길이 측정
				int size = 0;
				while (1) {
					if (arg[0][size] == ' ' || arg[0][size] == '\n')
						break;
					size++;
				}

				//문자열 복사
				for (int j = 0; j <= size; j++) {
					arg[argc][j] = arg[0][j];
				}

				//원본 문자열 재배치
				for (int j = 0; j < BUF_SIZE; j++) {
					arg[0][j] = arg[0][j + size + 1];
				}

				//다 읽을때의 조건
				if (arg[argc][size] == '\n') {
					arg[argc][size] = 0;
					break;
				}
				arg[argc][size] = 0;
				argc++;
			}

			while (1) {
				if (std::string(arg[1]) == "--input") {
					// error
					if (argc < 2) {
						std::cerr << "Error: program needs the path of bib file." << std::endl;
						break;
					}

					//인풋 실행
					for (int i = 2; i <= argc; i++) {
						//절대 경로 변환
						char* path = changeAPath(arg[i]);

						char txtpath[10][BUF_SIZE] = { 0, };
						if (strstr(path, ".txt") != NULL) {
							ifstream inFile(path);
							if (!inFile.is_open()) {
								perror("error");
								break;
							}
							for (int i = 0;!inFile.eof();i++) {
								inFile.getline(txtpath[i], BUF_SIZE);
								std::cout << "txt:" << txtpath[i] << endl;
								openFile(txtpath[i], 0);
							}
							inFile.close();
						}
						else {
							openFile(arg[i], 0);
						}
					//for end
					std::cout << ">input order end" << std::endl;
					}
					break;

				}
				else if (std::string(arg[1]) == "--list") {
					// error
					if (argc < 2) {
						std::cerr << "Error: program needs the order how to show the table." << std::endl;
						break;
					}
					if (argc == 2) {
						if (strcmp(strlwr(arg[2]), "all") == 0)
							ui.listAll();
					}
					else {
						ui.listSearch(string(strlwr(arg[2])), string(arg[3]));
					}
					std::cout << ">list order end" << std::endl;
					break;
				}
				else if (std::string(arg[1]) == "--update") {
					// error
					if (argc < 3) {
						std::cerr << "Error: program needs the order what record have to change." << std::endl;
						break;
					}

					if(argc == 2)
						std::cout << ">Insert bib file path name" << std::endl;
					else {
						int k = stoi(string(arg[2]));
						char* path = changeAPath(arg[3]);
						openFile(path, 1);
						ui.delete_data(k);
						insertData(chk, k);
					}
					std::cout << ">update order end" << std::endl;
					break;
				}
				else if (std::string(arg[1]) == "--element") {
					// error
					if (argc < 3) {
						std::cerr << "Error: program needs the order what record have to change." << std::endl;
						break;
					}

					if (argc == 2)
						std::cout << ">example> --element key year 2010" << std::endl;
					else if(argc >= 4) {
						string att = string(arg[3]);
						string newdata = string(arg[4]);
						for (int i = 5;;i++) {
							if (arg[i][0] == 0)
								break;
							newdata.append(" ");
							newdata.append(arg[i]);
						}		
						if (att.find_first_not_of("0123456789") != string::npos)
							ui.element(string(arg[2]), string(arg[3]), newdata);
						else
							std::cout << "Insert Key Number not Character" << endl;
					}
					std::cout << ">element order end" << std::endl;
					break;
				}
				else if (std::string(arg[1]) == "--exit") {
					// End of Program
					return 0;
				}
				else {
					std::cerr << "Usage:" << std::endl
						<< "1. --input file1 file2" << std::endl
						<< "2. --list all or command" << std::endl
						<< "3. --update command" << std::endl
						<< "4. --element att value att value" << std::endl
						<< "5. --exit : program exit" << std::endl;
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
		vector<string> v;
		ifstream inFile(path);
		if (!inFile.is_open()) {
			perror("error");
			return;
		}
		while (!inFile.eof()) {
			inFile.getline(inputstring, BUF_SIZE);
			//std::cout << inputstring << endl;
			v.push_back(string(inputstring));
			if (strcmp(inputstring, "") == 0) {
				//for (int i = 0; v.at(i).compare("") != 0; i++)
					//std::cout << "v : " << v.at(i) << endl;

				if (v.at(0).find("@", 0) != std::string::npos) {
					chk = createData(v);

					if(flag == 0)
						insertData(chk, 0);
				}
				v.clear();
			}
		}
		inFile.close();
	}

	string truncData(string data) {
		data.erase(std::remove(data.end() - 1, data.end(), ','), data.end());
		data.erase(std::remove(data.begin(),data.end(),'{'), data.end());
		data.erase(std::remove(data.begin(), data.end(), '}'), data.end());
		return data;
	}


	char* changeAPath(char* arg) {
		// 절대경로로 만들기
		char repath[BUF_SIZE] = { 0, };
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
		//printf("re:%s\n", repath);
		int j = -1;
		path[t++] = '\\';
		//strcat(path, arg);
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

	int createData(vector<string> buf) {
		//파일 읽기
		string att;
		string value;
		int pos;
		int chk = 0;
		for (int i = 0;i < buf.size();i++) {
			// 객체 만들기
			if (buf.at(i).find("@") != std::string::npos) {
				if (buf.at(i).find("article", 0) != std::string::npos) {
					//puts("-----aritcle ----");
					Article aobj = Article();
					chk = 1;
				}
				else if (buf.at(i).find("book", 0) != std::string::npos) {
					Book bobj = Book();
					chk = 2;
				}
				else if (buf.at(i).find("inproceedings", 0) != std::string::npos) {
					Inproceedings iobj = Inproceedings();
					chk = 3;
				}
				else {
					//std::cout << "Unknown Type" << endl;
					chk = 4;
				}
			} // 인자 넣기
			else if (pos = buf.at(i).find('=') != std::string::npos) {
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
					else if (att.compare("chapter") == 0) {
						int j = i;
						while (buf.at(++j).find("=", 0) == std::string::npos) {
							if (buf.at(j).compare("}") == 0 || buf.at(j).compare("},"))
								break;
							value.append(truncData(buf.at(i + 1)));
						}
						aobj.setChapter(value);
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
					else if (att.compare("chpater") == 0) {
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
							aobj.setVolume(c);
						}
						catch (std::invalid_argument&) {
							aobj.setVolume(0);
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
						iobj.setAuthor(value);
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