#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

struct card//카드들의 구조체
{
    char color[10];
    int num;
    unsigned jocker;
};

struct playercard {//플레이어의 카드
    int enroll;//등록여부를 조사한다.
    unsigned long long owncard[60];//player가 가지고 있는 카드;
    int size;
};

void putkeep(unsigned long long* keep, struct card* cards, unsigned long long* setting);
//주머니에 카드를 넣는다.
//setting에는 나중에 정리하기위해 '0'으로 표시해준다.

void takeoutkepp(unsigned long long* keep, struct card* cards, unsigned long long* setting);
//주머니에서 카드를 꺼낸다.
//

void draw(struct card* cards, struct playercard* playercards);
//플레이어에게 랜덤으로 한장을 준다.

void investigate(unsigned long long* setting);
//setting에 있는 숫자들이 맞는지 조사하는 함수.

void printsettingcard(unsigned long long* a);
//내려놓은 카드만 출력
//카드를 색깔별로 출력할 함수
//포인터 배열에는 새로운 배열함수가 존재(2차원 배열이라 생각)

void printplayercard(unsigned long long* a);
//플레이어의 카드를 출력

void copyarray(unsigned long long* a, unsigned long long* b);
//원래 상태로 복구할 것을 대비하기 위해 복사해두기.

void startrandom(struct playercard* playercards);
//게임을 시작할 때 14장의 카드를 랜덤으로 나누어준다.
//플레이어에게 분배된 카드는 카드의 숫자를 0으로 만들어준다.

void finish(struct playercard* playercards);
//플레이어가 몇장의 카드를 가졌는지 조사해주기.

int main(void) {
    struct card cards[106] = { {"blue",1,0},{"blue",2,0}, {"blue",3,0},{"blue",4,0}, {"blue",5,0},{"blue",6,0}, {"blue",7,0},{"blue",8,0}, {"blue",9,0},{"blue",10,0},{"blue",11,0},{"blue",12,0},{"blue",13,0},
       {"blue",1,0},{"blue",2,0}, {"blue",3,0},{"blue",4,0}, {"blue",5,0},{"blue",6,0}, {"blue",7,0},{"blue",8,0}, {"blue",9,0},{"blue",10,0},{"blue",11,0},{"blue",12,0},{"blue",13,0},
    {"red",1,0},{"red",2,0}, {"red",3,0},{"red",4,0}, {"red",5,0},{"red",6,0}, {"red",7,0},{"red",8,0}, {"red",9,0},{"red",10,0},{"red",11,0},{"red",12,0},{"red",13,0},
    {"red",1,0},{"red",2,0}, {"red",3,0},{"red",4,0}, {"red",5,0},{"red",6,0}, {"red",7,0},{"red",8,0}, {"red",9,0},{"red",10,0},{"red",11,0},{"red",12,0},{"red",13,0},
    {"black",1,0},{"black",2,0}, {"black",3,0},{"black",4,0}, {"black",5,0},{"black",6,0}, {"black",7,0},{"balck",8,0}, {"black",9,0},{"black",10,0},{"black",11,0},{"black",12,0},{"black",13,0},
    {"black",1,0},{"black",2,0}, {"black",3,0},{"black",4,0}, {"black",5,0},{"black",6,0}, {"black",7,0},{"balck",8,0}, {"black",9,0},{"black",10,0},{"black",11,0},{"black",12,0},{"black",13,0} ,
    {"orange",1,0},{"orange",2,0}, {"orange",3,0},{"orange",4,0}, {"orange",5,0},{"orange",6,0}, {"orange",7,0},{"orange",8,0}, {"orange",9,0},{"orange",10,0},{"orange",11,0},{"orange",12,0},{"orange",13,0},
    {"orange",1,0},{"orange",2,0}, {"orange",3,0},{"orange",4,0}, {"orange",5,0},{"orange",6,0}, {"orange",7,0},{"orange",8,0}, {"orange",9,0},{"orange",10,0},{"orange",11,0},{"orange",12,0},{"orange",13,0}, {"jocker",0,1 }, {"jocker",0,1} };
    unsigned long long setting[35][15] = { 0 };
    //바닥에 깔려있는 카드들
    unsigned long long keep[15] = { 0 };
    //플레이어의 차례에 사용할 주머니
    int playernumber = 0;
    printf("게임할 인원을 입력해주세요. ");
    scanf_s("%d", &playernumber);//플레이어의 수 입력받기
    struct playercard playercards[4] = { 0 };
    for (int i = 0; i < playernumber; i++) {
        startrandom(&playercards[i]);
    }
    system("cls");
    printf("start game");
    Sleep(3000);
    system("cls");
    int turn=0;//플레이어의 순서
    int control = 0;//차례에 무엇을 할 지 입력받기
    int check = 0;//순서를 넘겨도 되는지 확인

    while(1){
        if (turn + 1 == playernumber)//순서를 반복하기 위해
            turn = 0;
        if (playercards[turn].size == 0) {//플레이어의 카드 숫자가 0장이라면 다음 사람으로 넘어간다.
            turn++;
        }
        else {
            while (1) {
                unsigned long long virtualsetting[35][15] = { 0 };
                //초기화를 대비하기 위해서 이용할 가상의 setting;
                copyarray(setting, virtualsetting);
                check = 0;
                printsettingcard(setting);
                printf("player%d's card : ");
                printplayercard(&playercards[turn]);
                if (playercards[turn].enroll == 0) {
                    printf("1. 내려놓기 2.XX 3.XX 4.조커바꾸기 5. 초기화 6. 카드 뽑기");
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
                switch(control) {
                    case 1:
                        printf("dd");
                        break;
                    case 2:
                        printf("asdf");
                        break;
                    case 3:
                        printf("asdf");
                    case 4:
                        printf("dd");
                        break;
                    case 5:
                        printf("asdf");
                        break;
                    case 6:
                        printf("asdf");
                    case 7:
                        printf("asdf");

                }
            }

        }
    }
    return 0;
}