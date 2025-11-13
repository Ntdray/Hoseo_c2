#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy, strlen, menset

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 30 //문자열 길이 제한, 대신 string 사용가능

// 입력 버퍼를 비우는 헬퍼 함수
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 제품 분류 정보
typedef struct {
    int id;
    int stock_qty;
    int sales_qty;
    char name[MAX_NAME_LENGTH];
    int price;
} Product;

long long total_revenue = 0;

// ID로 상품 인덱스를 찾는 함수
int find_product_index(Product products[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            return i; // 찾았을 경우 인덱스 반환
        }
    }
    return -1; // 찾지 못했을 경우 -1 반환
}

// 재고 추가 함수
void Add_stock(Product products[], int *count) {
    int id, stock_qty, price;
    char temp_name[MAX_NAME_LENGTH];
    
    printf("\n--- 현재 등록된 상품 목록 (ID: 이름) ---\n");
    if (*count == 0) {
        printf("  (등록된 상품이 없습니다.)\n");
    } else {
        for (int i = 0; i < *count; i++) {
            printf("  ID: %d, 이름: %s\n", products[i].id, products[i].name);
        }
    }
    printf("--------------------------------------\n");
    
    // 상품 ID 입력
    printf("상품ID: (입력) ");
    if (scanf("%d", &id) != 1) {
        printf("잘못된 입력입니다. (숫자만 입력하세요) 입고를 취소합니다.\n");
        clear_input_buffer();
        return;
    }

    // 상품 ID로 기존 상품 여부 확인
    int index = find_product_index(products, *count, id);

    // ------------------- 1. 기존 상품 업데이트 -------------------
    if (index != -1) {
        printf("상품 ID %d는 기존 상품(%s)입니다. 재고만 추가합니다. (현재 재고: %d)\n", 
               id, products[index].name, products[index].stock_qty);

        // 입고량 입력
        printf("입고량: (입력) ");
        if (scanf("%d", &stock_qty) != 1) {
            printf("잘못된 입고량 입력. (숫자만 입력하세요) 재고 추가를 취소합니다.\n");
            clear_input_buffer();
            return;
        }

        if (stock_qty <= 0) {
            printf("입고수량은 0보다 커야 합니다. (입력: %d)\n", stock_qty);
            return;
        }
        
        // 재고 업데이트
        products[index].stock_qty += stock_qty;
        printf("상품 ID %d에 %d의 재고가 추가되었습니다. (총 재고: %d)\n", 
               id, stock_qty, products[index].stock_qty);

    } 
    // ------------------- 2. 신규 상품 등록 -------------------
    else {
        // 상품 갯수 초과 메시지 출력 확인
        if (*count >= MAX_PRODUCTS) {
            printf("상품수초과: 더 이상 새로운 상품을 추가할 수 없습니다. (최대 %d개)\n", MAX_PRODUCTS);
            return;
        }

        printf("상품 ID %d는 신규 상품입니다. 등록을 시작합니다.\n", id);

        // 1. 상품명 입력
        printf("상품명: (입력) 상품명 입력 ");
        if (scanf("%29s", temp_name) != 1) {  
            printf("상품명 입력 오류. 신규 상품 등록을 취소합니다.\n");
            clear_input_buffer();
            return;
        }
        
        // 2. 입고량 입력 (재고 초기값)
        printf("입고량: (입력) 입고수량 입력 ");
        if (scanf("%d", &stock_qty) != 1) {
            printf("잘못된 입고량 입력. (숫자만 입력하세요) 신규 상품 등록을 취소합니다.\n");
            clear_input_buffer();
            return;
        }

        if (stock_qty <= 0) {
            printf("입고수량은 0보다 커야 합니다. 신규 상품 등록을 취소합니다.\n");
            return;
        }

        // 3. 판매가격 입력
        printf("판매가격: (입력) 판매가격 입력 ");
        if (scanf("%d", &price) != 1) {
            printf("잘못된 판매가격 입력. (숫자만 입력하세요) 신규 상품 등록을 취소합니다.\n");
            clear_input_buffer();
            return;
        }

        if (price <= 0) {
            printf("판매가격은 0보다 커야 합니다. 신규 상품 등록을 취소합니다.\n");
            return;
        }
        
        // 배열의 마지막에 새 상품 정보 저장
        products[*count].id = id;
        strcpy(products[*count].name, temp_name); // 상품 이름 복사
        products[*count].stock_qty = stock_qty;
        products[*count].sales_qty = 0; // 신규 상품이므로 판매량은 0
        products[*count].price = price; // 판매 가격 저장
        
        (*count)++; // 전체 상품 개수 1 증가
        printf("신규 상품 ID %d ('%s')가 성공적으로 등록되었고, %d의 재고가 입고되었습니다.\n", 
               id, temp_name, stock_qty);
    }
}

