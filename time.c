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
} // gotoxy && 커서 지우기

int main() {
	system("mode 80, 25"); // 콘솔창 크기 조절

	int q;
	int w;
	int m;
	int cnt;
	int on[2];

	q = clock();
	w = clock(); // 시간 초기화
	m = 0; // N분
	cnt = 1; // Timer over 개수
	on[0] = 0;
	on[1] = 0; // 변수 값 증가 오류 방지

	while (1) {
		gotoxy(0, 0);
		printf("%3d분 %3d초", m, (clock() - q) / 1000); // (clock() - q) / 1000 << 1초씩 증가

		if ((clock() - q) / 1000 == 60 && on[0] != 1) {
			m++;
			q = clock(); // 시간 초기화
			on[0] = 1; // 변수 값 증가 오류 방지 ON
		}
		else if ((clock() - q) / 1000 == 0) on[0] = 0; // 변수 값 증가 오류 방지 OFF

		gotoxy(0, 5);
		printf("%3d초 남음", 10 - (clock() - w) / 1000); // 10 - (clock() - w) / 1000 << 10초에서 1초씩 감소

		if (10 - (clock() - w) / 1000 == 0 && on[1] != 1) {
			if (cnt == 1) {
				gotoxy(2, 6);
				printf("Time over!");
				cnt++; // Time over 개수 값 증가
			}
			else {
				gotoxy(2, 6);
				printf("Time over! * %d", cnt);
				cnt++;
			}
			w = clock(); // 시간 초기화
			on[1] = 1; // 변수 값 증가 오류 방지 ON
		}
		else if ((clock() - w) / 1000 == 0) on[1] = 0; // 변수 값 증가 오류 방지 OFF

		Sleep(1); // CPU 차지를 줄여주기 위함
	}
}