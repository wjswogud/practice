// judges.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INPUT 1024
#define FIELD_COUNT 7

char judges_array[MAX_JUDGES][MAX_INPUT];

void print_header(const char *title) {
    printf("####################################\n");
    printf("#        %s        #\n", title);
    printf("####################################\n");
}

void print_separator() {
    printf("-----------------------------------\n");
}

int count_fields(const char *input) {
    int count = 1; // 첫 번째 항목 포함
    const char *p = input;
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    return count;
}

void parse_and_display_judge(const char *json, int index) {
    char buffer[MAX_INPUT];
    strcpy(buffer, json);
    char *token = strtok(buffer, ",");
    printf("[심사위원 %d]\n", index + 1);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    print_separator();
}

int main() {
    char project_name[100];
    int total_judges = 0;
    int selected_members = 0;

    print_header("심사위원 명단 데이터 입력");

    printf("> 참여 프로젝트: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // 개행 제거

    printf("> 심사 총 인원: ");
    scanf("%d", &total_judges);
    printf("> 선발 멤버 수: ");
    scanf("%d", &selected_members);
    getchar(); // 버퍼 비우기

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int current = 0;
    while (current < total_judges) {
        printf("*심사위원 %d: ", current + 1);
        char input[MAX_INPUT];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 개행 제거

        if (count_fields(input) != FIELD_COUNT) {
            printf("입력 항목이 정확하지 않습니다. 다시 입력해주세요.\n");
            continue;
        }

        strcpy(judges_array[current], input);
        current++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char check;
    printf("\"%s\" 심사위원 정보를 확인할까요? Y/N: ", project_name);
    scanf(" %c", &check);

    if (check == 'Y') {
        print_header("심사위원 데이터 출력");
        for (int i = 0; i < total_judges; i++) {
            parse_and_display_judge(judges_array[i], i);
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    return 0;
}
