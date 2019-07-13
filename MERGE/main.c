#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <strings.h> 
#include <wtypes.h>
#include <ctype.h>
#include <oleauto.h>
#include <conio.h>
#include <time.h>

char usedString[300][50];
int usedStringCnt = 0;

void short_gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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

void HomePrinter(void)
{
	int i = 0; //반복에 사용할 변수 i 
	int x = 22, y = 12;  //gotoxy 처음 좌표  
	int keyboard = 0; //키보드 입력을 받아 enterkey를 눌렀는지 확인하는 변수 
	const char *gameTitle = "End-To-End"; //게임 이름
	int flag = 0; //게임 시작, 게임 설명, 게임 종료 중 어떤 것을 선택했는지 판별하는 변수 

	set_color(0xE); //노란색으로 색상 바꿈
	short_gotoxy(63, 24); printf("made by 혁쟁이조"); //창의 밑에 부분에 made by 혁쟁이조를 출력 
	set_color(7); //출력이 끝난 후 색상을 다시 하얀색으로 변경

	//==========================================================================================================
	// 사각형 상자 UI 출력
	
	remove_cursor(0); //커서 없애기 
	short_gotoxy(x, y);    //커서를 15,15로 옮김 
	for (i = 0; i <= 8; i++){ gotoxy(x, y--); printf("|"); Sleep(20); } //올라가기
	for (i = 0; i <=17; i++){ printf("￣"); x += 2;Sleep(20); } //→으로 가기
	x -= 1;  //x를 1감소 
	for (i = 0; i <= 8; i++){ gotoxy(x, ++y); printf("|"); Sleep(20); } //아래로 가기
	for (i = 0; i < 17; i++){ x -= 2;gotoxy(x, y);printf("＿"); Sleep(20); } //→로 가기 

	//==========================================================================================================
	//제목과 게임 시작, 게임 설명, 게임 종료 부분
	short_gotoxy(34, 8); // 글자를 쓰기 위해 좌표를 재조정 
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

	while (_kbhit()) //수혁아 이거 어떻게 해야 돼? 
	{
		_getch();
	}

	Sleep(200); //아래 글자가 나오기 전에 잠깐의 waiting 
	remove_cursor(0); //커서 없애기
	short_gotoxy(24, 14); printf("☞ 게임 시작");
	short_gotoxy(24, 15); printf("   게임 설명");
	short_gotoxy(24, 16); printf("   끝내기");
	short_gotoxy(22, 14); //기본적으로 손 모양 이모티콘이 게임 시작을 가리키고 있기 위해 좌표 설정 

	//==========================================================================================================
	// 손모양 이모티콘 움직이기+게임 설명을 듣고 난 후 설정 
	
	y = 14;
	while (keyboard != 13)
	{
		keyboard = getch();
		switch (keyboard)
		{
			case 72: 
				if (y <= 14)continue;
				short_gotoxy(24, y); printf("  "); short_gotoxy(24, --y); printf("☞");
				flag =  y == 14 ? 0 : 1;
				break;
			case 80: 
				if (y >= 16)continue;
				short_gotoxy(24, y); printf("  "); short_gotoxy(24, ++y); printf("☞");
				flag = y== 15 ? 1 : 2;
				break;
		}
			
	}

	if (flag == 0) //만약 게임 시작하기를 눌렀다면
	{
		system("cls"); //화면 지우기
		return; //게임 시작하기를 누르면 함수를 탈출하기 
	}
	else if(flag==1)//만약 게임 규칙 설명을 눌렀다면 
	{
		system("cls"); //화면 지우기 
		int key=0;

		for (i = 0; i < 25; i++) //시각적 요소 
		{
			short_gotoxy(3, i); printf("|");
		}
		//대사
		short_gotoxy(10, 4); printf("< End-to-End >는 끝말잇기 게임입니다.\n");
		short_gotoxy(10, 5); printf("흥미진진한 PC와의 대결!!\n");
		short_gotoxy(10, 6); printf("엔터 키를 누르면 다시 메인화면으로 돌아갑니다.");
		short_gotoxy(10, 7); printf("Ready start!!\n");
		
		short_gotoxy(10, 10); printf("<End-to-End> is an end-to-end game.\n");
		short_gotoxy(10, 11); printf("A battle against an exciting PC!!\n");
		short_gotoxy(10, 12); printf("Press the Enter key to return to the main screen.\n");
		short_gotoxy(10, 13); printf("Ready start!!\n");

		set_color(0xE); //노란색으로 색깔 변경
		short_gotoxy(60, 24); printf("@copyright 혁쟁이조");
		set_color(7);  //흰색으로 색깔 변경


		while (key != 13)
		{
			key = getch();
			if (key == 13)
			{
				system("cls"); //화면을 지우고 
				Sleep(800);
				HomePrinter();  //InitPrint() 함수를 다시 호출
			}
		}
	}
	else
	{
		exit(0); //종료 
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
	
	char a[50];
	char check_char = 0;
	char b = 0;
	int q = clock();
	int w = clock();
	int e = clock();
	int m = 0, cnt = 1, i;
	int on[2] = { 0, };
	int count = 0;
	
	system("mode con cols=80 lines=25"); //처음 크기 조정 
	HomePrinter();
	while (1)
	{
		if (_kbhit())
		{
			scanf("%s", a);
			if (clock()-e >= 10*1000)
			{
				gotoxy(0, 0);
				printf("%3d분 %3d초", m, (clock() - q) / 1000);
				gotoxy(0, 5);
				printf("0초 남음");
				printf("Time over!\n");
				return 0;
			}
			system("cls");
			for (i = 0;i < usedStringCnt;i++)
			{
				if (!strcmp(a, usedString[i]))
				{
					b = 1;
					break;
				}
			}
			if (!Check(a) || !(check_char == '\0' || a[0] == check_char) || strlen(a) <= 1 || b)
			{
				printf("GAMEOVER\n");
				return; //GAMEOVER
			}
			strcpy(usedString[usedStringCnt++], a);
			if (!Find(a[strlen(a) - 1], a))
			{
				printf("YOUWIN\n");
				return; //YOUWIN
			}
			printf("%s\n", a);
			check_char = a[strlen(a) - 1];
		}
		else
		{
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
					break;
				}
				else {
					gotoxy(2, 6);
					printf("Time over! * %d", cnt);
					cnt++;
					break;
				}
				w = clock();
				on[1] = 1;
			}
			else if ((clock() - w) / 1000 == 0) on[1] = 0;
	
			Sleep(1);
		}
	}
}
