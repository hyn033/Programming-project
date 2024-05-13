#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //열차 길이 최솟값 저장
#define Len_max 50		//열차 길이 최댓값 저장
#define Prob_min 10		//확률 최솟값 저장
#define Prob_max 90		//확률 최대값 저장

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
void cSpot(int, int);
void cSpot(int C, int befoC) {
	if (befoC != C) {
		printf("citizen: %d -> %d\n", befoC, C);
	}
	else
		printf("citizen: stay %d\n", befoC);
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

int main() {
	srand((unsigned int)time(NULL));		//난수 배열을 초기화 하기 위함

	//1. 인트로
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

	Sleep(1000);
	//인트로 끝

	// 2. 부산헹 초기 열차 설정하기
	int tr_length;
	printf("열차의 길이를 입력해주세요(%d~%d)>>: ", Len_min, Len_max);
	scanf_s("%d", &tr_length);
	printf("\n");

	if (tr_length < Len_min || tr_length > Len_max) {		//지정한 숫자 사이의 값이 아니면 "잘못된 입력입니다." 출력
		printf("잘못된 길이 입력입니다.");
	}
	else {
		int percent;	//확률 변수 지정 및 입력
		printf("확률을 입력해주세요(%d~%d)>>: ", Prob_min, Prob_max);
		scanf_s("%d", &percent);
		printf("\n");

		if (percent < Prob_min || percent > Prob_max) {		//지정한 숫자 사이의 값이 아니면 "잘못된 입력입니다." 출력
			printf("잘못된 확률 입력입니다.");
		}
		else {
			// 3. 확률에 따른 시민과 좀비 이동

			int C, Z, M;	//시민, 좀비, 마동석 변수 지정 후 열차 길이에 따른 초기 위치 설정
			C = tr_length - 6;
			Z = tr_length - 3;
			M = tr_length - 2;

			trMake(tr_length, C, Z, M);	//부산헹 초기 열차 설정 끝

			int befoC, befoZ, turnZ;		//시민, 좀비의 움직이기 직전 값 및 좀비의 턴 횟수를 저장하기 위한 변수 설정
			befoC = C;
			befoZ = Z;
			turnZ = 1;				//홀수턴은 실행이기 때문에 초깃값을 1로 설정

			while (C != 1 && Z != C + 1) { //무한반복 코드
				C = cMove(percent, C);

				if ((turnZ % 2) != 0)	//나머지가 0이 아니면 홀수턴임으로 난수 추출 실행
					Z = zMove(percent, Z);

				trMake(tr_length, C, Z, M);

				cSpot(C, befoC);

				zSpot(Z, befoZ, turnZ);

				if (befoC != C)
					befoC = C;
				if (befoZ != Z)
					befoZ = Z;

				turnZ += 1;		//좀비턴 횟수 증가
				printf("\n");
				Sleep(4000);
			}

			// 4. 아웃트로
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
	}
	return 0;
}		//끝