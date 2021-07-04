#include <WinSock2.h>
#include <iostream>


using namespace std;

int main()
{

    cout << ".............TCP SERVER..........." << endl;
    cout << endl;
    // local veriable
    // initialize DLL
    WSADATA WinSocketData ;
    int iWsaStartup;
    int iWsaCleanUp;

    SOCKET TCPServerSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);

    int iBind;
    int iListen;

    SOCKET sAcceptSocket;

    int iSend;
    char SenderBuffer[512] = "Hello from server!";
    int iSenderBuffer = sizeof(SenderBuffer) + 1;       //(old) strlen(SenderBuffer)

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = sizeof(RecvBuffer) + 1;           //(old) strlen(RecvBuffer)

    //STEP - 1 WSAStartup Fun
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &WinSocketData);
    if(iWsaStartup != 0)
    {
        cout << "WSAStartup Failed!" << endl;
    }
    cout << "WSAStartup Success" << endl;

    //STEP - 2 fill the Structure
    TCPServerAdd.sin_family = AF_INET;                      // The internet protocol version 4 (Pv4) address family
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //STEP - 3 Socket Creation
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //socket() funtion is return value is INVALED_SOCKET 
    if(TCPServerSocket == INVALID_SOCKET)
    {
        cout << "TCP Server Socket Creation Failed!" << WSAGetLastError() << endl;
    }
    cout << "TCP Server Socket Creation Success" << endl;

    //STEP-4 bind fun
    iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd,sizeof(TCPServerAdd));
    if(iBind == SOCKET_ERROR)
    {
        cout << "Binding Failed! & Error no-> " << WSAGetLastError() << endl;
    }
    cout << "Binding Success" << endl;

    //STEP-5 Listen socket
    iListen = listen(TCPServerSocket, 2);
    if(iListen == SOCKET_ERROR)
    {
        cout << "Listen func. failed & error no->" << WSAGetLastError() << endl;
    }
    cout << "listen func. success" << endl;

    // STEP-6 Accept
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if(sAcceptSocket == INVALID_SOCKET)
    {
        cout << "Accept Failed & Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Conection Accepted! " << endl;

    // STEP-7 Send Data to Client
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed & Error no-> " << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;

    //STEP-8 Recv Data from Client
    iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
    if(iRecv == SOCKET_ERROR)
    {
        cout << "Receive Data Failed & Error No-> " << WSAGetLastError() << endl;
    }
    cout << "DATA RECIEVED -> " << RecvBuffer << endl;
    
    //STEP-9 Close Socket
    iCloseSocket = closesocket(TCPServerSocket);
    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closed Socket Failed & Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success ->" << endl;

    //STEP-10 Clean up from DLL
    iWsaCleanUp = WSACleanup();
    if(iWsaCleanUp == SOCKET_ERROR)
    {
        cout << "CleanUp fun Failed & Error no -> " << WSAGetLastError() << endl;
    }
    cout << "CleanUp Fun Success" << endl;
    
    system("PAUSE");
    return 0;
}