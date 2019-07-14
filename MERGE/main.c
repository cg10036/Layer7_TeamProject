#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 0 :: ������ 
// 7 :: ���
// 96 :: Ÿ�̸� ���, ������ 
// 100 :: Ÿ�̸� ���, ������ 
// 109 :: Ÿ�̸� ��
// 114 :: ȸ�� ���, �ʷϻ� �� 
// 120 :: ä�� 
// 124 :: ȸ�� ���, ������ 
// 128 :: �ܾ�� ��

char usedString[300][50];
int usedStringCnt = 0;

void soundplayer(int mode, int flag)
{
	switch(mode)
	{
		case 1:
			if(flag)
			{
				mciSendString("play main.mp3", NULL, 0, NULL);
			}
			else
			{
				mciSendString("stop main.mp3", NULL, 0, NULL);
			}
			break;
		case 2:
			if(flag)
			{
				if(rand() % 2)
				{
					mciSendString("play bye1.mp3", NULL, 0, NULL);
				}
				else
				{
					mciSendString("play bye2.mp3", NULL, 0, NULL);
				}
			}
			else
			{
				mciSendString("stop bye1.mp3", NULL, 0, NULL);
				mciSendString("stop bye2.mp3", NULL, 0, NULL);
			}
			break;
		default:
			break;
	}
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void set_color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

void remove_cursor(int num)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = num;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void title()
{
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

	set_color(7); // ������� ���� ����
}

int timer(int n)
{
	int q;
	
	q = clock(); // ���� ��ǻ�� �ð����� �ʱ�ȭ
	
	return n - (clock() - q) / 1000; // n - q �� ��ȯ 
} // if (_kbhit()) ���� ���� ��� �޴´�. 

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
	set_color(7); // ���� �Ͼ��
	gotoxy(x, y);    //Ŀ���� 15,15�� �ű� 
	for (i = 0; i <= 8; i++) { gotoxy(x, y--); printf("|"); Sleep(20); } //�ö󰡱�
	for (i = 0; i <= 17; i++) { printf("��"); x += 2; Sleep(20); } //������ ����
	x -= 1;  //x�� 1���� 
	for (i = 0; i <= 8; i++) { gotoxy(x, ++y); printf("|"); Sleep(20); } //�Ʒ��� ����
	for (i = 0; i < 17; i++) { x -= 2; gotoxy(x, y); printf("��"); Sleep(20); } //��� ���� 

	//==========================================================================================================
	//����� ���� ����, ���� ����, ���� ���� �κ�
	gotoxy(35, 8); // ���ڸ� ���� ���� ��ǥ�� ������ 
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
		soundplayer(1, 1);
		return 0; //���� �����ϱ⸦ ������ �Լ��� Ż���ϱ� 
	}
	else if (flag == 1)//���� ���� ��Ģ ������ �����ٸ� 
	{
		system("cls"); //ȭ�� ����� 
		int key = 0;
		
		/*
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
		*/
		
		for (i = 0; i < 25; i++) //�ð��� ��� 
		{
			gotoxy(3, i); printf("|");
		}

		set_color(7); // ��� �۾�

		//���
		gotoxy(10, 4); printf("< End-to-End >�� �����ձ� �����Դϴ�.\n");
		gotoxy(10, 5); printf("��������� PC���� ���!!\n");
		gotoxy(10, 6); printf("���� Ű�� ������ �ٽ� ����ȭ������ ���ư��ϴ�.");
		gotoxy(10, 7); printf("Ready start!!\n");

		gotoxy(10, 10);  printf("< End-to-End > is an end-to-end game.\n");
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
				//========================================================

				// ��ٸ��°Ϳ� ��ģ �������� ���� . . .

				gotoxy(0, 0);
				set_color(0xE); // ��������� ���� ��ȯ
				printf("�� �� �� ��");
				gotoxy(0, 0);
				Sleep(200);
				printf("�� �� �� ��");
				gotoxy(0, 0);
				Sleep(200);
				printf("�� �� �� ��");
				Sleep(200);
				gotoxy(0, 0);
				printf("%12c", ' ');
				gotoxy(0, 0);
				printf("����� . . .");
				Sleep(200);
				gotoxy(0, 0);
				printf("%13c", ' ');
				set_color(7); // ������� ���� ��ȯ

				//========================================================

				HomePrinter();  //InitPrint() �Լ��� �ٽ� ȣ��
			}
		}
	}
	else
	{
		system("cls");
		soundplayer(2, 1);
		Sleep(2000);
		soundplayer(2, 0);
		exit(0); //���� 
	}
}

