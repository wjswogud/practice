#ifndef STAGE8_H
#define STAGE8_H

#define MAX_LEN 100
#define MAX_ARTISTS 50

typedef struct {
    char name[MAX_LEN];
    char nickname[MAX_LEN];
    char birthdate[MAX_LEN];
    char gender[MAX_LEN];
    char education[MAX_LEN];
    char phone[MAX_LEN];      // 암호화
    char email[MAX_LEN];      // 암호화
    char nationality[MAX_LEN];
    char height[MAX_LEN];
    char weight[MAX_LEN];
    char bloodType[MAX_LEN];
    char allergy[MAX_LEN];    // 암호화
    char sns[MAX_LEN];
} Artist;

extern Artist artistList[MAX_ARTISTS];
extern int artistCount;
extern int encryptionMethod;

enum { XOR_ENCRYPT = 1, OR_ENCRYPT, AND_ENCRYPT, SHIFT_ENCRYPT };

void protectMyData();
void encrypt(char *data, char key);
void decrypt(char *data, char key);
void saveArtistsToFile(const char *filename, char key);
void loadArtistsFromFile(const char *filename);
void displayArtistList();
void displayArtistDetails(int index, int decrypt, char key);
void chooseEncryptionMethod();

#endif
