#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //열차 길이
#define Len_max 50		
#define Prob_min 10		//확률 
#define Prob_max 90		
#define Stm_min 0		//마동석 체력
#define Stm_max 5
#define Move_stay 0		//마동석 이동 방향
#define Move_left 1
#define Action_rest 0	//마동석 행동
#define Action_proboke 1
#define Action_pull 2
#define Aggro_min 0		//어그로 범위
#define Aggro_max 5
#define Atk_none 0		//좀비의 공격 대상
#define Atk_citizen 1	
#define Atk_dongseok 2

//인트로
void intro(void);
void intro(void) {
	printf(" ______                   _      _         _____               _        \n");
	Sleep(200);
	printf("|___  /                  | |    (_)       |_   _|             (_)       \n");
	Sleep(300);
	printf("   / /   ___   _ __ ___  | |__   _   ___    | |   _ __   __ _  _  _ ___ \n");
	Sleep(200);
	printf("  / /   / _ | | '_ ` _ | | '_ | | | / _ |   | |  | '__| / _` || || '_  |\n");
	Sleep(300);
	printf(" / /___| (_) || | | | | || |_) || ||  __/   | |  | |   | (_| || || | | |\n");
	Sleep(200);
	printf("|_____/ |___/ |_| |_| |_||_.__/ |_| |___|   |_/  |_|    |__,_||_||_| |_|\n\n");
	Sleep(300);

	printf("			      TITLE : 부산헹\n\n");
	printf("			     게임을 시작합니다.\n\n");
}
//아웃트로
void outro(int);
void outro(int C) {
	if (C == 1) {
		printf("     탈출성공!!\n");
		printf("  ___        _  _   \n");
		printf(" / __|      (_)| |  \n");
		printf("| |__  _, __ _ | |_ \n");
		printf("|  __|| |/ /| || __|\n");
		printf("| |__  >  < | || |_ \n");
		printf("|____|/_/|_||_||___|\n");
	}
	else {
		printf("                탈출실패..\n");
		printf(",_   __                _____  _       \n");
		printf("| | / /               |  _  |(_)      \n");
		printf(" L V /   ___   _   _  | | | | _   ___ \n");
		printf("  | /   / _ | | | | | | | | || | / _ |\n");
		printf("  | |  | (_) || |_| | | |/ / | ||  __/\n");
		printf("  |_/   |___/  |__,_| |___/  |_| |___|\n");
	}
}
//열차 길이 입력받는 함수
int trTrue(void);
int trTrue(void) {
	int x;
	while (1) {
		printf("train length(%d~%d)>>: ", Len_min,Len_max);
		scanf_s("%d", &x);
		if (x >= Len_min && x <= Len_max)
			return x;
		else
			continue;
	}
}
//확률 입력받는 함수
int perTrue(void);
int perTrue(void){
	int x;
	while (1) {
		printf("percentile probability 'p'(%d~%d)>>: ", Prob_min,Prob_max);
		scanf_s("%d", &x);
		if (x >= Prob_min && x <= Prob_max)
			return x;
		else
			continue;
	}
}
//마동석 체력 입력받는 함수
int maTrue(void);
int maTrue(void){
	int x;
	while (1) {
		printf("madongseok stamina(%d~%d)>>: ", Stm_min,Stm_max);
		scanf_s("%d", &x);
		if (x >= Stm_min && x <=Stm_max)
			return x;
		else
			continue;
	}
}
//열차 만드는 함수 : 기차길이, 시민위치, 마동석 위치, 좀비 위치
void trMake(int, int, int, int);
void trMake(int tr_length, int C, int Z, int M) {
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		if (i == 0 || i == tr_length - 1)
			printf("#");
		else if (i == C)
			printf("C");
		else if (i == M)
			printf("M");
		else if (i == Z)
			printf("Z");
		else
			printf(" ");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n");
}
//시민 움직이기 함수 : 시민위치, 확률
int cMove(int, int);
int cMove(int percent, int C) {
	int Rd = rand() % 100;
	if (Rd < (100 - percent))
		return C -= 1;
	else
		return C;
}
//좀비 움직이기 함수 : 좀비위치, 확률
int zMove(int, int);
int zMove(int percent, int Z) {
	int Rd2 = rand() % 100;
	if (Rd2 < percent)
		return Z -= 1;
	else
		return Z;
}
//시민 이동 현황 출력 함수 : 시민의 현재위치, 시민의 이전위치
void cSpot(int, int, int, int);
void cSpot(int C, int befoC ,int befo_aggroC,int aggroC) {
	if (befoC != C) {
		printf("citizen: %d -> %d (aggro : %d -> %d)\n", befoC, C,befo_aggroC,aggroC);
	}
	else
		printf("citizen: stay %d (aggro : %d -> %d)\n", befoC,befo_aggroC,aggroC);
}
//좀비 이동 현황 출력 함수 : 좀비의 현재위치, 좀비의 이전위치, 좀비의 턴 수
void zSpot(int, int, int);
void zSpot(int Z, int befoZ, int turnZ) {
	if (turnZ % 2 == 0) {
		printf("zombie: stay %d (cannot move)\n", befoZ);
	}
	else if (befoZ != Z) {
		printf("zombie: %d -> %d\n", befoZ, Z);
	}
	else {
		printf("zombie: stay %d\n", befoZ);
	}
}
//시민 어그로 
int cAggro(int, int,int);
int cAggro(int C, int befoC, int aggroC) {
	if (befoC != C) {
		if (aggroC < Aggro_max)
			aggroC += 1;
	}
	else {
		if (aggroC > Aggro_min)
			aggroC -= 1;
	}
	return aggroC; 
}
//마동석 움직이기 함수
int mMove(int, int);
int mMove(int Z, int M) {
	int x;
	while (1) {
		if (M == (Z + 1)){
			printf("madongseok move (%d:stay)>>: ", Move_stay);
			scanf_s("%d", &x);
			if (x == Move_stay)
				return M;
		}	
		else {
			printf("madongseok move (%d:stay, %d:left)>>: ", Move_stay, Move_left);
			scanf_s("%d", &x);
			if (x == Move_stay || x == Move_left) {
				if (x == Move_left)
					return M;
				else
					M -= 1;
					return M;
			}
		}	
	}
}

