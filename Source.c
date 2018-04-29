#include < stdio.h >
#include < stdlib.h >

int sudoku[81];                                // �ƿW�D�ذ}�C
int tempNum[81];                               // �W�@����Ʀ�m
int tempSp = 0;                                 // �W�@����Ʀ�m����
int startH[81];                                // �C��m���_�I
int startV[81];                                // ���m���_�I
int startB[81];                                // �E�c���m���_�I
int addH[9];                                   // �C��m���[��
int addV[9];                                   // ���m���[��
int addB[9];                                   // �E�c���m���[��

int main(int argc, char *argv[]) {
	int j;
	if (argc>1) for (j = 0; j<81; j++) sudoku[j] = argv[1][j] - '0';
	else exit(0);
	printf("------------------\n");
	printSudoku(sudoku);
	init();                                     // �ѼƳ]�w
	tryAns();                                   // ���ըD��
	printf("------------------\n");
	printSudoku(sudoku);
	printf("------------------\n");
}

int init() {
	// �ѼƳ]�w(�]�w�o�ǰѼƤ���A�L���ˬd��B�C�B�E�c�泣��K�h�F)
	int i;
	for (i = 0; i<81; i++) {
		startH[i] = i / 9 * 9;                       // �C��m���_�I
		startV[i] = i % 9;                         // ���m���_�I
		startB[i] = ((i / 9) / 3) * 27 + ((i % 9) / 3) * 3;    // �E�c���m���_�I
	}
	for (i = 0; i<9; i++) {
		addH[i] = i;                              // �C��m���[��
		addV[i] = i * 9;                            // ���m���[��
		addB[i] = (i / 3) * 9 + (i % 3);                 // �E�c���m���[��
	}
}

int printSudoku(int *prn) {
	// �L�X�ƿW�D��(�}�C���e)
	int i;
	for (i = 0; i<81; i++) {
		printf("%2d", prn[i]);
		if (i % 9 == 8) printf("\n");
	}
}

int tryAns() {
	// ���ըD��
	int sp = getNextBlank(-1);                    // ���o�Ĥ@�Ӫťժ���m�}�l��J�Ʀr
	do {
		sudoku[sp]++;                            // �N����m�Ʀr�[ 1
		if (sudoku[sp]>9) {                        // �p�G����m���Ʀr�w�j�� 9 �ɫh�^��W�@�Ӧ�m�~�����
			sudoku[sp] = 0;
			sp = pop();
		}
		else {
			if (check(sp) == 0) {                     // �p�G�P��B�C�B�E�c�泣�S���ۦP���Ʀr�A�h��U�@�ӪťճB�~��
				push(sp);                          // ��M�A�p�G�o�{���ۦP���Ʀr�ɡA�N�ݧ���m���Ʀr�[ 1(�ҥH���B���򳣤���)
				sp = getNextBlank(sp);
			}
		}
	} while (sp >= 0 && sp<81);
}

int getNextBlank(int sp) {
	// ���o�U�@�Ӫťժ���m
	do {
		sp++;
	} while (sp<81 && sudoku[sp]>0);
	return(sp);
}

int check(int sp) {
	// �ˬd�P��B�C�B�E�c�榳�S���ۦP���Ʀr�A�Y���Ǧ^ 1
	int fg = 0;
	if (!fg) fg = check1(sp, startH[sp], addH);   // �ˬd�P�C���S���ۦP���Ʀr
	if (!fg) fg = check1(sp, startV[sp], addV);   // �ˬd�P�榳�S���ۦP���Ʀr
	if (!fg) fg = check1(sp, startB[sp], addB);   // �ˬd�P�E�c�榳�S���ۦP���Ʀr
	return(fg);
}

int check1(int sp, int start, int *addnum) {
	// �ˬd���w����B�C�B�E�c�榳�S���ۦP���Ʀr�A�Y���Ǧ^ 1
	int fg = 0, i, sp1;
	for (i = 0; i<9; i++) {
		sp1 = start + addnum[i];
		if (sp != sp1 && sudoku[sp] == sudoku[sp1]) fg++;
	}
	return(fg);
}

int push(int sp) {
	// �N���w����m��J���|��
	tempNum[tempSp++] = sp;
}

int pop() {
	// ���X���|�����W�@�Ӧ�m
	if (tempSp <= 0) return(-1);
	else return(tempNum[--tempSp]);
}