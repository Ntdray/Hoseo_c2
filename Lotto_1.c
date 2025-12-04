#include <stdio.h>

typedef struct _lotto{
  int number[6];
  int bonus;
  int NO;
} LOTTO;

void initLotto(LOTTO* l){
  for(int i=0;i<6;i++) l->number[i] = 0;
  l->bonus = 0;
  l->NO = 0;
}

LOTTO createManual(int NO){
  LOTTO l;
  int num;
  initLotto(&l);
  l.NO = NO;
  for(int i=0;i<6;i++){
    printf("input number #%d : ", i+1);
    scanf("%d", &num);
    l.number[i] = num;
  }
  return l;
}

void printLotto(LOTTO l){
  printf("#%d lotto number : %2d, %2d, %2d, %2d, %2d, %2d\n", l.NO,
    l.number[0],l.number[1],l.number[2],l.number[3],l.number[4],l.number[5]);
  printf("BONUS : %d\n", l.bonus);
}

int main()
{
  LOTTO l;
  
  l = createManual(20201111);
  printLotto(l);
  return 0;
}
