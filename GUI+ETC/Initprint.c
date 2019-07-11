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
	//==========================================================================================================
	//���� ���� 
	int i = 0; //�ݺ��� ����� ���� i 
	int x = 22, y = 12;  //gotoxy ó�� ��ǥ  
	int keyboard = 0; //Ű���� �Է��� �޾� enterkey�� �������� Ȯ���ϴ� ���� 
	const char *gameTitle = "End-To-End"; //���� �̸�
	int flag = 0; //���� ����, ���� ����, ���� ���� �� � ���� �����ߴ��� �Ǻ��ϴ� ���� 

	set_color(0xE); //��������� ���� �ٲ�
	gotoxy(63, 24); printf("made by ��������"); //â�� �ؿ� �κп� made by ���������� ��� 
	set_color(7); //����� ���� �� ������ �ٽ� �Ͼ������ ����
	
	//==========================================================================================================
	// �簢�� ���� UI ���
	remove_cursor(0); //Ŀ�� ���ֱ� 
	gotoxy(x, y);    //Ŀ���� 15,15�� �ű� 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //�ö󰡱�
	for (i = 0; i <=17; i++){ printf("��"); x += 2;Sleep(30); } //������ ����
	x -= 1;  //x�� 1���� 
	for (i = 0; i <= 8; i++){ gotoxy(x, ++y); printf("|"); Sleep(30); } //�Ʒ��� ����
	for (i = 0; i < 17; i++){ x -= 2;gotoxy(x, y);printf("��"); Sleep(30); } //��� ���� 

	//==========================================================================================================
	//����� ���� ����, ���� ����, ���� ���� �κ�
	gotoxy(34, 8); // ���ڸ� ���� ���� ��ǥ�� ������ 
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

	Sleep(200); //�Ʒ� ���ڰ� ������ ���� ����� waiting 
	remove_cursor(0); //Ŀ�� ���ֱ�
	gotoxy(24, 14);	printf("�� ���� ����");
	gotoxy(24, 15); printf("   ���� ����");
	gotoxy(24, 16); printf("   ���� ����");
	gotoxy(22, 14); //�⺻������ �� ��� �̸�Ƽ���� ���� ������ ����Ű�� �ֱ� ���� ��ǥ ���� 

	//==========================================================================================================
	// �ո�� �̸�Ƽ�� �����̱�+���� ������ ��� �� �� ���� 
	
	while (keyboard != 13)
	{
		keyboard = getch();
		switch (keyboard)
		{
			case 72: gotoxy(24, 15); printf("  "); gotoxy(24, 14); printf("��"); flag = 0; break;
			case 80: gotoxy(24, 14); printf("  "); gotoxy(24, 15); printf("��"); flag = 1; break;
		}
	}

	if (flag == 0) //���� ���� �����ϱ⸦ �����ٸ�
	{
		return 0; //���� �����ϱ⸦ ������ �Լ��� Ż���ϱ� 
	}
	else if(flag==1)//���� ���� ��Ģ ������ �����ٸ� 
	{
		system("cls"); //ȭ�� ����� 
		int key=0;

		//���
		gotoxy(10, 3); printf("< End-to-End >�� �����ձ� �����Դϴ�.\n");
		gotoxy(10, 4); printf("��������� �� �������� ���!!\n");
		gotoxy(10, 5); printf("���� Ű�� ������ �ٽ� ����ȭ������ ���ư��ϴ�.");
		gotoxy(10, 6); printf("Ready start!!\n");
		
		gotoxy(10, 9);  printf("<End-to-End> is an end-to-end game.\n");
		gotoxy(10, 10); printf("A battle against an exciting web server!!\n");
		gotoxy(10, 11); printf("Press the Enter key to return to the main screen.\n");
		gotoxy(10, 12); printf("Ready start!!\n");

		set_color(0xE); //��������� ���� ����
		gotoxy(60, 24); printf("@copyright ��������");
		set_color(7);  //������� ���� ����


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
	system("mode con cols=80 lines=25"); //ó�� ũ�� ���� 
	InitPrint();
	
	
}