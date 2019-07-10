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
	const char *gameTitle = "GUN vs UK";
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

	gotoxy(35, 8); //좌표를 재조정 

	remove_cursor(1); //커서 없애기 
	for (i = 0; gameTitle[i] != '\0'; i++)
	{
		Sleep(100);
		if (gameTitle[i] == 'v' || gameTitle[i] == 's')
		{
			set_color(4);
			printf("%c", gameTitle[i]);
			set_color(7);
			continue;
		}
		printf("%c",gameTitle[i]);
	}
	Sleep(100);
	remove_cursor(0); //커서 없애기
	gotoxy(24, 14);	printf("▶ 게임 시작");
	gotoxy(24, 15); printf("▶ 게임 설명");
	gotoxy(22, 14);
	remove_cursor(1); //커서 생성 

	while (keyboard != 13)
	{
		keyboard = getch();	
		switch (keyboard)
		{
		case 72: gotoxy(22, 14); flag = 1; break;
		case 80: gotoxy(22, 15); flag = 0; break;
		}
	}
}

int main()
{
	
	InitPrint();

	
}