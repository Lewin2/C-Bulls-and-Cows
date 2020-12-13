#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>


void gotoxy(int x, int y); //gotoxy �Լ� ����
void clear_GUI(); //ȭ�� �ʱ�ȭ �Լ�
void set_menu_UI(); //�޴� ȭ�� ���� �Լ�
void menu_select(int *); //�޴� ���� �Լ�
void game_rule(); //�޴� - 2.���� ����
void gen_answer(int *); //���� ���� ����
void game_start(int *); // �޴� - 1.���� ����

int main(void)
{
	while (1)
	{
		int answer[4] = { 0, 0, 0, 0 }; //���� �迭 ����
		while (1)
		{
			int menu = 1; //�⺻ �޴� GUI 1
			set_menu_UI(); //�޴� ȭ�� ����
			menu_select(&menu); //�޴� ����

			if (menu == 2) //2�� ����
			{
				game_rule(); //2.���� ����
			}

			if (menu == 1) //1�� ����
			{
				break; //1.���� ����
			}

			if (menu == 3) //3�� ����
			{
				exit(0); //3.���� ����
			}
		}
		gen_answer(answer); //���� ����
		game_start(answer); //���� ����
		_getch();//�Է� ����
	}
	return 0;
}

void set_menu_UI() //�޴�ȭ�� GUI����
{
	int i;
	system("mode con cols=78 lines=21"); 

	for (i = 0; i < 39; i++)		
	{
		gotoxy(i, 0); printf("��");
		gotoxy(i, 20); printf("��");
	}
	for (i = 1; i < 20; i++)
	{
		gotoxy(0, i); printf("��");
		gotoxy(38, i); printf("��");
	}

	gotoxy(15, 5); printf("��  ���ھ߱�  ��");
	gotoxy(17, 10); printf("���ӽ���");
	gotoxy(17, 12); printf("���Ӽ���");
	gotoxy(17, 14); printf("��������");
}
void clear_GUI() //ȭ�� �ʱ�ȭ
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
		//-------------------------------------------- ���� Ŀ�� �̵�
		for (j = 0; j < 5; j += 2)
		{
			gotoxy(16, 10 + j); printf(" ");
			gotoxy(21, 10 + j); printf("  ");
		}
		
		gotoxy(16, 10 + 2 * (*i - 1)); printf(">");
		gotoxy(21, 10 + 2 * (*i - 1)); printf(" <");
		//--------------------------------------------

		//-------------------------------------------- Ű���� �Է�
		key = _getch();
		if (key == 224) //����Ű�� ��
		{
			key = _getch();
			if (key == 80 || key == 77) //�Ʒ� ����Ű �Ǵ� ���� ����Ű�� ���
			{
				*i += 1; //Ŀ���� 1�� ����
			}
			else if (key == 72 || key == 75) //�� ����Ű �Ǵ� ���� ����Ű�� ���
			{
				*i -= 1; //Ŀ���� 1�� �ø�
			}
		}
		else
		{
			if (key == 13) //enterŰ �� ���
				break;
		}

		if (*i == 4) //Ŀ�� ��ġ�� ���� �Ѿ ���
		{
			*i = 1; //ù��°�� �̵�
		}

		if (*i == 0) //Ŀ�� ��ġ�� ó���� �Ѿ ���
		{
			*i = 3; //���������� �̵�
		}
	}
	
}
void gen_answer(int * answer)
{
	srand(time(NULL)); //�ʸ��� ���� �ʱ�ȭ

	int i, j;
	for (i = 0; i < 4; i++)
	{
		answer[i] = (rand() % 9) + 1; //1~9 ���� �����Ͽ� answer�迭�� ���ʷ� �Է�

		for (j = 0; j < i; j++) //���� ������ ������ �ߺ��� ��� ����
		{
			if (answer[i] == answer[j])
			{
				i--; //���� �ٽ� ����
			}
		}
	}
}
void game_start(int * answer)
{
	int Input[4] = { 0, 0, 0, 0 }; //��ǲ �迭
	int Input_num; //��ǲ �Է� ����
	int count = 1; //ȸ�� ���� ����
	int s, b; //��Ʈ����ũ, �� ����
	int i, j; //�ݺ� ����

	clear_GUI(); //ȭ�� �ʱ�ȭ
	for (i = 0; i < 9; i++) //����� GUI����
	{
		gotoxy(36, 2 + 2*i); printf("��");
	}
	
	//printf("%d%d%d%d", answer[0], answer[1], answer[2], answer[3]); //���� Ȯ�� �׽�Ʈ��

	while (1)
	{
		while (1)
		{
			gotoxy(15, 3); printf("�� %d��° ȸ�� ��", count++); //GUI����
			gotoxy(3, 18); printf("4�ڸ� ���ڸ� �Է����ּ���: ");
			gotoxy(17, 18); scanf_s("%d", &Input_num); //��ǲ
			gotoxy(17, 18); printf("                                      ");
			Input[0] = Input_num / 1000; //��ǲ �迭�� �ڸ������� �и��Ͽ� ����
			Input[1] = (Input_num % 1000) / 100;
			Input[2] = (Input_num % 100) / 10;
			Input[3] = Input_num % 10;

			//----------------------------------------------- �Է� ���� ���������� �Ǻ�
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
				gotoxy(23, 18); printf("(�߸��� �Է��Դϴ�)");
			}

			else if (1111 < Input_num && Input_num < 9999)
			{
				break;
			}

			else
			{
				count--;
				gotoxy(23, 18); printf("(�߸��� �Է��Դϴ�)");
			}
			//-----------------------------------------------
		}

		//----------------------------------------------- ��Ʈ����ũ, �� �Ǻ�
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

		if (s == 4) //������ ���
		{
			clear_GUI();
			gotoxy(15, 3); printf("��  ���� Ŭ����  ��");
			gotoxy(18, 6); printf("<����>");
			gotoxy(17, 8); printf("%d  %d  %d  %d", answer[0], answer[1], answer[2], answer[3]);
			gotoxy(14, 10); printf("<Ŭ������� �ɸ� ȸ��>");
			gotoxy(18, 12); printf("%d ȸ��", count - 1);

			gotoxy(13, 16); printf("�ƹ� ��ư�̳� �Է����ּ���");
					
			break;
		}

		else //��, ��Ʈ����ũ ���
		{
			gotoxy(5, 18);  printf("��Ʈ����ũ: %d  ��: %d\n", s, b);
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

		if (count == 10) //����� �������� ���� ���� ����
		{
			clear_GUI();
			gotoxy(15, 3); printf("��  ����  ����  ��");
			gotoxy(18, 6); printf("<����>");
			gotoxy(17, 8); printf("%d  %d  %d  %d", answer[0], answer[1], answer[2], answer[3]);
			gotoxy(13, 16); printf("�ƹ� ��ư�̳� �Է����ּ���");
			break;
		}
	}
}
void game_rule()
{
	int i;
	for (i = 0; i < 39; i++)
	{
		gotoxy(i, 0); printf("��");
		gotoxy(i, 20); printf("��");
	}
	for (i = 1; i < 20; i++)
	{
		gotoxy(0, i); printf("��");
		gotoxy(38, i); printf("��");
	}
	
	gotoxy(15, 5); printf("��  ���� ����  ��");
	gotoxy(16, 12); printf(" ");
	gotoxy(21, 12); printf("  ");
	gotoxy(17, 10); printf("��������");
	gotoxy(17, 12); printf("�����ϱ�");
	gotoxy(8, 14); printf("��Ģ ���Ⱑ ������ �������� �����ϰ��� ��");
	gotoxy(10, 16); printf("�ƹ� ��ư�̳� ������ ��������");
	
	_getch();
}
void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
