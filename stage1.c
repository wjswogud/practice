#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINING 8

// 메뉴 텍스트 정의 (보너스: 2개의 2차원 배열)
const char *main_menu[] = {
    "I. 오디션 관리",
    "II. 훈련",
    "III. 데뷔"
};

const char *training_menu[] = {
    "1. 체력과 지식",
    "2. 자기관리 및 팀워크",
    "3. 언어 및 발음",
    "4. 보컬",
    "5. 댄스",
    "6. 비주얼 및 이미지",
    "7. 연기 및 무대 퍼포먼스",
    "8. 팬 소통"
};

// 훈련 결과 저장
char training_results[MAX_TRAINING] = {0}; // 'P' = 합격, 'F' = 불합격, 0 = 미수행

// 함수 선언
void run_main_menu();
void audition_management();
void training_menu_handler();
void debut();
void print_main_menu();
void print_training_menu();
void handle_training(int index);
int all_pre_training_passed();

// 메인 함수
int main() {
    run_main_menu();
    return 0;
}

// 주 메뉴 출력 및 선택
void run_main_menu() {
    char input[10];

    while (1) {
        print_main_menu();
        printf("메뉴를 선택하세요 (Q 또는 0 입력 시 종료): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') {
            printf("프로그램을 종료합니다.\n");
            exit(0);
        }

        switch (input[0]) {
            case '1':
                audition_management();
                break;
            case '2':
                training_menu_handler();
                break;
            case '3':
                debut();
                break;
            default:
                printf("올바른 번호를 입력하세요.\n");
        }
    }
}

// 주 메뉴 출력
void print_main_menu() {
    printf("\n==== 마그라테아 프로그램 ====\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, main_menu[i]);
    }
}

// 오디션 관리 함수
void audition_management() {
    printf("\n[오디션 관리 시스템] 준비 중입니다...\n\n");
}

// 데뷔 함수
void debut() {
    printf("\n[데뷔 시스템] 준비 중입니다...\n\n");
}

// 훈련 메뉴 처리
void training_menu_handler() {
    char input[10];

    while (1) {
        print_training_menu();
        printf("훈련 메뉴를 선택하세요 (B 또는 Q: 이전 메뉴): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'B' || input[0] == 'b' || input[0] == 'Q' || input[0] == 'q') {
            return;
        }

        int choice = atoi(input);
        if (choice < 1 || choice > MAX_TRAINING) {
            printf("1~8 사이의 숫자를 입력하세요.\n");
            continue;
        }

        handle_training(choice - 1);
    }
}

// 훈련 메뉴 출력
void print_training_menu() {
    printf("\n==== 훈련 메뉴 ====\n");
    for (int i = 0; i < MAX_TRAINING; i++) {
        printf("%d. %s [%c]\n", i + 1, training_menu[i], training_results[i] ? training_results[i] : '-');
    }
}

// 훈련 항목 처리
void handle_training(int index) {
    if (training_results[index]) {
        printf("이미 완료한 훈련입니다.\n");
        return;
    }

    // 조건 확인
    if (index == 0) {
        // 체력과 지식은 언제나 가능
    } else if (index == 1) {
        if (training_results[0] != 'P') {
            printf("1번 훈련을 먼저 통과해야 합니다.\n");
            return;
        }
    } else {
        if (!all_pre_training_passed()) {
            printf("1번과 2번 훈련을 모두 통과해야 이 항목을 선택할 수 있습니다.\n");
            return;
        }
    }

    char input[10];
    printf("평가 결과를 입력하시겠습니까? (Y/N): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("훈련을 마치고 인증에 통과했나요? (P/F): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'P' || input[0] == 'p') {
            training_results[index] = 'P';
            printf("훈련에 통과했습니다!\n");
        } else {
            training_results[index] = 'F';
            printf("훈련에 실패했습니다.\n");
        }
    } else {
        printf("훈련을 취소했습니다.\n");
    }
}

// 1, 2번 훈련 통과 여부
int all_pre_training_passed() {
    return (training_results[0] == 'P' && training_results[1] == 'P');
}
