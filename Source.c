#include < stdio.h >
#include < stdlib.h >

int sudoku[81];                                // 计縒肈ヘ皚
int tempNum[81];                               // Ω恶计竚
int tempSp = 0;                                 // Ω恶计竚夹
int startH[81];                                // 竚癬翴
int startV[81];                                // ︽竚癬翴
int startB[81];                                // 甤竚癬翴
int addH[9];                                   // 竚
int addV[9];                                   // ︽竚
int addB[9];                                   // 甤竚

int main(int argc, char *argv[]) {
	int j;
	if (argc>1) for (j = 0; j<81; j++) sudoku[j] = argv[1][j] - '0';
	else exit(0);
	printf("------------------\n");
	printSudoku(sudoku);
	init();                                     // 把计砞﹚
	tryAns();                                   // 代刚―秆
	printf("------------------\n");
	printSudoku(sudoku);
	printf("------------------\n");
}

int init() {
	// 把计砞﹚(砞﹚硂ㄇ把计ぇ礚阶浪琩︽甤常よ獽)
	int i;
	for (i = 0; i<81; i++) {
		startH[i] = i / 9 * 9;                       // 竚癬翴
		startV[i] = i % 9;                         // ︽竚癬翴
		startB[i] = ((i / 9) / 3) * 27 + ((i % 9) / 3) * 3;    // 甤竚癬翴
	}
	for (i = 0; i<9; i++) {
		addH[i] = i;                              // 竚
		addV[i] = i * 9;                            // ︽竚
		addB[i] = (i / 3) * 9 + (i % 3);                 // 甤竚
	}
}

int printSudoku(int *prn) {
	// 计縒肈ヘ(皚ず甧)
	int i;
	for (i = 0; i<81; i++) {
		printf("%2d", prn[i]);
		if (i % 9 == 8) printf("\n");
	}
}

int tryAns() {
	// 代刚―秆
	int sp = getNextBlank(-1);                    // 眔材フ竚秨﹍恶计
	do {
		sudoku[sp]++;                            // 盢セ竚计 1
		if (sudoku[sp]>9) {                        // 狦セ竚计 9 玥竚膥尿代刚
			sudoku[sp] = 0;
			sp = pop();
		}
		else {
			if (check(sp) == 0) {                     // 狦︽甤常⊿Τ计玥フ矪膥尿
				push(sp);                          // 讽礛狦祇瞷Τ计碞惠р竚计 1(┮セ矪ぐ或常ぃ暗)
				sp = getNextBlank(sp);
			}
		}
	} while (sp >= 0 && sp<81);
}

int getNextBlank(int sp) {
	// 眔フ竚
	do {
		sp++;
	} while (sp<81 && sudoku[sp]>0);
	return(sp);
}

int check(int sp) {
	// 浪琩︽甤Τ⊿Τ计璝Τ肚 1
	int fg = 0;
	if (!fg) fg = check1(sp, startH[sp], addH);   // 浪琩Τ⊿Τ计
	if (!fg) fg = check1(sp, startV[sp], addV);   // 浪琩︽Τ⊿Τ计
	if (!fg) fg = check1(sp, startB[sp], addB);   // 浪琩甤Τ⊿Τ计
	return(fg);
}

int check1(int sp, int start, int *addnum) {
	// 浪琩﹚︽甤Τ⊿Τ计璝Τ肚 1
	int fg = 0, i, sp1;
	for (i = 0; i<9; i++) {
		sp1 = start + addnum[i];
		if (sp != sp1 && sudoku[sp] == sudoku[sp1]) fg++;
	}
	return(fg);
}

int push(int sp) {
	// 盢﹚竚帮舼い
	tempNum[tempSp++] = sp;
}

int pop() {
	// 帮舼い竚
	if (tempSp <= 0) return(-1);
	else return(tempNum[--tempSp]);
}