#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_NOTES 7

// 음표 정의 (A~G)
const char VALID_NOTES[NUM_NOTES] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

// 구조체 정의
typedef struct {
    char name;   // 음표 이름 (A~G)
    int octave;  // 옥타브 (1~8)
} Note;

typedef struct {
    Note root;
    Note third;
    Note fifth;
} Chord;

// 함수 포인터 타입
typedef void (*InputNoteFunc)(Note *note);

// 유효한 음표인지 확인
int isValidNote(char name) {
    for (int i = 0; i < NUM_NOTES; ++i) {
        if (VALID_NOTES[i] == toupper(name)) return 1;
    }
    return 0;
}

// 음표의 인덱스 (음정 계산용)
int getNoteIndex(char name) {
    for (int i = 0; i < NUM_NOTES; ++i) {
        if (VALID_NOTES[i] == toupper(name)) return i;
    }
    return -1;
}

// Note 입력 함수
void inputNote(Note *note) {
    char name;
    int octave;

    // 음표 이름 입력
    do {
        printf("음표를 입력하세요 (A~G): ");
        scanf(" %c", &name);
        name = toupper(name);
    } while (!isValidNote(name));

    // 옥타브 입력
    do {
        printf("옥타브를 입력하세요 (1~8): ");
        scanf("%d", &octave);
    } while (octave < 1 || octave > 8);

    note->name = name;
    note->octave = octave;
}

// 화음 유효성 검사
int validateChord(Chord *chord) {
    // 옥타브 일치
    if (chord->root.octave != chord->third.octave ||
        chord->root.octave != chord->fifth.octave) {
        printf("❌ 모든 음표는 같은 옥타브여야 합니다.\n");
        return 0;
    }

    // 음표 중복
    if (chord->root.name == chord->third.name ||
        chord->root.name == chord->fifth.name ||
        chord->third.name == chord->fifth.name) {
        printf("❌ 음표는 서로 달라야 합니다.\n");
        return 0;
    }

    return 1;
}

// 조화로운 화음 판별 (보너스)
void checkHarmony(Chord *chord) {
    int rootIdx = getNoteIndex(chord->root.name);
    int thirdIdx = getNoteIndex(chord->third.name);
    int fifthIdx = getNoteIndex(chord->fifth.name);

    // 음정 간격 계산
    int thirdInterval = (thirdIdx - rootIdx + NUM_NOTES) % NUM_NOTES;
    int fifthInterval = (fifthIdx - rootIdx + NUM_NOTES) % NUM_NOTES;

    printf("🎼 음정 간격 - 3음: %d, 5음: %d\n", thirdInterval, fifthInterval);

    if ((thirdInterval == 2 || thirdInterval == 3) &&
        (fifthInterval == 4 || fifthInterval == 5)) {
        printf("✅ 조화로운 화음입니다.\n");
    } else {
        printf("⚠️ 조화롭지 않은 화음일 수 있습니다.\n");
    }
}

// [II. 훈련 > 4. 보컬 훈련 > C. 음악이론] 실행 함수
void learnMusicTheory() {
    Chord chord;

    printf("\n🎵 음악이론 훈련 - 화음 구성 🎵\n");

    InputNoteFunc inputFunc = inputNote;

    printf("\n근음을 입력하세요:\n");
    inputFunc(&chord.root);

    printf("\n3음을 입력하세요:\n");
    inputFunc(&chord.third);

    printf("\n5음을 입력하세요:\n");
    inputFunc(&chord.fifth);

    // 입력된 화음 출력
    printf("\n입력한 화음 정보:\n");
    printf("근음: %c%d\n", chord.root.name, chord.root.octave);
    printf("3음 : %c%d\n", chord.third.name, chord.third.octave);
    printf("5음 : %c%d\n", chord.fifth.name, chord.fifth.octave);

    // 화음 검사
    if (validateChord(&chord)) {
        checkHarmony(&chord);
    } else {
        printf("🚫 유효하지 않은 화음입니다.\n");
    }
}
