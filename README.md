# AdvancedProgramming
ver2.0
사용법
------
1. cmake를 이용하여 컴파일 합니다.

2. 실행파일이 생성된 폴더에 예제용 bib파일과 txt파일을 넣습니다.(프로그램은 실행파일의 절대경로를 참조하여 파일을 import합니다) 
- mybib.bib     : article과 book, inproceedings의 bibtex정보가 들어 있는 파일입니다.
- listb.bib     : 약 1000개가 넘는 bibtex정보가 들어 있는 파일입니다.
- testlist.txt  : bib파일의 경로정보를 가진 텍스트 파일입니다. 이 파일을 프로그램에 입력하면 경로에 위치한 bib파일을 import 합니다.
- mybib2.bib    : testlist.txt파일의 예제로 쓰이는 bib파일입니다. 이 파일을 원하시는 위치에 두고 그 경로를 testlist.txt에 입력해줍니다.
- newrecord.bib : update 예제를 위해 만들어진 bib파일로 내부에는 하나의 bibtex정보가 있습니다.
- wrongbib.bib  : 예외처리를 확인하기 위해, 프로그램에서 지원하지 않는 bibtex형식의 정보가 저장된 파일입니다.

3. 프로그램을 실행합니다.
![main](https://user-images.githubusercontent.com/38119700/41143960-2e6aec58-6b36-11e8-933d-c3148ab80e80.jpg)

4. 제시된 명령어를 입력하여 bib파일을 관리합니다.

명령어
-----
--input [File] [File] [File] ...

: 파일을 import하기 위한 명령입니다. [File]에 bib파일이나 txt파일의 이름을 입력하여 해당 파일을 import합니다. 
- 올바른 형식의 파일을 입력 후 데이터 import가 성공적으로 끝난다면 [Info]: Input Complete 메시지가 출력됩니다.
- 잘못된 형식의 파일을 입력할 시 [Error]메시지가 출력됩니다.
- 프로그램에서 지원하지 않는 bib파일 형식을 입력하면 [Error]메시지가 출력됩니다. 프로그램은 '\n'기준으로 분리된 bib파일을 읽습니다.

--list all

: 현재 저장되어 있는 모든 데이터를 불러와 화면에 출력합니다. 데이터는 article, book, inproceedings 테이블 순서로 출력됩니다.
- 데이터는 100개를 기준으로 출력됩니다.(데이터가 100개를 넘는다면 사용자에게 계속 출력할 것인지 묻습니다.)
- 만약 테이블에 데이터가 존재하지 않을 경우 [Info]: Nothing Data 메시지를 출력합니다.

--list [Attribute] ["value"]

: 특정 [Attribute]의 값이 [value]인 데이터만을 출력합니다.
- [Attribute]는 각 테이블의 요소 이름을 입력합니다.
- [value]는 문자열일 경우 큰 따옴표를 이용하여 입력합니다. ex> --list title "a Big title"

--update [key] [File]

: [key]값에 해당하는 데이터를 [File]에서 읽어온 데이터로 수정합니다.
- [File]안에는 bib파일 형식이 들어가야합니다. 또한 하나의 데이터를 수정하기 때문에 bib파일에도 하나의 bibtex정보만 읽어옵니다.

--element [key] [Attribute] ["value"]

: [key]값에 해당하는 데이터의 [Attribute]를 [value]값으로 수정합니다.
- [value]는 문자열일 경우 큰 따옴표를 이용하여 입력합니다.
- 값이 수정되면 해당 요소가 수정되었다는 메시지를 출력합니다.

추가기능

--sort [Attribute] [asc or desc]

: [Attribute]를 기준으로 오름차순 혹은 내림차순으로 테이블을 정렬합니다.(각 테이블별로 정리합니다)
- 오름차순 정렬은 [asc or desc]에 asc를 입력하고 내림차순 정렬은 desc를 입력합니다.
- [Attribute]는 각 클래스에서 공통으로 쓰이는 key, year, author, title만 입력이 가능합니다.
