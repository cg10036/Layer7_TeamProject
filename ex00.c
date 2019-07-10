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

//Ŀ���� ����(0) / ����(1) �ϴ� �Լ�
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
	int x = 22, y = 12;  //gotoxy ��ǥ  
	int keyboard = 0;
	const char *gameTitle = "End-To-End";
	int flag = 1;

	system("mode con cols=80 lines=25");
	set_color(0xE); //��������� ���� �ٲ�
	gotoxy(63, 24); printf("made by ��������");
	set_color(7);

	remove_cursor(0); //Ŀ�� ���ֱ� 

	gotoxy(x, y);    //Ŀ���� 15,15�� �ű� 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(30); } //�ö󰡱�
	for (i = 0; i <= 17; i++) { printf("��"); x += 2; Sleep(30); } //������ ����
	x -= 1;  //x�� 1���� 
	for (i = 0; i <= 8; i++) { gotoxy(x, ++y); printf("|"); Sleep(30); } //�Ʒ��� ����
	for (i = 0; i < 17; i++) { x -= 2; gotoxy(x, y); printf("��"); Sleep(30); } //��� ���� 

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
		printf("%c", gameTitle[i]);
	}
	Sleep(200);
	remove_cursor(0); //Ŀ�� ���ֱ�
	gotoxy(24, 14);	printf("�� ���� ����");
	gotoxy(24, 15); printf("   ���� ����");
	gotoxy(24, 16); printf("   ���� ����");
	gotoxy(22, 14);


	while (keyboard != 13)
	{
		keyboard = _getch();
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
		gotoxy(10, 3); printf("< End-to-End >�� �����ձ� �����Դϴ�.\n");
		gotoxy(10, 4); printf("��������� �� �������� ���!!\n");
		gotoxy(10, 5); printf("���� Ű�� ������ ");
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
		for (i = 0; i <= 48; i++) { printf("_"); Sleep(2); } // ���μ� ���
		for (i = 0; i <= 24; i++) {
			gotoxy(x, y); printf("|"); Sleep(5);
			gotoxy(62, y++); printf("��"); Sleep(5); // ���μ� ���
		}
	}
	else {
		int x, y; // gotoxy(x, y);
		int i;

		x = 15;
		y = 0;

		gotoxy(15, 2);
		for (i = 0; i <= 48; i++) { printf("_"); } // ���μ� ���
		for (i = 0; i <= 24; i++) {
			gotoxy(x, y); printf("|");
			gotoxy(62, y++); printf("��"); // ���μ� ���
		}
	}
}

void PlayGame() {
	GameTitle(0);

	int y; // Ŀ�� y ��ǥ
	int ncnt; // ���� �������� Ƚ��
	int cnt; // �ִ� ���� Ƚ��
	int i; // for ���� ���� i

	char a[100]; // �Է¹��� �迭
	char p; // ���� �ܾ�

	y = 6;
	ncnt = 0;
	cnt = 1;
	p = 's';

	while (1) {
		ncnt++; // ���� �������� Ƚ�� ����

		gotoxy(60, y);
		printf("%c", p); // ���� �ܾ� ���

		y += 2; // y ��ǥ ����

		while (1) {
			remove_cursor(1); // Ŀ�� ����
			gotoxy(17, y);
			gets_s(a); // �Է¹��� �ܾ�
			remove_cursor(0); // Ŀ�� ����

			// ���õ� �ܾ�� �� �ܾ Ʋ����
			if (a[0] != p) {
				gotoxy(17, 1);
				printf("�ܾ Ʋ���ϴ�!");

				Sleep(1000);

				gotoxy(17, 1);
				printf("%17c", ' '); // �ܾ� ����� (�ܾ Ʋ���ϴ�!)
				gotoxy(17, y);
				printf("%12c", ' '); // �ܾ� ����� (�Է��� �ܾ�)
			}
			else break;
		}

		for (i = 0; a[i] != '\0'; i++) {
			p = a[i];
		}

		y += 2;

		if (ncnt == cnt) {
			cnt++; // �ִ� ���� Ƚ�� ����
			y = 6; // y ��ǥ �ʱ�ȭ
			ncnt = 0; // ���� ���� Ƚ�� �ʱ�ȭ
			system("cls"); // ���� Ÿ��Ʋ ����
			GameTitle(1); // ���� Ÿ��Ʋ ����
		}
	}

	_getch();
}

int main()
{
	InitPrint();

	PlayGame();
}