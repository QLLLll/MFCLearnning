#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#define MAXBLOCKSIZE 1024
#pragma comment( lib, "wininet.lib" )

void download(const char *Url, const char *save_as)/*将Url指向的地址的文件下载到save_as指向的本地文件*/
{
	byte Temp[MAXBLOCKSIZE];
	ULONG Number = 1;

	FILE *stream;
	HINTERNET hSession = InternetOpen("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		HINTERNET handle2 = InternetOpenUrl(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (handle2 != NULL)
		{


			if ((fopen_s(&stream,save_as, "wb")) == 0)
			{
				while (Number > 0)
				{
					InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);

					fwrite(Temp, sizeof(char), Number, stream);
				}
				fclose(stream);
			}

			InternetCloseHandle(handle2);
			handle2 = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
}

int main(int argc, char* argv[]) {

	download("http://www.baidu.com/", "d:\\index.html");/*调用示例，下载百度的首页到c:\index.html文件*/
	return 0;
}