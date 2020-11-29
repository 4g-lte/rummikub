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
/* main함수에 추가
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
/*main함수에 추가
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
                    takeoutkepp(keep[a], setting[b],c);
*/



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