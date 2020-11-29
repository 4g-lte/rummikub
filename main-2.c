#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

struct card//ī����� ����ü
{
    char* color;
    int num;
    unsigned jocker;
};

struct playercard {//�÷��̾��� ī��
    int enroll;//��Ͽ��θ� �����Ѵ�.
    struct card* owncard[60];//player�� ������ �ִ� ī��;
    int size;
};

void putkeep(struct card** keep, struct card* setting);
//�ָӴϿ� ī�带 �ִ´�.
//setting���� ���߿� �����ϱ����� '0'���� ǥ�����ش�.
void takeoutkepp(struct card** keep, struct card** setting, int c);
//�ָӴϿ��� ī�带 ������.
void keepprint(struct card** keep);
//keep�ȿ� �ִ� ����ü�� ������ִ� �Լ�.


int investigate(struct card* setting);
//setting�� �ִ� ���ڵ��� �´��� �����ϴ� �Լ�.
//������ �߻����� ������ 1�� ��ȯ.
void printsettingcard(struct card* a);
//�������� ī�常 ���
//ī�带 ���򺰷� ����� �Լ�
//������ �迭���� ���ο� �迭�Լ��� ����(2���� �迭�̶� ����)
void printplayercard(struct card* a);
//�÷��̾��� ī�带 ���


