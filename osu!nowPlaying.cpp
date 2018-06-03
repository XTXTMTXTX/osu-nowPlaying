#include<windows.h>
#include<cstdio>
#include<cstdlib>
#include<tchar.h>
using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow) {
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;
	BOOL bQuit=FALSE;

	wc.style=CS_OWNDC;
	wc.lpfnWndProc=WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName="MsnMsgrUIManager";
	RegisterClass(&wc);
	hWnd=CreateWindow("MsnMsgrUIManager",_T("MsnMsgrUIManager"),0,0,0,0,0,NULL,NULL,hInstance,NULL);

	while (!bQuit) {
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
			if(msg.message==WM_QUIT) {
				bQuit=TRUE;
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {

		}
	}
	DestroyWindow(hWnd);
	return msg.wParam;
}
LRESULT CALLBACK WndProc (HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	//printf("%d\n",message);
	switch (message) {
	case WM_CREATE:
		return 0;
	case WM_CLOSE:
		PostQuitMessage (0);
		return 0;
	case WM_DESTROY:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_COPYDATA:{
		COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
		char szBuffer[300],Authorname[300],Songname[300],Diffname[300];
		char *pos=0;
		memset(szBuffer, 0, sizeof(szBuffer));
		memset(Authorname, 0, sizeof(Authorname));
		memset(Songname, 0, sizeof(Songname));
		sprintf(Diffname,"Listening");
		//wprintf(L"dwData:%d cbData:%d\r\nlpData:0x%08x = %ls\n",
		//        pCopyData->dwData, pCopyData->cbData,
		//       (PVOID)pCopyData->lpData, (wchar_t*)pCopyData->lpData);
		for(unsigned int i=0;i<(pCopyData->cbData)/2;i++)szBuffer[i]=((unsigned char*)pCopyData->lpData)[i*2];
		if((pos=strstr(szBuffer,"Listening to {0} - {1} ({2})\\0"))){
			snprintf(Songname,1+int(strstr(pos+30,"\\0")-(pos+30)),"%s",pos+30);
			pos=strstr(pos+30,"\\0");
			snprintf(Authorname,1+int(strstr(pos+2,"\\0")-(pos+2)),"%s",pos+2);
		}else if((pos=strstr(szBuffer,"Playing {0} - {1} [{3}] ({2})\\0"))){
			snprintf(Songname,1+int(strstr(pos+31,"\\0")-(pos+31)),"%s",pos+31);
			pos=strstr(pos+31,"\\0");
			snprintf(Authorname,1+int(strstr(pos+2,"\\0")-(pos+2)),"%s",pos+2);
			pos=strstr(pos+2,"\\0");
			pos=strstr(pos+2,"\\0");
			snprintf(Diffname,1+int(strstr(pos+2,"\\0")-(pos+2)),"%s",pos+2);
		}
		printf("%s - %s [%s]\n",Authorname,Songname,Diffname);
		return 0;
	}
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
}
