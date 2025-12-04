#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _lotto{
  int number[6];
  int bonus;
  int NO;
} LOTTO;

void initLotto(LOTTO* l){
  for(int i=0; i<6; i++) l->number[i] = 0;
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
  for(int i=0; i<6; i++){
    num = rand() % 45 + 1;
    if(i==0) l.number[i] = num;
    else if(i>0 && !dup(l, num, i-1)) l.number[i] = num;
    else{
      i--;
    }
  }
  return l;
}

LOTTO drawingLotto(int NO){
  LOTTO l;
  int num;
  initLotto(&l);
  l.NO = NO;
  for(int i=0; i<6; i++){
    num = rand() % 45 + 1;
    if(i==0) l.number[i] = num;
    else if(i>0 && !dup(l, num, i-1)) l.number[i] = num;
    else{
      i--;
    }
  }
  do{
    l.bonus = rand() % 45 + 1;
  } while(dup(l, l.bonus, 5)); 
  return l;
}

void printLotto(LOTTO l){
  printf("#%d lotto number : %2d, %2d, %2d, %2d, %2d, %2d\n", l.NO,
    l.number[0], l.number[1], l.number[2], l.number[3], l.number[4], l.number[5]);
  printf("BONUS : %d\n", l.bonus);
}


int matchCount(LOTTO l1, LOTTO l2){
  int mcount = 0;
  for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
      if(l1.number[i] == l2.number[j]) mcount++;
    }
  }
  return mcount;
}

int main()
{
  LOTTO l, l2;
  FILE* fp;
  int count;
  
  srand(time(NULL)); // 랜덤 시드 초기화
    fp = fopen("20201111.bin", "rb");

  if(fp == NULL) {
    printf("[알림] 파일이 없어 테스트용 데이터를 생성합니다.\n");
    l = createAuto(20201111);
    fp = fopen("20201111.bin", "wb");
    fwrite(&l, sizeof(LOTTO), 1, fp);
    fclose(fp);
        
    fp = fopen("20201111.bin", "rb");
  }

  if(fp == NULL) exit(1);
  fread(&l, sizeof(LOTTO), 1, fp);
  fclose(fp);

  l2 = drawingLotto(l.NO); 
  count = matchCount(l, l2);
  
  printf("--- 구매한 로또 (파일에서 읽음) ---\n");
  printLotto(l);
  printf("\n--- 당첨 번호 추첨 ---\n");
  printLotto(l2);
  printf("\n[결과] 일치하는 번호 개수 : %d\n", count);
  return 0;
}
