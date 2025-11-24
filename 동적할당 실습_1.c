//동적할당 실습_1 - 동적할당 활용하기
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
  int x;
  int y;
} POINT;

// 메뉴 입력 함수
int inputMenu(void){
  int input;
  printf("메뉴입력(1. 구조체 만들기, 2. 구조체 출력하기, -1. 종료) : ");
  scanf("%d", &input);
  return input;
}

POINT* makePoint(void){
  POINT* p = (POINT*)malloc(sizeof(POINT));
  p->x = rand() % 100;
  p->y = rand() % 100;
  return p;
}

void printPoint(POINT* p[], int size){
  for(int i = 0; i < size; i++){
    printf("x:%d, y:%d\n", p[i]->x, p[i]->y);
  }
}

void freePoints(POINT* p[], int size){
  for(int i = 0; i < size; i++) free(p[i]);
}

int main()
{
  int menu;
  int count = 0;
  POINT* points[100];

  do{
    menu = inputMenu();
    if(menu == 1){
           
      points[count] = makePoint();
      count++;
      printf("잘 만들었습니다.\n");

    }else if(menu == 2){
      // 구조체 출력하기
      printPoint(points, count);
    }else if(menu == -1){
      // 종료 및 메모리 해제
      freePoints(points, count);
      printf("프로그램을 종료합니다.\n");
    }
  }while(menu > 0);
  return 0;
}
