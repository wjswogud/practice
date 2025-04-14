#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

void printSplash(const char* name, const char* date);

int main() {
    char date[20];
    char name[50];

    printf("[현재 날짜를 \"yyyy-mm-dd\" 형식으로 입력하세요]: ");
    scanf("%19s", date);

    printf("[당신의 이름을 입력하세요]: ");
    scanf(" %[^\n]", name); // 공백 포함해서 입력받기

    printf("**입력이 정상적으로 처리되었습니다.**\n");

    // 3초 대기
    printf("3초 후 스플래시 화면을 표시합니다...\n");
    sleep(3);  // 유닉스계열 (리눅스, macOS)
    // Sleep(3000); // 윈도우즈라면 이걸로 교체하고 #include <windows.h> 추가

    system(CLEAR_COMMAND); // 화면 지우기
    printSplash(name, date);

    return 0;
}

void printSplash(const char* name, const char* date) {
    char year[5], month[3], day[3];
    sscanf(date, "%4[^-]-%2[^-]-%2s", year, month, day);

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    // 정 직삼각형 왼쪽 + 역 직삼각형 오른쪽
    for (int i = 0; i < 3; i++) {
        // 왼쪽 삼각형
        for (int j = 0; j <= i; j++) {
            printf("*");
        }

        // 가운데 내용 출력
        if (i == 0)
            printf("                         [마그라테아 ver 0.1]                             ");
        else if (i == 1)
            printf("           풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,         ");
        else if (i == 2)
            printf("         사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,    ");

        // 오른쪽 역 삼각형
        for (int j = 3; j > i; j--) {
            printf("*");
        }
        printf("\n");
    }

    // 마지막 줄 문구
    printf("           마그라테아에 오신걸 환영합니다.   \n");

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[사용자]: %-40s[실행 시간]: %s년 %s월 %s일\n", name, year, month, day);
    printf("================================================================================\n");
}