int main() {
	srand((unsigned int)time(NULL));		//난수 배열을 초기화 하기 위함

	//1. 인트로
	intro();

	// 2. 부산헹 초기 설정
	int tr_length;
	tr_length = trTrue(Len_min, Len_max);

	int ma_stamina;
	ma_stamina = maTrue(Stm_min, Stm_max);

	int percent;	//확률 변수 지정 및 입력
	percent = perTrue(Prob_min, Prob_max);

	// 3. 확률에 따른 시민과 좀비 이동

	int C, Z, M;	//시민, 좀비, 마동석 변수 지정 후 열차 길이에 따른 초기 위치 설정
	C = tr_length - 6;
	Z = tr_length - 3;
	M = tr_length - 2;

	trMake(tr_length, C, Z, M);	//부산헹 초기 열차 설정 끝

	int befoC, befoZ, turnZ;	//시민, 좀비의 움직이기 직전 값 및 좀비의 턴 횟수를 저장하기 위한 변수 설정
	befoC = C;
	befoZ = Z;
	turnZ = 1;

	int aggroC, befo_aggroC;
	aggroC = 0;
	befo_aggroC = 0;

	while (C != 1 && Z != C + 1) { //무한반복 코드
		C = cMove(percent, C);

		aggroC = cAggro(C, befoC, aggroC);

		if ((turnZ % 2) != 0)
			Z = zMove(percent, Z);

		trMake(tr_length, C, Z, M);

		cSpot(C, befoC,befo_aggroC,aggroC);

		zSpot(Z, befoZ, turnZ);

		M = mMove(Z, M);

		trMake(tr_length, C, Z, M);

		befoC = C;		//바뀐 값으로 초기화
		befoZ = Z;
		befo_aggroC = aggroC;

		turnZ += 1;		//좀비턴 횟수 증가
		printf("\n");
	}
	// 4. 아웃트로
	outro(C);
}		//끝