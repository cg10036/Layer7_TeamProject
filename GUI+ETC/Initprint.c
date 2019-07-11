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
	//==========================================================================================================
	//기초 설정 
	int i = 0; //반복에 사용할 변수 i 
	int x = 22, y = 12;  //gotoxy 처음 좌표  
	int keyboard = 0; //키보드 입력을 받아 enterkey를 눌렀는지 확인하는 변수 
	const char *gameTitle = "End-To-End"; //게임 이름
	int flag = 0; //게임 시작, 게임 설명, 게임 종료 중 어떤 것을 선택했는지 판별하는 변수 

	set_color(0xE); //노란색으로 색상 바꿈
	gotoxy(63, 24); printf("made by 혁쟁이조"); //창의 밑에 부분에 made by 혁쟁이조를 출력 
	set_color(7); //출력이 끝난 후 색상을 다시 하얀색으로 변경
	
	//==========================================================================================================
	// 사각형 상자 UI 출력
	remove_cursor(0); //커서 없애기 
	gotoxy(x, y);    //커서를 15,15로 옮김 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //올라가기
	for (i = 0; i <=17; i++){ printf("￣"); x += 2;Sleep(30); } //→으로 가기
	x -= 1;  //x를 1감소 
	for (i = 0; i <= 8; i++){ gotoxy(x, ++y); printf("|"); Sleep(30); } //아래로 가기
	for (i = 0; i < 17; i++){ x -= 2;gotoxy(x, y);printf("＿"); Sleep(30); } //→로 가기 

	//==========================================================================================================
	//제목과 게임 시작, 게임 설명, 게임 종료 부분
	gotoxy(34, 8); // 글자를 쓰기 위해 좌표를 재조정 
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

	Sleep(200); //아래 글자가 나오기 전에 잠깐의 waiting 
	remove_cursor(0); //커서 없애기
	gotoxy(24, 14);	printf("☞ 게임 시작");
	gotoxy(24, 15); printf("   게임 설명");
	gotoxy(24, 16); printf("   게임 종료");
	gotoxy(22, 14); //기본적으로 손 모양 이모티콘이 게임 시작을 가리키고 있기 위해 좌표 설정 

	//==========================================================================================================
	// 손모양 이모티콘 움직이기+게임 설명을 듣고 난 후 설정 
	
	while (keyboard != 13)
	{
		keyboard = getch();
		switch (keyboard)
		{
			case 72: gotoxy(24, 15); printf("  "); gotoxy(24, 14); printf("☞"); flag = 0; break;
			case 80: gotoxy(24, 14); printf("  "); gotoxy(24, 15); printf("☞"); flag = 1; break;
		}
	}

	if (flag == 0) //만약 게임 시작하기를 눌렀다면
	{
		return 0; //게임 시작하기를 누르면 함수를 탈출하기 
	}
	else if(flag==1)//만약 게임 규칙 설명을 눌렀다면 
	{
		system("cls"); //화면 지우기 
		int key=0;

		//대사
		gotoxy(10, 3); printf("< End-to-End >는 끝말잇기 게임입니다.\n");
		gotoxy(10, 4); printf("흥미진진한 웹 서버와의 대결!!\n");
		gotoxy(10, 5); printf("엔터 키를 누르면 다시 메인화면으로 돌아갑니다.");
		gotoxy(10, 6); printf("Ready start!!\n");
		
		gotoxy(10, 9);  printf("<End-to-End> is an end-to-end game.\n");
		gotoxy(10, 10); printf("A battle against an exciting web server!!\n");
		gotoxy(10, 11); printf("Press the Enter key to return to the main screen.\n");
		gotoxy(10, 12); printf("Ready start!!\n");

		set_color(0xE); //노란색으로 색깔 변경
		gotoxy(60, 24); printf("@copyright 혁쟁이조");
		set_color(7);  //흰색으로 색깔 변경


		while (key != 13)
		{
			key = getch();
			if (key == 13)
			{
				system("cls");
				InitPrint();
			}
		}
	}
}

int main()
{
	system("mode con cols=80 lines=25"); //처음 크기 조정 
	InitPrint();
	
	
}