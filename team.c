#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

struct card//ī����� ����ü
{
    char color[10];
    int num;
    unsigned jocker;
};

struct playercard {//�÷��̾��� ī��
    int enroll;//��Ͽ��θ� �����Ѵ�.
    unsigned long long owncard[60];//player�� ������ �ִ� ī��;
    int size;
};

void putkeep(unsigned long long* keep, struct card* cards, unsigned long long* setting);
//�ָӴϿ� ī�带 �ִ´�.
//setting���� ���߿� �����ϱ����� '0'���� ǥ�����ش�.

void takeoutkepp(unsigned long long* keep, struct card* cards, unsigned long long* setting);
//�ָӴϿ��� ī�带 ������.
//

void draw(struct card* cards, struct playercard* playercards);
//�÷��̾�� �������� ������ �ش�.

void investigate(unsigned long long* setting);
//setting�� �ִ� ���ڵ��� �´��� �����ϴ� �Լ�.

void printsettingcard(unsigned long long* a);
//�������� ī�常 ���
//ī�带 ���򺰷� ����� �Լ�
//������ �迭���� ���ο� �迭�Լ��� ����(2���� �迭�̶� ����)

void printplayercard(unsigned long long* a);
//�÷��̾��� ī�带 ���

void copyarray(unsigned long long* a, unsigned long long* b);
//���� ���·� ������ ���� ����ϱ� ���� �����صα�.

void startrandom(struct playercard* playercards);
//������ ������ �� 14���� ī�带 �������� �������ش�.
//�÷��̾�� �й�� ī��� ī���� ���ڸ� 0���� ������ش�.

void finish(struct playercard* playercards);
//�÷��̾ ������ ī�带 �������� �������ֱ�.

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
    //�ٴڿ� ����ִ� ī���
    unsigned long long keep[15] = { 0 };
    //�÷��̾��� ���ʿ� ����� �ָӴ�
    int playernumber = 0;
    printf("������ �ο��� �Է����ּ���. ");
    scanf_s("%d", &playernumber);//�÷��̾��� �� �Է¹ޱ�
    struct playercard playercards[4] = { 0 };
    for (int i = 0; i < playernumber; i++) {
        startrandom(&playercards[i]);
    }
    system("cls");
    printf("start game");
    Sleep(3000);
    system("cls");
    int turn=0;//�÷��̾��� ����
    int control = 0;//���ʿ� ������ �� �� �Է¹ޱ�
    int check = 0;//������ �Ѱܵ� �Ǵ��� Ȯ��

    while(1){
        if (turn + 1 == playernumber)//������ �ݺ��ϱ� ����
            turn = 0;
        if (playercards[turn].size == 0) {//�÷��̾��� ī�� ���ڰ� 0���̶�� ���� ������� �Ѿ��.
            turn++;
        }
        else {
            while (1) {
                unsigned long long virtualsetting[35][15] = { 0 };
                //�ʱ�ȭ�� ����ϱ� ���ؼ� �̿��� ������ setting;
                copyarray(setting, virtualsetting);
                check = 0;
                printsettingcard(setting);
                printf("player%d's card : ");
                printplayercard(&playercards[turn]);
                if (playercards[turn].enroll == 0) {
                    printf("1. �������� 2.XX 3.XX 4.��Ŀ�ٲٱ� 5. �ʱ�ȭ 6. ī�� �̱�");
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