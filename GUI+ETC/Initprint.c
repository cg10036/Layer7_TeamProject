#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//���ڻ��� �ٲٴ� �Լ�
void set_color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

//Ŀ���� ���ִ� �Լ�
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
	int x=22, y=12;  //gotoxy ��ǥ  
	int keyboard = 0;
	const char *gameTitle = "End-To-End";
	int flag = 0; 

	system("mode con cols=80 lines=25");
	set_color(0xE); //��������� ���� �ٲ�
	gotoxy(63, 24);printf("made by ��������");
	set_color(7);

	remove_cursor(0); //Ŀ�� ���ֱ� 

	gotoxy(x, y);    //Ŀ���� 15,15�� �ű� 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //�ö󰡱�
	for (i = 0; i <=17; i++){ printf("��"); x += 2;Sleep(30); } //������ ����
	x -= 1;  //x�� 1���� 
	for (i = 0; i <= 8; i++){ gotoxy(x, ++y); printf("|"); Sleep(30); } //�Ʒ��� ����
	for (i = 0; i < 17; i++){ x -= 2;gotoxy(x, y);printf("��"); Sleep(30); } //��� ���� 

	gotoxy(34, 8); //��ǥ�� ������ 

	remove_cursor(1); //Ŀ�� ���ֱ� 
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
	remove_cursor(0); //Ŀ�� ���ֱ�
	gotoxy(24, 14);	printf("�� ���� ����");
	gotoxy(24, 15); printf("   ���� ����");
	gotoxy(24, 16); printf("   ���� ����");
	gotoxy(22, 14);

	
	while (keyboard != 13)
	{
		keyboard = getch();
		int y = 15;
		switch (keyboard)
		{
		case 72: gotoxy(24, 15); printf("  "); gotoxy(24, 14); printf("��"); flag = 1; break;
		case 80: gotoxy(24, 14); printf("  "); gotoxy(24, 15); printf("��"); flag = 0; break;
		}
	}

	system("cls"); //ȭ�� ����� 
	if (flag == 1) //���� ���� �����ϱ⸦ �����ٸ�
	{

	}
	else //���� ���� ��Ģ ������ �����ٸ� 
	{
		gotoxy(10, 3);printf("< End-to-End >�� �����ձ� �����Դϴ�.\n");
		gotoxy(10, 4);printf("��������� �� �������� ���!!\n");
		gotoxy(10, 5); printf("���� Ű�� ������ ");
		gotoxy(10, 6);printf("Ready start!!\n");
		
	}
	getch();
}

int main()
{

	InitPrint();
	
	
}