/* test gui 
http://winprog.org/tutorial/simple_window.html
http://geekswithblogs.net/TechTwaddle/archive/2009/10/21/applications-appending-text-to-a-multiline-edit-control.aspx
https://support.microsoft.com/en-us/help/109550/how-to-programatically-append-text-to-an-edit-control
https://cboard.cprogramming.com/windows-programming/55742-appending-text-edit-control.html
https://cboard.cprogramming.com/windows-programming/53577-displaying-text-numbers-edit-control.html?highlight=EM_SETSEL+EM_REPLACESEL

to compile:
windres testgui.rc gui.o  //set up resource file 
gcc -Wall -mwindows testgui.c gui.o -o testgui.exe
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "heap.h"

const char g_szClassName[] = "myWindowClass";

static Heap *my_heap; 
static HashMap *temp;

/* the window procedure */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	
	switch(msg){
		case WM_LBUTTONDOWN:
		{
			/*
			char szFileName[MAX_PATH];
			HINSTANCE hInstance = GetModuleHandle(NULL);
			
			GetModuleFileName(hInstance, szFileName, MAX_PATH);
			MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
			*/
		}
		break;
		case WM_COMMAND:
			/* LOWORD takes the lower 16 bits of wParam => the element clicked on */
			switch(LOWORD(wParam)){
				case ID_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				break;
				case ID_STUFF_GO:
					/* do nothing */
				break;
				case ID_ADD_TASK:
				{
					HWND task = GetDlgItem(hwnd, IDC_TEXT);
					HWND priority = GetDlgItem(hwnd, ID_GET_TASK_PRIORITY);
					
					TCHAR taskBuff[1024];
					TCHAR priorityBuff[4];

					GetWindowText(task, taskBuff, 100);
					GetWindowText(priority, priorityBuff, 4);
					int priority_num = atoi(priorityBuff);
					
					int i;
					
					for(i = 0; taskBuff[i] != '\0'; i++){
						/* get to null terminator */
					}				
					
					/* append priority num to taskBuff just to check! remove this event later 
					int j; //remove this later
					taskBuff[i++] = ' '; //add a space
					for(j = 0; priorityBuff[j] != '\0'; j++){
							taskBuff[i++] = priorityBuff[j];
					}
					*/
					
					taskBuff[i++] = '\r'; 
					taskBuff[i++] = '\n';
					taskBuff[i] = '\0';
					
					/* put taskBuffer string in heap, along with priority number */
					/* 
					   taskBuff is what's displayed, i.e. "feed cats 10" (task, priority num)
					   what goes in the heap is char * (the task) and an int (priority_num)
					*/
					
					temp = createNewHashMap((char *)taskBuff, priority_num);
					addToHeap(my_heap, temp);
						
					//fprintf(stdout, "the next task is: %s\n", getSmallest(my_heap)); 
					//fprintf(stdout, "the heap has size of: %d\n", my_heap->size); 
					
					/* append to read-only display */
					//HWND hWndEditDisplay = GetDlgItem(hwnd, ID_TEXT_READONLY);
					//int length = GetWindowTextLength(hWndEditDisplay);
					
					//SendMessage(hWndEditDisplay, EM_SETSEL, length, length);
					//SendMessage(hWndEditDisplay, EM_REPLACESEL, 0, (LPARAM)TEXT(taskBuff));
				}
				break;
				case ID_GET_TASK:
				{	
					/* append to read-only display */
					HWND hWndEditDisplay = GetDlgItem(hwnd, ID_TEXT_READONLY);
					int length = GetWindowTextLength(hWndEditDisplay);
					
					SendMessage(hWndEditDisplay, EM_SETSEL, length, length);
					SendMessage(hWndEditDisplay, EM_REPLACESEL, 0, (LPARAM)TEXT(getSmallest(my_heap)));
					
					/* SendMessage(hWndEditDisplay, EM_REPLACESEL, 0, (LPARAM)TEXT(" replace this string\r\n")); */
				}
				break;
			}
		break;
		case WM_CLOSE:
		{
			freeHeap(my_heap);
			DestroyWindow(hwnd);
		}
		break;
		case WM_DESTROY:
		{
			freeHeap(my_heap);
			PostQuitMessage(0);
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	/* console attached for debugging */
	AllocConsole();
	freopen( "CON", "w", stdout );
	
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	
	/* initialize heap */
	init(&my_heap); /* notice the pointer to a heap pointer */
	//fprintf(stdout, "the heap has size of: %d\n", my_heap->size);
	
	/* register the window class */
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	if(!RegisterClassEx(&wc)){
		MessageBox(NULL, "window registration failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	/* create the window */
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"title",
		WS_TILEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 450, 450,
		NULL, NULL, hInstance, NULL);
	
	if(hwnd == NULL){
		MessageBox(NULL, "window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	/* make a title label */
	CreateWindow(
		TEXT("STATIC"),
		TEXT(" TASK SCHEDULER "),
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		10, 10,
		200, 20,
		hwnd, /* parent window */
		(HMENU)ID_INPUT_LABEL,
		hInstance,
		NULL
	);
	
	/* make text box LABEL (HWND textInputLabel)*/
	CreateWindow(
		TEXT("STATIC"),
		TEXT("Add task: "),
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		10, 49,
		65, 20,
		hwnd, /* parent window */
		(HMENU)ID_INPUT_LABEL,
		hInstance,
		NULL
	);
	
	/* make text box  ADD NEW TASK  (HWND textInput)*/
	CreateWindow(
		TEXT("edit"),
		TEXT(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		80, 50,  /* x, y coords */
		130, 20, /* width, height */
		hwnd,
		(HMENU)IDC_TEXT,
		hInstance,
		NULL
	);
	/* prepopulate text input */
	SetDlgItemText(hwnd, IDC_TEXT, "This is a string");
	
	/* make text box LABEL FOR PRIORITY NUMBER (HWND textInputPriorityLabel) */
	CreateWindow(
		TEXT("STATIC"),
		TEXT("Priority #: "),
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		215, 50,
		65, 20,
		hwnd, /* parent window */
		(HMENU)ID_PRIORITY_NUM,
		hInstance,
		NULL
	);
	/* make text box  ADD NEW TASK PRIORITY NUMBER (HWND textInput)*/
	CreateWindow(
		TEXT("edit"),
		TEXT(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
		280, 50,  /* x, y coords */
		30, 20, /* width, height */
		hwnd,
		(HMENU)ID_GET_TASK_PRIORITY,
		hInstance,
		NULL
	);
	
	/* make button to add new task */
	CreateWindow(
		TEXT("button"),
		TEXT("add task"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		320, 45, /* x, y coords */
		85, 30, /* width, height */
		hwnd,
		(HMENU)ID_ADD_TASK,
		hInstance,
		NULL
	);
	
	
	/* read-only area label! TASKS TO DO*/
	CreateWindow(
		TEXT("STATIC"),
		TEXT("tasks to do: "),
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		10, 95, //x, y coords
		70, 79, //width, height
		hwnd, //parent window
		(HMENU)ID_TASKS_TO_DO,
		hInstance,
		NULL
	);
	
	/* make button to GET new task and put on display */
	CreateWindow(
		TEXT("button"),
		TEXT("get new task"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		305, 95, /* x, y coords */
		100, 30, /* width, height */
		hwnd,
		(HMENU)ID_GET_TASK,
		hInstance,
		NULL
	);
	
	/* make read-only text box - TASKS TO DO (HWND displayTasks)*/
	CreateWindow(
		TEXT("edit"),
		TEXT(""),
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_MULTILINE,
		80, 90,
		220, 180,
		hwnd,
		(HMENU)ID_TEXT_READONLY,
		hInstance,
		NULL
	);
	/* prepopulate text input */
	//SetDlgItemText(hwnd, ID_TEXT_READONLY, "This is a read-only section! ^_^\r\n");
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	/* message loop */
	while(GetMessage(&Msg, NULL, 0, 0) > 0){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


