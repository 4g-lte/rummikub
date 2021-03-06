void copyarray(struct card* a, struct card* b) {
    //원래 상태로 복구할 것을 대비하기 위해 복사해두기.
    memcpy(b, a, sizeof(struct card));
}
void startrandom(struct playercard* playercards, struct card* cards) {
    //게임을 시작할 때 14장의 카드를 랜덤으로 나누어준다.
    //플레이어에게 분배된 카드는 카드의 숫자를 0으로 만들어준다.
    srand((unsigned)time(NULL));
    for (int i = 0; i < 14; i++)
    {
        int k = 0;
        k = rand() % 106;
        if ((cards[k].num == 0) && (cards[k].jocker == 0))
            i--;
        else
        {
            strcpy_s(playercards->owncard[i]->color, sizeof(cards[k].color), cards[k].color);
            playercards->owncard[i]->num = cards[k].num;
            playercards->owncard[i]->jocker = cards[k].jocker;
            strcpy_s(cards[k].color,sizeof(cards[k].color), "0");//카드 색깔 = "0"
            cards[k].num = 0;//카드 숫자 = 0
            cards[k].jocker = 0;// 카드 조커 = 0
            printf("%s%d ", playercards->owncard[i]->color, playercards->owncard[i]->num);
        }
    }
}
void draw(struct card* cards, struct playercard* playercards) {
    //플레이어에게 랜덤으로 한장을 준다.
    int k = 0;
    int i = 0;
    while (1)
    {
        if ((playercards->owncard[i]->color) != "0")
            i++;
        else
            break;
    }
    while (1) {
        k = rand() % 106;
        if (cards[k].color != "0")
        {
            strcpy_s(playercards->owncard[i]->color, sizeof(cards[k].color), cards[k].color);
            playercards->owncard[i]->num = cards[k].num;
            playercards->owncard[i]->jocker = cards[k].jocker;
            break;
        }
    }
}
int finish(struct playercard* playercards) {
    //플레이어가 몇장의 카드를 가졌는지 조사해주기.
    //플레이어가 0장의 카드를 갖고 있으면 1로 반환.
    int card_Num = 0;
    while (card_Num < 27) {
        if ((playercards->owncard[card_Num]->color) != "0")
            card_Num++;
    }
    if (card_Num == 0)
        return 1;
    else
        return 0;
}