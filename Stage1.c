#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 10
#define MAX_NAME 50
#define MAX_NICK 20
#define DAYS 6
#define TESTS 7

// 회원 정보 배열
char milliways_members[MAX_MEMBERS][2][MAX_NAME] = {
    {"김연습생", "연습쌤"}, {"박미래", "미래짱"}, {"이준호", "준호팍"},
    {"최성실", "성실킹"}, {"장아름", "아름둥"}, {"강의지", "의지왕"},
    {"윤빛나", "빛나별"}, {"정한결", "한결심"}, {"신도연", "도연짱"},
    {"문채원", "채원밍"}
};

// 체력 항목
const char* health_tests[TESTS] = {
    "1마일 러닝", "스피드 스프린트", "푸시업", "스쿼트", "팔굽혀 펴기", "수영", "무게들기"
};

// 체력 점수 배열 [회원][항목]
int health_scores[MAX_MEMBERS][TESTS];

// 운동 유형
const char* exercise_types[5][3] = {
    {"러닝", "자전거", "빠른 걷기"}, // 유산소
    {"푸시업", "스쿼트", ""},        // 전신 근력
    {"레그 프레스", "레그 컬", ""}, // 하체 근력
    {"철봉", "풀업 바", ""},         // 상체 근력
    {"플랭크", "크런치", ""}         // 코어
};

// 운동 루틴 배열 [회원][요일][운동]
char member_routine[MAX_MEMBERS][DAYS][MAX_NAME];

// 훈련 상태 기록
char training_passed[MAX_MEMBERS][8];

// 헬퍼 함수
int findMemberIndexByName(const char* name) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, milliways_members[i][0]) == 0) return i;
    }
    return -1;
}

// 메뉴 출력 함수
void showMainMenu() {
    printf("\n== 마그라테아 주 메뉴 ==\n");
    printf("I. 오디션 관리\n");
    printf("II. 훈련\n");
    printf("III. 데뷔\n");
    printf("0 또는 Q/q 입력 시 종료\n");
    printf("선택: ");
}

// 훈련 메뉴
void showTrainingMenu() {
    printf("\n== 훈련 메뉴 ==\n");
    printf("1. 체력과 지식\n");
    printf("2. 자기관리 및 팀워크\n");
    printf("3. 언어 및 발음\n");
    printf("4. 보컬\n");
    printf("5. 댄스\n");
    printf("6. 비주얼 및 이미지\n");
    printf("7. 연기 및 무대 퍼포먼스\n");
    printf("8. 팬 소통\n");
    printf("0. 상위 메뉴로\n");
    printf("선택: ");
}

// 체력 입력
void setHealth() {
    char name[MAX_NAME], input[200];
    int index;
    printf("회원 이름을 입력하세요: ");
    scanf("%s", name);
    index = findMemberIndexByName(name);
    if (index == -1) {
        printf("회원이 존재하지 않습니다.\n");
        return;
    }

    printf("7가지 체력 데이터를 쉼표로 구분하여 입력하세요:\n");
    printf("예시: 12,15,30,25,20,13,40\n입력: ");
    scanf(" %[^\n]", input);

    char* token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < TESTS) {
        health_scores[index][i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    if (i == TESTS) {
        printf("데이터 저장 완료!\n");
    } else {
        printf("입력 오류: 7개 항목을 모두 입력하세요.\n");
    }
}

// 체력 조회
void getHealth() {
    char name[MAX_NAME];
    printf("회원 이름을 입력하세요 (전체: all): ");
    scanf("%s", name);

    if (strcmp(name, "all") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("[%s/%s]: ", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < TESTS; j++) {
                printf("%s: %d ", health_tests[j], health_scores[i][j]);
            }
            printf("\n");
        }
    } else {
        int idx = findMemberIndexByName(name);
        if (idx == -1) {
            printf("회원이 존재하지 않습니다.\n");
            return;
        }
        printf("[%s/%s] 체력 데이터:\n", milliways_members[idx][0], milliways_members[idx][1]);
        for (int j = 0; j < TESTS; j++) {
            printf("%s: %d\n", health_tests[j], health_scores[idx][j]);
        }
    }
}

// 운동 루틴 설정
void setExerciseRoutine() {
    char name[MAX_NAME];
    int idx;
    printf("회원 이름을 입력하세요: ");
    scanf("%s", name);
    idx = findMemberIndexByName(name);
    if (idx == -1) {
        printf("회원이 존재하지 않습니다.\n");
        return;
    }

    for (int day = 0; day < DAYS; day++) {
        printf("요일 %d - 유산소(0), 전신(1), 하체(2), 상체(3), 코어(4): ", day + 1);
        int aerobic, strength;
        scanf("%d %d", &aerobic, &strength);

        if (aerobic < 0 || aerobic > 2 || strength < 1 || strength > 4) {
            printf("잘못된 입력입니다. 스킵합니다.\n");
            continue;
        }

        snprintf(member_routine[idx][day], MAX_NAME, "%s + %s",
                 exercise_types[0][aerobic], exercise_types[strength][0]);
    }

    printf("운동 루틴 설정 완료!\n");
}

// 운동 루틴 조회
void getExerciseRoutine() {
    char name[MAX_NAME];
    printf("회원 이름을 입력하세요: ");
    scanf("%s", name);
    int idx = findMemberIndexByName(name);
    if (idx == -1) {
        printf("회원이 존재하지 않습니다.\n");
        return;
    }

    printf("[%s/%s] 운동 루틴:\n", milliways_members[idx][0], milliways_members[idx][1]);
    for (int day = 0; day < DAYS; day++) {
        printf("요일 %d: %s\n", day + 1, member_routine[idx][day]);
    }
}

// 훈련 서브 메뉴
void trainingSubMenu() {
    int option;
    while (1) {
        showTrainingMenu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("\nA. 체력 상태 입력\nB. 체력 상태 조회\nC. 운동 루틴 설정\nD. 운동 루틴 조회\n");
                char sub;
                scanf(" %c", &sub);
                if (sub == 'A') setHealth();
                else if (sub == 'B') getHealth();
                else if (sub == 'C') setExerciseRoutine();
                else if (sub == 'D') getExerciseRoutine();
                break;
            case 0:
                return;
            default:
                printf("올바른 번호를 입력하세요.\n");
        }
    }
}

// 메인 함수
int main() {
    char choice[10];
    while (1) {
        showMainMenu();
        scanf("%s", choice);
        if (strcmp(choice, "0") == 0 || strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else if (strcmp(choice, "I") == 0) {
            printf("오디션 관리 메뉴 준비 중...\n");
        } else if (strcmp(choice, "II") == 0) {
            trainingSubMenu();
        } else if (strcmp(choice, "III") == 0) {
            printf("데뷔 메뉴 준비 중...\n");
        } else {
            printf("유효한 메뉴를 선택하세요.\n");
        }
    }
    return 0;
}
