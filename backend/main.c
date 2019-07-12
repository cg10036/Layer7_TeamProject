#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <strings.h> 
#include <wtypes.h>
#include <ctype.h>
#include <oleauto.h>
 
SOCKET HTTPConnectToServer(char* server){
	SOCKADDR_IN serverInfo;
	SOCKET sck; 
	WSADATA wsaData; 
	LPHOSTENT hostEntry; 
	WSAStartup(MAKEWORD(2,2),&wsaData);
	hostEntry = gethostbyname(server);
	if(!hostEntry){  
		WSACleanup();  
		return 0; 
	} 
	sck = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sck==INVALID_SOCKET){
		WSACleanup(); 
		puts("Failed to setup socket");
		getchar(); 
		return 0; 
	} 
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr   = *((LPIN_ADDR)*hostEntry->h_addr_list); 
	serverInfo.sin_port   = htons(80); 
	int i = connect(sck,(LPSOCKADDR)&serverInfo,sizeof(struct sockaddr));
	
	if(sck==SOCKET_ERROR) return 0;
	if(i!=0) return 0;
	
	return sck;
}
 
void HTTPRequestPage(SOCKET s,char *page,char *host){
	unsigned int len;
	if(strlen(page)>strlen(host)){
		len=strlen(page);
	}else len = strlen(host);
	
	char message[20+len];
	if(strlen(page)<=0){
		strcpy(message,"GET / HTTP/1.1\r\n");
	}else sprintf(message,"GET %s HTTP/1.1\r\n",page);
	send(s,message,strlen(message),0);
	
	memset(message,0,sizeof(message));
	sprintf(message,"Host: %s\r\n\r\n",host);
	send(s,message,strlen(message),0);
}
 
int DownloadToBuffer(char * webpage,char * buffer,unsigned long max){
	if(webpage==NULL||buffer==NULL||max==0) return FALSE;
	
	unsigned short shift=0;
	if(strncasecmp(webpage,"http://",strlen("http://"))==0){
		shift=strlen("http://");
	}
	if(strncasecmp(webpage+shift,"www.",strlen("www."))==0){
		shift+=strlen("www.");
	}
	char cut[strlen(webpage)-shift+1];
	strcpy(cut,strdup(webpage+shift));
	
	char *server = strtok(cut,"/");
	
	char *page = strdup(webpage+shift+strlen(server));
	
	SOCKET s = HTTPConnectToServer(server);
	HTTPRequestPage(s,page,server);
	
	int i = recv(s,buffer,max,0);
	closesocket(s);
	
	if(i<=0) return 1;
	return 0;
}

char usedString[300][50];
int usedStringCnt = 0;

int Find(char Word, char* Dest)
{
	char buffer[2000], url[100] = "http://sunrin.duckdns.org/api/word.php?Mode=Find&Word=", word[200][100];
	memset(buffer, 0, sizeof(buffer));
	memset(word, 0, sizeof(word));
	url[strlen(url)] = Word;
	url[strlen(url)] = '\0';
	DownloadToBuffer(url, buffer, sizeof(buffer));
	int i, j = 0, k = 0;
	for(i = 0;buffer[i] != '\0';i++)
	{
		if(buffer[i] == '\n')
		{
			word[j][k] = '\0';
			k = 0;
			j++;
			continue;
		}
		word[j][k++] = buffer[i];
	}
	for(i = 0;i < 194;i++)
	{
		for(j = 0;j < usedStringCnt;j++)
		{
			if(!strcmp(word[i + 7], usedString[j]))
			{
				break;
			}
		}
		if(j == usedStringCnt)
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
	char buffer[2000], url[100] = "http://sunrin.duckdns.org/api/word.php?Mode=Check&Word=", word[200][100];
	memset(buffer, 0, sizeof(buffer));
	memset(word, 0, sizeof(word));
	strcat(url, Check);
	DownloadToBuffer(url, buffer, sizeof(buffer));
	int i, j = 0, k = 0;
	for(i = 0;buffer[i] != '\0';i++)
	{
		if(buffer[i] == '\n')
		{
			word[j][k] = '\0';
			k = 0;
			j++;
			continue;
		}
		word[j][k++] = buffer[i];
	}
	if(!strcmp(word[6], "OK"))
	{
		return 1; //TRUE
	}
	return 0; //FALSE
}

int main(int argc,char *argv[]){
	char a[50], check_char = 0, b = 0, i;
	while(1)
	{
		scanf("%s", a);
		for(i = 0;i < usedStringCnt;i++)
		{
			if(!strcmp(a, usedString[i]))
			{
				b = 1;
				break;
			}
		}
		if(!Check(a) || !(check_char == '\0' || a[0] == check_char) || strlen(a) <= 1 || b)
		{
			printf("GAMEOVER\n");
			return; //GAMEOVER
		}
		strcpy(usedString[usedStringCnt++], a);
		if(!Find(a[strlen(a) - 1], a))
		{
			printf("YOUWIN\n");
			return; //YOUWIN
		}
		printf("%s\n", a);
		check_char = a[strlen(a) - 1];
	}
}
