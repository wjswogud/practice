#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 10
#define MAX_NAME_LEN 50
#define MAX_FEEDBACK_LEN 51
#define MIN_MIDI 0
#define MAX_MIDI 127

typedef struct {
    char name[MAX_NAME_LEN];
    int range;  // 음성 범위 (최대 MIDI 값)
    int midiCount;
    int midiValues[12]; // 최대 12개까지 허용
    float stability; // 음성 안정성
    char feedback[MAX_FEEDBACK_LEN];
} Trainee;

Trainee trainees[MAX_TRAINEES];
int traineeCount = 0;

// 포인터를 사용한 함수 예시
void provideFeedback(Trainee *t) {
    printf("피드백을 입력하세요 (50자 이내): ");
    fgets(t->feedback, MAX_FEEDBACK_LEN, stdin);
    t->feedback[strcspn(t->feedback, "\n")] = '\0'; // 줄바꿈 제거
}

float calculateStability(int *midiValues, int count) {
    int sumDiff = 0;
    for (int i = 0; i < count - 1; i++) {
        sumDiff += abs(midiValues[i] - midiValues[i + 1]);
    }
    return (float)sumDiff / (count - 1);
}

// MIDI 배열 내에 중복 없이 무작위로 생성
void generateUniqueMidiValues(int *array, int count, int maxVal) {
    int used[MAX_MIDI + 1] = {0};
    int value;
    for (int i = 0; i < count; ) {
        value = rand() % (maxVal + 1);
        if (!used[value]) {
            used[value] = 1;
            array[i++] = value;
        }
    }
}

// 음성 범위 및 MIDI 수 입력 -> 측정
void measure(Trainee *t) {
    printf("음성 범위를 입력하세요 (0 ~ 127): ");
    scanf("%d", &t->range);
    while (getchar() != '\n');

    printf("무작위 MIDI 값 개수 (5~12개): ");
    scanf("%d", &t->midiCount);
    while (getchar() != '\n');

    if (t->midiCount < 5 || t->midiCount > 12 || t->midiCount > (t->range + 1)) {
        printf("잘못된 입력입니다. 기본값 10개로 설정합니다.\n");
        t->midiCount = 10;
    }

    generateUniqueMidiValues(t->midiValues, t->midiCount, t->range);
    t->stability = calculateStability(t->midiValues, t->midiCount);
}

// 연습생 평가
void evalVocal() {
    if (traineeCount >= MAX_TRAINEES) {
        printf("평가 가능한 연습생 수를 초과했습니다.\n");
        return;
    }

    Trainee *t = &trainees[traineeCount];

    printf("연습생 이름을 입력하세요: ");
    fgets(t->name, MAX_NAME_LEN, stdin);
    t->name[strcspn(t->name, "\n")] = '\0'; // 줄바꿈 제거

    measure(t);
    provideFeedback(t);

    traineeCount++;
}

// 안정성 기준으로 정렬하여 출력
void printVocalInfo() {
    // 안정성 기준 오름차순 정렬
    for (int i = 0; i < traineeCount - 1; i++) {
        for (int j = i + 1; j < traineeCount; j++) {
            if (trainees[i].stability > trainees[j].stability) {
                Trainee temp = trainees[i];
                trainees[i] = trainees[j];
                trainees[j] = temp;
            }
        }
    }

    printf("\n===== 평가 결과 (안정성 순) =====\n");
    for (int i = 0; i < traineeCount; i++) {
        printf("이름: %s | 안정성: %.2f | 피드백: %s\n",
               trainees[i].name, trainees[i].stability, trainees[i].feedback);
    }
    printf("=================================\n");
}

// 메뉴 시스템
void showMenu() {
    int choice;
    do {
        printf("\n[II. 훈련 > 4. 보컬 훈련 > A. 보컬 평가]\n");
        printf("1. 보컬 평가\n");
        printf("2. 평가 결과 출력\n");
        printf("0. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // 입력 버퍼 비우기

        switch (choice) {
            case 1:
                evalVocal();
                break;
            case 2:
                printVocalInfo();
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 입력입니다.\n");
        }
    } while (choice != 0);
}

int main() {
    srand((unsigned int)time(NULL)); // 무작위 초기화
    showMenu();
    return 0;
}
