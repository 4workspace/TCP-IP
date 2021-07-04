#include <WinSock2.h>
#include <iostream>

using namespace std;

int main()
{

    cout << ".............TCP CLIENT..........." << endl;
    cout << endl;
    // local veriable
    // initialize DLL
    WSADATA WinSocketData ;
    int iWsaStartup;
    int iWsaCleanUp;

    SOCKET TCPClientSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;

    int iConnect;

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = sizeof(RecvBuffer) + 1;           //(old) strlen(RecvBuffer)

    int iSend;
    char SenderBuffer[512] = "Hello from Client!";
    int iSenderBuffer = sizeof(SenderBuffer) + 1;       //(old) strlen(SenderBuffer)


    //STEP - 1 WSAStartup Fun
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &WinSocketData);
    if(iWsaStartup != 0)
    {
        cout << "WSAStartup Failed!" << endl;
    }
    cout << "WSAStartup Success" << endl;

    //STEP - 2 fill the Structure
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(TCPClientSocket == INVALID_SOCKET)
    {
        cout << "TCP Client Scket Creation Failed" << WSAGetLastError() << endl;
    }
    cout << "TCP Client Socket Creation Success" << WSAGetLastError() << endl;

    //STEP - 3 Socket Creation
    TCPServerAdd.sin_family = AF_INET;                      // The internet protocol version 4 (Pv4) address family
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //STEP-4 bind func
    iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if(iConnect == SOCKET_ERROR)
    {
        cout << "Connction filed & Error no-> " << WSAGetLastError() << endl;
    }
    cout << "Connection Success"<< endl;

    //STEP-5 RECV data from server side
    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
    if(iRecv == SOCKET_ERROR)
    {
        cout << "Receive data failed & error no->" << WSAGetLastError() << endl;
    }
    cout << "DATA RECEİVED" << endl;

    // STEP-6 Sent data to server
    iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed & Error no-> " << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;

    // STEP-7 Close Socket func.
    iCloseSocket = closesocket(TCPClientSocket);
    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing socket failed & Error no-> " << WSAGetLastError <<endl;
    }
    cout << "Closing socket success" << endl;

    //STEP-8 WSA cleanup func.
    iWsaCleanUp = WSACleanup();
    if(iWsaCleanUp == SOCKET_ERROR)
    {
        cout << "CleanUp fun Failed & Error no -> " << WSAGetLastError() << endl;
    }
    cout << "CleanUp Fun Success" << endl;

    system("PAUSE");
    return 0;
}