//동적할당 실습_2
#include <stdio.h>
#include <stdlib.h>
typedef struct point{
  int x;
int y;
} POINT;

// 메뉴 입력 함수
int inputMenu(void){
  int input;
  printf("\n=========================\n");
  printf("1. point 만들기\n");
  printf("2. point 출력하기\n");
  printf("3. 화면 클리어\n");
  printf("4. 파일 저장\n");
  printf("5. 파일 로드\n");
  printf("-1. 종료\n");
  printf("메뉴 입력 : ");
  scanf("%d", &input);
  return input;
}

// 구조체 생성 (메모리 할당 및 난수 설정)
POINT* makePoint(void){
  POINT* p = (POINT*)malloc(sizeof(POINT));
  p->x = rand() % 100;
  p->y = rand() % 100;
  return p;
}

// 구조체 배열 출력
void printPoint(POINT* p[], int size){
  for(int i = 0; i < size; i++){
    printf("x:%d, y:%d\n", p[i]->x, p[i]->y);
  }
}

// 메모리 해제
void freePoints(POINT* p[], int size){
  for(int i = 0; i < size; i++) free(p[i]);
}

// 파일 저장 함수
int saveFile(POINT* p[], int count){
  FILE* fp;
  fp = fopen("points.bin", "ab");
  if(fp == NULL) return 0;

  for(int i = 0; i < count; i++){
    fwrite(p[i], sizeof(POINT), 1, fp);
  }
  fclose(fp);
  return 1;
}
// 파일 로드 함수
int loadFile(POINT* p[], int max){
  FILE* fp;
  int fSize, fCount;
  fp = fopen("points.bin", "rb");
  if(fp == NULL) return 0;

  fseek(fp, 0, SEEK_END);
  fSize = ftell(fp);
  fCount = fSize / sizeof(POINT);
  rewind(fp);

  for(int i = 0; i < fCount; i++){
    if(i == max) break; // 배열 최대 크기(100)를 넘으면 중단
    p[i] = (POINT*)malloc(sizeof(POINT)); // 로드할 데이터를 담을 메모리 할당
    fread(p[i], sizeof(POINT), 1, fp);
  }
  fclose(fp);
  return fCount; // 로드된 개수 반환
}

int main()
{
  int menu;
  int count = 0;
  POINT* points[100];

  do{
    menu = inputMenu();
    switch(menu){
      case 1:
        points[count] = makePoint();
        count++;
        printf("잘 만들었습니다.\n");
        break;
      case 2:
        printPoint(points, count);
        break;
      case 3:
        system("clear");
        break;
      
      case 4: // 파일 저장
        if(!saveFile(points, count)) printf("file open error...\n");
        else printf("file writing success..\n");
        break;
      case 5: // 파일 로드
        count = loadFile(points, 100);
        printf("파일에서 %d개의 데이터를 로드했습니다.\n", count);
        break;
      case -1:
        freePoints(points, count);
        printf("프로그램을 종료합니다.\n");
        break;
        }
  }while(menu > 0);
  return 0;
}
