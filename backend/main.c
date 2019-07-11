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

int Search(char* buffer, char* _input)
{
	if(strlen(_input) > 1)
	{
		char input[22] = "|";
		strcat(input, _input);
		strcat(input, "|");
		char *ptr = strstr(buffer, input);
		if(ptr == NULL)
		{
			return 0;
		}
		return 1;
	}
	else
	{
		int i, j, k = 0;
		char word[30][50] = { 0 };
		for(i = 0;buffer[i - 1] != '[';i++)
		{
			
		}
		for(;buffer[i] != '\0';i++)
		{
			if(buffer[i - 5] == 'k' && buffer[i - 4] == 'u' && buffer[i - 3] == 'e' && buffer[i - 2] == 'k' && buffer[i - 1] == '|')
			{
				for(j = 0;buffer[i + j] != '|';j++)
				{
					word[k][j] = buffer[i + j];
				}
				word[k][j] = '\0';
				i += j + 1;
				for(j = 0;buffer[i + j] != '\"';j++)
				{
					if((buffer[i + j] >= 'A' && buffer[i + j] <= 'Z') || (buffer[i + j] >= 'a' && buffer[i + j] <= 'z'))
					{
						break;
					}
				}
				if(buffer[i + j] == '\"' && strlen(word[k]) > 1)
				{
					k++;
				}
				else if(buffer[i] == _input[0])
				{
					for(j = 0;((buffer[i + j] >= 'a' && buffer[i + j] <= 'z') || (buffer[i + j] >= 'A' && buffer[i + j] <= 'Z'));j++)
					{
						word[k][j] = buffer[i + j];
					}
					word[k][j] = '\0';
					k++;
				}
				else
				{
					for(j = 0;word[k][j] != '\0';j++)
					{
						word[k][j] = '\0';
					}
				}
			}
		}
		for(i = 0;i < 30;i++)
		{
			printf("%s\n", word[i]);
		}
	}
}

int main(int argc,char *argv[]){
	char buffer[2000], input[20], url[110] = "http://suggest.dic.daum.net/dic_all_ctsuggest?mod=json&code=utf_in_out&enc=utf&cate=lan&q=";
	memset(buffer,0,sizeof(buffer));
	scanf("%s", input);
	strcat(url, input);
	DownloadToBuffer(url, buffer, sizeof(buffer));
	printf("%s\n", (Search(buffer, input) == 1 ? "YES" : "NO"));
	
	getchar();
	return 0;
}