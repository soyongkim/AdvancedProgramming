# AdvancedProgramming
ver2.0
사용법
----- 
1. 우선 첨부되어 있는 bib파일은 cmake로 컴파일을 진행하고 난 후 생성되는 실행파일이 들어있는 폴더에 넣어 주셔야 합니다.(절대경로로 변환해서 파일이름 입력시 파일이름만 입력하면 되도록 하기 위함입니다)
2. testlist.txt 파일에는 bib파일의 경로를 적어주시면 됩니다.
3. 프로그램을 실행하면 아래 그림과 같이 실행됩니다.
![main](C:\Users\soyongkim\image\main.jpg)
4. 첨부되어 있는 mybib.bib / newrecord.bib / listb.bib 은 같은 실행 폴더에, mybib2.bib은 아무데나 두셔도 되지만 이 경로를 testlist.txt안에 절대경로로 적어 두셔야 합니다.

명령어
-----
--input mybib.bib
: 프로그램 실행후 위 명령을 하게 되면 mybib.bib에서 bibtex 정보를 읽어와서 파싱을 한 후 저장해둡니다.

--input mybib.bib mybib.bib ... 
:이런 식으로 여러번 호출해서 한번에 여러개의 bib파일을 불러올수도 있습니다.

--input testlist.txt
:bib파일의 절대경로를 입력한 txt 파일을 불러오면 그 경로를 바탕으로 bib파일을 읽어 데이터를 저장합니다. 여러개의 경로를 \n 기준으로 입력하시면 여러개의 bib파일을 읽으실 수 있습니다.

--list all
:저장되어 있는 모든 데이터를 읽어와 아티클, 북, 인프로시딩 순서로 데이터를 불러들이게 됩니다.

--list key 6
:key 값이 6인 데이터만 찾아서 불러오는 명령입니다. 두번 째 인자에는 찾을 대상의 애트리뷰트 이름이 그리고 세번 째 인자에는 찾을 값이 들어가야 합니다.

--update 6 newrecord.bib
:key 값이 6인 데이터를 newrecord.bib에서 불러와 데이터를 대체합니다. 기존에 존재했던 데이터를 삭제하고 새롭게 읽어 드린 데이터를 추가하는 식으로 구현되었습니다.

--element 6 title BIG PAPER
:key 값이 6인 데이터의 title 정보를 BIG PAPER로 바꾸라는 명령입니다. 두번 째 인자에는 key 값을, 세번 째 인자에는 바꾸고자하는 애트리뷰트의 이름 그리고 마지막은 값을 적어주시면 됩니다.


