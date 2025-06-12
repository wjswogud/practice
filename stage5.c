#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 30
#define MAX_STEP_LEN 50
#define NUM_DANCES 6
#define NUM_STEPS 6
#define MAX_MEMBERS 5

typedef struct {
    char hangul[MAX_STEP_LEN];
    char english[MAX_STEP_LEN];
    char steps[NUM_STEPS][MAX_STEP_LEN];
} DanceStep;

typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
    int score;
} Member;

DanceStep danceSteps[NUM_DANCES];
Member members[MAX_MEMBERS] = {
    {"김민수", "Minsu", 0},
    {"이영희", "Younghee", 0},
    {"박지훈", "Jihoon", 0},
    {"최지은", "Jieun", 0},
    {"정수빈", "Subin", 0}
};

void shuffleSteps(char steps[NUM_STEPS][MAX_STEP_LEN]) {
    for (int i = NUM_STEPS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_STEP_LEN];
        strcpy(temp, steps[i]);
        strcpy(steps[i], steps[j]);
        strcpy(steps[j], temp);
    }
}

void displayDanceStep(int index) {
    printf("댄스명: %s\n", danceSteps[index].english);
    for (int i = 0; i < NUM_STEPS; i++) {
        printf("%d. %s\n", i + 1, danceSteps[index].steps[i]);
    }
}

int evaluateAnswer(char correct[NUM_STEPS][MAX_STEP_LEN], char user[NUM_STEPS][MAX_STEP_LEN]) {
    int correctOrder = 1;
    int correctSteps = 0;
    for (int i = 0; i < NUM_STEPS; i++) {
        if (strcmp(correct[i], user[i]) == 0) {
            correctSteps++;
        } else {
            correctOrder = 0;
        }
    }
    if (correctOrder) return 100;
    if (correctSteps == NUM_STEPS) return 50;
    if (correctSteps > 0) return 20;
    return 0;
}

void learnDanceStep() {
    srand(time(NULL));

    char nickname[MAX_NAME_LEN];
    printf("밀리웨이즈 멤버의 닉네임을 입력하세요: ");
    for (int i = 0; i < 3; i++) {
        fgets(nickname, MAX_NAME_LEN, stdin);
        nickname[strcspn(nickname, "\n")] = '\0'; // 개행 문자 제거

        int memberIndex = -1;
        for (int j = 0; j < MAX_MEMBERS; j++) {
            if (strcmp(members[j].nickname, nickname) == 0) {
                memberIndex = j;
                break;
            }
        }

        if (memberIndex != -1) {
            printf("멤버 %s님을 찾았습니다.\n", members[memberIndex].nickname);
            break;
        } else if (i < 2) {
            printf("일치하는 닉네임이 없습니다. 다시 시도하세요.\n");
        } else {
            printf("3번의 시도 후 종료합니다.\n");
            return;
        }
    }

    // 댄스 스텝 무작위 섞기 및 출력
    int danceIndex = rand() % NUM_DANCES;
    shuffleSteps(danceSteps[danceIndex].steps);

    // 10초 동안 댄스 스텝 표시
    displayDanceStep(danceIndex);
    printf("10초 후에 댄스 스텝이 사라집니다.\n");
    sleep(10);

    // 사용자 입력 받기
    char userSteps[NUM_STEPS][MAX_STEP_LEN];
    for (int i = 0; i < NUM_STEPS; i++) {
        printf("스텝 %d: ", i + 1);
        fgets(userSteps[i], MAX_STEP_LEN, stdin);
        userSteps[i][strcspn(userSteps[i], "\n")] = '\0'; // 개행 문자 제거
    }

    // 정답 평가
    int score = evaluateAnswer(danceSteps[danceIndex].steps, userSteps);
    printf("당신의 점수는 %d점입니다.\n", score);

    // 점수 저장
    members[0].score = score; // 예시로 첫 번째 멤버의 점수만 저장
}

int main() {
    // 댄스 스텝 데이터 초기화
    strcpy(danceSteps[0].english, "Basic Step");
    strcpy(danceSteps[0].steps[0], "Step Forward");
    strcpy(danceSteps[0].steps[1], "Step Backward");
    strcpy(danceSteps[0].steps[2], "Step Left");
    strcpy(danceSteps[0].steps[3], "Step Right");
    strcpy(danceSteps[0].steps[4], "Turn Left");
    strcpy(danceSteps[0].steps[5], "Turn Right");

    strcpy(danceSteps[1].english, "Box Step");
    strcpy(danceSteps[1].steps[0], "Step Forward");
    strcpy(danceSteps[1].steps[1], "Step Side");
    strcpy(danceSteps[1].steps[2], "Step Close");
    strcpy(danceSteps[1].steps[3], "Step Back");
    strcpy(danceSteps[1].steps[4], "Step Side");
    strcpy(danceSteps[1].steps[5], "Step Close");

    strcpy(danceSteps[2].english, "Cha Cha");
    strcpy(danceSteps[2].steps[0], "Step Forward");
    strcpy(danceSteps[2].steps[1], "Step Back");
    strcpy(danceSteps[2].steps[2], "Step Side");
    strcpy(danceSteps[2].steps[3], "Rock Step");
    strcpy(danceSteps[2].steps[4], "Cha Cha Step");
    strcpy(danceSteps[2].steps[5], "Cha Cha Step");

    strcpy(danceSteps[3].english, "Waltz");
    strcpy(danceSteps[3].steps[0], "Step Forward");
    strcpy(danceSteps[3].steps[1], "Step Side");
    strcpy(danceSteps[3].steps[2], "Step Close");
    strcpy(danceSteps[3].steps[3], "Step Back");
    strcpy(danceSteps[3].steps[4], "Step Side");
    strcpy(danceSteps[3].steps[5], "Step Close");

    strcpy(danceSteps[4].english, "Rumba");
    strcpy(danceSteps[4].steps[0], "Step Forward");
    strcpy(danceSteps[4].steps[1], "Step Side");
    strcpy(danceSteps[4].steps[2], "Step Close");
    strcpy(danceSteps[4].steps[3], "Step Back");
    strcpy(danceSteps[4].steps[4], "Step Side");
    strcpy(danceSteps[4].steps[5], "Step Close");

    strcpy(danceSteps[5].english, "Samba");
    strcpy(danceSteps[5].steps[0], "Step Forward");
    strcpy(danceSteps[5].steps[1], "Step Back");
    strcpy(danceSteps[5].steps[2], "Step Side");
    strcpy(danceSteps[5].steps[3], "Step Close");
    strcpy(danceSteps[5].steps[4], "Samba Step");
    strcpy(danceSteps[5].steps[5], "Samba Step");

    // 댄스 학습 시작
    learnDanceStep();

    return 0;
}
