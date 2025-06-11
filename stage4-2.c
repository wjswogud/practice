#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50

typedef enum { MALE, FEMALE } Gender;

// GRBAS 구조체 정의
typedef struct {
    int G, R, B, A, S;
} GRBAS;

// 나의 소리 정보 저장 구조체
typedef struct {
    char name[MAX_NAME];
    float frequency;  // Hz
    float amplitude;  // dB
    float jitter;     // %
    GRBAS tone;
} VoiceInfo;

// 범위 구조체 (불변)
typedef struct {
    float freqMin, freqMax;
    float ampMin, ampMax;
    float jitterMin, jitterMax;
} const VoiceRange;

// 남성과 여성의 범위 정의 (불변)
const VoiceRange maleRange = {85.0, 180.0, 2.5, 3.6, 0.2, 0.6};
const VoiceRange femaleRange = {165.0, 255.0, 3.5, 4.7, 0.3, 1.0};

// 함수 포인터 예시: 비교용
typedef int (*CompareFunc)(float, float);

// ------------------ 기능 함수 ------------------

float getRandomInRange(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

int getRandomGRBAS() {
    return rand() % 4;
}

void getMyVoiceFromHeaven(VoiceInfo* voice, Gender gender) {
    const VoiceRange* range = (gender == MALE) ? &maleRange : &femaleRange;

    voice->frequency = getRandomInRange(range->freqMin, range->freqMax);
    voice->amplitude = getRandomInRange(range->ampMin, range->ampMax);
    voice->jitter = getRandomInRange(range->jitterMin, range->jitterMax);

    voice->tone.G = getRandomGRBAS();
    voice->tone.R = getRandomGRBAS();
    voice->tone.B = getRandomGRBAS();
    voice->tone.A = getRandomGRBAS();
    voice->tone.S = getRandomGRBAS();
}

int guessFloat(float answer, float min, float max, const char* label) {
    float guess;
    int chances = 3;
    while (chances--) {
        printf("%s를 입력하세요 (%.2f ~ %.2f): ", label, min, max);
        scanf("%f", &guess);
        if (guess < answer)
            printf("Up!\n");
        else if (guess > answer)
            printf("Down!\n");
        else {
            printf("정답입니다!\n");
            return 1;
        }
    }
    printf("정답은 %.2f였습니다.\n", answer);
    return 0;
}

int guessInt(int answer, const char* label) {
    int guess;
    int chances = 3;
    while (chances--) {
        printf("%s 점수를 입력하세요 (0~3): ", label);
        scanf("%d", &guess);
        if (guess < answer)
            printf("Up!\n");
        else if (guess > answer)
            printf("Down!\n");
        else {
            printf("정답입니다!\n");
            return 1;
        }
    }
    printf("정답은 %d였습니다.\n", answer);
    return 0;
}

// ------------------ 음성 추측 게임 ------------------

void guessMyFreq(float answer, const VoiceRange* range) {
    guessFloat(answer, range->freqMin, range->freqMax, "주파수");
}

void guessMyAmplitude(float answer, const VoiceRange* range) {
    guessFloat(answer, range->ampMin, range->ampMax, "진폭");
}

void guessMyJitter(float answer, const VoiceRange* range) {
    guessFloat(answer, range->jitterMin, range->jitterMax, "Jitter");
}

void guessMyTone(GRBAS answer) {
    guessInt(answer.G, "G (Grade)");
    guessInt(answer.R, "R (Roughness)");
    guessInt(answer.B, "B (Breathiness)");
    guessInt(answer.A, "A (Asthenia)");
    guessInt(answer.S, "S (Strain)");
}

// ------------------ 메인 메뉴 함수 ------------------

void findMyVoice() {
    char nickname[MAX_NAME];
    char genderInput;
    Gender gender;
    VoiceInfo myVoice;

    printf("닉네임을 입력하세요: ");
    scanf("%s", nickname);
    strcpy(myVoice.name, nickname);

    printf("성별을 입력하세요 (M/F): ");
    scanf(" %c", &genderInput);
    gender = (genderInput == 'M' || genderInput == 'm') ? MALE : FEMALE;

    getMyVoiceFromHeaven(&myVoice, gender);

    const VoiceRange* range = (gender == MALE) ? &maleRange : &femaleRange;

    printf(">> 주파수 추측 게임 시작!\n");
    guessMyFreq(myVoice.frequency, range);

    printf(">> 진폭 추측 게임 시작!\n");
    guessMyAmplitude(myVoice.amplitude, range);

    printf(">> Jitter 추측 게임 시작!\n");
    guessMyJitter(myVoice.jitter, range);

    printf(">> 보너스: 음성 톤(GRBAS) 추측 게임!\n");
    guessMyTone(myVoice.tone);

    printf("\n🎉 %s님의 목소리 프로파일링 완료!\n", myVoice.name);
    printf("주파수: %.2f Hz, 진폭: %.2f dB, Jitter: %.2f%%\n", myVoice.frequency, myVoice.amplitude, myVoice.jitter);
    printf("GRBAS 점수 => G:%d R:%d B:%d A:%d S:%d\n",
           myVoice.tone.G, myVoice.tone.R, myVoice.tone.B, myVoice.tone.A, myVoice.tone.S);
}

