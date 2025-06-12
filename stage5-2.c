#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATTERN_COUNT 6
#define MAX_PATTERN_NAME 30
#define MAX_PATTERN_DESC 256
#define MAX_SONGS 4
#define MAX_SONG_TITLE 50
#define MAX_LINE 512

typedef struct DancePattern {
    char name[MAX_PATTERN_NAME];
    char description[MAX_PATTERN_DESC];
} DancePattern;

typedef struct DancePatternNode {
    int patternIndex;
    struct DancePatternNode *next;
} DancePatternNode;

typedef struct SongTree {
    char title[MAX_SONG_TITLE];
    DancePatternNode *root;
} SongTree;

DancePattern patterns[PATTERN_COUNT];
SongTree songs[MAX_SONGS];

// 함수 원형 선언
int loadDancePatterns(const char *filename);
void freeSongTrees();
int loadSongs(const char *filename);
void printPatterns();
void printSongPatterns();
void freePatterns();
void clearInputBuffer();
void pauseAndClear();
int patternIndexByName(const char *name);
int askPatternQuestions();
void learnDancePattern();
void bonusGame();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pauseAndClear() {
    printf("계속하려면 Enter 키를 누르세요...");
    getchar();
    system("clear"); // 윈도우면 "cls"
}

// dance_pattern.txt 읽기
int loadDancePatterns(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("안무 패턴 파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }
    char line[MAX_LINE];
    int idx = 0;
    while (idx < PATTERN_COUNT) {
        if (!fgets(line, sizeof(line), fp)) break;
        // 이름 저장 (첫 줄)
        line[strcspn(line, "\r\n")] = 0;
        strncpy(patterns[idx].name, line, MAX_PATTERN_NAME);
        // 설명 읽기 (다음 줄)
        if (!fgets(line, sizeof(line), fp)) break;
        line[strcspn(line, "\r\n")] = 0;
        strncpy(patterns[idx].description, line, MAX_PATTERN_DESC);
        idx++;
    }
    fclose(fp);
    if (idx < PATTERN_COUNT) {
        printf("패턴 개수가 부족합니다.\n");
        return 0;
    }
    return 1;
}

// pattern 이름으로 index 찾기
int patternIndexByName(const char *name) {
    for (int i = 0; i < PATTERN_COUNT; i++) {
        if (strcmp(patterns[i].name, name) == 0)
            return i;
    }
    return -1;
}

// K-POP 노래 파일 읽기
int loadSongs(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("노래 안무 분석 보고서 파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }
    char line[MAX_LINE];
    int songCount = 0;

    // 첫 줄 헤더 스킵
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return 0;
    }

    while (songCount < MAX_SONGS && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;

        char *token = strtok(line, ",");
        if (!token) continue;

        strncpy(songs[songCount].title, token, MAX_SONG_TITLE);

        DancePatternNode *head = NULL, *tail = NULL;

        while ((token = strtok(NULL, ",")) != NULL) {
            int pIdx = patternIndexByName(token);
            if (pIdx == -1) continue; // 없는 패턴 무시

            DancePatternNode *node = malloc(sizeof(DancePatternNode));
            if (!node) {
                fclose(fp);
                return 0;
            }
            node->patternIndex = pIdx;
            node->next = NULL;
            if (!head) head = tail = node;
            else {
                tail->next = node;
                tail = node;
            }
        }
        songs[songCount].root = head;
        songCount++;
    }
    fclose(fp);

    if (songCount < MAX_SONGS) {
        printf("노래 데이터가 부족합니다.\n");
        return 0;
    }
    return 1;
}

void freeSongTrees() {
    for (int i = 0; i < MAX_SONGS; i++) {
        DancePatternNode *curr = songs[i].root;
        while (curr) {
            DancePatternNode *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        songs[i].root = NULL;
    }
}

// 문제 출제용: 패턴 설명에서 공백 제외 임의 10자 추출
void extractRandom10Chars(const char *desc, char *out) {
    // 공백 제외한 문자열 생성
    char tmp[MAX_PATTERN_DESC] = {0};
    int len = 0;
    for (int i = 0; desc[i] != '\0'; i++) {
        if (desc[i] != ' ') {
            tmp[len++] = desc[i];
        }
    }
    if (len < 10) {
        strncpy(out, tmp, len);
        out[len] = '\0';
        return;
    }
    int start = rand() % (len - 10 + 1);
    strncpy(out, tmp + start, 10);
    out[10] = '\0';
}

// 문제 출제 및 평가
int askPatternQuestions() {
    int correctCount = 0;
    char input[64];

    for (int i = 0; i < 4; i++) {
        int idx = rand() % PATTERN_COUNT;
        char snippet[11];
        extractRandom10Chars(patterns[idx].description, snippet);
        printf("문제 %d: 설명에서 발췌한 부분: \"%s\"\n", i+1, snippet);
        printf("패턴 이름을 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\r\n")] = 0;

        if (strcmp(input, patterns[idx].name) == 0) {
            printf("정답입니다!\n\n");
            correctCount++;
        } else {
            printf("오답입니다. 정답은 \"%s\" 입니다.\n\n", patterns[idx].name);
        }
    }
    return correctCount;
}

// 전체 노래별 안무 패턴 출력
void printSongPatterns() {
    printf("===== K-POP 노래별 안무 패턴 =====\n");
    for (int i = 0; i < MAX_SONGS; i++) {
        printf("노래: %s\n", songs[i].title);
        DancePatternNode *curr = songs[i].root;
        printf("안무 패턴: ");
        while (curr) {
            printf("%s ", patterns[curr->patternIndex].name);
            curr = curr->next;
        }
        printf("\n\n");
    }
}

// 보너스 기능: 노래 선택 후 패턴 맞히기 게임
void bonusGame() {
    printf("===== 보너스 게임: 노래를 선택하세요 =====\n");
    for (int i = 0; i < MAX_SONGS; i++) {
        printf("%d. %s\n", i+1, songs[i].title);
    }
    printf("선택 (1-%d): ", MAX_SONGS);

    int choice = 0;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > MAX_SONGS) {
        clearInputBuffer();
        printf("잘못된 선택입니다.\n");
        return;
    }
    clearInputBuffer();

    SongTree *selectedSong = &songs[choice - 1];
    DancePatternNode *curr = selectedSong->root;

    if (!curr) {
        printf("선택한 노래에 안무 패턴이 없습니다.\n");
        return;
    }

    char input[64];
    printf("첫 번째 패턴: %s\n", patterns[curr->patternIndex].name);
    curr = curr->next;

    while (curr) {
        printf("다음 패턴 이름을 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\r\n")] = 0;

        if (strcmp(input, patterns[curr->patternIndex].name) == 0) {
            printf("정답!\n");
            curr = curr->next;
        } else {
            printf("오답입니다. 게임을 종료합니다.\n");
            return;
        }
    }
    printf("축하합니다! 모든 패턴을 맞히셨습니다!\n");
}

// learnDancePattern 함수 구현
void learnDancePattern() {
    if (!loadDancePatterns("dance_pattern.txt")) {
        printf("안무 패턴 로드 실패\n");
        return;
    }

    printf("[II. 훈련 > 5. 댄스 훈련 > B. 안무 패턴]\n\n");
    printf("기초 안무 패턴 학습을 시작합니다.\n");

    int correct = askPatternQuestions();

    if (correct < 3) {
        printf("정답 개수가 3개 미만입니다. 기능을 종료합니다.\n");
        return;
    }

    if (!loadSongs("analyz_dance-pattern.csv")) {
        printf("노래 안무 분석 보고서 로드 실패\n");
        return;
    }

    printSongPatterns();

    // 보너스 게임 실행
    bonusGame();

    freeSongTrees();
}

int main() {
    srand((unsigned int)time(NULL));

    // 메뉴에서 learnDancePattern 호출 가정
    learnDancePattern();

    return 0;
}
