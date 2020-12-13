#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>


void gotoxy(int x, int y); //gotoxy 함수 정의
void clear_GUI(); //화면 초기화 함수
void set_menu_UI(); //메뉴 화면 구현 함수
void menu_select(int *); //메뉴 선택 함수
void game_rule(); //메뉴 - 2.게임 설명
void gen_answer(int *); //정답 난수 생성
void game_start(int *); // 메뉴 - 1.게임 시작

int main(void)
{
	while (1)
	{
		int answer[4] = { 0, 0, 0, 0 }; //정답 배열 생성
		while (1)
		{
			int menu = 1; //기본 메뉴 GUI 1
			set_menu_UI(); //메뉴 화면 구현
			menu_select(&menu); //메뉴 선택

			if (menu == 2) //2번 선택
			{
				game_rule(); //2.게임 설명
			}

			if (menu == 1) //1번 선택
			{
				break; //1.게임 시작
			}

			if (menu == 3) //3번 선택
			{
				exit(0); //3.게임 종료
			}
		}
		gen_answer(answer); //정답 생성
		game_start(answer); //게임 시작
		_getch();//입력 퍼즈
	}
	return 0;
}

void set_menu_UI() //메뉴화면 GUI구현
{
	int i;
	system("mode con cols=78 lines=21"); 

	for (i = 0; i < 39; i++)		
	{
		gotoxy(i, 0); printf("■");
		gotoxy(i, 20); printf("■");
	}
	for (i = 1; i < 20; i++)
	{
		gotoxy(0, i); printf("■");
		gotoxy(38, i); printf("■");
	}

	gotoxy(15, 5); printf("▩  숫자야구  ▩");
	gotoxy(17, 10); printf("게임시작");
	gotoxy(17, 12); printf("게임설명");
	gotoxy(17, 14); printf("게임종료");
}
void clear_GUI() //화면 초기화
{
	int i, j;
	for (i = 1; i < 37; i++)
	{
		for (j = 1; j < 19; j++)
		{
			gotoxy(i, j); printf("  ");
		}
	}
}
void menu_select(int* i)
{
	int key = 0, j;

	while (1)
	{
		//-------------------------------------------- 선택 커서 이동
		for (j = 0; j < 5; j += 2)
		{
			gotoxy(16, 10 + j); printf(" ");
			gotoxy(21, 10 + j); printf("  ");
		}
		
		gotoxy(16, 10 + 2 * (*i - 1)); printf(">");
		gotoxy(21, 10 + 2 * (*i - 1)); printf(" <");
		//--------------------------------------------

		//-------------------------------------------- 키보드 입력
		key = _getch();
		if (key == 224) //방향키일 때
		{
			key = _getch();
			if (key == 80 || key == 77) //아래 방향키 또는 우측 방향키일 경우
			{
				*i += 1; //커서를 1개 내림
			}
			else if (key == 72 || key == 75) //위 방향키 또는 좌측 방향키인 경우
			{
				*i -= 1; //커서를 1개 올림
			}
		}
		else
		{
			if (key == 13) //enter키 일 경우
				break;
		}

		if (*i == 4) //커서 위치가 끝을 넘어간 경우
		{
			*i = 1; //첫번째로 이동
		}

		if (*i == 0) //커서 위치가 처음을 넘어간 경우
		{
			*i = 3; //마지막으로 이동
		}
	}
	
}
void gen_answer(int * answer)
{
	srand(time(NULL)); //초마다 난수 초기화

	int i, j;
	for (i = 0; i < 4; i++)
	{
		answer[i] = (rand() % 9) + 1; //1~9 난수 생성하여 answer배열에 차례로 입력

		for (j = 0; j < i; j++) //만약 생성된 난수가 중복될 경우 감지
		{
			if (answer[i] == answer[j])
			{
				i--; //난수 다시 실행
			}
		}
	}
}
void game_start(int * answer)
{
	int Input[4] = { 0, 0, 0, 0 }; //인풋 배열
	int Input_num; //인풋 입력 변수
	int count = 1; //회차 감지 변수
	int s, b; //스트라이크, 볼 변수
	int i, j; //반복 변수

	clear_GUI(); //화면 초기화
	for (i = 0; i < 9; i++) //생명력 GUI설정
	{
		gotoxy(36, 2 + 2*i); printf("♥");
	}
	
	//printf("%d%d%d%d", answer[0], answer[1], answer[2], answer[3]); //정답 확인 테스트용

	while (1)
	{
		while (1)
		{
			gotoxy(15, 3); printf("▩ %d번째 회차 ▩", count++); //GUI설정
			gotoxy(3, 18); printf("4자리 숫자를 입력해주세요: ");
			gotoxy(17, 18); scanf_s("%d", &Input_num); //인풋
			gotoxy(17, 18); printf("                                      ");
			Input[0] = Input_num / 1000; //인풋 배열에 자리수별로 분리하여 저장
			Input[1] = (Input_num % 1000) / 100;
			Input[2] = (Input_num % 100) / 10;
			Input[3] = Input_num % 10;

			//----------------------------------------------- 입력 수가 정상적인지 판별
			int same = 0;
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					if (Input[i] == Input[j])
					{
						same++;
					}
						
				}
			}
			
			if (same != 4)
			{
				count--;
				gotoxy(23, 18); printf("(잘못된 입력입니다)");
			}

			else if (1111 < Input_num && Input_num < 9999)
			{
				break;
			}

			else
			{
				count--;
				gotoxy(23, 18); printf("(잘못된 입력입니다)");
			}
			//-----------------------------------------------
		}

		//----------------------------------------------- 스트라이크, 볼 판별
		s = 0, b = 0;
		for (i = 0; i < 4; i++)
		{
			if (Input[i] == answer[i])
			{
				s++;
			}

			else
			{
				for (j = 0; j < 4; j++)
				{
					if (Input[i] == answer[j])
					{
						b++;
					}
				}
			}

		}
		//-----------------------------------------------

		if (s == 4) //정답일 경우
		{
			clear_GUI();
			gotoxy(15, 3); printf("▩  게임 클리어  ▩");
			gotoxy(18, 6); printf("<정답>");
			gotoxy(17, 8); printf("%d  %d  %d  %d", answer[0], answer[1], answer[2], answer[3]);
			gotoxy(14, 10); printf("<클리어까지 걸린 회차>");
			gotoxy(18, 12); printf("%d 회차", count - 1);

			gotoxy(13, 16); printf("아무 버튼이나 입력해주세요");
					
			break;
		}

		else //볼, 스트라이크 출력
		{
			gotoxy(5, 18);  printf("스트라이크: %d  볼: %d\n", s, b);
			if (count < 7)
			{
				gotoxy(5, 7 + 2 * (count - 2));  printf("%d %d %d %d     S: %d  B: %d\n", Input[0], Input[1], Input[2], Input[3], s, b);
			}
			else
			{
				gotoxy(22, 7 + 2 * (count - 7));  printf("%d %d %d %d     S: %d  B: %d\n", Input[0], Input[1], Input[2], Input[3], s, b);
			}
			gotoxy(36, 2 * (count - 1)); printf("  ");
		}

		if (count == 10) //생명력 소진으로 인한 게임 오버
		{
			clear_GUI();
			gotoxy(15, 3); printf("▩  게임  오버  ▩");
			gotoxy(18, 6); printf("<정답>");
			gotoxy(17, 8); printf("%d  %d  %d  %d", answer[0], answer[1], answer[2], answer[3]);
			gotoxy(13, 16); printf("아무 버튼이나 입력해주세요");
			break;
		}
	}
}
void game_rule()
{
	int i;
	for (i = 0; i < 39; i++)
	{
		gotoxy(i, 0); printf("■");
		gotoxy(i, 20); printf("■");
	}
	for (i = 1; i < 20; i++)
	{
		gotoxy(0, i); printf("■");
		gotoxy(38, i); printf("■");
	}
	
	gotoxy(15, 5); printf("▩  추후 구현  ▩");
	gotoxy(16, 12); printf(" ");
	gotoxy(21, 12); printf("  ");
	gotoxy(17, 10); printf("언젠가는");
	gotoxy(17, 12); printf("구현하기");
	gotoxy(8, 14); printf("규칙 쓰기가 귀찮다 언젠가는 구현하겠지 뭐");
	gotoxy(10, 16); printf("아무 버튼이나 누르면 나가진다");
	
	_getch();
}
void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
