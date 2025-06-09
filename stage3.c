#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 50
#define MAX_COUNTRY_LEN 30
#define MAX_QUIZ_COUNT 5
#define MAX_GRAMMAR_COUNT 10
#define MAX_CHALLENGE_COUNT 3

// 한국어 문제은행 구조체
struct KoreanQuiz {
    int id;
    char question[100];
    char answer[100];
};

// 밀리웨이즈 연습생 구조체
struct Trainee {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
    char country[MAX_COUNTRY_LEN];
    int quiz_score;
    int passed;
};

// 퀴즈 답지 구조체
struct AnswerSheet {
    int quiz_id;
    char answer[100];
    char is_correct;
};

// 한글 자모 구조체
struct Hangul {
    char hangul[10];
    char english[10];
    char pronunciation[10];
};

// 학습 성적 구조체
struct LearningRecord {
    char name[MAX_NAME_LEN];
    char challenge_type[3];
    int total_score;
    int challenge_round;
};

// 영한 문장 구조체
struct EngKorSentence {
    char english[100];
    char korean[100];
};

// 문법 성적 배열
struct GrammarScore {
    char nickname[MAX_NAME_LEN];
    int total_score;
};

// 전역 변수 선언
struct KoreanQuiz quiz_bank[] = {
    {1, "What is your name?", "이름이 뭐에요?"},
    {2, "Where are you from?", "어디에서 오셨어요?"},
    {3, "How old are you?", "몇 살이에요?"},
    {4, "What is your favorite color?", "가장 좋아하는 색깔이 뭐에요?"},
    {5, "Do you like Korean food?", "한국 음식을 좋아해요?"},
    {6, "What time is it?", "지금 몇 시에요?"},
    {7, "How are you?", "어떻게 지내세요?"},
    {8, "Where do you live?", "어디에 살아요?"},
    {9, "What is your hobby?", "취미가 뭐에요?"},
    {10, "Do you have any siblings?", "형제나 자매가 있어요?"}
};

struct Trainee trainees[] = {
    {"박지연", "Jiyeon", "Korea", 0, 0},
    {"김민수", "Minsu", "Korea", 0, 0},
    {"이수진", "Sujin", "Korea", 0, 0},
    {"최지훈", "Jihoon", "Korea", 0, 0},
    {"정하늘", "Haneul", "Korea", 0, 0},
    {"박준영", "Junyoung", "Korea", 0, 0},
    {"김지민", "Jimin", "Korea", 0, 0},
    {"이서연", "Seoyeon", "Korea", 0, 0},
    {"최유진", "Yujin", "Korea", 0, 0},
    {"정민재", "Minjae", "Korea", 0, 0}
};

struct Hangul hangul_data[] = {
    {"ㄱ", "g", "g"},
    {"ㄴ", "n", "n"},
    {"ㄷ", "d", "d"},
    {"ㄹ", "r", "r"},
    {"ㅁ", "m", "m"},
    {"ㅂ", "b", "b"},
    {"ㅅ", "s", "s"},
    {"ㅇ", "ng", "ng"},
    {"ㅈ", "j", "j"},
    {"ㅊ", "ch", "ch"},
    {"ㅋ", "k", "k"},
    {"ㅌ", "t", "t"},
    {"ㅍ", "p", "p"},
    {"ㅎ", "h", "h"},
    {"ㅏ", "a", "a"},
    {"ㅓ", "eo", "eo"},
    {"ㅗ", "o", "o"},
    {"ㅜ", "u", "u"},
    {"ㅡ", "eu", "eu"},
    {"ㅣ", "i", "i"}
};

struct EngKorSentence grammar_sentences[] = {
    {"I am a student.", "저는 학생입니다."},
    {"She is reading a book.", "그녀는 책을 읽고 있습니다."},
    {"They are playing soccer.", "그들은 축구를 하고 있습니다."},
    {"We will go to the park tomorrow.", "우리는 내일 공원에 갈 것입니다."},
    {"He has a cat.", "그는 고양이를 가지고 있습니다."},
    {"My brother is a doctor.", "제 동생은 의사입니다."},
    {"She likes to swim.", "그녀는 수영하는 것을 좋아합니다."},
    {"I have been to Japan.", "저는 일본에 가본 적이 있습니다."},
    {"They are studying Korean.", "그들은 한국어를 공부하고 있습니다."},
    {"We will meet at 3 PM.", "우리는 오후 3시에 만날 것입니다."}
};

