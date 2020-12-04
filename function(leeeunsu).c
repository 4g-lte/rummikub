#include <stdio.h>

struct card//카드들의 구조체
{
    char* color;
    int num;
    int jocker;
    int use;
};

struct playercard {//플레이어의 카드
    int enroll;
    struct card* owncard[60];
    int win;
};

int investigate(struct card** setting) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    for (int i = 0; i < 15; i++) {
        if (setting[i] != NULL) {
            a = i;
            break;
        }
    }


    if (b != 1) {
        for (int i = a; i < 15; i++) {
            if (setting[i] != NULL)
                d++;
        }
    }

    if (setting[a]->num != setting[a + 1]->num) {
        b = 1;
        if (setting[a]->num < setting[a + 1]->num)
            c = 1;
    }
    if (b == 1) {
        if (c == 1) {
            for (int i = a; i < a + d - 1; i++) {
                if (setting[i]->num + 1 == setting[i + 1]->num)
                    e = i - a + 2;
                else if (setting[i]->num + 1 != setting[i + 1]->num || setting[i]->color != setting[i + 1]->color)
                    return 0;
            }
        }
        else {
            for (int i = a; i < a + d - 1; i++) {
                if (setting[i]->num == setting[i + 1]->num + 1)
                    e = i - a + 2;
                else if (setting[i]->num != setting[i + 1]->num + 1 || setting[i]->color != setting[i + 1]->color)
                    return 0;
            }
        }
    }
    else {
        for (int i = a; i < a + d - 1; i++) {
            for (int j = i + 1; j < a + 4; j++) {
                if (setting[a]->color == setting[j]->color)
                    return 0;
            }
            e++;
        }
    }
    if (e >= 3) {
        return 1;
    }
    return 0;

}

void printsettingcard(struct card** setting) {
    int a = 0;
    for (int i = 0; i < 15; i++) {
        if (setting[i] != NULL) {
            if (setting[i]->jocker == 1)
                printf("jocker ");
            else
                printf("%s%d ", setting[i]->color, setting[i]->num);
        }
        else {
            printf("00 ");
        }
    }
    for (int i = 0; i < 15; i++) {
        if (setting[i] != NULL) {
            printf("\n");
            break;
        }
    }
}

void printplayercard(struct playercard* playercards) {
    for (int i = 0; i < 60; i++) {

        if (i % 10 == 0 && i != 0)
            if (playercards->owncard[i] != NULL)
                printf("\n");


        if (playercards->owncard[i] == NULL) {

        }
        else if (playercards->owncard[i]->jocker == 1)
            printf("jocker ");
        else if (playercards->owncard[i]->color != '\0')
            printf("%s%d ", playercards->owncard[i]->color, playercards->owncard[i]->num);
    }
    printf("\n");
}
