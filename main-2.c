#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

struct card//카드들의 구조체
{
    char* color;
    int num;
    unsigned jocker;
};

struct playercard {//플레이어의 카드
    int enroll;//등록여부를 조사한다.
    struct card* owncard[60];//player가 가지고 있는 카드;
    int size;
};

void putkeep(struct card** keep, struct card* setting);
//주머니에 카드를 넣는다.
//setting에는 나중에 정리하기위해 '0'으로 표시해준다.
void takeoutkepp(struct card** keep, struct card** setting, int c);
//주머니에서 카드를 꺼낸다.
void keepprint(struct card** keep);
//keep안에 있는 구조체를 출력해주는 함수.


int investigate(struct card* setting);
//setting에 있는 숫자들이 맞는지 조사하는 함수.
//문제가 발생하지 않으면 1을 반환.
void printsettingcard(struct card* a);
//내려놓은 카드만 출력
//카드를 색깔별로 출력할 함수
//포인터 배열에는 새로운 배열함수가 존재(2차원 배열이라 생각)
void printplayercard(struct card* a);
//플레이어의 카드를 출력


void copyarray(struct card* a, struct card* b);
//원래 상태로 복구할 것을 대비하기 위해 복사해두기.
void startrandom(struct playercard* playercards, struct card* cards);
//게임을 시작할 때 14장의 카드를 랜덤으로 나누어준다.
//플레이어에게 분배된 카드는 카드의 숫자를 0으로 만들어준다.
void draw(struct card* cards, struct playercard* playercards);
//플레이어에게 랜덤으로 한장을 준다.
int finish(struct playercard* playercards);
//플레이어가 몇장의 카드를 가졌는지 조사해주기.
//플레이어가 0장의 카드를 갖고 있으면 1로 반환.

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;
    struct card* d = 0;
    struct card* e = 0;
    int enrollcard = 0;
    char* blue = "blue";
    char* red = "red";
    char* black = "black";
    char* orange = "orange";
    struct card cards[106] = { {"blue",1,0},{"blue",2,0}, {"blue",3,0},{"blue",4,0}, {"blue",5,0},{"blue",6,0}, {"blue",7,0},{"blue",8,0}, {"blue",9,0},{"blue",10,0},{"blue",11,0},{"blue",12,0},{"blue",13,0},
       {"blue",1,0},{"blue",2,0}, {"blue",3,0},{"blue",4,0}, {"blue",5,0},{"blue",6,0}, {"blue",7,0},{"blue",8,0}, {"blue",9,0},{"blue",10,0},{"blue",11,0},{"blue",12,0},{"blue",13,0},
    {"red",1,0},{"red",2,0}, {"red",3,0},{"red",4,0}, {"red",5,0},{"red",6,0}, {"red",7,0},{"red",8,0}, {"red",9,0},{"red",10,0},{"red",11,0},{"red",12,0},{"red",13,0},
    {"red",1,0},{"red",2,0}, {"red",3,0},{"red",4,0}, {"red",5,0},{"red",6,0}, {"red",7,0},{"red",8,0}, {"red",9,0},{"red",10,0},{"red",11,0},{"red",12,0},{"red",13,0},
    {"black",1,0},{"black",2,0}, {"black",3,0},{"black",4,0}, {"black",5,0},{"black",6,0}, {"black",7,0},{"balck",8,0}, {"black",9,0},{"black",10,0},{"black",11,0},{"black",12,0},{"black",13,0},
    {"black",1,0},{"black",2,0}, {"black",3,0},{"black",4,0}, {"black",5,0},{"black",6,0}, {"black",7,0},{"balck",8,0}, {"black",9,0},{"black",10,0},{"black",11,0},{"black",12,0},{"black",13,0} ,
    {"orange",1,0},{"orange",2,0}, {"orange",3,0},{"orange",4,0}, {"orange",5,0},{"orange",6,0}, {"orange",7,0},{"orange",8,0}, {"orange",9,0},{"orange",10,0},{"orange",11,0},{"orange",12,0},{"orange",13,0},
    {"orange",1,0},{"orange",2,0}, {"orange",3,0},{"orange",4,0}, {"orange",5,0},{"orange",6,0}, {"orange",7,0},{"orange",8,0}, {"orange",9,0},{"orange",10,0},{"orange",11,0},{"orange",12,0},{"orange",13,0}, {"jocker",0,1 }, {"jocker",0,1} };
    struct card* setting[35][15] = { 0 };
    //바닥에 깔려있는 카드들
    struct card* keep[15] = { 0 };
    //플레이어의 차례에 사용할 주머니
    int playernumber = 0;
    printf("게임할 인원을 입력해주세요. ");
    scanf_s("%d", &playernumber);//플레이어의 수 입력받기
    struct playercard playercards[4] = { 0 };
    for (int i = 0; i < playernumber; i++) {
        startrandom(&playercards[i], cards);
    }
    system("cls");
    printf("start game");
    Sleep(3000);
    system("cls");
    int turn = 0;//플레이어의 순서
    int control = 0;//차례에 무엇을 할 지 입력받기
    int check = 0;//순서를 넘겨도 되는지 확인
    int winner[4] = { 0 };
    int win = 0;
    int finishgame = 0;
    while (1) {
        enrollcard = 0;
        finishgame = 0;
        if (turn + 1 == playernumber)//순서를 반복하기 위해
            turn = 0;
        if (playercards[turn].size == 0) {//플레이어의 카드 숫자가 0장이라면 다음 사람으로 넘어간다.
            turn++;
        }
        else {
            while (1) {
                a = 0; b = 0; c = 0; d = 0; e = 0;
                struct card* virtualsetting[35][15] = { 0 };
                //초기화를 대비하기 위해서 이용할 가상의 setting;
                struct card* virtualowncards[60] = { 0 };
                copyarray(setting, virtualsetting);
                copyarray(playercards[turn].owncard, virtualowncards);
                check = 0;
                printsettingcard(setting);
                printf("player%d's card : ", turn + 1);
                printplayercard(&playercards[turn]);
                if (playercards[turn].enroll == 0) {
                    printf("1. 내려놓기 2.XX 3.XX 4.조커바꾸기 5. 초기화 6. 카드 뽑기 7.턴 종료\\n");
                    while (1) {
                        scanf_s("%d", &control);
                        if (control != 2 && control != 3)
                            break;
                        printf("다시 입력해주세요.\n");
                    }
                }
                else {
                    printf("1.내려놓기 2.주머니에 넣기 3.주머니에서 꺼내기 4.조커바꾸기 5.초기화 6.카드 뽑기 7.턴 종료\n");
                    while (1) {
                        scanf_s("%d", &control);
                        if (control >= 1 && control <= 7);
                        break;
                        printf("다시 입력해주세요.\n");
                    }
                }
                if (control == 1) {
                    int playercardsize = 0;
                    for (int j = 0; j < 60; j++) {
                        if (playercards[turn].owncard[j] != 0)
                            playercardsize++;
                    }
                    while (1) {
                        printf("몇 번째 카드를 내리실 건가요?");
                        scanf_s("%d", &a);
                        if ((a < 0) && (a > playercardsize)) {
                            printf("다시 입력해주세요.\n");
                        }
                        else {
                            break;
                        }
                    }
                    printf("넣고 싶은 위치를 입력해주세요.\n");
                    scanf_s("%d %d", &b, &c);
                    struct card* owncards = playercards[turn].owncard[a];
                    enrollcard += (owncards)->num;
                    setting[b][c] = 0;
                    for (int j = 1; j <= 15; j++) {
                        if (virtualsetting[b][c + j - 1] == 0)
                            break;
                        setting[b][c + j] = virtualsetting[b][c];
                    }
                }
                else if (control == 2) {
                    printf("1. 바닥 -> 주머니\n2. 나가기\n");
                    scanf_s("%d", &c);
                    if (c == 1)
                        printf("몇 번째 카드를 주머니로 넣겠습니까?\n(예시 : 4번째줄 5번째카드일 경우 '4 5'입력\n)");
                    scanf_s("%d %d", &a, &b);
                    if (setting[a][b] == NULL) {
                        printf("존재하지 않습니다.\n");
                        break;
                    }
                    putkeep(keep, setting[a][b]);
                    setting[a][b] = NULL;

                }
                else if (control == 3) {
                    printf("몇 번째 카드를 주머니에서 꺼낼까요?\n");
                    scanf_s("%d", &a);
                    if (a == -1)
                        break;
                    else if (keep[a] != NULL) {
                        printf("a번째에 존재하지 않습니다.\n");
                        break;
                    }
                    printf("넣고 싶은 위치를 입력해주세요.\n");
                    scanf_s("%d %d", &b, &c);
                    takeoutkepp(keep[a], setting[b], c);
                }
                else if (control == 4) {
                    while (1) {
                        printf("조커의 위치를 입력해주세요.(조커가 없으면 '-1'을 입력해주세요.)\n");
                        scanf_s("%d", &a);
                        if ((playercards[turn].owncard[a])->jocker == 1) {
                            b = 1;
                            break;
                        }
                        else if (a == -1) {
                            break;
                        }

                    }
                    if (b == -1) {
                        while (1) {
                            printf("1.blue\n2.red\n3.black\n4.orange\n원하는 색깔의 숫자를 입력해주세요.\n");
                            scanf_s("%d", &c);
                            if (1 <= c && c <= 4) {
                                break;
                            }
                            else {
                                printf("다시 입력해주세요.\n");
                            }
                        }
                        switch (c) {

                        case 1:
                            (playercards[turn].owncard[a])->color = NULL;
                            (playercards[turn].owncard[a])->color = "blue";
                            break;
                        case 2:
                            (playercards[turn].owncard[a])->color = NULL;
                            (playercards[turn].owncard[a])->color = "red";
                            break;
                        case 3:
                            (playercards[turn].owncard[a])->color = NULL;
                            (playercards[turn].owncard[a])->color = "black";
                            break;
                        case 4:
                            (playercards[turn].owncard[a])->color = NULL;
                            (playercards[turn].owncard[a])->color = "orange";
                            break;
                        }
                        while (1) {
                            printf("원하는 숫자를 입력해주세요.\n");
                            scanf_s("%d", &c);
                            if (1 <= a && a <= 13) {
                                (playercards[turn].owncard[a])->num = a;
                                break;
                            }
                            else {
                                printf("다시 입력해주세요.\n");
                            }
                        }
                    }
                }
                else if (control == 5) {
                    copyarray(virtualsetting, setting);
                    copyarray(virtualowncards, playercards[turn].owncard);
                }
                else if (control == 6) {
                    copyarray(virtualsetting, setting);
                    copyarray(virtualowncards, playercards[turn].owncard);
                    draw(cards, &playercards[turn]);
                    turn++;
                    printf("5초가 지나면 다음 차례로 넘어갑니다.\n");
                    Sleep(5000);
                    system("cls");
                    break;
                }
                else if (control == 7) {//enrollcard조사하기
                    int invest = investigate(setting);
                    if (enrollcard >= 30) {
                        playercards[turn].enroll = 1;
                    }
                    if (invest == 1 && playercards[turn].enroll == 1) {
                        a = finish(&playercards[turn]);
                        if (a == 0) {
                            printf("축하합니다.");
                        }
                        printf("5초가 지나면 다음 차례로 넘어갑니다.\n");
                        Sleep(5000);
                        system("cls");
                        turn++;

                        break;
                    }
                    else {
                        printf("턴을 종료할 수 없습니다.\n");
                    }
                }
            }

            for (int i = 0; i < playernumber; i++) {
                finishgame = finish(&playercards[i]);
            }
            if (finishgame == 1) {
                printf("게임이 끝났습니다.");
                break;
            }
        }
    }
    return 0;
}




void putkeep(struct card** keep, struct card* setting) {
    for (int i = 0; i < 15; i++) {
        if (keep[i] == NULL)
            keep[i] = setting;
    }
}

void takeoutkepp(struct card** keep, struct card** setting, int c) {
    struct card* virtual[15] = { 0 };
    for (int i = 0; i < 15; i++) {
        virtual[i] = setting[i];
    }
    for (int i = c; i < 14; i++) {
        if (setting[c] != NULL)
            setting[c + 1] = virtual[c];
    }
    setting[c] = keep;
}

void keepprint(struct card** keep) {
    if (keep[0] != NULL)
        printf("주머니에 있는 카드 : ");
    for (int i = 0; i < 15; i++) {
        if (keep[i] == NULL)
            break;
        if (keep[i]->jocker == 1) {
            printf("jocker ");
        }
        else if (keep[i]->color != '\0') {
            printf("%s%d ", keep[i]->color, keep[i]->num);
        }
    }
    if (keep[0] != NULL)
        printf("\n");
}