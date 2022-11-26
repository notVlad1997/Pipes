
#include <Windows.h>
#include <iostream>
using namespace std;



int main()
{
	cout << "\t\t named pipe server..." << endl;
	HANDLE hCreateNamedPipe;
	char szInputBuffer[1023];
	char szOutputBuffer[1023];
	DWORD dwszInputBuffer = sizeof(szInputBuffer);
	DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

	BOOL bConnectNamedPipe;

	BOOL bWritefile;
	char szWriteFileBuffer[1023] = "Hello from NamedPipe server!!";
	DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesWrite;

	BOOL bFlushFileBuffer;

	BOOL bReadfile;
	char szReadFileBuffer[1023];
	DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesRead;
	const wchar_t* name = L"\\\\.\\pipe\\MYNAMEDPIPE";
	for (int j = 1; j <= 10; j++)
	{
		switch (j)
		{
		case 1:
			name = L"\\\\.\\pipe\\MYNAMEDPIP1";
			break;
		case 2:
			name = L"\\\\.\\pipe\\MYNAMEDPIP2";
			break;
		case 3:
			name = L"\\\\.\\pipe\\MYNAMEDPIP3";
			break;
		case 4:
			name = L"\\\\.\\pipe\\MYNAMEDPIP4";
			break;
		case 5:
			name = L"\\\\.\\pipe\\MYNAMEDPIP5";
			break;
		case 6:
			name = L"\\\\.\\pipe\\MYNAMEDPIP6";
			break;
		case 7:
			name = L"\\\\.\\pipe\\MYNAMEDPIP7";
			break;
		case 8:
			name = L"\\\\.\\pipe\\MYNAMEDPIP8";
			break;
		case 9:
			name = L"\\\\.\\pipe\\MYNAMEDPIP9";
			break;
		case 10:
			name = L"\\\\.\\pipe\\MYNAMEDPI10";
			break;
		}

		hCreateNamedPipe = CreateNamedPipe(
			name,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			dwszOutputBuffer,
			dwszInputBuffer,
			0,
			NULL);
		if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
		{
			cout << "NamedPipe creation failed && Error No" << GetLastError() << endl;
		}
		cout << "Succes" << endl;

		bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
		if (bConnectNamedPipe == FALSE)
		{
			cout << "Conection failed & Error number " << GetLastError() << endl;
		}
		cout << "Connection Success";

		bWritefile = WriteFile(
			hCreateNamedPipe,
			szWriteFileBuffer,
			dwWriteBufferSize,
			&dwNoBytesWrite,
			NULL);

		if (bWritefile == FALSE)
		{
			cout << "WriteFile Failed = " << GetLastError() << endl;
		}
		cout << "WriteFile Success" << endl;

		bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);

		if (bFlushFileBuffer == FALSE)
		{
			cout << "FlushFileBuffer Failed & Failed Error No" << GetLastError() << endl;
		}
		cout << "ReadFile Succes" << endl;

		bReadfile = ReadFile(
			hCreateNamedPipe,
			szReadFileBuffer,
			dwReadBufferSize,
			&dwNoBytesWrite,
			NULL);

		if (bReadfile == FALSE)
		{
			cout << "ReadFile Failed = " << GetLastError() << endl;
		}
		cout << "ReadFile Success" << endl;

		cout << "Data Reading from cliend " << szReadFileBuffer << endl;

		DisconnectNamedPipe(hCreateNamedPipe);

		CloseHandle(hCreateNamedPipe);

		//system("PAUSE");
	}


	return 0;
}

