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
#define Action_provoke 1
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
	printf("\n\n\n");
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
//좀비 움직이기 함수(+방향) : 좀비위치, 확률, 시민어그로, 마동석어그로
int zMove(int, int,int,int);
int zMove(int percent, int Z, int aggroC, int aggroM) {
	int Rd2 = rand() % 100;
	if (Rd2 < percent) {
		if (aggroC >= aggroM)
			return Z -= 1;
		else
			return Z += 1;
	}
	else
		return Z;
}
//시민 이동 현황 출력 함수 : 시민의 현재위치, 시민의 이전위치, 어그로 값
void cSpot(int, int, int, int);
void cSpot(int C, int befoC ,int befo_aggroC,int aggroC) {
	if (befoC != C) {
		if (befo_aggroC == Aggro_max && aggroC == Aggro_max)
			printf("citizen: %d -> %d (aggro : %d)\n", befoC, C,aggroC);
		else
			printf("citizen: %d -> %d (aggro : %d -> %d)\n", befoC, C, befo_aggroC, aggroC);
	}
	else {
		if (befo_aggroC == Aggro_min && aggroC == Aggro_min)
			printf("citizen: stay %d (aggro : %d)\n", befoC, aggroC);
		else
			printf("citizen: stay %d (aggro : %d -> %d)\n", befoC, befo_aggroC, aggroC);
	}
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
//마동석 어그로 
int mAggro(int, int, int);
int mAggro(int M, int befoM, int aggroM) {
	if (befoM != M) {
		if (aggroM < Aggro_max)
			aggroM += 1;
	}
	else {
		if (aggroM > Aggro_min)
			aggroM -= 1;
	}
	return aggroM;
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
				if (x == Move_left) {
					M -= 1;
					return M;
				}
				else
					return M;
			}
		}	
	}
}
//마동석 이동 형환 출력 함수 : 마동석 현재위치, 마동석 이전위치, 어그로 값, 마동석 체력
void mSpot(int, int, int, int, int);
void mSpot(int M, int befoM, int aggroM, int befo_aggroM, int ma_stamina){
	if (befoM != M) {
		if(befo_aggroM == Aggro_max&& aggroM == Aggro_max)
			printf("madongseok: %d -> %d (aggro : %d, stamina: %d)\n", befoM, M, aggroM, ma_stamina);
		else
			printf("madongseok: %d -> %d (aggro : %d -> %d, stamina: %d)\n", befoM, M, befo_aggroM, aggroM, ma_stamina);
	}
	else {
		if (befo_aggroM == Aggro_min && aggroM == Aggro_min)
			printf("madongseok: stay %d (aggro : %d, stamina: %d)\n", befoM, aggroM,ma_stamina);
		else
			printf("madongseok: stay %d (aggro : %d -> %d, stamina: %d)\n", befoM, befo_aggroM, aggroM,ma_stamina);
	}
	printf("\n");
}
//시민 현재상황
void cCondition(void);
void cCondition(void) {
	printf("citizen does nothing.\n");
}
//좀비 행동상황 : 시민위치, 마동석위치, 좀비위치, 시민어그로, 마동석어그로
int zAction(int, int, int, int, int);
int zAction(int C, int M, int Z, int aggroC, int aggroM) {
	int x;
	if (Z == (C + 1) && Z == (M - 1)) {
		if (aggroC > aggroM)
			x = Atk_citizen;
		else
			x = Atk_dongseok;
	}
	else if (Z == (C + 1))
		x = Atk_citizen;
	else if (Z == (M - 1))
		x = Atk_dongseok;
	else
		x = Atk_none;
	return x;
}
//좀비가 공격하지 않는 상황
void noAttack(void);
void noAttack(void) {
	printf("zombie attcked nobody.\n");
}
//좀비가 시민을 공격하는 상황
int cAttack(int, int, int, int, int);
int cAttack(int C, int M, int Z, int aggroC, int aggroM) {
	if (Z == (C + 1) && Z == (M - 1))
		printf("Zombie attacked citizen (aggro: %d vs. %d, citizen dead)\n", aggroC, aggroM);
	else
		printf("Zombie attacked citizen \n");
	return 1;
}
//좀비가 마동석을 공격하는 상황
int mAttack(int, int, int,int,int,int,int);
int mAttack(int C, int M, int Z, int aggroC, int aggroM, int ma_stamina, int befo_ma_stamina) {
	ma_stamina -=1;
	if (Z == (C + 1) && Z == (M - 1))
		printf("Zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", aggroC, aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("Zombie attacked madongseok (madongseok stamina: %d -> %d)\n", befo_ma_stamina, ma_stamina);
	return ma_stamina;
}
//마동석 행동 : 좀비위치, 마동석위치
int mAction(int, int);
int mAction(int Z, int M) {
	int x;
	if (Z == (M - 1)) {
		printf("madongseok action(%d.rest, %d.provoke, %d.pull)>> ", Action_rest, Action_provoke, Action_pull);
		scanf_s("%d", &x);
		printf("\n");
		if (x == Action_rest)
			return Action_rest;
		else if (x == Action_pull)
			return Action_pull;
		else
			return Action_provoke;
	}
	else {
		printf("madongseok action(%d.rest, %d.provoke)>> ", Action_rest, Action_provoke);
		scanf_s("%d", &x);
		printf("\n");
		if (x == Action_rest)
			return Action_rest;
		else
			return Action_provoke;
	}
}
//마동석이 쉬는 상황 : 마동석 위치, 마동석 어그로, 마동석 체력
void mRest(int, int, int,int,int);
void mRest(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok rests...\n");
	if(befo_aggroM==Aggro_min)
		printf("madongseok: %d (aggro : %d, stamina : %d -> %d)\n", M, aggroM, ma_stamina, befo_ma_stamina);
	else if(befo_ma_stamina==Stm_max)
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d)\n", M, befo_aggroM, aggroM, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, ma_stamina, befo_ma_stamina);
}

