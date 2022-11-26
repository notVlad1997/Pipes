#include <Windows.h>
#include <iostream>
using namespace std;

bool isPrime(int n)
{

	if (n <= 1)
		return false;


	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return false;

	return true;
}




int main()
{

	int inceput_interval = 0;
	int sfarsit_interval = 1000;

	HANDLE hCreatefile;

	BOOL bReadfile;
	DWORD dwNoBytesRead;
	char szReadFileBuffer[1023];
	DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

	BOOL bWritefile;
	DWORD dwNoBytesWrite;
	char szWriteFileBuffer[1023] = "Hello From NamedPipe Client!";
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);
	const wchar_t* name = L"\\\\.\\pipe\\MYNAMEDPIP1";
	for (int j = 1; j <= 10; j++)
	{

		switch (j)
		{
		case 1:
			name = L"\\\\.\\pipe\\MYNAMEDPIP1";
			inceput_interval = 0;
			sfarsit_interval = 1000;
			break;
		case 2:
			name = L"\\\\.\\pipe\\MYNAMEDPIP2";
			inceput_interval = 1000;
			sfarsit_interval = 2000;
			break;
		case 3:
			name = L"\\\\.\\pipe\\MYNAMEDPIP3";
			inceput_interval = 2000;
			sfarsit_interval = 3000;
			break;
		case 4:
			name = L"\\\\.\\pipe\\MYNAMEDPIP4";
			inceput_interval = 3000;
			sfarsit_interval = 4000;
			break;
		case 5:
			name = L"\\\\.\\pipe\\MYNAMEDPIP5";
			inceput_interval = 4000;
			sfarsit_interval = 5000;
			break;
		case 6:
			name = L"\\\\.\\pipe\\MYNAMEDPIP6";
			inceput_interval = 5000;
			sfarsit_interval = 6000;
			break;
		case 7:
			name = L"\\\\.\\pipe\\MYNAMEDPIP7";
			inceput_interval = 6000;
			sfarsit_interval = 7000;
			break;
		case 8:
			name = L"\\\\.\\pipe\\MYNAMEDPIP8";
			inceput_interval = 7000;
			sfarsit_interval = 8000;
			break;
		case 9:
			name = L"\\\\.\\pipe\\MYNAMEDPIP9";
			inceput_interval = 8000;
			sfarsit_interval = 9000;
			break;
		case 10:
			name = L"\\\\.\\pipe\\MYNAMEDPI10";
			inceput_interval = 9000;
			sfarsit_interval = 10000;
			break;
		}

		hCreatefile = CreateFile(
			name,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hCreatefile)
		{
			cout << "File Creation Failed = " << GetLastError() << endl;

		}



		bReadfile = ReadFile(
			hCreatefile,
			szReadFileBuffer,
			dwReadFileBufferSize,
			&dwNoBytesRead,
			NULL);
		if (bReadfile == FALSE)
		{
			cout << "ReadFile Failed = " << GetLastError() << endl;
		}


		bWritefile = WriteFile(
			hCreatefile,
			szWriteFileBuffer,
			dwWriteFileBufferSize,
			&dwNoBytesWrite,
			NULL);
		if (bWritefile == FALSE)
		{
			cout << "WriteFile Failed = " << GetLastError() << endl;
		}
		cout << "WriteFile Succes" << endl;

		if (INVALID_HANDLE_VALUE != hCreatefile)
		{
			for (int i = inceput_interval; i < sfarsit_interval; i++)
			{
				if (isPrime(i) == true)
				{
					cout << i << endl;
				}
			}
		}


		CloseHandle(hCreatefile);
		//system("PAUSE");
	}
	return 0;
}