SOCKET HTTPConnectToServer(char* server)
{
	int i;
	SOCKADDR_IN serverInfo;
	SOCKET sck; 
	WSADATA wsaData; 
	LPHOSTENT hostEntry; 
	WSAStartup(MAKEWORD(2,2),&wsaData);
	hostEntry = gethostbyname(server);
	
	if (!hostEntry)
	{  
		WSACleanup();  
		return 0; 
	} 
	sck = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sck==INVALID_SOCKET)
	{
		WSACleanup(); 
		puts("Failed to setup socket");
		getchar(); 
		return 0; 
	} 
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr   = *((LPIN_ADDR)*hostEntry->h_addr_list); 
	serverInfo.sin_port   = htons(80); 
	i = connect(sck,(LPSOCKADDR)&serverInfo,sizeof(struct sockaddr));
	
	if (sck==SOCKET_ERROR) return 0;
	if (i!=0) return 0;
	
	return sck;
}
 
void HTTPRequestPage(SOCKET s,char *page,char *host)
{
	unsigned int len;
	if (strlen(page) > strlen(host))
	{
		len=strlen(page);
	}
	else len = strlen(host);
	
	char message[20+len];
	if (strlen(page)<=0)
	{
		strcpy(message,"GET / HTTP/1.1\r\n");
	}
	else sprintf(message,"GET %s HTTP/1.1\r\n",page);
	send(s,message,strlen(message),0);
	
	memset(message,0,sizeof(message));
	sprintf(message,"Host: %s\r\n\r\n",host);
	send(s,message,strlen(message),0);
}
 
int DownloadToBuffer(char * webpage,char * buffer,unsigned long max)
{
	int i;
	char *server, *page;
	
	if (webpage==NULL||buffer==NULL||max==0) return FALSE;
	
	unsigned short shift=0;
	if (strncasecmp(webpage,"http://",strlen("http://"))==0)
	{
		shift=strlen("http://");
	}
	if (strncasecmp(webpage+shift,"www.",strlen("www."))==0)
	{
		shift+=strlen("www.");
	}
	char cut[strlen(webpage)-shift+1];
	strcpy(cut,strdup(webpage+shift));
	
	server = strtok(cut,"/");
	page = strdup(webpage+shift+strlen(server));
	
	SOCKET s = HTTPConnectToServer(server);
	HTTPRequestPage(s,page,server);
	
	i = recv(s,buffer,max,0);
	closesocket(s);
	
	if (i <= 0) return 1;
	return 0;
}

int Find(char Word, char* Dest)
{
	int i, j = 0, k = 0;
	char buffer[2000], word[200][100];
	char url[100] = "http://sunrin.duckdns.org/api/word.php?Mode=Find&Word=";
	memset(buffer, 0, sizeof(buffer));
	memset(word, 0, sizeof(word));
	url[strlen(url)] = Word;
	url[strlen(url)] = '\0';
	DownloadToBuffer(url, buffer, sizeof(buffer));
	
	for (i = 0;buffer[i] != '\0';i++)
	{
		if (buffer[i] == '\n')
		{
			word[j][k] = '\0';
			k = 0;
			j++;
			continue;
		}
		word[j][k++] = buffer[i];
	}
	for (i = 0;i < 194;i++)
	{
		for (j = 0;j < usedStringCnt;j++)
		{
			if (!strcmp(word[i + 7], usedString[j]))
			{
				break;
			}
		}
		if (j == usedStringCnt)
		{
			strcpy(usedString[usedStringCnt++], word[i + 7]);
			strcpy(Dest, word[i + 7]);
			return 1;
		}
	}
	return 0;
}

int Check(char* Check)
{
	int i, j = 0, k = 0;
	char buffer[2000], word[200][100];
	char url[100] = "http://sunrin.duckdns.org/api/word.php?Mode=Check&Word=";
	memset(buffer, 0, sizeof(buffer));
	memset(word, 0, sizeof(word));
	strcat(url, Check);
	DownloadToBuffer(url, buffer, sizeof(buffer));
	
	for (i = 0;buffer[i] != '\0';i++)
	{
		if (buffer[i] == '\n')
		{
			word[j][k] = '\0';
			k = 0;
			j++;
			continue;
		}
		word[j][k++] = buffer[i];
	}
	if (!strcmp(word[6], "OK"))
	{
		return 1; //TRUE
	}
	return 0; //FALSE
}