int main() {
	srand((unsigned int)time(NULL));		//난수 배열을 초기화 하기 위함

	//1. 인트로
	intro();

	// 2. 부산헹 초기 설정
	int tr_length;
	tr_length = trTrue();

	int ma_stamina;
	ma_stamina = maTrue();

	int percent;
	percent = perTrue();

	// 3. 확률에 따른 시민과 좀비 이동

	int C, Z, M;	//시민, 좀비, 마동석 변수 지정 후 열차 길이에 따른 초기 위치 설정
	C = tr_length - 6;
	Z = tr_length - 3;
	M = tr_length - 2;

	printf("\n\n");

	trMake(tr_length, C, Z, M);

	int befoC, befoZ, befoM, befo_ma_stamina, turnZ;	//시민, 좀비, 마동석의 움직이기 직전 값 및 좀비의 턴 횟수를 저장하기 위한 변수 설정
	befoC = C;
	befoZ = Z;
	befoM = M;
	befo_ma_stamina = ma_stamina;
	turnZ = 1;

	int aggroC, befo_aggroC, aggroM, befo_aggroM;
	aggroC = 0;
	befo_aggroC = 0;
	aggroM = 0;
	befo_aggroM = 0;

	int actionZ, actionM;

	int Cdead = 0;

	while (C != 1 && Z != C + 1) { //무한반복 코드
		printf("\n\n");

		C = cMove(percent, C);

		aggroC = cAggro(C, befoC, aggroC);

		if ((turnZ % 2) != 0) {
			// 시민, 마동석과 인접해있을 때는 움직이지 X
			if(Z!=(C+1)||Z!=(M-1))
				Z = zMove(percent, Z, aggroC, aggroM);
		}


		trMake(tr_length, C, Z, M);

		cSpot(C, befoC,befo_aggroC,aggroC);

		zSpot(Z, befoZ, turnZ);

		printf("\n");

		M = mMove(Z, M);

		aggroM = mAggro(M, befoM, aggroM);

		trMake(tr_length, C, Z, M);

		mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

		cCondition();

		actionZ = zAction(C, M, Z, aggroC, aggroM);

		switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: Cdead = cAttack(C, M, Z, aggroC, aggroM); break;
			case Atk_dongseok: ma_stamina = mAttack(C, M, Z, aggroC, aggroM,ma_stamina, befo_ma_stamina); break;
		}

		actionM = mAction(Z, M);

		if (actionM == Action_rest) { //마동석 행동 rest 구현
			mRest(M, befo_aggroM, aggroM, ma_stamina, befo_ma_stamina);
			aggroM = befo_aggroM;
			ma_stamina = befo_ma_stamina;
		}
	

		befoC = C;		//바뀐 값으로 초기화
		befoZ = Z;
		befoM = M;
		befo_aggroC = aggroC;
		befo_aggroM = aggroM;
		befo_ma_stamina = ma_stamina;
		turnZ += 1;		//좀비턴 횟수 증가
	}
	// 4. 아웃트로
	outro(C);
}		//끝