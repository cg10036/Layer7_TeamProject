#include <stdio.h>
#include <Windows.h>
#include <time.h> // clock() ���� �����Ͽ� ���α׷� ������ ���� ���� �ð� ����

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
} // gotoxy && Ŀ�� �����

int main() {
	system("mode 80, 25"); // �ܼ�â ũ�� ����

	int q;
	int w;
	int m;
	int cnt;
	int on[2];

	q = clock();
	w = clock(); // �ð� �ʱ�ȭ
	m = 0; // N��
	cnt = 1; // Timer over ����
	on[0] = 0;
	on[1] = 0; // ���� �� ���� ���� ����

	while (1) {
		gotoxy(0, 0);
		printf("%3d�� %3d��", m, (clock() - q) / 1000); // (clock() - q) / 1000 << 1�ʾ� ����

		if ((clock() - q) / 1000 == 60 && on[0] != 1) {
			m++;
			q = clock(); // �ð� �ʱ�ȭ
			on[0] = 1; // ���� �� ���� ���� ���� ON
		}
		else if ((clock() - q) / 1000 == 0) on[0] = 0; // ���� �� ���� ���� ���� OFF

		gotoxy(0, 5);
		printf("%3d�� ����", 10 - (clock() - w) / 1000); // 10 - (clock() - w) / 1000 << 10�ʿ��� 1�ʾ� ����

		if (10 - (clock() - w) / 1000 == 0 && on[1] != 1) {
			if (cnt == 1) {
				gotoxy(2, 6);
				printf("Time over!");
				cnt++; // Time over ���� �� ����
			}
			else {
				gotoxy(2, 6);
				printf("Time over! * %d", cnt);
				cnt++;
			}
			w = clock(); // �ð� �ʱ�ȭ
			on[1] = 1; // ���� �� ���� ���� ���� ON
		}
		else if ((clock() - w) / 1000 == 0) on[1] = 0; // ���� �� ���� ���� ���� OFF

		Sleep(1); // CPU ������ �ٿ��ֱ� ����
	}
}