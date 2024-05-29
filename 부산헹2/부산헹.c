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

int citizens[Len_max] = { 0 };  //int 형 50개를 저장할 수 있음
int befo_citizens[Len_max] = { 0 };
int citizensAggro[Len_max] = { 0 };
int befo_citizensAggro[Len_max] = { 0 }; 
int max_citizensAggro[1] = { 0 }; //어그로 중 가장 큰 값
int citizensNumber[Len_max] = { 0 };
int zombies[Len_max] = { 0 }; // 좀비 저장
int befo_zombies[Len_max] = { 0 }; 

//시민 탈출시 순서 땡기는 함수
void Re_citizensNums(int);
void Re_citizensNums(int citizensNum) {
	for (int i = 0; i < citizensNum; i++) {
		citizensNumber[i] = citizensNumber[i + 1];
	}
}
//인트로
void intro(void);
void intro(void) {
	printf(" ______                   _      _         _____               _        \n");
	printf("|___  /                  | |    (_)       |_   _|             (_)       \n");
	printf("   / /   ___   _ __ ___  | |__   _   ___    | |   _ __   __ _  _  _ ___ \n");
	printf("  / /   / _ | | '_ ` _ | | '_ | | | / _ |   | |  | '__| / _` || || '_  |\n");
	printf(" / /___| (_) || | | | | || |_) || ||  __/   | |  | |   | (_| || || | | |\n");
	printf("|_____/ |___/ |_| |_| |_||_.__/ |_| |___|   |_/  |_|    |__,_||_||_| |_|\n\n");

	printf("			      TITLE : 부산헹\n\n");
	printf("			     게임을 시작합니다.\n\n");
}
//아웃트로
void outro(int, int, int, int);
void outro(int stage, int ma_stamina, int saveDieCitizens, int save_citizens) {
	if (stage==3 && ma_stamina !=0 && saveDieCitizens != save_citizens) {
		printf("\n\n");
		printf("     탈출성공!!\n");
		printf("  ___        _  _   \n");
		printf(" / __|      (_)| |  \n");
		printf("| |__  _, __ _ | |_ \n");
		printf("|  __|| |/ /| || __|\n");
		printf("| |__  >  < | || |_ \n");
		printf("|____|/_/|_||_||___|\n\n\n");
	}
	else {
		printf("\n\n");
		printf("                탈출실패..\n");
		printf(",_   __                _____  _       \n");
		printf("| | / /               |  _  |(_)      \n");
		printf(" L V /   ___   _   _  | | | | _   ___ \n");
		printf("  | /   / _ | | | | | | | | || | / _ |\n");
		printf("  | |  | (_) || |_| | | |/ / | ||  __/\n");
		printf("  |_/   |___/  |__,_| |___/  |_| |___|\n\n\n");
	}
}
//다음 스테이지 넘어갈때 출력
void nextStage(void);
void nextStage(void) {
	printf("\n\nnext stage\n");
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
//스테이지 1 열차 만드는 함수 : 기차길이, 시민위치, 마동석 위치, 좀비 위치
void trMakeFirst(int, int, int, int);
void trMakeFirst(int tr_length, int C, int Z, int M) {
	printf("\n\n");
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
//스테이지 2 열차 만드는 함수 : 기차길이, 시민위치, 마동석 위치, 좀비 위치, 빌런위치
void trMakeSecond(int, int, int, int,int);
void trMakeSecond(int tr_length, int C, int Z, int M, int V) {
	printf("\n\n");
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
		else if (i == V)
			printf("V");
		else
			printf(" ");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n\n\n");
}
//스테이지 3 열차 만드는 함수
void trMakeThird(int, int, int);
void trMakeThird(int tr_length, int Z, int M) {
	int c = 0;
	printf("\n\n");
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		if (i == 0 || i == tr_length - 1)
			printf("#");
		else if (i == M)
			printf("M");
		else if (i == Z)
			printf("Z");
		else if (i == citizens[c]) {
			printf("C");
			c++;
		}
		else
			printf(" ");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n\n\n");
}
//스테이지 4 열차 만드는 함수
void trMakeFourth(int, int, int);
void trMakeFourth(int tr_length, int M, int countZ) {
	int c = 0;
	printf("\n\n");
	for (int i = 0; i < tr_length; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < tr_length; i++) {
		if (i == 0 || i == tr_length - 1)
			printf("#");
		else if (i == M)
			printf("M");
		else if (i == zombies[countZ-1]) {
			printf("Z");
			countZ--;
		}
		else if (i == citizens[c]) {
			printf("C");
			c++;
		}
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
int zMove(int, int,int,int, int, int);
int zMove(int percent, int Z, int aggroC, int aggroM, int C, int M) {
	int Rd2 = rand() % 100;
	if (Rd2 < percent) {
		if (aggroC >= aggroM) {
			if (Z != (C + 1))
				return Z -= 1;
			else
				return Z;
		}
		else if (Z != (M - 1))
			return Z += 1;
		else
			return Z;
	}
	else
		return Z;
}
//빌런 움직이기 함수
int vMove(int, int,int);
int vMove(int C, int befoC, int V) {
	if (C == befoC)
		return V;
	else
		return V - 1;
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
//빌런 이동 현환 출력 함수
void vSpot(int, int, int);
void vSpot(int V, int befoV,int aggroV) {
	if (befoV != V) {
		printf("villain: %d -> %d (aggro : %d)\n", befoV, V, aggroV);
	}
	else {
		printf("villain: stay %d (aggro : %d)\n",V, aggroV);
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
	printf("\n");
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
//빌런 어그로
int vAggro(int, int, int);
int vAggro(int V, int befoV, int aggroV) {
	if (V != befoV) {
		if (aggroV != Aggro_max)
			return aggroV += 1;
		else
			return aggroV = Aggro_max;
	}
	else {
		if (aggroV != Aggro_min)
			return aggroV -= 1;
		else
			return aggroV = Aggro_min;
	}
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
				else if(x==Move_stay)
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
//빌런 발암행동
int vAction(void);
int vAction(void){
	int x = rand() % 100;
	if (x < 30) {
		printf("- Change trying succes -\n");
		return 1;
	}
	else {
		printf("- Change trying fail -\n");
		return 0;
	}
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
//마동석 행동 상황 : 좀비위치, 마동석위치
int mAction(int, int);
int mAction(int Z, int M) {
	int x;
	while (1) {
		if (Z == (M - 1)) {
			printf("madongseok action(%d.rest, %d.provoke, %d.pull)>> ", Action_rest, Action_provoke, Action_pull);
			scanf_s("%d", &x);
			printf("\n");
			if (x == Action_rest)
				return Action_rest;
			else if (x == Action_pull)
				return Action_pull;
			else if(x == Action_provoke)
				return Action_provoke;
		}
		else {
			printf("madongseok action(%d.rest, %d.provoke)>> ", Action_rest, Action_provoke);
			scanf_s("%d", &x);
			printf("\n");
			if (x == Action_rest)
				return Action_rest;
			else if(x== Action_provoke)
				return Action_provoke;
		}
	}
}
//마동석 체력 1 증가 함수
int addStm(int);
int addStm(int ma_stamina) {
	if (ma_stamina != Stm_max)
		return ma_stamina += 1;
	else
		return ma_stamina =Stm_max;
}
//마동석 체력 1 감소 함수
int minusStm(int);
int minusStm(int ma_stamina) {
	if (ma_stamina != Stm_min)
		return ma_stamina -= 1;
	else
		return ma_stamina = Stm_min;
}
//마동석 어그로 1 감소 함수
int minus_one_AggroM(int);
int minus_one_AggroM(int aggroM) {
	if (aggroM != Aggro_min)
		return aggroM -= 1;
	else
		return aggroM = Aggro_min;
}
//마동석 어그로 2 증가 함수
int add_two_AggroM(int);
int add_two_AggroM(int aggroM) {
	if ((aggroM+2)<=Aggro_max)
		return aggroM += 2;
	else
		return aggroM = Aggro_max;
}
//마동석 rest 상황 : 마동석 위치, 마동석 어그로, 마동석 체력
void mRest(int, int, int,int,int);
void mRest(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok rests...\n");
	if(befo_aggroM==aggroM && befo_ma_stamina == ma_stamina)
		printf("madongseok: %d (aggro : %d, stamina : %d)\n", M, aggroM, ma_stamina);
	else if (befo_aggroM == aggroM)
		printf("madongseok: %d (aggro : %d, stamina : %d -> %d)\n", M, aggroM, befo_ma_stamina, ma_stamina);
	else if(befo_ma_stamina == ma_stamina)
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d)\n", M, befo_aggroM, aggroM, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, befo_ma_stamina, ma_stamina);
}
//마동석 provoke 상황 : 마동석 위치, 마동석 어그로. 마동석 체력
void mProvoke(int,int,int,int,int);
void mProvoke(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok provoked zombie...\n");
	if(befo_aggroM==Aggro_max)
		printf("madongseok: %d (aggro : %d, stamina : %d)\n", M, aggroM, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d)\n", M, befo_aggroM, aggroM, ma_stamina);
}
//마동석 pull 확률 : 퍼센트 
int mPull(int);
int mPull(int percent) {
	int x = rand() % 100;
	if (x < (100 - percent))
		return 1;
	else
		return 0;
}
//마동석이 붙들기 성공한 상황: 
void success_mPull(int, int, int, int, int);
void success_mPull(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok pulled zombie... Next turn, it can't move\n");
	if (befo_aggroM == aggroM)
		printf("madongseok: %d (aggro : %d, stamina : %d -> %d)\n", M, aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, befo_ma_stamina,ma_stamina);
}
//마동석이 붙들기 실패한 상황: 
void fail_mPull(int, int, int, int, int);
void fail_mPull(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok failed to pull zombie\n");
	if (befo_aggroM == aggroM)
		printf("madongseok: %d (aggro : %d, stamina : %d -> %d)\n", M, aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, befo_ma_stamina, ma_stamina);
}
//스테이지 1
void stageFirst(void);
void stageFirst(void) {
	printf("\n\n- 스테이지1 -\n\n");
}
//스테이지 2
void stageSecond(void);
void stageSecond(void) {
	printf("\n\n스테이지2 : 빌런\n\n");
}
//스테이지 3
void stageThird(void);
void stageThird(void) {
	printf("\n\n스테이지3 : 시민들\n\n");
}
//스테이지 4
void stageFourth(void);
void stageFourth(void) {
	printf("\n\n스테이지4 : 변이\n\n");
}
//스테이지 출력 함수
void printStage(int);
void printStage(int stage) {
	switch (stage) {
		case 0: stageFirst(); break;
		case 1: stageSecond(); break;
		case 2: stageThird(); break;
		case 3: stageFourth(); break;
	}
}
//기차길이에 따른 시민들 수
int citizensNumMake(int, int);
int citizensNumMake(int citizens_num_min, int citizens_num_max) {
	int citizensNum = rand() % (citizens_num_max - citizens_num_min ) + citizens_num_min;
	return citizensNum;
}
//기차길이에 따른 시민들 위치
void citizensSpotMake(int, int);
void citizensSpotMake(int C, int citizensNum) {
	for (int i = 0; i < citizensNum; i++) {
		citizens[i] = rand() % (C - 2) + 2;
		for (int j = 0; j < i; j++) {
			if (citizens[j] == citizens[i]) {
				citizens[i] = rand() % (C - 2) + 2;
				j = -1;
			}
		}
	}
}
//시민들 위치 정렬
void spotSort(int citizensNum);
void spotSort(int citizensNum) {
	for (int i = 0; i < citizensNum-1; i++) {
		for (int j = 0; j < citizensNum - 1 - i; j++) {
			if (citizens[j] > citizens[j + 1]) {
				int save = citizens[j];
				citizens[j] = citizens[j + 1];
				citizens[j + 1] = save;
			}
		}
	}
}
//시민들이 움직이는 상황
void citizensMove(int, int);
void citizensMove(int percent, int citizensNum) {
	int Rd;
	for (int i = 0; i < citizensNum; i++) {
		if (i == 0) {
			Rd = rand() % 100;
			if (Rd < (100 - percent)) {
				citizens[i] -= 1;
			}
		}
		if (citizens[i+1] != 0) {
			Rd = rand() % 100;
			if (Rd < (100 - percent)) {
				citizens[i+1] -= 1;
				if (citizens[i+1] == citizens[i])
					citizens[i+1] += 1;
			}
		}
	}
}
//시민들 상황
void citizensCondition(int);
void citizensCondition(int citizensNum) {
	int count = 0;
	for (int i = 0; i < citizensNum; i++) {
		if (citizens[i] != 0)
			count++;
	}
	printf("%d citizen(s) alive(s).\n", count);
}
//시민들 현재위치
void citizensSpot(int);
void citizensSpot(int citizenNum) {
	for (int i = 0; i < citizenNum; i++) {
		if (citizens[i] == befo_citizens[i]) {
			if(citizensAggro[i] == befo_citizensAggro[i])
				printf("citizen%d : stay %d ( aggro : %d )\n", citizensNumber[i], citizens[i], citizensAggro[i]);
			else
				printf("citizen%d : stay %d ( aggro : %d -> %d )\n", citizensNumber[i], citizens[i], befo_citizensAggro[i], citizensAggro[i]);
		}
		else {
			if (citizensAggro[i] == befo_citizensAggro[i])
				printf("citizen%d : %d -> %d ( aggro : %d )\n", citizensNumber[i], befo_citizens[i], citizens[i], citizensAggro[i]);
			else
				printf("citizen%d : %d -> %d ( aggro : %d -> %d)\n", citizensNumber[i], befo_citizens[i], citizens[i], befo_citizensAggro[i], citizensAggro[i]);
		}
	}
}
//시민들 이전값 저장하기
void befo_citizensMake(int);
void befo_citizensMake(int citizensNum) {
	for (int i = 0; i < citizensNum; i++) {
		befo_citizens[i] = citizens[i];
	}
}
//시민들 어그로 이전값 저장하기
void befo_citizensAggroMake(int);
void befo_citizensAggroMake(int citizensNum) {
	for (int i = 0; i < citizensNum; i++) {
		befo_citizensAggro[i] = citizensAggro[i];
	}
}
//탈출한 시민
int exit_citizens(int);
int exit_citizens(int citizensNum) {
	int count = 0;
	if (citizens[0] == 1) {
		count++;
		for (int i = 0; i < citizensNum; i++) {
			citizens[i] = citizens[i+1];
		}
		Re_citizensNums(citizensNum);
	}
	if(count !=0)
		printf("%d citizen exits  / ", count);
	citizensNum -= count;
	return citizensNum;
}
//좀비 공격에 의해 죽은 시민
int die_citizens(int);
int die_citizens(int citizensNum) {
	int count = 0;
	if (citizens[citizensNum - 1] == 0)
		count++;
	return count;
}
//시민들 어그로
void Aggro_citizens(int);
void Aggro_citizens(int citizensNum){
	for (int i = 0; i < citizensNum; i++) {
		if (befo_citizens[i] != citizens[i]) {
			if (citizensAggro[i] != Aggro_max)
				citizensAggro[i] += 1;
			else
				citizensAggro[i] = Aggro_max;
		}
		else {
			if (citizensAggro[i] != Aggro_min)
				citizensAggro[i] -= 1;
			else
				citizensAggro[i] = Aggro_min;
		}
	}
}
//좀비 시민들 공격 상황
void citizensAttack(int, int, int, int);
void citizensAttack(int Z, int M, int citizensNum, int aggroM) {
	if (Z == (citizens[citizensNum-1] + 1) && Z == (M - 1))
		printf("citizen%d has been attacked by zombie. ( aggro : %d vs. %d )\n", citizensNumber[citizensNum-1], citizensAggro[citizensNum - 1], aggroM);
	else
		printf("citizen%d has been attacked by zombie.\n", citizensNumber[citizensNum-1]);
	citizens[citizensNum - 1] = 0;
}
//빌런 공격당한 상황
void vAttack(void);
void vAttack(void) {
	printf("villain has been attacked by zombie.\n");
}
//스테이지2 좀비 행동상황 : 시민위치, 마동석위치, 좀비위치, 시민어그로, 마동석어그로
int zAction2(int, int, int, int, int, int);
int zAction2(int C, int M, int Z, int aggroC, int aggroM, int V) {
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
	else if (Z == (V + 1))
		x = V;
	else
		x = Atk_none;
	return x;
}
//스테이지3 좀비 행동상황 :마동석위치, 좀비위치, 마동석 어그로
int zAction3(int, int, int, int);
int zAction3(int M, int Z, int aggroM, int citizensNum) {
	int x;
	if (Z == citizens[citizensNum-1]+1 && Z == (M - 1)) {
		if (citizensAggro[citizensNum-1]+1 > aggroM)
			x = Atk_citizen;
		else
			x = Atk_dongseok;
	}
	else if (Z == citizens[citizensNum - 1]+1)
		x = Atk_citizen;
	else if (Z == (M - 1))
		x = Atk_dongseok;
	else
		x = Atk_none;
	return x;
}
//시민들 어그로 중 최대값
void citizensAggroMax(void);
void citizensAggroMax(void) {
	for (int i = 0; i < Len_max; i++) {
		max_citizensAggro[1] = citizensAggro[i];
		if(citizensAggro[i]<citizensAggro[i+1])
			max_citizensAggro[1] = citizensAggro[i+1];
	}
}
//스테이지3 좀비 이동
int zMove3(int, int, int, int, int);
int zMove3(int Z, int M, int percent, int aggroM, int citizensNum) {
	citizensAggroMax();
	int Rd2 = rand() % 100;
	if (Rd2 < percent) {
		if (max_citizensAggro[1]>=aggroM) {
			if (Z != (citizens[citizensNum-1] + 1))
				return Z -= 1;
			else
				return Z;
		}
		else if (Z != (M - 1))
			return Z += 1;
		else
			return Z;
	}
	else
		return Z;
}
//시민 숫자 부여하는 함수
void citizensNums(int);
void citizensNums(int citizensNum) {
	for (int i = 0; i < citizensNum; i++) {
		citizensNumber[i] = i;
	}
}
//스테이지4 좀비 이동
void zMove4(int, int, int, int);
void zMove4(int M, int percent, int aggroM, int citizensNum) {
	citizensAggroMax();
	int Rd2 = rand() % 100;
	if (Rd2 < percent) {
		if (max_citizensAggro[1] >= aggroM) {
			if (zombies[0] != (citizens[citizensNum - 1] + 1) && zombies[0] != zombies[1]+1)
				zombies[0] -= 1;
		}
		else if (zombies[0] != (M - 1))
			zombies[0] += 1;
		else
			zombies[0];
	}
}
//스테이지4 강화좀비 이동
void strong_zMove4(int, int, int, int);
void strong_zMove4(int M, int percent, int aggroM, int citizensNum) {
	citizensAggroMax();
	for (int i = 1; zombies[i] != 0; i++) {
		int Rd2 = rand() % 100;
		if (Rd2 < percent) {
			if (max_citizensAggro[1] >= aggroM) {
				if (zombies[i] != (citizens[citizensNum - 1] + 1) && zombies[i] != zombies[i + 1] + 1)
					zombies[i] -= 1;
			}
			else if (zombies[i] != (zombies[0] - 1) && zombies[i] !=zombies[i-1]-1)
				zombies[i] += 1;
		}
	}
}
//좀비 수 카운트
int countZombie(void);
int countZombie(void){
	int count=0;
	for (int i = 0; zombies[i]!=0; i++) {
		count++;
	}
	return count;
}
//스테이지4 좀비 시민공격
void citizensAttack2(int, int, int, int);
void citizensAttack2(int M, int citizensNum, int aggroM, int countZ) {
	if (zombies[countZ-1] == (citizens[citizensNum - 1] + 1) && zombies[countZ - 1] == (M - 1))
		printf("%dciziten turned into a zombie! ( aggro : %d vs. %d )\n", citizensNumber[citizensNum - 1], citizensAggro[citizensNum - 1], aggroM);
	else
		printf("%dciziten turned into a zombie!\n", citizensNumber[citizensNum - 1]);
	zombies[countZ] = citizens[citizensNum - 1];
	citizens[citizensNum - 1] = 0;
}
//스테이지4 좀비 이동 현황 출력 함수 : 좀비의 현재위치, 좀비의 이전위치, 좀비의 턴 수
void zSpot2(int);
void zSpot2(int turnZ) {
	if (turnZ % 2 == 0)
		printf("zombie: stay %d (cannot move)\n", zombies[0]);
	else if (befo_zombies[0]!=zombies[0])
		printf("zombie: %d -> %d\n", befo_zombies[0] , zombies[0]);
	else 
		printf("zombie: stay %d\n", zombies[0]);
	for (int i = 1; zombies[i] != 0; i++) {
		if (zombies[i] == befo_zombies[i])
			printf("strong zombie: stay %d\n", zombies[i]);
		else
			printf("strong zombie: %d -> %d\n", befo_zombies[i], zombies[i]);
	}
	printf("\n");
}
//스테이지 4 좀비 마동석공격
int mAttack3(int,int, int, int, int);
int mAttack3(int M,int aggroM, int ma_stamina, int befo_ma_stamina, int citizensNum) {
	ma_stamina -= 1;
	if (zombies[0] == (citizens[citizensNum-1] + 1) && zombies[0] == (M - 1))
		printf("Zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", citizensAggro[citizensNum-1], aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("Zombie attacked madongseok (madongseok stamina: %d -> %d)\n", befo_ma_stamina, ma_stamina);
	return ma_stamina;
}
//스테이지 3 좀비가 마동석을 공격하는 상황
int mAttack2(int, int, int, int, int, int, int);
int mAttack2(int M, int Z, int aggroC, int aggroM, int ma_stamina, int befo_ma_stamina, int citizensNum) {
	ma_stamina -= 1;
	if (Z == (citizens[citizensNum-1] + 1) && Z == (M - 1))
		printf("Zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", citizensAggro[citizensNum-1], aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("Zombie attacked madongseok (madongseok stamina: %d -> %d)\n", befo_ma_stamina, ma_stamina);
	return ma_stamina;
}
//스테이지4 좀비 행동상황 :마동석위치, 좀비위치, 마동석 어그로
int zAction4(int, int, int, int);
int zAction4(int M, int aggroM, int citizensNum, int countZ) {
	int x;
	if (zombies[0] == citizens[citizensNum - 1] + 1 && zombies[0] == (M - 1)) {
		if (citizensAggro[citizensNum - 1] + 1 > aggroM)
			x = Atk_citizen;
		else
			x = Atk_dongseok;
	}
	else if (zombies[countZ-1] == citizens[citizensNum - 1] + 1)
		x = Atk_citizen;
	else if (zombies[0] == (M - 1))
		x = Atk_dongseok;
	else
		x = Atk_none;
	return x;
}
//좀비들 이전값 저장하기
void befo_zombiesMake(int);
void befo_zombiesMake(int countZ) {
	for (int i = 0; i < countZ+1; i++) {
		befo_zombies[i] = zombies[i];
	}
}
//스테이지 4 마동석 움직이기
int mMove2(int);
int mMove2(int M) {
	int x;
	while (1) {
		if (M == (zombies[0] + 1)) {
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
				else if (x == Move_stay)
					return M;
			}
		}
	}
}
//배열 초기화 하는 함수
void rePut(void);
void rePut(void) {
	for (int i = 0; i < Len_max; i++) {
		citizens[i] = 0;
	}
}

int main() {
	srand((unsigned int)time(NULL));		//난수 배열을 초기화 하기 위함
	//인트로
	intro();
	int stage = 0;

	//부산헹 초기 설정
	int tr_length = trTrue();
	int ma_stamina = maTrue();
	int percent = perTrue();
	int C, Z, M, V;
	C = tr_length - 6;
	Z = tr_length - 3;
	M = tr_length - 2;
	V = C + 1;
	int dieCitizens = 0;
	int saveDieCitizens = 0;
	int save_citizens;

	//스테이지3 설정
	int citizens_num_max = tr_length / 2;
	int citizens_num_min = tr_length / 4;
	int citizensNum = citizensNumMake(citizens_num_min, citizens_num_max);  //총 시민들 수
	citizensSpotMake(C, citizensNum); //초기 위치
	citizens[citizensNum - 1] = C; // 배열 마지막 자리에 기존 C 넣기
	spotSort(citizensNum); // 정렬
	befo_citizensMake(citizensNum); //이전 시민들 위치 저장 배열
	citizensNums(citizensNum);
	save_citizens = citizensNum;

	while (stage != 4) {
		
		printStage(stage);

		C = tr_length - 6;
		Z = tr_length - 3;
		M = tr_length - 2;
		V = C + 1;

		int befoC, befoZ, befoM, befo_ma_stamina, befoV, turnZ;
		befoC = C;
		befoZ = Z;
		befoM = M;
		befoV = V;
		befo_ma_stamina = ma_stamina;
		turnZ = 1;

		int aggroC, befo_aggroC, aggroM, aggroV, befo_aggroM;
		aggroC = 0;
		befo_aggroC = 0;
		aggroM = 0;
		befo_aggroM = 0;
		aggroV = 0;

		int actionZ, actionM, actionV;
		int Cdead = 0;
		int pull_percent;
		int countZ=1;


		if (stage == 3) {
			zombies[0] = Z;
			rePut();
			citizensNum = citizensNumMake(citizens_num_min, citizens_num_max);  //총 시민들 수
			countZ = countZombie(citizensNum);
			citizensSpotMake(C, citizensNum); //초기 위치
			citizens[citizensNum - 1] = C; // 배열 마지막 자리에 기존 C 넣기
			spotSort(citizensNum); // 정렬
			befo_citizensMake(citizensNum); //이전 시민들 위치 저장 배열
			citizensNums(citizensNum);
			befo_zombiesMake(countZ);
			save_citizens = citizensNum;
			dieCitizens = 0;
			saveDieCitizens = 0;
		}

		switch (stage) {
		case 0: trMakeFirst(tr_length, C, Z, M); break;
		case 1: trMakeSecond(tr_length, C, Z, M, V); break;
		case 2: trMakeThird(tr_length, Z, M); break;
		case 3: trMakeFourth(tr_length, M, countZ); break;
		}
		printf("=========================================================\n\n\n");

		//무한반복 코드
		while (stage == 0) {
			//시민, 좀비 이동
			C = cMove(percent, C);
			aggroC = cAggro(C, befoC, aggroC);
			if ((turnZ % 2) != 0)
				Z = zMove(percent, Z, aggroC, aggroM, C, M);

			trMakeFirst(tr_length, C, Z, M);

			cSpot(C, befoC, befo_aggroC, aggroC);
			zSpot(Z, befoZ, turnZ);
			
			//마동석 이동
			M = mMove(Z, M);
			aggroM = mAggro(M, befoM, aggroM);

			trMakeFirst(tr_length, C, Z, M);

			mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

			//시민상태, 좀비행동
			cCondition();
			actionZ = zAction(C, M, Z, aggroC, aggroM);
			switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: Cdead = cAttack(C, M, Z, aggroC, aggroM); break;
			case Atk_dongseok: ma_stamina = mAttack(C, M, Z, aggroC, aggroM, ma_stamina, befo_ma_stamina); break;
			}

			if (C == 1)
				break;
			if (ma_stamina == 0 || Cdead == 1)
				break;

			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;

			actionM = mAction(Z, M);

			//마동석 행동
			if (actionM == Action_rest) {
				ma_stamina = addStm(ma_stamina);
				aggroM = minus_one_AggroM(aggroM);
				mRest(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_provoke) {
				aggroM = Aggro_max;
				mProvoke(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_pull) {
				pull_percent = mPull(percent);
				if (pull_percent == 1) {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					success_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
				else {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					fail_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
			}

			//현재 값으로 초기화
			befoC = C;
			befoZ = Z;
			befoM = M;
			befo_aggroC = aggroC;
			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;
			turnZ += 1;
		}   //스테이지 1
		while (stage == 1) {
			//시민, 좀비 이동
			C = cMove(percent, C);
			aggroC = cAggro(C, befoC, aggroC);

			if (V != 0) {
				V = vMove(C, befoC, V);
				aggroV = vAggro(V, befoV, aggroV);
			}

			if ((turnZ % 2) != 0)
				Z = zMove(percent, Z, aggroC, aggroM, C, M);

			trMakeSecond(tr_length, C, Z, M, V);

			cSpot(C, befoC, befo_aggroC, aggroC);
			if(V!=0)
				vSpot(V, befoV, aggroV);
			zSpot(Z, befoZ, turnZ);
			printf("\n");

			//마동석 이동
			M = mMove(Z, M);
			aggroM = mAggro(M, befoM, aggroM);

			trMakeSecond(tr_length, C, Z, M, V);
			mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

			//시민상태
			cCondition();
			if (C == 1) {
				break;
			}
			//빌런 상태
			if (V != 0) {
				actionV = vAction();
				if (actionV == 1) {
					int x;
					x = V;
					V = C;
					C = x;
				}
			}	
			//마동석 행동
			actionM = mAction(Z, M);
			if (actionM == Action_rest) {
				ma_stamina = addStm(ma_stamina);
				aggroM = minus_one_AggroM(aggroM);
				mRest(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_provoke) {
				aggroM = Aggro_max;
				mProvoke(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_pull) {
				pull_percent = mPull(percent);
				if (pull_percent == 1) {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					success_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
				else {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					fail_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
			}
			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;

			//좀비 행동
			actionZ = zAction2(C, M, Z, aggroC, aggroM, V);

			switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: Cdead = cAttack(C, M, Z, aggroC, aggroM); break;
			case Atk_dongseok: ma_stamina = mAttack(C, M, Z, aggroC, aggroM, ma_stamina, befo_ma_stamina); break;
			default: V = 0; vAttack(); break;
			}
			if (ma_stamina == 0 || Cdead == 1)
				break;

			//현재 값으로 초기화
			befoC = C;
			befoZ = Z;
			befoM = M;
			befoV = V;
			befo_aggroC = aggroC;
			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;
			turnZ += 1;
		}
		while (stage == 2) {
			//시민들 움직임
			citizensMove(percent, citizensNum);
			Aggro_citizens(citizensNum);
			if ((turnZ % 2) != 0)
				Z = zMove3(Z, M, percent, aggroM, citizensNum);

			trMakeThird(tr_length, Z, M);

			//자리 출력
			citizensSpot(citizensNum);
			zSpot(Z, befoZ, turnZ);
			trMakeThird(tr_length, Z, M);

			//마동석 이동
			M = mMove(Z, M);
			aggroM = mAggro(M, befoM, aggroM);
			trMakeThird(tr_length, Z, M);
			mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

			//시민상태, 좀비행동
			actionZ = zAction3(M, Z, aggroM, citizensNum);
			switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: citizensAttack(Z, M, citizensNum, aggroM); break;
			case Atk_dongseok: ma_stamina = mAttack2(M, Z, aggroC, aggroM, ma_stamina, befo_ma_stamina,citizensNum); break;
			}

			//시민 배열 업데이트 후 상태 출력
			dieCitizens = die_citizens(citizensNum);
			citizensNum = exit_citizens(citizensNum);
			saveDieCitizens += dieCitizens;
			if (dieCitizens != 0);
				citizensNum -= dieCitizens;
			citizensCondition(citizensNum);

			if (ma_stamina == 0 || citizensNum == 0 || save_citizens == saveDieCitizens)
				break;

			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;

			//마동석 행동
			actionM = mAction(Z, M);
			if (actionM == Action_rest) {
				ma_stamina = addStm(ma_stamina);
				aggroM = minus_one_AggroM(aggroM);
				mRest(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_provoke) {
				aggroM = Aggro_max;
				mProvoke(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_pull) {
				pull_percent = mPull(percent);
				if (pull_percent == 1) {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					success_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
				else {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					fail_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
			}

			//현재 값으로 초기화
			befoC = C;
			befoZ = Z;
			befoM = M;
			befo_aggroC = aggroC;
			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;
			turnZ += 1;
			befo_citizensMake(citizensNum);
			befo_citizensAggroMake(citizensNum);
			}
		while (stage == 3) {
			citizensMove(percent, citizensNum);
			Aggro_citizens(citizensNum);

			
			if((turnZ % 2) != 0)
				zMove4(M, percent, aggroM, citizensNum);
			strong_zMove4(M, percent, aggroM, citizensNum);

			trMakeFourth(tr_length, M, countZ);

			//자리 출력
			citizensSpot(citizensNum);
			zSpot2(turnZ);
			trMakeFourth(tr_length, M, countZ);

			//마동석 이동
			M = mMove2(M);
			aggroM = mAggro(M, befoM, aggroM);
			trMakeFourth(tr_length, M, countZ);
			mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

			//시민상태, 좀비행동
			actionZ = zAction4(M,aggroM, citizensNum, countZ);
			switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: citizensAttack2(M, citizensNum, aggroM, countZ); break;
			case Atk_dongseok: ma_stamina = mAttack3(M, aggroM, ma_stamina, befo_ma_stamina, citizensNum); break;
			}

			//시민 배열 업데이트 후 상태 출력
			countZ = countZombie();
			dieCitizens = die_citizens(citizensNum);
			citizensNum = exit_citizens(citizensNum);
			saveDieCitizens += dieCitizens;
			if (dieCitizens != 0);
				citizensNum -= dieCitizens;
			citizensCondition(citizensNum);

			if (ma_stamina == 0 || citizensNum == 0 || save_citizens == saveDieCitizens)
				break;

			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;

			//마동석 행동
			actionM = mAction(Z, M);
			if (actionM == Action_rest) {
				ma_stamina = addStm(ma_stamina);
				aggroM = minus_one_AggroM(aggroM);
				mRest(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_provoke) {
				aggroM = Aggro_max;
				mProvoke(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
			}
			if (actionM == Action_pull) {
				pull_percent = mPull(percent);
				if (pull_percent == 1) {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					success_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
				else {
					aggroM = add_two_AggroM(aggroM);
					ma_stamina = minusStm(ma_stamina);
					fail_mPull(M, aggroM, befo_aggroM, ma_stamina, befo_ma_stamina);
				}
			}
			//현재 값으로 초기화
			befoZ = Z;
			befoM = M;
			befo_aggroM = aggroM;
			befo_ma_stamina = ma_stamina;
			turnZ += 1;
			befo_citizensMake(citizensNum);
			befo_citizensAggroMake(citizensNum);
			befo_zombiesMake(countZ);
			countZ = countZombie(citizensNum);
		}
		//시민 탈출시
		if (stage==0 || stage==1) {
			if (C == 1) {
				nextStage();
				stage++;
			}
			else
				break;
		}
		else if (stage==2) {
			if (C == 1 || save_citizens!=saveDieCitizens) {
				nextStage();
				stage++;
			}
			else
				break;
		}
		//스테이지4 전에 게임 끝냈을때
		else
			break;
	}
	outro(stage, ma_stamina, saveDieCitizens, save_citizens);
}