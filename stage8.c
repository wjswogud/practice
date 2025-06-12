#include <stdio.h>
#include <string.h>
#include "stage8.h"

Artist artistList[MAX_ARTISTS];
int artistCount = 0;

void encrypt(char *data, char key, CryptoAlgorithm algo) {
    for (int i = 0; i < strlen(data); i++) {
        switch (algo) {
            case XOR: data[i] ^= key; break;
            case OR: data[i] |= key; break;
            case AND: data[i] &= key; break;
            case SHIFT: data[i] = (data[i] << 1) | (key & 1); break;
        }
    }
}

void decrypt(char *data, char key, CryptoAlgorithm algo) {
    for (int i = 0; i < strlen(data); i++) {
        switch (algo) {
            case XOR: data[i] ^= key; break;
            case OR: data[i] &= ~key; break; // OR 복호화는 손실있음
            case AND: data[i] |= ~key; break; // AND 복호화는 손실있음
            case SHIFT: data[i] = (data[i] >> 1); break;
        }
    }
}

void saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < artistCount; i++) {
        Artist *a = &artistList[i];
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%.2f,%.2f,%s,%s,%s,%d\n",
            a->name, a->nickname, a->birthdate, a->gender, a->education,
            a->phone, a->email, a->nationality, a->height, a->weight,
            a->blood_type, a->allergy, a->sns, a->isEncrypted);
    }
    fclose(fp);
}

void loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    while (fscanf(fp, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%f,%f,%99[^,],%99[^,],%99[^,],%d\n",
           artistList[artistCount].name, artistList[artistCount].nickname,
           artistList[artistCount].birthdate, artistList[artistCount].gender,
           artistList[artistCount].education, artistList[artistCount].phone,
           artistList[artistCount].email, artistList[artistCount].nationality,
           &artistList[artistCount].height, &artistList[artistCount].weight,
           artistList[artistCount].blood_type, artistList[artistCount].allergy,
           artistList[artistCount].sns, &artistList[artistCount].isEncrypted) != EOF) {
        artistCount++;
    }
    fclose(fp);
}

void protectMyData(void) {
    char key;
    int algo;
    printf("암호화 알고리즘 선택 (0: XOR, 1: OR, 2: AND, 3: SHIFT): ");
    scanf("%d", &algo);
    printf("암호화 키 입력 (1글자): ");
    scanf(" %c", &key);

    int n;
    printf("입력할 아티스트 수: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Artist a;
        printf("이름: "); scanf("%s", a.name);
        printf("닉네임: "); scanf("%s", a.nickname);
        printf("생년월일: "); scanf("%s", a.birthdate);
        printf("성별: "); scanf("%s", a.gender);
        printf("학력: "); scanf("%s", a.education);
        printf("휴대폰 번호: "); scanf("%s", a.phone);
        printf("메일: "); scanf("%s", a.email);
        printf("국적: "); scanf("%s", a.nationality);
        printf("키: "); scanf("%f", &a.height);
        printf("몸무게: "); scanf("%f", &a.weight);
        printf("혈액형: "); scanf("%s", a.blood_type);
        printf("알러지: "); scanf("%s", a.allergy);
        printf("SNS: "); scanf("%s", a.sns);

        encrypt(a.phone, key, (CryptoAlgorithm)algo);
        encrypt(a.email, key, (CryptoAlgorithm)algo);
        encrypt(a.allergy, key, (CryptoAlgorithm)algo);

        a.isEncrypted = 1;
        artistList[artistCount++] = a;
    }

    saveToFile("artist_data.txt");

    printf("\n저장된 아티스트 목록:\n");
    for (int i = 0; i < artistCount; i++) {
        printf("%d. %s (%s)\n", i + 1, artistList[i].name, artistList[i].nickname);
    }

    int select;
    printf("출력할 아티스트 번호 선택 (0: 전체 출력): ");
    scanf("%d", &select);

    if (select == 0) {
        for (int i = 0; i < artistCount; i++) {
            Artist *a = &artistList[i];
            printf("\n[%s | %s]\n", a->name, a->nickname);
            printf("전화: %s\n", a->phone);
            printf("메일: %s\n", a->email);
            printf("알러지: %s\n", a->allergy);
        }
    } else if (select > 0 && select <= artistCount) {
        Artist *a = &artistList[select - 1];
        printf("\n[%s | %s]\n", a->name, a->nickname);
        printf("전화: %s\n", a->phone);
        printf("메일: %s\n", a->email);
        printf("알러지: %s\n", a->allergy);

        char opt;
        printf("복호화 하시겠습니까? (y/n): ");
        scanf(" %c", &opt);
        if (opt == 'y') {
            char inputKey;
            printf("복호화 키 입력: ");
            scanf(" %c", &inputKey);
            decrypt(a->phone, inputKey, (CryptoAlgorithm)algo);
            decrypt(a->email, inputKey, (CryptoAlgorithm)algo);
            decrypt(a->allergy, inputKey, (CryptoAlgorithm)algo);
            printf("복호화된 전화: %s\n", a->phone);
            printf("복호화된 메일: %s\n", a->email);
            printf("복호화된 알러지: %s\n", a->allergy);
        }
    }
}
