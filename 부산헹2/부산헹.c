#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //���� ����
#define Len_max 50		
#define Prob_min 10		//Ȯ�� 
#define Prob_max 90		
#define Stm_min 0		//������ ü��
#define Stm_max 5
#define Move_stay 0		//������ �̵� ����
#define Move_left 1
#define Action_rest 0	//������ �ൿ
#define Action_proboke 1
#define Action_pull 2
#define Aggro_min 0		//��׷� ����
#define Aggro_max 5
#define Atk_none 0		//������ ���� ���
#define Atk_citizen 1	
#define Atk_dongseok 2

//��Ʈ��
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

	printf("			      TITLE : �λ���\n\n");
	printf("			     ������ �����մϴ�.\n\n");
}
//�ƿ�Ʈ��
void outro(int);
void outro(int C) {
	if (C == 1) {
		printf("     Ż�⼺��!!\n");
		printf("  ___        _  _   \n");
		printf(" / __|      (_)| |  \n");
		printf("| |__  _, __ _ | |_ \n");
		printf("|  __|| |/ /| || __|\n");
		printf("| |__  >  < | || |_ \n");
		printf("|____|/_/|_||_||___|\n");
	}
	else {
		printf("                Ż�����..\n");
		printf(",_   __                _____  _       \n");
		printf("| | / /               |  _  |(_)      \n");
		printf(" L V /   ___   _   _  | | | | _   ___ \n");
		printf("  | /   / _ | | | | | | | | || | / _ |\n");
		printf("  | |  | (_) || |_| | | |/ / | ||  __/\n");
		printf("  |_/   |___/  |__,_| |___/  |_| |___|\n");
	}
}
//���� ���� �Է¹޴� �Լ�
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
//Ȯ�� �Է¹޴� �Լ�
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
//������ ü�� �Է¹޴� �Լ�
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
//���� ����� �Լ� : ��������, �ù���ġ, ������ ��ġ, ���� ��ġ
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
//�ù� �����̱� �Լ� : �ù���ġ, Ȯ��
int cMove(int, int);
int cMove(int percent, int C) {
	int Rd = rand() % 100;
	if (Rd < (100 - percent))
		return C -= 1;
	else
		return C;
}
//���� �����̱� �Լ� : ������ġ, Ȯ��
int zMove(int, int);
int zMove(int percent, int Z) {
	int Rd2 = rand() % 100;
	if (Rd2 < percent)
		return Z -= 1;
	else
		return Z;
}
//�ù� �̵� ��Ȳ ��� �Լ� : �ù��� ������ġ, �ù��� ������ġ
void cSpot(int, int, int, int);
void cSpot(int C, int befoC ,int befo_aggroC,int aggroC) {
	if (befoC != C) {
		printf("citizen: %d -> %d (aggro : %d -> %d)\n", befoC, C,befo_aggroC,aggroC);
	}
	else
		printf("citizen: stay %d (aggro : %d -> %d)\n", befoC,befo_aggroC,aggroC);
}
//���� �̵� ��Ȳ ��� �Լ� : ������ ������ġ, ������ ������ġ, ������ �� ��
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
//�ù� ��׷� 
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
//������ �����̱� �Լ�
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
	srand((unsigned int)time(NULL));		//���� �迭�� �ʱ�ȭ �ϱ� ����

	//1. ��Ʈ��
	intro();

	// 2. �λ��� �ʱ� ����
	int tr_length;
	tr_length = trTrue(Len_min, Len_max);

	int ma_stamina;
	ma_stamina = maTrue(Stm_min, Stm_max);

	int percent;	//Ȯ�� ���� ���� �� �Է�
	percent = perTrue(Prob_min, Prob_max);

	// 3. Ȯ���� ���� �ùΰ� ���� �̵�

	int C, Z, M;	//�ù�, ����, ������ ���� ���� �� ���� ���̿� ���� �ʱ� ��ġ ����
	C = tr_length - 6;
	Z = tr_length - 3;
	M = tr_length - 2;

	trMake(tr_length, C, Z, M);	//�λ��� �ʱ� ���� ���� ��

	int befoC, befoZ, turnZ;	//�ù�, ������ �����̱� ���� �� �� ������ �� Ƚ���� �����ϱ� ���� ���� ����
	befoC = C;
	befoZ = Z;
	turnZ = 1;

	int aggroC, befo_aggroC;
	aggroC = 0;
	befo_aggroC = 0;

	while (C != 1 && Z != C + 1) { //���ѹݺ� �ڵ�
		C = cMove(percent, C);

		aggroC = cAggro(C, befoC, aggroC);

		if ((turnZ % 2) != 0)
			Z = zMove(percent, Z);

		trMake(tr_length, C, Z, M);

		cSpot(C, befoC,befo_aggroC,aggroC);

		zSpot(Z, befoZ, turnZ);

		M = mMove(Z, M);

		trMake(tr_length, C, Z, M);

		befoC = C;		//�ٲ� ������ �ʱ�ȭ
		befoZ = Z;
		befo_aggroC = aggroC;

		turnZ += 1;		//������ Ƚ�� ����
		printf("\n");
	}
	// 4. �ƿ�Ʈ��
	outro(C);
}		//��