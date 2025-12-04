#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int dup(LOTTO l, int num, int n){
  for(int i=0; i <= n; i++){
    if(l.number[i] == num) return 1;
  }
  return 0;
}

//자동
LOTTO createAuto(int NO){
    LOTTO l;
    int num;
    initLotto(&l);
    l.NO = NO;
    for(int i=0;i<6;i++){
        num = rand() % 45 + 1;
        if(i==0) l.number[i] = num;
        else if(i>0 && !dup(l, num, i-1)) l.number[i] = num;
        else{
          i--;
          printf("중복발생.. 다시 뽑으세요..\n");
        }
    }
  return l;
}

//수동
LOTTO createManual(int NO){
  LOTTO l;
  int num;
  initLotto(&l);
  l.NO = NO;
  for(int i=0;i<6;i++){
    printf("input number #%d : ", i+1);
    scanf("%d", &num);
    if(i==0) l.number[i] = num;
    else if(i>0 && !dup(l, num, i-1)) l.number[i] = num;
    else{
      i--;
      printf("중복발생.. 다시 뽑으세요..\n");
    }
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
  srand(time(NULL));
  l = createAuto(20201111);
  printLotto(l);
  return 0;
}