struct GrammarScore grammar_scores[] = {
    {"Jiyeon", 0},
    {"Minsu", 0},
    {"Sujin", 0},
    {"Jihoon", 0},
    {"Haneul", 0},
    {"Junyoung", 0},
    {"Jimin", 0},
    {"Seoyeon", 0},
    {"Yujin", 0},
    {"Minjae", 0}
};

// 함수 선언
void testKoreanLang();
void learnHangul();
void learnKoreanGrammar();
void printScore(char *nickname);
void composeSentences(char *nickname);
void showResult(char *nickname);
void shuffleWords(char *sentence);
void playKor2EngGame(char *nickname);
void playEng2KorGame(char *nickname);
void selectRandomTakers();
void serveRandomQuiz(struct Trainee *trainee);
void isAnswer(int quiz_id, char *answer, struct AnswerSheet *answer_sheet);
void quickSort(char *arr[], int low, int high);
int partition(char *arr[], int low, int high);
void swap(char **a, char **b);
void printGrammarScores();
void updateGrammarScore(char *nickname, int score);
void printGrammarRanking();
void printGrammarRankingByChallengeType(char *challenge_type);
void printGrammarRankingByNickname(char *nickname);

// 메인 함수
int main() {
    int choice;

    while (1) {
        printf("\n[II. 훈련 > 3. 언어 및 발음 훈련]\n");
        printf("1. 한국어 퀴즈\n");
        printf("2. 한글 자모 학습\n");
        printf("3. 한국어 문법 학습\n");
        printf("4. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                testKoreanLang();
                break;
            case 2:
                learnHangul();
                break;
            case 3:
                learnKoreanGrammar();
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}

// 한국어 퀴즈 함수
void testKoreanLang() {
    printf("\n한국어 퀴즈를 시작합니다.\n");
    selectRandomTakers();
    serveRandomQuiz(NULL);
}

// 한글 자모 학습 함수
void learnHangul() {
    int choice;
    char nickname[MAX_NAME_LEN];

    printf("\n한글 자모 학습을 시작합니다.\n");
    printf("학습자의 닉네임을 입력하세요: ");
    scanf("%s", nickname);

    while (1) {
        printf("\n작업을 선택하세요:\n");
        printf("1. 한글 표시 영어 입력\n");
        printf("2. 영어 표시 한글 입력\n");
        printf("3. 결과 확인\n");
        printf("4. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playKor2EngGame(nickname);
                break;
            case 2:
                playEng2KorGame(nickname);
                break;
            case 3:
                showResult(nickname);
                break;
            case 4:
                printf("한글 자모 학습을 종료합니다.\n");
                return;
            default:
                printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }
}

// 한국어 문법 학습 함수
void learnKoreanGrammar() {
    int choice;
    char nickname[MAX_NAME_LEN];

    printf("\n한국어 문법 학습을 시작합니다.\n");
    printf("학습자의 닉네임을 입력하세요: ");
    scanf("%s", nickname);

    while (1) {
        printf("\n작업을 선택하세요:\n");
        printf("1. 한국어 문장 구성\n");
        printf("2. 성적 확인\n");
        printf("3. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                composeSentences(nickname);
                break;
            case 2:
                printScore(nickname);
                break;
            case 3:
                printf("한국어 문법 학습을 종료합니다.\n");
                return;
            default:
                printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }
}

// 문법 성적 출력 함수
void printScore(char *nickname) {
    printf("\n[%s의 문법 성적]\n", nickname);
    // 성적 출력 로직 구현
}

// 문장 구성 함수
void composeSentences(char *nickname) {
    printf("\n[%s의 문장 구성]\n", nickname);
    // 문장 구성 로직 구현
}

// 결과 확인 함수
void showResult(char *nickname) {
    printf("\n[%s의 결과 확인]\n", nickname);
    // 결과 확인 로직 구현
}