int main(int argc,char *argv[]){
	srand(time(NULL));
	char a[50];
	char check_char = 0;
	char b = 0;
	char *sa; // ���ڿ� ���� ���� 
	char *ca; // �� ���ھ� ��� 
	int t_on = 0; // Ÿ�̸� ����? 
	int scnt; // ī��Ʈ 
	int timer; // timer
	int rnd; // round
	int rtm; // com �ӵ� ��ȯ 
	int q = clock();
	int w = clock();
	int e = clock();
	int r = clock();
	int m = 0, cnt = 1, i;
	int on[2] = { 0, };
	int count = 0;
	
	int x, y;
	int cx, cy;
	
	x = 22;
	y = 4;
	
	cx = 58;
	cy = 6;
	
	scnt = 0;
	timer = 10;
	rnd = 1;
	rtm = 0;
	
	system("mode con cols=80 lines=25"); //ó�� ũ�� ���� 
	HomePrinter();
	system("cls"); // ȭ�� �ʱ�ȭ
	title();
	//region Tiny-Bug-fix by leesoohyuk
	q = clock();
	w = clock();
	e = clock();
	//endregion
	
	while (1)
	{	
		if (_kbhit())
		{	
			scnt++;
			scanf("%s", a);
			set_color(7);
			
			if (timer - (clock() - r) / 1000 <= 0) {
				gotoxy(22, 1);
				set_color(100);
				printf("%22c", ' ');
				gotoxy(22, 1);
				printf("Time Over\n");
				set_color (7);
				
				Sleep(2000);
				mciSendString("stop main.mp3", NULL, 0, NULL);
				system("cls");
				main(0,0); 
				
				exit(0);
			}
			
			printf("\n");
			
			gotoxy(cx - 6, cy);
			set_color(112);
			for (i = 0; i < 3; i++) {
				printf("@ ");
				Sleep(200);
			}
			
			for (i = 0;i < usedStringCnt;i++)
			{
				if (!strcmp(a, usedString[i]))
				{
					b = 1;
					break;
				}
			}
			
			gotoxy(cx - 6, cy);
			set_color(112);
			printf("      ");
			
			if (!Check(a) || !(check_char == '\0' || a[0] == check_char) || strlen(a) <= 1 || b)
			{
				gotoxy(22, 1);
				set_color(100);
				printf("%22c", ' ');
				gotoxy(22, 1);
				printf("GAME OVER\n");
				set_color(0);
				Sleep(2500);
				
				mciSendString("stop main.mp3", NULL, 0, NULL);
				system("cls");
				
				main(0,0);
						
				exit(0); //GAMEOVER
			}
			else {
				gotoxy(22, 1);
				set_color(96);
				printf("%22c");
				gotoxy(22, 1);
				printf("pass!");
				Sleep(500);
				gotoxy(22, 1);
				printf("%6c", ' ');
			}
			
			if (scnt == 5) {
				gotoxy(22, 1);
				set_color(100);
				printf("%22c", ' ');
				gotoxy(22, 1);
				printf("YOU WIN\n");
				set_color(0);
				Sleep(2500);
				mciSendString("stop main.mp3", NULL, 0, NULL);
				system("cls");
				main(0, 0);
				exit(0); //YOUWIN
			}
			
			strcpy(usedString[usedStringCnt++], a);
			if (!Find(a[strlen(a) - 1], a))
			{
				gotoxy(22, 1);
				set_color(100);
				printf("%22c", ' ');
				gotoxy(22, 1);
				printf("YOU WIN\n");
				set_color(0);
				Sleep(2500);
				system("cls");
				exit(0); //YOUWIN
			}
			
			sa = a;
			ca = a;
			
			i = 0;
			
			//region Tiny-Print-Fix by leesoohyuk
			for (; *sa != '\0'; sa++) i++;
			gotoxy((cx - i), cy);
			set_color(112);
			//printf("%s\n", a);
			for (; *ca != '\0'; ca++) {
				printf("%c", *ca);
				if (rtm < 2) {
					Sleep(400);
					rtm++;
				} 
				else if (rtm < 4) {
					Sleep(70);
					rtm++;
				}
				else Sleep(50);
			}
			//gotoxy(22, 4);
			//printf("%20c", ' ');
			y+=4;
			cy+=4;
			//endregion
			check_char = a[strlen(a) - 1];
			//region Tiny-Bug-Fix by leesoohyuk
			w = clock();
			e = clock();
			//endregion
			check_char = a[strlen(a) - 1];
			
			t_on = 0;
			if (timer > 7) timer-=3;
			else timer-=2;
		}
		else if (t_on == 0) {
			r = clock();
			t_on = 1;
			gotoxy(22, 1);
			set_color(96);
			printf("%d�� �ȿ� �Է��Ͻÿ�.", timer);
			gotoxy(49, 1);
			printf("round : %d", rnd);
			rnd++;
			gotoxy(x, y);
			set_color(112);
			printf("$ ");
		}
		else
		{
			//endregion
			/*
			if (10 - (clock() - r) / 1000 == 0 && on[1] != 1) {
				if (cnt == 1) {
					gotoxy(35, 13);
					set_color(124);
					printf("Time over!");
					set_color(0);
					cnt++;
					break;
				}
				else {
					gotoxy(35, 13);
					set_color(124);
					printf("Time over! * %d", cnt);
					set_color(0);
					cnt++;
					break;
				}
				r = clock();
				on[1] = 1;
			}
			else if ((clock() - r) / 1000 == 0) on[1] = 0;
			*/
	
			Sleep(1);
		}
	}
	
	_getch();
	exit(0);
}
