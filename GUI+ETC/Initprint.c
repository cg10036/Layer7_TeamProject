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

//커서를 없애는 함수
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
	int x=22, y=12;  //gotoxy 좌표  
	int keyboard = 0;
	const char *gameTitle = "End-To-End";
	int flag = 0; 

	system("mode con cols=80 lines=25");
	set_color(0xE); //노란색으로 색상 바꿈
	gotoxy(63, 24);printf("made by 혁쟁이조");
	set_color(7);

	remove_cursor(0); //커서 없애기 

	gotoxy(x, y);    //커서를 15,15로 옮김 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //올라가기
	for (i = 0; i <=17; i++){ printf("￣"); x += 2;Sleep(30); } //→으로 가기
	x -= 1;  //x를 1감소 
	for (i = 0; i <= 8; i++){ gotoxy(x, ++y); printf("|"); Sleep(30); } //아래로 가기
	for (i = 0; i < 17; i++){ x -= 2;gotoxy(x, y);printf("＿"); Sleep(30); } //→로 가기 

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
		printf("%c",gameTitle[i]);
	}
	Sleep(200);
	remove_cursor(0); //커서 없애기
	gotoxy(24, 14);	printf("☞ 게임 시작");
	gotoxy(24, 15); printf("   게임 설명");
	gotoxy(24, 16); printf("   게임 종료");
	gotoxy(22, 14);

	
	while (keyboard != 13)
	{
		keyboard = getch();
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
		gotoxy(10, 3);printf("< End-to-End >는 끝말잇기 게임입니다.\n");
		gotoxy(10, 4);printf("흥미진진한 웹 서버와의 대결!!\n");
		gotoxy(10, 5); printf("엔터 키를 누르면 ");
		gotoxy(10, 6);printf("Ready start!!\n");
		
	}
	getch();
}

int main()
{

	InitPrint();
	
	
}