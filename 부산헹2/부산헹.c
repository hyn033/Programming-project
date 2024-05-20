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
#define Action_provoke 1
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
		printf("\n\n");
		printf("     Ż�⼺��!!\n");
		printf("  ___        _  _   \n");
		printf(" / __|      (_)| |  \n");
		printf("| |__  _, __ _ | |_ \n");
		printf("|  __|| |/ /| || __|\n");
		printf("| |__  >  < | || |_ \n");
		printf("|____|/_/|_||_||___|\n");
	}
	else {
		printf("\n\n");
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
//�ù� �����̱� �Լ� : �ù���ġ, Ȯ��
int cMove(int, int);
int cMove(int percent, int C) {
	int Rd = rand() % 100;
	if (Rd < (100 - percent))
		return C -= 1;
	else
		return C;
}
//���� �����̱� �Լ�(+����) : ������ġ, Ȯ��, �ùξ�׷�, ��������׷�
int zMove(int, int,int,int, int, int);
int zMove(int percent, int Z, int aggroC, int aggroM, int C, int M) {
	int Rd2 = rand() % 100;
	if (Rd2 < percent) {
		if (aggroC >= aggroM) {
			if (Z != (C + 1))
				return Z -= 1;
		}
		else if (Z != (M - 1))
			return Z += 1;
		else
			return Z;
	}
	else
		return Z;
	return Z;
}
//�ù� �̵� ��Ȳ ��� �Լ� : �ù��� ������ġ, �ù��� ������ġ, ��׷� ��
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
//������ ��׷� 
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
//������ �̵� ��ȯ ��� �Լ� : ������ ������ġ, ������ ������ġ, ��׷� ��, ������ ü��
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
//�ù� �����Ȳ
void cCondition(void);
void cCondition(void) {
	printf("citizen does nothing.\n");
}
//���� �ൿ��Ȳ : �ù���ġ, ��������ġ, ������ġ, �ùξ�׷�, ��������׷�
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
//���� �������� �ʴ� ��Ȳ
void noAttack(void);
void noAttack(void) {
	printf("zombie attcked nobody.\n");
}
//���� �ù��� �����ϴ� ��Ȳ
int cAttack(int, int, int, int, int);
int cAttack(int C, int M, int Z, int aggroC, int aggroM) {
	if (Z == (C + 1) && Z == (M - 1))
		printf("Zombie attacked citizen (aggro: %d vs. %d, citizen dead)\n", aggroC, aggroM);
	else
		printf("Zombie attacked citizen \n");
	return 1;
}
//���� �������� �����ϴ� ��Ȳ
int mAttack(int, int, int,int,int,int,int);
int mAttack(int C, int M, int Z, int aggroC, int aggroM, int ma_stamina, int befo_ma_stamina) {
	ma_stamina -=1;
	if (Z == (C + 1) && Z == (M - 1))
		printf("Zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", aggroC, aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("Zombie attacked madongseok (madongseok stamina: %d -> %d)\n", befo_ma_stamina, ma_stamina);
	return ma_stamina;
}
//������ �ൿ : ������ġ, ��������ġ
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
//������ ü�� 1 ���� �Լ�
int addStm(int);
int addStm(int ma_stamina) {
	if (ma_stamina != Stm_max)
		return ma_stamina += 1;
	else
		return ma_stamina =Stm_max;
}
//������ ü�� 1 ���� �Լ�
int minusStm(int);
int minusStm(int ma_stamina) {
	if (ma_stamina != Stm_min)
		return ma_stamina -= 1;
	else
		return ma_stamina = Stm_min;
}
//������ ��׷� 1 ���� �Լ�
int minus_one_AggroM(int);
int minus_one_AggroM(int aggroM) {
	if (aggroM != Aggro_min)
		return aggroM -= 1;
	else
		return aggroM = Aggro_min;
}
//������ ��׷� 2 ���� �Լ�
int add_two_AggroM(int);
int add_two_AggroM(int aggroM) {
	if ((aggroM+2)<=Aggro_max)
		return aggroM += 2;
	else
		return aggroM = Aggro_max;
}
//������ rest ��Ȳ : ������ ��ġ, ������ ��׷�, ������ ü��
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
//������ provoke ��Ȳ : ������ ��ġ, ������ ��׷�. ������ ü��
void mProvoke(int,int,int,int,int);
void mProvoke(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok provoked zombie...\n");
	if(befo_aggroM==Aggro_max)
		printf("madongseok: %d (aggro : %d, stamina : %d)\n", M, aggroM, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d)\n", M, befo_aggroM, aggroM, ma_stamina);
}
//������ pull Ȯ�� : �ۼ�Ʈ 
int mPull(int);
int mPull(int percent) {
	int x = rand() % 100;
	if (x < (100 - percent))
		return 1;
	else
		return 0;
}
//�������� �ٵ�� ������ ��Ȳ: 
void success_mPull(int, int, int, int, int);
void success_mPull(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok pulled zombie... Next turn, it can't move\n");
	if (befo_aggroM == aggroM)
		printf("madongseok: %d (aggro : %d, stamina : %d)\n", M, aggroM, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, befo_ma_stamina,ma_stamina);
}
//�������� �ٵ�� ������ ��Ȳ: 
void fail_mPull(int, int, int, int, int);
void fail_mPull(int M, int aggroM, int befo_aggroM, int ma_stamina, int befo_ma_stamina) {
	printf("madongseok failed to pull zombie\n");
	if (befo_aggroM == aggroM)
		printf("madongseok: %d (aggro : %d, stamina : %d -> %d)\n", M, aggroM, befo_ma_stamina, ma_stamina);
	else
		printf("madongseok: %d (aggro : %d -> %d, stamina : %d -> %d)\n", M, befo_aggroM, aggroM, befo_ma_stamina, ma_stamina);
}

int main() {
	srand((unsigned int)time(NULL));		//���� �迭�� �ʱ�ȭ �ϱ� ����
	//��Ʈ��
	intro();

	//�λ��� �ʱ� ����
	int tr_length = trTrue();
	int ma_stamina = maTrue();
	int percent = perTrue();

	int C, Z, M;	
	C = tr_length - 6;
	Z = tr_length - 3;
	M = tr_length - 2;

	trMake(tr_length, C, Z, M);

	int befoC, befoZ, befoM, befo_ma_stamina, turnZ;
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
	int pull_percent;

	//���ѹݺ� �ڵ�
	while (C != 1 && Cdead!=1 && ma_stamina!= 0) { 
		//�ù�, ���� �̵�
		C = cMove(percent, C);
		aggroC = cAggro(C, befoC, aggroC);

		if ((turnZ % 2) != 0) {
				Z = zMove(percent, Z, aggroC, aggroM, C, M);
		}
		trMake(tr_length, C, Z, M);

		cSpot(C, befoC,befo_aggroC,aggroC);
		zSpot(Z, befoZ, turnZ); 
		printf("\n");
		if (C == 1)
			break;

		//������ �̵�
		M = mMove(Z, M);
		aggroM = mAggro(M, befoM, aggroM);

		trMake(tr_length, C, Z, M);

		mSpot(M, befoM, aggroM, befo_aggroM, ma_stamina);

		//�ùλ���, �����ൿ
		cCondition();
		actionZ = zAction(C, M, Z, aggroC, aggroM);

		switch (actionZ) {
			case Atk_none: noAttack(); break;
			case Atk_citizen: Cdead = cAttack(C, M, Z, aggroC, aggroM); break;
			case Atk_dongseok: ma_stamina = mAttack(C, M, Z, aggroC, aggroM,ma_stamina, befo_ma_stamina); break;
		}
		if (ma_stamina == 0 || Cdead == 1)
			break;

		befo_aggroM = aggroM;
		befo_ma_stamina = ma_stamina;

		actionM = mAction(Z, M);

		//������ �ൿ
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
		//���� ������ �ʱ�ȭ
		befoC = C;		
		befoZ = Z;
		befoM = M;
		befo_aggroC = aggroC;
		befo_aggroM = aggroM;
		befo_ma_stamina = ma_stamina;
		turnZ += 1;	
	}
	//�ƿ�Ʈ��
	outro(C);
}