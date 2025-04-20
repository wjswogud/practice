#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 6
#define MAX_STR 200

// 현재 기준 날짜 (2025년 4월 20일)
#define CUR_YEAR 2025
#define CUR_MONTH 4
#define CUR_DAY 20

char group_name[50];
char *member_info[MAX] = {
    "성명", "생일", "성별", "메일", "국적", "BMI", "주스킬", "보조스킬", "TOPIK", "MBTI", "소개"
};

// 후보자 구조체 정의
typedef struct {
    char name[50];
    int year, month, day;
    char gender;
    char email[50];
    char nationality[30];
    float bmi;
    char main_skill[30];
    char sub_skill[50];
    int topik;
    char mbti[10];
    char intro[MAX_STR];
} Candidate;

Candidate candidate01, candidate02, candidate03, candidate04, candidate05, candidate06;
Candidate *candidates[MAX] = {
    &candidate01, &candidate02, &candidate03,
    &candidate04, &candidate05, &candidate06
};

// 문자열로 TOPIK 등급 변환
const char* get_korean_level(int level) {
    switch (level) {
        case 0: return "원어민";
        case 1: return "1급";
        case 2: return "2급";
        case 3: return "3급";
        case 4: return "4급";
        case 5: return "5급";
        case 6: return "6급";
        default: return "미지정";
    }
}

// 만 나이 계산
int calculate_age(int y, int m, int d) {
    int age = CUR_YEAR - y;
    if (CUR_MONTH < m || (CUR_MONTH == m && CUR_DAY < d)) {
        age--;
    }
    return age;
}

// 후보자 데이터 입력 함수
void input_candidates() {
    int i;
    printf("####################################\n");
    printf("[%s] 오디션 후보자 데이터 입력\n", group_name);
    printf("####################################\n");

    i = 0;
    while (i < MAX) {
        Candidate *c = candidates[i];
        printf("첫 번째 후보자의 정보를 입력합니다.\n");
        printf("---------------------------------\n");
        printf("1. 성명: "); fgets(c->name, sizeof(c->name), stdin);
        c->name[strcspn(c->name, "\n")] = 0;

        printf("2. 생일(YYYY/MM/DD 형식): ");
        scanf("%d/%d/%d", &c->year, &c->month, &c->day);
        getchar(); // flush newline

        printf("3. 성별(여성이면 F 또는 남성이면 M): ");
        scanf(" %c", &c->gender);
        getchar();

        printf("4. 메일 주소: "); fgets(c->email, sizeof(c->email), stdin);
        c->email[strcspn(c->email, "\n")] = 0;

        printf("5. 국적: "); fgets(c->nationality, sizeof(c->nationality), stdin);
        c->nationality[strcspn(c->nationality, "\n")] = 0;

        printf("6. BMI: "); scanf("%f", &c->bmi); getchar();

        printf("7. 주 스킬: "); fgets(c->main_skill, sizeof(c->main_skill), stdin);
        c->main_skill[strcspn(c->main_skill, "\n")] = 0;

        printf("8. 보조 스킬: "); fgets(c->sub_skill, sizeof(c->sub_skill), stdin);
        c->sub_skill[strcspn(c->sub_skill, "\n")] = 0;

        printf("9. 한국어 등급(TOPIK): "); scanf("%d", &c->topik); getchar();

        printf("10. MBTI: "); fgets(c->mbti, sizeof(c->mbti), stdin);
        c->mbti[strcspn(c->mbti, "\n")] = 0;

        printf("11. 소개: "); fgets(c->intro, sizeof(c->intro), stdin);
        c->intro[strcspn(c->intro, "\n")] = 0;

        printf("=================================\n");

        i++;
        if (i < MAX) {
            printf("다음 후보자의 정보를 입력합니다.\n");
            printf("---------------------------------\n");
        }
    }
}

// 후보자 데이터 출력 함수
void output_candidates() {
    int i;
    printf("\n####################################\n");
    printf("[%s] 오디션 후보자 데이터 조회\n", group_name);
    printf("####################################\n");
    printf("===========================================================================================================\n");
    printf("성   명      | 생   일     | 성별 | 메   일               | 국적   | BMI  | 주스킬 | 보조스킬     | TOPIK | MBTI  |\n");
    printf("===========================================================================================================\n");

    for (i = 0; i < MAX; i++) {
        Candidate *c = candidates[i];
        int age = calculate_age(c->year, c->month, c->day);
        printf("%-10s(%2d)| %04d%02d%02d |  %c  | %-20s| %-6s| %-5.1f| %-6s| %-10s| %-6s| %-6s|\n",
            c->name, age, c->year, c->month, c->day, c->gender,
            c->email, c->nationality, c->bmi,
            c->main_skill, c->sub_skill,
            get_korean_level(c->topik), c->mbti);

        printf("-----------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", c->intro);
        printf("-----------------------------------------------------------------------------------------------------------\n");
    }
}

int main() {
    // 그룹명 입력 (getchar 사용)
    printf("지원하는 오디션 그룹명을 입력하세요: ");
    fgets(group_name, sizeof(group_name), stdin);
    group_name[strcspn(group_name, "\n")] = 0;

    input_candidates();
    output_candidates();

    return 0;
}
