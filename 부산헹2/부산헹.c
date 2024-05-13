#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define Len_min 15      //열차 길이 최솟값 저장
#define Len_max 50		//열차 길이 최댓값 저장
#define Prob_min 10		//확률 최솟값 저장
#define Prob_max 90		//확률 최대값 저장

int main() {

	srand((unsigned int)time(NULL));		//난수 배열을 초기화 하기 위함

	// 1. 인트로
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

	int tr_length;		//열차 길이 변수 지정 및 입력
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

			int C, M, Z;		//시민, 좀비, 마동석 변수 지정 후 열차 길이에 따른 초기 위치 설정
			C = tr_length - 6;
			M = tr_length - 2;
			Z = tr_length - 3;


			for (int i = 0; i < tr_length; i++) {		// 열차 1번째 행
				printf("#");
			}
			printf("\n");

			for (int i = 0; i < tr_length; i++) {		//기차 2번째 행
				if (i == 0 || i == tr_length - 1)
					printf("#");	//기차 첫번째와 마지막 부분은 #으로 막아줌

				else if (i == C)
					printf("C");	//시민 위치는 C로 표시

				else if (i == M)
					printf("M");	//마동석 위치는 M으로 표시

				else if (i == Z)
					printf("Z");	//좀비 위치는 Z로 표시

				else
					printf(" ");	//그 외는 빈칸으로 표시
			}
			printf("\n");


			for (int i = 0; i < tr_length; i++) {		//기차 3번째 행
				printf("#");
			}
			printf("\n\n");
			//부산헹 초기 열차 설정 끝


					// 3. 확률에 따른 시민과 좀비 이동
			int CS, ZS, ZT;		//시민, 좀비의 움직이기 직전 값 및 좀비의 턴 횟수를 저장하기 위한 변수 설정
			CS = C;
			ZS = Z;
			ZT = 1;				//홀수턴은 실행이기 때문에 초깃값을 1로 설정

			while (1) { //무한반복 코드
				int Rd = rand() % 100;				//0~99 사이의 수 중 한개의 난수 추출

				if (Rd < (100 - percent)) 			//입력한 확률보다 난수가 낮으면 시민 이동
					C -= 1;

				if ((ZT % 2) != 0) {				//나머지가 0이 아니면 홀수턴임으로 난수 추출 실행

					int Rd2 = rand() % 100;			//0~99 사이의 수 중 한개의 난수 추출

					if (Rd2 < percent) 				//입력한 확률보다 난수가 낮으면 좀비 이동
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

				if (CS != C) {		//시민이 이동했을때 실행
					printf("citizen: %d -> %d\n", CS, C);
					CS = C;			//시민이 움직이기 직전 값을 현재 위치로 재설정
				}
				else {
					printf("citizen: stay %d\n", CS);		//시민이 제자리일 때 실행
				}
				if (ZT % 2 == 0) {		//좀비턴이 짝수일때 실행
					printf("zombie: stay %d (cannot move)\n", ZS);		//짝수턴에는 좀비가 움직이지 않음
				}
				else if (ZS != Z) {		//좀비가 이동했을때 실행
					printf("zombie: %d -> %d\n", ZS, Z);
					ZS = Z;
				}
				else {			//좀비가 제자리일 때 실행
					printf("zombie: stay %d\n", ZS);
				}

				ZT += 1;		//좀비턴 횟수 증가
				printf("\n");
				Sleep(4000);

				if (C == 1 || Z == C + 1)		//시민 탈출하거나 좀비에게 잡혔을때 실행
					break;						//반복 멈추기
			}
			//시민, 좀비 이동 및 반복 끝


			// 4. 아웃트로
			if (C == 1) {		//시민이 탈출했을 때의 아웃트로
				printf("     탈출성공!!\n");
				printf("  ___        _  _   \n");
				printf(" / __|      (_)| |  \n");
				printf("| |__  _, __ _ | |_ \n");
				printf("|  __|| |/ /| || __|\n");
				printf("| |__  >  < | || |_ \n");
				printf("|____|/_/|_||_||___|\n");
			}
			else {			//탈출 실패했을 때의 아웃트로
				printf("                탈출실패..\n");
				printf(",_   __                _____  _       \n");
				printf("| | / /               |  _  |(_)      \n");
				printf(" L V /   ___   _   _  | | | | _   ___ \n");
				printf("  | /   / _ | | | | | | | | || | / _ |\n");
				printf("  | |  | (_) || |_| | | |/ / | ||  __/\n");
				printf("  |_/   |___/  |__,_| |___/  |_| |___|\n");

			}
			//아웃트로 끝
		}
	}
	return 0;
}		//끝