// 판매 기록 함수
void Record_sale(Product products[], int count) {
    int choice;
    printf("판매(출력)판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2 를 선택\n");
    printf("> (입력) ");
    
    if (scanf("%d", &choice) != 1) {
        printf("잘못된 선택입니다. (1 또는 2를 입력하세요)\n");
        clear_input_buffer();
        return;
    }

    if (choice == 1) {
        int total_sale;
        printf("전체 판매수량을 입력해주세요 : ");
        
        if (scanf("%d", &total_sale) != 1) {
            printf("잘못된 판매수량입니다. (숫자만 입력하세요)\n");
            clear_input_buffer();
            return;
        }
        
        if (total_sale < 0) {
            printf("판매수량은 0보다 커야 합니다.\n");
            return;
        }
        
        long long current_revenue = 0; // 이 판매 기록에서 발생한 매출액
        int failed_count = 0;
        
        for (int i = 0; i < count; i++) {
            if (products[i].stock_qty >= total_sale) {
                products[i].stock_qty -= total_sale;
                products[i].sales_qty += total_sale;
                
                        //(재고/판매량 업데이트) 매출액 계산 및 누적
                current_revenue += (long long)total_sale * products[i].price;
            } else {printf("상품 ID %d의 재고가 부족하여 판매를 완료할 수 없습니다.\n", products[i].id);
            }
        }
        
        total_revenue += current_revenue;
        printf("모든 상품의 판매가 기록되었습니다.(총 %lld원)\n", current_revenue);
    } else if (choice == 2) {
        int id, sales_qty;
        printf("(입력)상품ID : ");
        
        if (scanf("%d", &id) != 1) {
            printf("잘못된 상품 ID입니다. (숫자만 입력하세요)\n");
            clear_input_buffer();
            return;
        }
        
        int index = find_product_index(products, count, id);
        if (index != -1) {
            printf("(입력)판매수량 : ");
            
            if (scanf("%d", &sales_qty) != 1) {
                printf("잘못된 판매수량입니다. (숫자만 입력하세요)\n");
                clear_input_buffer();
                return;
            }

            if (sales_qty < 0) {
                printf("판매수량은 0보다 커야 합니다.\n");
                return;
            }
            if (products[index].stock_qty >= sales_qty) {
                products[index].stock_qty -= sales_qty;
                products[index].sales_qty += sales_qty;
                long long revenue = (long long)sales_qty * products[index].price;
                total_revenue += revenue;
                printf("상품 ID %d에 %d의 판매가 기록되었습니다.\n", id, sales_qty);
            } else {
                printf("상품 ID %d의 재고(%d)가 부족하여 판매를 완료할 수 없습니다.\n", id, products[index].stock_qty);
            }
        } else {
            printf("존재하지 않는 상품 ID입니다.\n");
        }
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

// 상품 재고 및 판매 현황 표시 함수
//개별
void Individual_status(Product products[], int count) {
    if (count == 0) {
        printf("표시할 상품이 없습니다.\n");
        return;
    }
    // --- ID별 재고 현황 ---
    printf("\n--------------- ID별 재고 현황 -----------------\n");
    
    
    for (int i = 0; i < count; i++) {
        printf("%d\t%-15s\t%d원\t%d개\t%d개\n",
        products[i].id,
        products[i].name, 
        products[i].price,
        products[i].stock_qty,
        products[i].sales_qty);
        
    }
    printf("--------------------------------------------------\n");
}
//총합
void Overall_status(Product products[], int count) {
    if (count == 0) {
        printf("표시할 상품이 없습니다.\n");
        return;
    }

    int total_stock = 0;
    int total_sales = 0;
    
    int most_sold_index = 0; // 첫 번째 상품을 최다 판매 상품으로 가정하고 시작
    int least_sold_index = 0; // 첫 번째 상품을 최소 판매 상품으로 가정하고 시작
    
    for (int i = 0; i < count; i++) {
        total_stock += products[i].stock_qty;
        total_sales += products[i].sales_qty;
        
        if (products[i].sales_qty > products[most_sold_index].sales_qty) {
            most_sold_index = i;
        }
        
        if (products[i].sales_qty < products[least_sold_index].sales_qty) {
            least_sold_index = i;
        }
    }
    
    printf("\n--- 상품 현황 ---\n");
    printf("총 재고수량 : %d\n", total_stock);
    printf("총 판매량 : %d\n", total_sales);
    printf("총 매출액 : **%lld원**\n", total_revenue);
    
    if (total_sales > 0) {
        printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", 
               products[most_sold_index].id, products[most_sold_index].sales_qty);
        
        printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", 
               products[least_sold_index].id, products[least_sold_index].sales_qty);
    } else {
        printf("판매 기록이 없습니다.\n");
    }
    printf("----------------------\n");
}

