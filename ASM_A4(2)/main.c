#define _CRT_SECURE_NO_WARNINGS

/*��� ������ A �� 16 ����. �� ��������, ������� �������� ������ ��������,
���������� � ������ B (������� �������� �� �������������), � � ������ C
�������� ������ (��������) ���� ���������. ��������� ���������� ����� ���������.*/

#include "stdio.h"
#include "locale.h"

void clear_input() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
	setlocale(LC_ALL, "rus");
	setlocale(LC_NUMERIC, "eng");

	short A[16], B[14];
	int* C[14];
	short B_asm[14];
	int* C_asm[14];
	short input;
	short k = 0, k_asm = 0;

	unsigned tmp = 1, flag = 1;
	while (tmp) {

		for (short i = 0; i < 16; ++i) {
			flag = 1;
			while (flag) {
				printf("������� %hd �������:\n", i + 1);
				if (scanf("%hd", &input) != 1) {
					printf("��������� ���� %hd ��������:\n", i + 1);
					clear_input();
				}
				else if (input < -32768 || input > 32767)
				{
					printf("��������� ���� %hd ��������:\n", i + 1);
				}
				else {
					A[i] = input;
					flag = 0;
				}
			}
		}

		printf("\n\n������� �� ����� ��:\n\n");
		for (short i = 1; i < 15; ++i) {
			if (A[i] == (A[i + 1] + A[i - 1])) {
				B[k] = A[i];
				*(C + k) = &A[i];
				k++;
			}
		}
		printf("���������� ���������: %hd\n", k);
		if (k == 0) {
			printf("������� � � � ������");
		}
		else {
			printf("������ B:\n");
			for (short i = 0; i < k; ++i) {
				printf("%hd ", B[i]);
			}
			printf("\n������ C:\n");
			for (short i = 0; i < k; ++i) {
				printf("%p ", C[i]);
			}
		}
		printf("\n____________________\n");
		printf("\n\n������� �� ����������:\n\n");
		__asm {
			;
			lea esi, A;
			lea edi, B_asm;
			lea ebx, C_asm;
			mov k_asm, 0;
			xor ecx, ecx;
			;
		NEXT: cmp ecx, 14;
			jae DONE;
			mov ax, [esi + 2];
			mov dx, [esi + 4];
			add dx, [esi];
			cmp ax, dx;
			jne NOT_EQ;
			mov[edi], ax;
			add esi, 2;
			mov[ebx], esi;
			sub esi, 2;
			add ebx, 4;
			add edi, 2;
			inc k_asm;
		NOT_EQ:
			inc ecx;
			add esi, 2;
			;
			jmp NEXT;
		DONE:
			nop;
		}
		printf("���������� ���������: %hd\n", k_asm);
		if (k == 0) {
			printf("������� �_asm � �_asm ������");
		}
		else {
			printf("������ B_asm:\n");
			for (short i = 0; i < k_asm; ++i) {
				printf("%hd ", (short)B_asm[i]);
			}
			printf("\n������ C_asmm:\n");
			for (short i = 0; i < k_asm; ++i) {
				printf("%p ", C_asm[i]);
			}
		}
		printf("\n____________________\n");


		clear_input();

		printf("������ ����������?\n0 - ���\n1 - ��\n");

		int term = 1;
		while (term == 1) {
			if (scanf("%d", &tmp) != 1 || (tmp != 0 && tmp != 1)) {
				printf("������� �������� ��������\n");
				printf("������ ����������?\n0 - ���\n1 - ��\n");
				clear_input();
			}
			else {
				term = 0;
				flag = 1;
			}
		}
	}

	exit();
}