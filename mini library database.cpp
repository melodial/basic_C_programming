#include <windows.h>
#include <stdio.h>

struct perpus {
    char id[12];
    char judul[31];
    char penulis[31];
};

struct perpus buku[100]; // Max 100 books
int bookCount = 0;
HWND hEditID, hEditTitle, hEditAuthor, hEditOutput;

void scanTheData(HWND hwnd);
void printToFile();
void readFromFile();
void printToConsole(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "ID Buku:", WS_VISIBLE | WS_CHILD, 10, 10, 80, 20, hwnd, NULL, NULL, NULL);
            hEditID = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 10, 250, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("STATIC", "Judul Buku:", WS_VISIBLE | WS_CHILD, 10, 40, 80, 20, hwnd, NULL, NULL, NULL);
            hEditTitle = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 40, 250, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("STATIC", "Penulis Buku:", WS_VISIBLE | WS_CHILD, 10, 70, 80, 60, hwnd, NULL, NULL, NULL);
            hEditAuthor = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 70, 250, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("BUTTON", "Input Data", WS_VISIBLE | WS_CHILD, 10, 100, 100, 30, hwnd, (HMENU) 1, NULL, NULL);
            CreateWindow("BUTTON", "Display Data", WS_VISIBLE | WS_CHILD, 120, 100, 100, 30, hwnd, (HMENU) 2, NULL, NULL);
            CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD, 230, 100, 100, 30, hwnd, (HMENU) 3, NULL, NULL);
            
            hEditOutput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 140, 420, 300, hwnd, NULL, NULL, NULL);
        }
        break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1:
                    scanTheData(hwnd);
                    printToFile();
                    MessageBox(hwnd, "Data buku berhasil diinput!", "Information", MB_OK | MB_ICONINFORMATION);
                    break;
                case 2:
                    readFromFile();
                    printToConsole(hwnd);
                    break;
                case 3:
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
void scanTheData(HWND hwnd) {
    GetWindowText(hEditID, buku[bookCount].id, 12);
    GetWindowText(hEditTitle, buku[bookCount].judul, 31);
    GetWindowText(hEditAuthor, buku[bookCount].penulis, 31);
    bookCount++;
}

void printToFile() {
    FILE *fp = fopen("data_perpustakaan.txt", "w");
    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%s#%s#%s\n", buku[i].id, buku[i].judul, buku[i].penulis);
    }
    fclose(fp);
}

void readFromFile() {
    FILE *fp = fopen("data_perpustakaan.txt", "r");
    char line[100];
    bookCount = 0;
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^#]#%[^#]#%[^\n]", buku[bookCount].id, buku[bookCount].judul, buku[bookCount].penulis);
        bookCount++;
    }
    fclose(fp);
}

void printToConsole(HWND hwnd) {
    char buffer[1024] = "";
    for (int i = 0; i < bookCount; i++) {
        char line[128];
        snprintf(line, sizeof(line), " ID: %s Judul: %s Penulis: %s ", buku[i].id, buku[i].judul, buku[i].penulis);
        strcat(buffer, line);
    }
    SetWindowText(hEditOutput, buffer);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "myWindowClass",
        "Library Database by Melodial :3",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 350, 400,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