void copyarray(struct card* a, struct card* b);
//���� ���·� ������ ���� ����ϱ� ���� �����صα�.
void startrandom(struct playercard* playercards, struct card* cards);
//������ ������ �� 14���� ī�带 �������� �������ش�.
//�÷��̾�� �й�� ī��� ī���� ���ڸ� 0���� ������ش�.
void draw(struct card* cards, struct playercard* playercards);
//�÷��̾�� �������� ������ �ش�.
int finish(struct playercard* playercards);
//�÷��̾ ������ ī�带 �������� �������ֱ�.
//�÷��̾ 0���� ī�带 ���� ������ 1�� ��ȯ.

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
    //�ٴڿ� ����ִ� ī���
    struct card* keep[15] = { 0 };
    //�÷��̾��� ���ʿ� ����� �ָӴ�
    int playernumber = 0;
    printf("������ �ο��� �Է����ּ���. ");
    scanf_s("%d", &playernumber);//�÷��̾��� �� �Է¹ޱ�
    struct playercard playercards[4] = { 0 };
    for (int i = 0; i < playernumber; i++) {
        startrandom(&playercards[i], cards);
    }
    system("cls");
    printf("start game");
    Sleep(3000);
    system("cls");
    int turn = 0;//�÷��̾��� ����
    int control = 0;//���ʿ� ������ �� �� �Է¹ޱ�
    int check = 0;//������ �Ѱܵ� �Ǵ��� Ȯ��
    int winner[4] = { 0 };
    int win = 0;
    int finishgame = 0;
    while (1) {
        enrollcard = 0;
        finishgame = 0;
        if (turn + 1 == playernumber)//������ �ݺ��ϱ� ����
            turn = 0;
        if (playercards[turn].size == 0) {//�÷��̾��� ī�� ���ڰ� 0���̶�� ���� ������� �Ѿ��.
            turn++;
        }
        else {
            while (1) {
                a = 0; b = 0; c = 0; d = 0; e = 0;
                struct card* virtualsetting[35][15] = { 0 };
                //�ʱ�ȭ�� ����ϱ� ���ؼ� �̿��� ������ setting;
                struct card* virtualowncards[60] = { 0 };
                copyarray(setting, virtualsetting);
                copyarray(playercards[turn].owncard, virtualowncards);
                check = 0;
                printsettingcard(setting);
                printf("player%d's card : ", turn + 1);
                printplayercard(&playercards[turn]);
                if (playercards[turn].enroll == 0) {
                    printf("1. �������� 2.XX 3.XX 4.��Ŀ�ٲٱ� 5. �ʱ�ȭ 6. ī�� �̱� 7.�� ����\\n");
                    while (1) {
                        scanf_s("%d", &control);
                        if (control != 2 && control != 3)
                            break;
                        printf("�ٽ� �Է����ּ���.\n");
                    }
                }
                else {
                    printf("1.�������� 2.�ָӴϿ� �ֱ� 3.�ָӴϿ��� ������ 4.��Ŀ�ٲٱ� 5.�ʱ�ȭ 6.ī�� �̱� 7.�� ����\n");
                    while (1) {
                        scanf_s("%d", &control);
                        if (control >= 1 && control <= 7);
                        break;
                        printf("�ٽ� �Է����ּ���.\n");
                    }
                }
                if (control == 1) {
                    int playercardsize = 0;
                    for (int j = 0; j < 60; j++) {
                        if (playercards[turn].owncard[j] != 0)
                            playercardsize++;
                    }
                    while (1) {
                        printf("�� ��° ī�带 ������ �ǰ���?");
                        scanf_s("%d", &a);
                        if ((a < 0) && (a > playercardsize)) {
                            printf("�ٽ� �Է����ּ���.\n");
                        }
                        else {
                            break;
                        }
                    }
                    printf("�ְ� ���� ��ġ�� �Է����ּ���.\n");
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
                    printf("1. �ٴ� -> �ָӴ�\n2. ������\n");
                    scanf_s("%d", &c);
                    if (c == 1)
                        printf("�� ��° ī�带 �ָӴϷ� �ְڽ��ϱ�?\n(���� : 4��°�� 5��°ī���� ��� '4 5'�Է�\n)");
                    scanf_s("%d %d", &a, &b);
                    if (setting[a][b] == NULL) {
                        printf("�������� �ʽ��ϴ�.\n");
                        break;
                    }
                    putkeep(keep, setting[a][b]);
                    setting[a][b] = NULL;

                }
                else if (control == 3) {
                    printf("�� ��° ī�带 �ָӴϿ��� �������?\n");
                    scanf_s("%d", &a);
                    if (a == -1)
                        break;
                    else if (keep[a] != NULL) {
                        printf("a��°�� �������� �ʽ��ϴ�.\n");
                        break;
                    }
                    printf("�ְ� ���� ��ġ�� �Է����ּ���.\n");
                    scanf_s("%d %d", &b, &c);
                    takeoutkepp(keep[a], setting[b], c);
                }
                else if (control == 4) {
                    while (1) {
                        printf("��Ŀ�� ��ġ�� �Է����ּ���.(��Ŀ�� ������ '-1'�� �Է����ּ���.)\n");
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
                            printf("1.blue\n2.red\n3.black\n4.orange\n���ϴ� ������ ���ڸ� �Է����ּ���.\n");
                            scanf_s("%d", &c);
                            if (1 <= c && c <= 4) {
                                break;
                            }
                            else {
                                printf("�ٽ� �Է����ּ���.\n");
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
                            printf("���ϴ� ���ڸ� �Է����ּ���.\n");
                            scanf_s("%d", &c);
                            if (1 <= a && a <= 13) {
                                (playercards[turn].owncard[a])->num = a;
                                break;
                            }
                            else {
                                printf("�ٽ� �Է����ּ���.\n");
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
                    printf("5�ʰ� ������ ���� ���ʷ� �Ѿ�ϴ�.\n");
                    Sleep(5000);
                    system("cls");
                    break;
                }
                else if (control == 7) {//enrollcard�����ϱ�
                    int invest = investigate(setting);
                    if (enrollcard >= 30) {
                        playercards[turn].enroll = 1;
                    }
                    if (invest == 1 && playercards[turn].enroll == 1) {
                        a = finish(&playercards[turn]);
                        if (a == 0) {
                            printf("�����մϴ�.");
                        }
                        printf("5�ʰ� ������ ���� ���ʷ� �Ѿ�ϴ�.\n");
                        Sleep(5000);
                        system("cls");
                        turn++;

                        break;
                    }
                    else {
                        printf("���� ������ �� �����ϴ�.\n");
                    }
                }
            }

            for (int i = 0; i < playernumber; i++) {
                finishgame = finish(&playercards[i]);
            }
            if (finishgame == 1) {
                printf("������ �������ϴ�.");
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
        printf("�ָӴϿ� �ִ� ī�� : ");
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