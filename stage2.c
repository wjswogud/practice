#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 20
#define MAX_MENTORS 8
#define MAX_QUESTIONS 5
#define MAX_SESSIONS 50
#define MAX_LEN 100

// 구조체 정의
typedef struct {
    char nickname[20];
    int ascii_sum;
    int ability;
} Member;

typedef struct {
    int id;
    char name[20];
    int mentee_num;
} Mentor;

typedef struct {
    char nickname[20];
    int age;
    char trauma[100];
} Trauma;

typedef struct {
    int id;
    char question[MAX_LEN];
} Question;

typedef struct {
    char nickname[20];
    char question[MAX_LEN];
    char answer[MAX_LEN];
} Counseling;

typedef struct {
    char keyword[20];
    char message[300];
} EasterEgg;

// 함수 선언
int parseIntMember(char*);
int getRandomAbility();
void initMembers(Member[], int*);
void registerMentors(Mentor[], int*);
void matchMentoring(Member[], int, Mentor[], int);
void printMentorMatches(Member[], Mentor[], int);
void inputTrauma(Trauma[], int*, Member[], int);
void counselingSession(Trauma[], int, Counseling[], int*, Question[]);
void find_easter_egg();

// ASCII 합산
int parseIntMember(char* name) {
    int sum = 0;
    while (*name) sum += *(name++);
    return sum;
}

// 능력치 랜덤 생성
int getRandomAbility() {
    return rand() % (1000 - 100 + 1) + 100;
}

// 연습생 초기화
void initMembers(Member members[], int* count) {
    char* names[] = {"Neo", "Trin", "Morpheus", "Cypher", "Smith", "Tank", "Dozer", "Apoc"};
    *count = sizeof(names) / sizeof(names[0]);
    for (int i = 0; i < *count; i++) {
        strcpy(members[i].nickname, names[i]);
        members[i].ascii_sum = parseIntMember(names[i]);
        members[i].ability = getRandomAbility();
    }
}

// 멘토 초기화
void registerMentors(Mentor mentors[], int* count) {
    *count = MAX_MENTORS;
    for (int i = 0; i < *count; i++) {
        mentors[i].id = i + 1;
        sprintf(mentors[i].name, "Mentor%d", i + 1);
        mentors[i].mentee_num = -1;
    }
}

// 멘토링 매칭
void matchMentoring(Member members[], int m_count, Mentor mentors[], int mentor_count) {
    for (int i = 0; i < m_count; i++) {
        int mentor_id = members[i].ascii_sum % 8 + 1;
        for (int j = 0; j < mentor_count; j++) {
            if (mentors[j].id == mentor_id) {
                mentors[j].mentee_num = i;
                break;
            }
        }
    }
}

// 멘토링 결과 출력
void printMentorMatches(Member members[], Mentor mentors[], int mentor_count) {
    printf("=== Mentor-Mentee Matching ===\n");
    for (int i = 0; i < mentor_count; i++) {
        if (mentors[i].mentee_num != -1) {
            int idx = mentors[i].mentee_num;
            printf("Mentor ID: %d | Name: %s | Mentee: %s (ASCII: %d)\n",
                   mentors[i].id, mentors[i].name, members[idx].nickname, members[idx].ascii_sum);
        }
    }
}

// 트라우마 입력
void inputTrauma(Trauma traumas[], int* t_count, Member members[], int m_count) {
    char name[20], trauma_text[100];
    int found, age;

    while (1) {
        printf("닉네임 입력 (종료: exit): ");
        scanf("%s", name);
        if (strcmp(name, "exit") == 0) break;

        found = 0;
        for (int i = 0; i < m_count; i++) {
            if (strcmp(members[i].nickname, name) == 0) {
                found = 1;
                strcpy(traumas[*t_count].nickname, name);
                printf("나이 입력: ");
                scanf("%d", &age);
                traumas[*t_count].age = age;
                getchar(); // 버퍼 제거
                printf("트라우마 입력: ");
                fgets(trauma_text, 100, stdin);
                trauma_text[strcspn(trauma_text, "\n")] = 0;
                strcpy(traumas[*t_count].trauma, trauma_text);
                (*t_count)++;
                break;
            }
        }
        (!found) ? printf("존재하지 않는 닉네임입니다.\n") : 0;
    }
}

