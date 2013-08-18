/*UDP client*/
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	SOCKET sockClient;
	SOCKADDR_IN addrSrv;
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];

	int len=sizeof(SOCKADDR);

	int err;
	wVersionRequested=MAKEWORD(2,2);

	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
		return ;

	sockClient=socket(AF_INET,SOCK_DGRAM,0);

	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	while(1)
	{
		printf("please input data:\n");
		gets(sendBuf);
		sendto(sockClient,sendBuf,strlen(sendBuf)+1,0
			,(SOCKADDR*)&addrSrv,len);
		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);

		if('q'==recvBuf[0])
		{
			sendto(sockClient,"q",strlen("q")+1,0,
				(SOCKADDR*)&addrSrv,len);
			printf("chat end\n");
			break;
		}
		sprintf(tempBuf,"%s say :%s",inet_ntoa(addrSrv.sin_addr),recvBuf);
		printf("%s\n",tempBuf);
	}
	closesocket(sockClient);
	WSACleanup();
}
