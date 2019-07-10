#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//글자색을 바꾸는 함수
void set_color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

//커서를 삭제(0) / 생성(1) 하는 함수
void remove_cursor(int num)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = num;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void InitPrint(void)
{
	int i = 0;
	int x = 22, y = 12;  //gotoxy 좌표  
	int keyboard = 0;
	const char *gameTitle = "End-To-End";
	int flag = 1;

	system("mode con cols=80 lines=25");
	set_color(0xE); //노란색으로 색상 바꿈
	gotoxy(63, 24); printf("made by 혁쟁이조");
	set_color(7);

	remove_cursor(0); //커서 없애기 

	gotoxy(x, y);    //커서를 15,15로 옮김 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //올라가기
	for (i = 0; i <= 17; i++) { printf("￣"); x += 2; Sleep(30); } //→으로 가기
	x -= 1;  //x를 1감소 
	for (i = 0; i <= 8; i++) { gotoxy(x, ++y); printf("|"); Sleep(30); } //아래로 가기
	for (i = 0; i < 17; i++) { x -= 2; gotoxy(x, y); printf("＿"); Sleep(30); } //→로 가기 

	gotoxy(34, 8); //좌표를 재조정 

	remove_cursor(1); //커서 없애기 
	for (i = 0; gameTitle[i] != '\0'; i++)
	{
		Sleep(100);
		if (gameTitle[i] == 'E')
		{
			set_color(4);
			printf("%c", gameTitle[i]);
			set_color(7);
			continue;
		}
		printf("%c", gameTitle[i]);
	}
	Sleep(200);
	remove_cursor(0); //커서 없애기
	gotoxy(24, 14);	printf("☞ 게임 시작");
	gotoxy(24, 15); printf("   게임 설명");
	gotoxy(24, 16); printf("   게임 종료");
	gotoxy(22, 14);


	while (keyboard != 13)
	{
		keyboard = _getch();
		int y = 15;
		switch (keyboard)
		{
		case 72: gotoxy(24, 15); printf("  "); gotoxy(24, 14); printf("☞"); flag = 1; break;
		case 80: gotoxy(24, 14); printf("  "); gotoxy(24, 15); printf("☞"); flag = 0; break;
		}
	}

	system("cls"); //화면 지우기 
	if (flag == 1) //만약 게임 시작하기를 눌렀다면
	{

	}
	else //만약 게임 규칙 설명을 눌렀다면 
	{
		gotoxy(10, 3); printf("< End-to-End >는 끝말잇기 게임입니다.\n");
		gotoxy(10, 4); printf("흥미진진한 웹 서버와의 대결!!\n");
		gotoxy(10, 5); printf("엔터 키를 누르면 ");
		gotoxy(10, 6); printf("Ready start!!\n");

	}
	_getch();
}

void GameTitle(int a) {
	if (a == 0) {
		int x, y; // gotoxy(x, y);
		int i;

		x = 15;
		y = 0;

		gotoxy(15, 2);
		for (i = 0; i <= 48; i++) { printf("_"); Sleep(2); } // 가로선 출력
		for (i = 0; i <= 24; i++) {
			gotoxy(x, y); printf("|"); Sleep(5);
			gotoxy(62, y++); printf("ㅣ"); Sleep(5); // 세로선 출력
		}
	}
	else {
		int x, y; // gotoxy(x, y);
		int i;

		x = 15;
		y = 0;

		gotoxy(15, 2);
		for (i = 0; i <= 48; i++) { printf("_"); } // 가로선 출력
		for (i = 0; i <= 24; i++) {
			gotoxy(x, y); printf("|");
			gotoxy(62, y++); printf("ㅣ"); // 세로선 출력
		}
	}
}

void PlayGame() {
	GameTitle(0);

	int y; // 커서 y 좌표
	int ncnt; // 현재 진행중인 횟수
	int cnt; // 최대 진행 횟수
	int i; // for 전용 변수 i

	char a[100]; // 입력받을 배열
	char p; // 제시 단어

	y = 6;
	ncnt = 0;
	cnt = 1;
	p = 's';

	while (1) {
		ncnt++; // 현재 진행중인 횟수 증가

		gotoxy(60, y);
		printf("%c", p); // 제시 단어 출력

		y += 2; // y 좌표 증가

		while (1) {
			remove_cursor(1); // 커서 생성
			gotoxy(17, y);
			gets_s(a); // 입력받을 단어
			remove_cursor(0); // 커서 삭제

			// 제시된 단어와 앞 단어가 틀리면
			if (a[0] != p) {
				gotoxy(17, 1);
				printf("단어가 틀립니다!");

				Sleep(1000);

				gotoxy(17, 1);
				printf("%17c", ' '); // 단어 지우기 (단어가 틀립니다!)
				gotoxy(17, y);
				printf("%12c", ' '); // 단어 지우기 (입력한 단어)
			}
			else break;
		}

		for (i = 0; a[i] != '\0'; i++) {
			p = a[i];
		}

		y += 2;

		if (ncnt == cnt) {
			cnt++; // 최대 진행 횟수 증가
			y = 6; // y 좌표 초기화
			ncnt = 0; // 현재 진행 횟수 초기화
			system("cls"); // 게임 타이틀 삭제
			GameTitle(1); // 게임 타이틀 생성
		}
	}

	_getch();
}

int main()
{
	InitPrint();

	PlayGame();
}