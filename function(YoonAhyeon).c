#include<stdio.h>
struct card
{
    char* color;
    int num;
    int jocker;
    int use;
};

void putkeep(struct card** keep, struct card* setting) {
    for (int i = 0; i < 15; i++) {
        if (keep[i] == NULL)
            keep[i] = setting;
    }
}
/* main�Լ��� �߰�
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


*/


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
/*main�Լ��� �߰�
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
                    takeoutkepp(keep[a], setting[b],c);
*/



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