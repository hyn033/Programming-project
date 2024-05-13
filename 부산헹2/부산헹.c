#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //���� ���� �ּڰ� ����
#define Len_max 50		//���� ���� �ִ� ����
#define Prob_min 10		//Ȯ�� �ּڰ� ����
#define Prob_max 90		//Ȯ�� �ִ밪 ����

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
void cSpot(int, int);
void cSpot(int C, int befoC) {
	if (befoC != C) {
		printf("citizen: %d -> %d\n", befoC, C);
	}
	else
		printf("citizen: stay %d\n", befoC);
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

int main() {
	srand((unsigned int)time(NULL));		//���� �迭�� �ʱ�ȭ �ϱ� ����

	//1. ��Ʈ��
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

	Sleep(1000);
	//��Ʈ�� ��

	// 2. �λ��� �ʱ� ���� �����ϱ�
	int tr_length;
	printf("������ ���̸� �Է����ּ���(%d~%d)>>: ", Len_min, Len_max);
	scanf_s("%d", &tr_length);
	printf("\n");

	if (tr_length < Len_min || tr_length > Len_max) {		//������ ���� ������ ���� �ƴϸ� "�߸��� �Է��Դϴ�." ���
		printf("�߸��� ���� �Է��Դϴ�.");
	}
	else {
		int percent;	//Ȯ�� ���� ���� �� �Է�
		printf("Ȯ���� �Է����ּ���(%d~%d)>>: ", Prob_min, Prob_max);
		scanf_s("%d", &percent);
		printf("\n");

		if (percent < Prob_min || percent > Prob_max) {		//������ ���� ������ ���� �ƴϸ� "�߸��� �Է��Դϴ�." ���
			printf("�߸��� Ȯ�� �Է��Դϴ�.");
		}
		else {
			// 3. Ȯ���� ���� �ùΰ� ���� �̵�

			int C, Z, M;	//�ù�, ����, ������ ���� ���� �� ���� ���̿� ���� �ʱ� ��ġ ����
			C = tr_length - 6;
			Z = tr_length - 3;
			M = tr_length - 2;

			trMake(tr_length, C, Z, M);	//�λ��� �ʱ� ���� ���� ��

			int befoC, befoZ, turnZ;		//�ù�, ������ �����̱� ���� �� �� ������ �� Ƚ���� �����ϱ� ���� ���� ����
			befoC = C;
			befoZ = Z;
			turnZ = 1;				//Ȧ������ �����̱� ������ �ʱ갪�� 1�� ����

			while (C != 1 && Z != C + 1) { //���ѹݺ� �ڵ�
				C = cMove(percent, C);

				if ((turnZ % 2) != 0)	//�������� 0�� �ƴϸ� Ȧ���������� ���� ���� ����
					Z = zMove(percent, Z);

				trMake(tr_length, C, Z, M);

				cSpot(C, befoC);

				zSpot(Z, befoZ, turnZ);

				if (befoC != C)
					befoC = C;
				if (befoZ != Z)
					befoZ = Z;

				turnZ += 1;		//������ Ƚ�� ����
				printf("\n");
				Sleep(4000);
			}

			// 4. �ƿ�Ʈ��
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
	}
	return 0;
}		//��