int main() {
    Product products[MAX_PRODUCTS];
    int product_count = 0;
    int choice;

    // 인덱스 초기화
    products[0] = (Product){1, 0, 0, "", 0};   strcpy(products[0].name, "상품명 미등록"); //strcpy 문자열 복사
    products[1] = (Product){2, 0, 0, "", 0};   strcpy(products[1].name, "상품명 미등록");
    products[2] = (Product){3, 0, 0, "", 0};   strcpy(products[2].name, "상품명 미등록");
    products[3] = (Product){4, 0, 0, "", 0};   strcpy(products[3].name, "상품명 미등록");
    products[4] = (Product){5, 0, 0, "", 0};   strcpy(products[4].name, "상품명 미등록");
    product_count = 5;

    do {
        printf("\n원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n");
        printf("> ");
        
        if (scanf("%d", &choice) != 1) {
            printf("잘못된 선택입니다. (1~5 사이의 숫자만 입력하세요)\n");
            clear_input_buffer();
            choice = -1;
        }

        switch (choice) {
            case 1:
                Add_stock(products, &product_count);
                break;
            case 2:
                Record_sale(products, product_count);
                break;
            case 3:
                Individual_status(products, product_count);
                break;
            case 4:
                Overall_status(products, product_count);
                break;
            case 5:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 선택입니다. 다시 시도해주세요.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
        printf("잘못된 입력입니다. 입고를 취소합니다.\n");
        return;
    }

    // 상품 ID로 기존 상품 여부 확인
    int index = find_product_index(products, *count, id);

    // ------------------- 1. 기존 상품 업데이트 -------------------
    if (index != -1) {
        printf("상품 ID %d는 기존 상품(%s)입니다. 재고만 추가합니다. (현재 재고: %d)\n", 
               id, products[index].name, products[index].stock_qty);

        // 입고량 입력
        printf("입고량: (입력) ");
        if (scanf("%d", &stock_qty) != 1) {
            printf("잘못된 입고량 입력. 재고 추가를 취소합니다.\n");
            return;
        }

        if (stock_qty <= 0) {
            printf("입고수량은 0보다 커야 합니다. (입력: %d)\n", stock_qty);
            return;
        }
        
        // 재고 업데이트
        products[index].stock_qty += stock_qty;
        printf("상품 ID %d에 %d의 재고가 추가되었습니다. (총 재고: %d)\n", 
               id, stock_qty, products[index].stock_qty);

    } 
    // ------------------- 2. 신규 상품 등록 -------------------
    else {
        // 상품 갯수 초과 메시지 출력 확인
        if (*count >= MAX_PRODUCTS) {
            printf("상품수초과: 더 이상 새로운 상품을 추가할 수 없습니다. (최대 %d개)\n", MAX_PRODUCTS);
            return;
        }

        printf("상품 ID %d는 신규 상품입니다. 등록을 시작합니다.\n", id);

        // 1. 상품명 입력
        printf("상품명: (입력) 상품명 입력 ");
        // scanf("%s") 대신 안전한 문자열 입력을 위해 버퍼 비우기 및 형식 지정자 조정 필요
        if (scanf("%29s", temp_name) != 1) {  
            printf("상품명 입력 오류. 신규 상품 등록을 취소합니다.\n");
            return;
        }
        
        // 2. 입고량 입력 (재고 초기값)
        printf("입고량: (입력) 입고수량 입력 ");
        if (scanf("%d", &stock_qty) != 1) {
            printf("잘못된 입고량 입력. 신규 상품 등록을 취소합니다.\n");
            return;
        }

        if (stock_qty <= 0) {
            printf("입고수량은 0보다 커야 합니다. 신규 상품 등록을 취소합니다.\n");
            return;
        }

        // 3. 판매가격 입력
        printf("판매가격: (입력) 판매가격 입력 ");
        if (scanf("%d", &price) != 1) {
            printf("잘못된 판매가격 입력. 신규 상품 등록을 취소합니다.\n");
            return;
        }

        if (price <= 0) {
            printf("판매가격은 0보다 커야 합니다. 신규 상품 등록을 취소합니다.\n");
            return;
        }
        
        // 배열의 마지막에 새 상품 정보 저장
        products[*count].id = id;
        strcpy(products[*count].name, temp_name); // 상품 이름 복사
        products[*count].stock_qty = stock_qty;
        products[*count].sales_qty = 0; // 신규 상품이므로 판매량은 0
        products[*count].price = price; // 판매 가격 저장
        
        (*count)++; // 전체 상품 개수 1 증가
        printf("신규 상품 ID %d ('%s')가 성공적으로 등록되었고, %d의 재고가 입고되었습니다.\n", 
               id, temp_name, stock_qty);
    }
}

// 판매 기록 함수
void Record_sale(Product products[], int count) {
    int choice;
    printf("판매(출력)판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2 를 선택\n");
    printf("> (입력) ");
    scanf("%d", &choice);

    if (choice == 1) {
        int total_sale;
        printf("전체 판매수량을 입력해주세요 : ");
        scanf("%d", &total_sale);
        if (total_sale < 0) {
            printf("판매수량은 0보다 커야 합니다.\n");
            return;
        }
        
        long long current_revenue = 0; // 이 판매 기록에서 발생한 매출액
        int failed_count = 0;
        
        for (int i = 0; i < count; i++) {
            if (products[i].stock_qty >= total_sale) {
                products[i].stock_qty -= total_sale;
                products[i].sales_qty += total_sale;
                
                        //(재고/판매량 업데이트) 매출액 계산 및 누적
                current_revenue += (long long)total_sale * products[i].price;
            } else {printf("상품 ID %d의 재고가 부족하여 판매를 완료할 수 없습니다.\n", products[i].id);
            }
        }
        
        total_revenue += current_revenue;
        printf("모든 상품의 판매가 기록되었습니다.(총 %lld원)\n", current_revenue);
    } else if (choice == 2) {
        int id, sales_qty;
        printf("(입력)상품ID : ");
        scanf("%d", &id);
        int index = find_product_index(products, count, id);
        if (index != -1) {
            printf("(입력)판매수량 : ");
            scanf("%d", &sales_qty);
            if (sales_qty < 0) {
                printf("판매수량은 0보다 커야 합니다.\n");
                return;
            }
            if (products[index].stock_qty >= sales_qty) {
                products[index].stock_qty -= sales_qty;
                products[index].sales_qty += sales_qty;
                long long revenue = (long long)sales_qty * products[index].price;
                total_revenue += revenue;
                printf("상품 ID %d에 %d의 판매가 기록되었습니다.\n", id, sales_qty);
            } else {
                printf("상품 ID %d의 재고(%d)가 부족하여 판매를 완료할 수 없습니다.\n", id, products[index].stock_qty);
            }
        } else {
            printf("존재하지 않는 상품 ID입니다.\n");
        }
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

// 상품 재고 및 판매 현황 표시 함수
//개별
void Individual_status(Product products[], int count) {
    if (count == 0) {
        printf("표시할 상품이 없습니다.\n");
        return;
    }
    // --- ID별 재고 현황 ---
    printf("\n--------------- ID별 재고 현황 -----------------\n");
    
    
    for (int i = 0; i < count; i++) {
        printf("%d\t%-15s\t%d원\t%d개\t%d개\n",
        products[i].id,
        products[i].name, 
        products[i].price,
        products[i].stock_qty,
        products[i].sales_qty);
        
    }
    printf("--------------------------------------------------\n");
}
//총합
void Overall_status(Product products[], int count) {
    if (count == 0) {
        printf("표시할 상품이 없습니다.\n");
        return;
    }

    int total_stock = 0;
    int total_sales = 0;
    
    int most_sold_index = 0; // 첫 번째 상품을 최다 판매 상품으로 가정하고 시작
    int least_sold_index = 0; // 첫 번째 상품을 최소 판매 상품으로 가정하고 시작
    
    for (int i = 0; i < count; i++) {
        total_stock += products[i].stock_qty;
        total_sales += products[i].sales_qty;
        
        if (products[i].sales_qty > products[most_sold_index].sales_qty) {
            most_sold_index = i;
        }
        
        if (products[i].sales_qty < products[least_sold_index].sales_qty) {
            least_sold_index = i;
        }
    }
    
    printf("\n--- 상품 현황 ---\n");
    printf("총 재고수량 : %d\n", total_stock);
    printf("총 판매량 : %d\n", total_sales);
    printf("총 매출액 : **%lld원**\n", total_revenue);
    
    if (total_sales > 0) {
        printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", 
               products[most_sold_index].id, products[most_sold_index].sales_qty);
        
        printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", 
               products[least_sold_index].id, products[least_sold_index].sales_qty);
    } else {
        printf("판매 기록이 없습니다.\n");
    }
    printf("----------------------\n");
}

int main() {
    Product products[MAX_PRODUCTS];
    int product_count = 0;
    int choice;

    // 인덱스 초기화
    products[0] = (Product){1, 0, 0, "", 0};   strcpy(products[0].name, "상품명 미등록"); //strcpy 문자열 복사
    products[1] = (Product){2, 0, 0, "", 0};   strcpy(products[1].name, "상품명 미등록");
    products[2] = (Product){3, 0, 0, "", 0};   strcpy(products[2].name, "상품명 미등록");
    products[3] = (Product){4, 0, 0, "", 0};   strcpy(products[3].name, "상품명 미등록");
    products[4] = (Product){5, 0, 0, "", 0};   strcpy(products[4].name, "상품명 미등록");
    product_count = 5;

    do {
        printf("\n원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Add_stock(products, &product_count);
                break;
            case 2:
                Record_sale(products, product_count);
                break;
            case 3:
                Individual_status(products, product_count);
                break;
            case 4:
                Overall_status(products, product_count);
                break;
            case 5:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 선택입니다. 다시 시도해주세요.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}


