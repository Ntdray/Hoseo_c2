/동적할당 실습 - 동적할당 활용하기/
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    int x;
    int y;
}POINT;

int inputMenu(void){
    int input;
    printf("메뉴입력(1. 구조체 만들기, 2. 구조체 출력하기, -1. 종료) : ");
    scanf("%d", &input);
    return input;
}

int main(){
  
  int menu;
  int count = 0;
  POINT* points[100];
  do{
    menu = inputMenu();
    
    if(menu == 1){
      //구조체 만들기
      points[count] = (POINT*)malloc(sizeof(POINT));
      points[count]->x = rand() % 100;
      points[count]->y = rand() % 100;
      count++;
      printf("잘 만들었습니다.\n");
    }else if(menu == 2){
      //구조체 출력하기
      for(int i = 0; i < count; i++)
        printf("x:%d, y:%d\n", points[i]->x, points[i]->y);
    }else if(menu == -1){
      printf("프로그램을 종료합니다.\n");
      // 할당된 메모리를 하나씩 모두 해제
      for(int i = 0; i < count; i++){
        free(points[i]);
        }
    }while(menu > 0);

    return 0;
}
   /*
   POINT* points;
    int count;
    scanf("%d", &count);

    points = (POINT*)malloc(sizeof(POINT) * count);

    for(int i=0;i<count;i++){
        points[i].x = rand() % 100;
        points[i].y = rand() % 100;
    }
    for(int i=0;i<count;i++){
        printf("x - %d, y - %d\n", points[i].x, points[i].y);
    }
    free(points);
    */
