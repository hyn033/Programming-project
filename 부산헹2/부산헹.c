#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //���� ���� �ּڰ� ����
#define Len_max 50		//���� ���� �ִ� ����
#define Prob_min 10		//Ȯ�� �ּڰ� ����
#define Prob_max 90		//Ȯ�� �ִ밪 ����

int main() {

	srand((unsigned int)time(NULL));		//���� �迭�� �ʱ�ȭ �ϱ� ����

	// 1. ��Ʈ��
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

	int tr_length;		//���� ���� ���� ���� �� �Է�
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

			int C, M, Z;		//�ù�, ����, ������ ���� ���� �� ���� ���̿� ���� �ʱ� ��ġ ����
			C = tr_length - 6;
			M = tr_length - 2;
			Z = tr_length - 3;


			for (int i = 0; i < tr_length; i++) {		// ���� 1��° ��
				printf("#");
			}
			printf("\n");

			for (int i = 0; i < tr_length; i++) {		//���� 2��° ��
				if (i == 0 || i == tr_length - 1)
					printf("#");	//���� ù��°�� ������ �κ��� #���� ������

				else if (i == C)
					printf("C");	//�ù� ��ġ�� C�� ǥ��

				else if (i == M)
					printf("M");	//������ ��ġ�� M���� ǥ��

				else if (i == Z)
					printf("Z");	//���� ��ġ�� Z�� ǥ��

				else
					printf(" ");	//�� �ܴ� ��ĭ���� ǥ��
			}
			printf("\n");


			for (int i = 0; i < tr_length; i++) {		//���� 3��° ��
				printf("#");
			}
			printf("\n\n");
			//�λ��� �ʱ� ���� ���� ��


					// 3. Ȯ���� ���� �ùΰ� ���� �̵�
			int CS, ZS, ZT;		//�ù�, ������ �����̱� ���� �� �� ������ �� Ƚ���� �����ϱ� ���� ���� ����
			CS = C;
			ZS = Z;
			ZT = 1;				//Ȧ������ �����̱� ������ �ʱ갪�� 1�� ����

			while (1) { //���ѹݺ� �ڵ�
				int Rd = rand() % 100;				//0~99 ������ �� �� �Ѱ��� ���� ����

				if (Rd < (100 - percent)) 			//�Է��� Ȯ������ ������ ������ �ù� �̵�
					C -= 1;

				if ((ZT % 2) != 0) {				//�������� 0�� �ƴϸ� Ȧ���������� ���� ���� ����

					int Rd2 = rand() % 100;			//0~99 ������ �� �� �Ѱ��� ���� ����

					if (Rd2 < percent) 				//�Է��� Ȯ������ ������ ������ ���� �̵�
						Z -= 1;
				}

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
				printf("\n\n");

				if (CS != C) {		//�ù��� �̵������� ����
					printf("citizen: %d -> %d\n", CS, C);
					CS = C;			//�ù��� �����̱� ���� ���� ���� ��ġ�� �缳��
				}
				else {
					printf("citizen: stay %d\n", CS);		//�ù��� ���ڸ��� �� ����
				}
				if (ZT % 2 == 0) {		//�������� ¦���϶� ����
					printf("zombie: stay %d (cannot move)\n", ZS);		//¦���Ͽ��� ���� �������� ����
				}
				else if (ZS != Z) {		//���� �̵������� ����
					printf("zombie: %d -> %d\n", ZS, Z);
					ZS = Z;
				}
				else {			//���� ���ڸ��� �� ����
					printf("zombie: stay %d\n", ZS);
				}

				ZT += 1;		//������ Ƚ�� ����
				printf("\n");
				Sleep(4000);

				if (C == 1 || Z == C + 1)		//�ù� Ż���ϰų� ���񿡰� �������� ����
					break;						//�ݺ� ���߱�
			}
			//�ù�, ���� �̵� �� �ݺ� ��


			// 4. �ƿ�Ʈ��
			if (C == 1) {		//�ù��� Ż������ ���� �ƿ�Ʈ��
				printf("     Ż�⼺��!!\n");
				printf("  ___        _  _   \n");
				printf(" / __|      (_)| |  \n");
				printf("| |__  _, __ _ | |_ \n");
				printf("|  __|| |/ /| || __|\n");
				printf("| |__  >  < | || |_ \n");
				printf("|____|/_/|_||_||___|\n");
			}
			else {			//Ż�� �������� ���� �ƿ�Ʈ��
				printf("                Ż�����..\n");
				printf(",_   __                _____  _       \n");
				printf("| | / /               |  _  |(_)      \n");
				printf(" L V /   ___   _   _  | | | | _   ___ \n");
				printf("  | /   / _ | | | | | | | | || | / _ |\n");
				printf("  | |  | (_) || |_| | | |/ / | ||  __/\n");
				printf("  |_/   |___/  |__,_| |___/  |_| |___|\n");

			}
			//�ƿ�Ʈ�� ��
		}
	}
	return 0;
}		//��