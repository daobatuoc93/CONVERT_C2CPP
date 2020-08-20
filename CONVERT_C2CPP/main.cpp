#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h";
#include "stdint.h"

#include "Socket.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library

struct sockaddr_in client;
struct sockaddr_in server;
WSADATA wsa;
//void T_run_RS(vector<SOCKET> client_connect);
void T_run_RS1(Socket* s);
void T_check_client_void(SOCKET ListenSocket, Socket *s);
void T_run_RS(Socket* s);
//char* get_ip(char* DATA_from_client,int quotation_marks_set);
//vector<SOCKET> T_check_client1( SOCKET ListenSocket);
typedef struct
{
	uint8_t x;
	uint8_t y;
}struct_t;
uint8_t toan_cuc;
//int main_1(int argc, char* argv[])
//{
//	Socket client1;
//	char* ip;
//	ip = (char*)"52.220.188.34";
//	u_short port = 80;
//	client1.Socket_Init(ip, port);
//
//	char* data;
//	data = (char*)"GET /image HTTP/1.1\r\n"\
//		"Host: 52.220.188.34\r\n\r\n";
//	client1.Socket_Send(data, strlen(data));
//
//
//	char src[256];
//	memset(src, 0, sizeof(src));
//	int res = 0;
//	while (1)
//	{
//
//		res += client1.Socket_Recv(src + res, 1);
//		if (strstr(src, "\r\n\r\n") != NULL)
//			break;
//	}
//	printf("%s", src);
//	FILE* fx;
//	fx = fopen("image.jpeg", "a+b");
//	int step = 0;
//	char temp = 0;
//	while (step != 4)
//	{
//		client1.Socket_Recv(&temp, 1);
//		fputc(temp, fx);
//		switch (step)
//		{
//		case 0:
//			if (temp == (char)0xff)
//				step = 1;
//			break;
//		case 1:
//			if (temp == (char)0xd8)
//				step = 2;
//			else
//				step = 1;
//			break;
//		case 2:
//			if (temp == (char)0xff)
//				step = 3;
//			break;
//		case 3:
//			if (temp == (char)0xd9)
//				step = 4;
//			else
//				step = 2;
//			break;
//		}
//	}
//	fclose(fx);
//	return 0;
//}
int main() {
	//Initialize Socket then Create a new Socket to Listen Client.(Upon to Server)
	int a;
	Socket* Client = new Socket(3333);
	thread Checklisten = Client->CHECK_LISTEN_SEVER_th(Client->get_ListenSocket(), Client);
//	thread Check_A = Client->RECV_CLIENTA_th(Client);
	thread Check = Client->RECV_CLIENT_th(Client);
	/*Socket Client(3333);
	vector<SOCKET> client_re;

	printf("\waiting connection from clinent\n");
	thread threadClen_RS112(T_check_client_void, Client.get_ListenSocket(), &Client);
	thread threadClen_RS(T_run_RS, &Client);
	thread threadClen_RS1(T_run_RS1, &Client);*/

	cin >> a;
}
void T_run_RS1(Socket* s) {
	while (1) {
		vector<SOCKET> client_re = s->get_client();
		if (client_re.size() > 1) {
			char buf[4096];
			ZeroMemory(buf, 4096);
			SOCKET cl = client_re[1];
			int derect = recv(cl, buf, 4096, 0);
			printf("\n Client_connect[B] said: %s\r\n", buf);
			send(client_re[0], buf, strlen(buf), 0);
			//		else closesocket(client_connect[i]);
			ZeroMemory(buf, 4096);
		}
	}
}
void T_run_RS(Socket* s) {
	while (1) {
		vector<SOCKET> client_re = s->get_client();
		if (client_re.size() > 1) {
			char buf[4096];
			ZeroMemory(buf, 4096);
			SOCKET cl = client_re[0];
			int derect = recv(cl, buf, 4096, 0);
			printf("\n Client_connect[A] said: %s\r\n", buf);
			send(client_re[1], buf, strlen(buf), 0);
			//		else closesocket(client_connect[i]);
			ZeroMemory(buf, 4096);
		}		
	}
}

char* get_ip(char* DATA_from_client, int quotation_marks_set)
{
	return nullptr;
}



void T_check_client_void(SOCKET ListenSocket, Socket *s)
{
	while (true)
	{
		//create 2 client to accept in here.
		printf("\ACCEPT FUNcTION\n");
		struct sockaddr_in dst;
		socklen_t socksize = sizeof(struct sockaddr_in);
		SOCKET Newclient_CONNECT = accept(ListenSocket, (struct sockaddr*) & dst, &socksize);
		printf("\nIncoming connection from %s - sending welcome\n", inet_ntoa(dst.sin_addr));
		cout << "\nClient connected!" << endl;
		printf("\ndst.sin_addr: %d", dst.sin_addr.S_un.S_un_b.s_b1);
		printf("\ndst.sin_addr: %d", dst.sin_addr.S_un.S_un_b.s_b2);
		printf("\ndst.sin_addr: %d", dst.sin_addr.S_un.S_un_b.s_b3);
		printf("\ndst.sin_addr: %d\n", dst.sin_addr.S_un.S_un_b.s_b4);
		//save information with a new sock;
		s->add_client(Newclient_CONNECT);		
	}
	
}