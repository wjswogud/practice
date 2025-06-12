#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TITLE_LEN 100
#define FIELD_LEN 50
#define DATE_LEN 11
#define QUALIFICATION_LEN 500
#define SNS_NAME_LEN 20
#define API_KEY_LEN 50
#define API_URL_LEN 100

typedef struct JobPost {
    int id;
    char title[TITLE_LEN];
    char postDate[DATE_LEN];
    char dueDate[DATE_LEN];
    int numberOfHires;
    char field[FIELD_LEN];
    char *qualification;
    struct JobPost *next;
} JobPost;

typedef struct SNS {
    char name[SNS_NAME_LEN];
    char apiKey[API_KEY_LEN];
    char apiUrl[API_URL_LEN];
} SNS;

JobPost *jobList = NULL;
int nextId = 1;

SNS snsList[] = {
    {"Facebook", "FB123", "https://api.facebook.com/post"},
    {"Instagram", "IG123", "https://api.instagram.com/post"},
    {"Thread", "TH123", "https://api.thread.com/post"},
    {"LinkedIn", "LI123", "https://api.linkedin.com/post"},
    {"X", "X123", "https://api.x.com/post"}
};
const int snsCount = sizeof(snsList) / sizeof(SNS);

int compareDate(const char *d1, const char *d2) {
    return strcmp(d1, d2); // "2025-06-12" 형식일 경우 단순 strcmp 가능
}

void inputString(char *prompt, char *buffer, int maxLen) {
    do {
        printf("%s: ", prompt);
        fgets(buffer, maxLen, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
    } while(strlen(buffer) == 0);
}

void addJobPost() {
    JobPost *newPost = (JobPost *)malloc(sizeof(JobPost));
    newPost->id = nextId++;

    inputString("제목 입력", newPost->title, TITLE_LEN);
    inputString("게시 날짜 (YYYY-MM-DD)", newPost->postDate, DATE_LEN);
    inputString("마감 날짜 (YYYY-MM-DD)", newPost->dueDate, DATE_LEN);

    char buffer[10];
    do {
        inputString("채용 인원", buffer, sizeof(buffer));
        newPost->numberOfHires = atoi(buffer);
    } while(newPost->numberOfHires <= 0);

    inputString("채용 분야", newPost->field, FIELD_LEN);

    printf("자격 요건 입력 (끝에 줄바꿈 없이 입력 후 Enter): ");
    char qualBuf[QUALIFICATION_LEN];
    fgets(qualBuf, QUALIFICATION_LEN, stdin);
    qualBuf[strcspn(qualBuf, "\n")] = '\0';

    newPost->qualification = (char *)malloc(strlen(qualBuf) + 1);
    strcpy(newPost->qualification, qualBuf);
    newPost->next = jobList;
    jobList = newPost;

    printf("✅ 구인 공고가 등록되었습니다.\n\n");
}

void listActiveJobs() {
    char today[DATE_LEN];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(today, DATE_LEN, "%Y-%m-%d", tm_info);

    JobPost *cur = jobList;
    int count = 0;

    while(cur != NULL) {
        if(compareDate(cur->dueDate, today) >= 0) {
            printf("ID: %d | 제목: %s | 게시: %s | 마감: %s\n", cur->id, cur->title, cur->postDate, cur->dueDate);
            count++;
        }
        cur = cur->next;
    }
    if(count == 0) {
        printf("⚠️  마감되지 않은 공고가 없습니다. 공고를 새로 작성하세요.\n");
        addJobPost();
    }
}

void viewJobDetail() {
    listActiveJobs();
    int id;
    printf("상세 내용을 볼 공고 ID 입력: ");
    scanf("%d", &id); getchar(); // flush newline

    JobPost *cur = jobList;
    while(cur != NULL) {
        if(cur->id == id) {
            printf("\n[공고 상세 정보]\n");
            printf("제목: %s\n", cur->title);
            printf("게시일: %s\n", cur->postDate);
            printf("마감일: %s\n", cur->dueDate);
            printf("채용 인원: %d\n", cur->numberOfHires);
            printf("채용 분야: %s\n", cur->field);
            printf("자격 요건: %s\n\n", cur->qualification);
            return;
        }
        cur = cur->next;
    }
    printf("❌ 해당 ID의 공고를 찾을 수 없습니다.\n\n");
}

void postToSNS() {
    printf("소셜 네트워크 목록:\n");
    for(int i = 0; i < snsCount; i++) {
        printf("%d. %s\n", i+1, snsList[i].name);
    }
    printf("SNS 선택 번호 입력: ");
    int choice;
    scanf("%d", &choice); getchar();
    if(choice < 1 || choice > snsCount) {
        printf("❌ 잘못된 선택입니다.\n");
        return;
    }

    int id;
    printf("게시할 공고 ID 입력: ");
    scanf("%d", &id); getchar();

    printf("✅ SNS [%s]에 공고(ID: %d)가 게시되었습니다.\n", snsList[choice-1].name, id);
    printf("API KEY: %s\nAPI URL: %s\n\n", snsList[choice-1].apiKey, snsList[choice-1].apiUrl);
}

void listExpiredJobs() {
    char today[DATE_LEN];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(today, DATE_LEN, "%Y-%m-%d", tm_info);

    JobPost *cur = jobList;
    int found = 0;

    printf("[마감된 구인 공고 목록]\n");
    while(cur != NULL) {
        if(compareDate(cur->dueDate, today) < 0) {
            printf("ID: %d | 제목: %s | 게시: %s | 마감: %s\n", cur->id, cur->title, cur->postDate, cur->dueDate);
            found = 1;
        }
        cur = cur->next;
    }

    if(!found) {
        printf("📅 마감된 공고가 없습니다.\n");
    }
}

void freeJobPosts() {
    JobPost *cur = jobList;
    while(cur != NULL) {
        JobPost *tmp = cur;
        cur = cur->next;
        free(tmp->qualification);
        free(tmp);
    }
}

void findSpecialist() {
    int menu;
    do {
        printf("\n===== 사람을 찾습니다 =====\n");
        printf("1. 구인 공고 작성\n");
        printf("2. 구인 공고 확인\n");
        printf("3. SNS에 게시\n");
        printf("4. 마감된 공고 확인\n");
        printf("0. 종료\n");
        printf("선택 > ");
        scanf("%d", &menu); getchar(); // flush newline

        switch(menu) {
            case 1: addJobPost(); break;
            case 2: viewJobDetail(); break;
            case 3: postToSNS(); break;
            case 4: listExpiredJobs(); break;
            case 0: printf("👋 종료합니다.\n"); break;
            default: printf("❌ 잘못된 선택입니다.\n"); break;
        }
    } while(menu != 0);

    freeJobPosts();
}
