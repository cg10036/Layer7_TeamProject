#include <stdio.h>
#include <Windows.h>
#include <time.h> // clock() 으로 설정하여 프로그램 구동에 관계 없이 시간 측정

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main() {
	system("mode 80, 25");

	int q;
	int w;
	int m;
	int cnt;
	int on[2];

	q = clock();
	w = clock();
	m = 0;
	cnt = 1;
	on[0] = 0;
	on[1] = 0;

	while (1) {
		gotoxy(0, 0);
		printf("%3d분 %3d초", m, (clock() - q) / 1000);

		if ((clock() - q) / 1000 == 60 && on[0] != 1) {
			m++;
			q = clock();
			on[0] = 1;
		}
		else if ((clock() - q) / 1000 == 0) on[0] = 0;

		gotoxy(0, 5);
		printf("%3d초 남음", 10 - (clock() - w) / 1000);

		if (10 - (clock() - w) / 1000 == 0 && on[1] != 1) {
			if (cnt == 1) {
				gotoxy(2, 6);
				printf("Time over!");
				cnt++;
			}
			else {
				gotoxy(2, 6);
				printf("Time over! * %d", cnt);
				cnt++;
			}
			w = clock();
			on[1] = 1;
		}
		else if ((clock() - w) / 1000 == 0) on[1] = 0;

		Sleep(1);
	}
}