// 상담 세션
void counselingSession(Trauma traumas[], int t_count, Counseling sessions[], int* s_count, Question questions[]) {
    char name[20], answer[MAX_LEN];
    int found = 0;
    printf("상담할 닉네임 입력: ");
    scanf("%s", name);

    for (int i = 0; i < t_count; i++) {
        if (strcmp(name, traumas[i].nickname) == 0) {
            found = 1;
            for (int j = 0; j < 3; j++) {
                int q_idx = rand() % MAX_QUESTIONS;
                printf("Q%d: %s\n답변: ", j + 1, questions[q_idx].question);
                getchar();
                fgets(answer, MAX_LEN, stdin);
                answer[strcspn(answer, "\n")] = 0;
                while (strlen(answer) == 0 || strlen(answer) > 100) {
                    printf("다시 입력 (1~100자): ");
                    fgets(answer, MAX_LEN, stdin);
                    answer[strcspn(answer, "\n")] = 0;
                }
                strcpy(sessions[*s_count].nickname, name);
                strcpy(sessions[*s_count].question, questions[q_idx].question);
                strcpy(sessions[*s_count].answer, answer);
                (*s_count)++;
            }
            break;
        }
    }
    if (!found) printf("해당 멤버를 찾을 수 없습니다.\n");
}

// 이스터에그 기능
void find_easter_egg() {
    EasterEgg egg = {
        "specter",
        "나는 고백한다. 대학 졸업 후 스타트업 창업이라는 허세에 빠져 치기 어린 행동으로 친구들의 앞길을 막았다. 나는 나의 아이디어가 설득되는 사람이 나 뿐일 때 파괴적인 결과를 보게 된다는 것을 뼈저리게 경험했다. 과거의 아서는 독선과 아집의 망령이다."
    };

    printf("<<아서의 이스터에그>>\n");
    for (int i = strlen(egg.keyword) - 1; i >= 0; i--) {
        unsigned char c = egg.keyword[i];
        for (int j = 7; j >= 0; j--)
            printf("%d", (c >> j) & 1);
        printf(" ");
    }
    printf("\n정답 입력: ");
    char input[20];
    scanf("%s", input);
    if (strcmp(input, egg.keyword) == 0) {
        printf("##이스터에그 발견!$$\n%s\n", egg.message);
    } else {
        printf("틀렸습니다. 다시 메뉴로 돌아갑니다.\n");
    }
}

// 메인 함수
int main() {
    srand(time(NULL));

    Member members[MAX_MEMBERS];
    Mentor mentors[MAX_MENTORS];
    Trauma traumas[MAX_MEMBERS];
    Counseling sessions[MAX_SESSIONS];
    Question questions[MAX_QUESTIONS] = {
        {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
        {2, "그 상황이 일상과 감정에 어떤 영향을 주었나요?"},
        {3, "트라우마를 어떻게 극복하려 하셨나요?"},
        {4, "지금 느끼는 감정은 무엇인가요?"},
        {5, "극복에 어떤 지원이 필요하다고 생각하나요?"}
    };

    int member_count = 0, mentor_count = 0, trauma_count = 0, session_count = 0;
    int menu;

    initMembers(members, &member_count);
    registerMentors(mentors, &mentor_count);

    while (1) {
        printf("\n[II. 훈련 > 2. 자기관리와 팀워크]\n");
        printf("1. 멘토링\n2. 트라우마 관리\n3. Arthur\n0. 종료\n메뉴 선택: ");
        scanf("%d", &menu);
        if (menu == 0) break;
        if (menu == 1) {
            matchMentoring(members, member_count, mentors, mentor_count);
            print
