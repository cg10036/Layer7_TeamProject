#include<stdio.h>
#include<windows.h>
#include<conio.h>

// 128 :: �ܾ�� ��
// 109 :: Ÿ�̸� ��
// 7 :: ���

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

// Ÿ��Ʋ�� �׸��� �Լ� 
void title() {
	int x, y; // gotoxy ���� ��ǥ 
	remove_cursor(0); // Ŀ���� �����

	x = 20;
	y = 0;

	// Ÿ�̸� ����
	while (1) {
		gotoxy(x, y);
		set_color(100);
		printf(" ");

		x++;

		if (x == 60) {
			x = 20; // x ��ǥ �ʱ�ȭ
			y++; // �ѹ��� �Ʒ��� 
		}
		if (y == 3) {
			break;
		}
	}

	x = 20;

	// ä��â ����
	while (1) {
		gotoxy(x, y);
		set_color(120);
		printf(" ");

		x++;

		if (x == 60) {
			x = 20;
			y++;
		}
		if (y == 25) {
			break;
		}
	}
}


int HomePrinter(void)
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
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(20); } //�ö󰡱�
	for (i = 0; i <= 17; i++) { printf("��"); x += 2; Sleep(20); } //������ ����
	x -= 1;  //x�� 1���� 
	for (i = 0; i <= 8; i++) { gotoxy(x, ++y); printf("|"); Sleep(20); } //�Ʒ��� ����
	for (i = 0; i < 17; i++) { x -= 2; gotoxy(x, y); printf("��"); Sleep(20); } //��� ���� 

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
		printf("%c", gameTitle[i]);
	}

	while (_kbhit()) //������ �̰� ��� �ؾ� ��? 
	{
		_getch();
	}

	Sleep(200); //�Ʒ� ���ڰ� ������ ���� ����� waiting 
	remove_cursor(0); //Ŀ�� ���ֱ�
	gotoxy(24, 14);	printf("�� ���� ����");
	gotoxy(24, 15); printf("   ���� ����");
	gotoxy(24, 16); printf("   ������");
	gotoxy(22, 14); //�⺻������ �� ��� �̸�Ƽ���� ���� ������ ����Ű�� �ֱ� ���� ��ǥ ���� 

	//==========================================================================================================
	// �ո�� �̸�Ƽ�� �����̱�+���� ������ ��� �� �� ���� 

	y = 14;
	while (keyboard != 13)
	{
		keyboard = _getch();
		switch (keyboard)
		{
		case 72:
			if (y <= 14)continue;
			gotoxy(24, y); printf("  "); gotoxy(24, --y); printf("��");
			flag = y == 14 ? 0 : 1;
			break;
		case 80:
			if (y >= 16)continue;
			gotoxy(24, y); printf("  "); gotoxy(24, ++y); printf("��");
			flag = y == 15 ? 1 : 2;
			break;
		}

	}

	if (flag == 0) //���� ���� �����ϱ⸦ �����ٸ�
	{
		return 0; //���� �����ϱ⸦ ������ �Լ��� Ż���ϱ� 
	}
	else if (flag == 1)//���� ���� ��Ģ ������ �����ٸ� 
	{
		system("cls"); //ȭ�� ����� 
		int key = 0;

		set_color(110); // ����� �׵θ�

		for (i = 0; i < 25; i++) //�ð��� ��� 
		{
			gotoxy(3, i); printf(" ");
			gotoxy(2, i); printf(" ");
		}

		set_color(60); // �Ķ��� �׵θ�

		for (i = 0; i < 80; i++) { // �ð��� ���
			gotoxy(i, 23); printf(" ");
		}

		set_color(90);
		gotoxy(2, 23); printf(" ");
		gotoxy(3, 23); printf(" ");

		set_color(7); // ��� �۾�

		//���
		gotoxy(10, 4); printf("< End-to-End >�� �����ձ� �����Դϴ�.\n");
		gotoxy(10, 5); printf("��������� PC���� ���!!\n");
		gotoxy(10, 6); printf("���� Ű�� ������ �ٽ� ����ȭ������ ���ư��ϴ�.");
		gotoxy(10, 7); printf("Ready start!!\n");

		gotoxy(10, 10);  printf("<End-to-End> is an end-to-end game.\n");
		gotoxy(10, 11); printf("A battle against an exciting PC!!\n");
		gotoxy(10, 12); printf("Press the Enter key to return to the main screen.\n");
		gotoxy(10, 13); printf("Ready start!!\n");

		set_color(0xE); //��������� ���� ����
		gotoxy(60, 24); printf("@copyright ��������");
		set_color(7);  //������� ���� ����


		while (key != 13)
		{
			key = _getch();
			if (key == 13)
			{
				system("cls"); //ȭ���� ����� 
				Sleep(800);
				HomePrinter();  //InitPrint() �Լ��� �ٽ� ȣ��
			}
		}
	}
	else
	{
		system("cls");
		exit(0); //���� 
	}
}

int main()
{
	system("mode con cols=80 lines=25"); //ó�� ũ�� ���� 
	HomePrinter();
	system("cls"); // ȭ�� �ʱ�ȭ
	title();

	_getch();
}
