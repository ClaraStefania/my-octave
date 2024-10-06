// Copyright Stefania-Clara Diaconescu 313CAb 2023-2024

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DIE(assertion, call_description)                                      \
	do {                                                                      \
		if (assertion) {                                                      \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                \
			perror(call_description);                                         \
			exit(errno);                                                      \
		}                                                                     \
	} while (0)

void aloc_lin_col(int **lin, int **col, int nr_mat, int *cap_linii_coloane)
{
	int *verif1, *verif2;
	if (nr_mat == 0) {
		//Daca vectorii nu au fost alocati, ii aloca, iar capacitatea e 1.
		//In cazul in care nu se pot aloca, se afiseaza mesajul de eroare si
		//se iese din functie.
		*lin = (int *)malloc(1 * sizeof(int));
		*col = (int *)malloc(1 * sizeof(int));
		DIE(!(*lin), "Alocarea vectorului linii a esuat\n");
		DIE(!(*col), "Alocarea vectorului coloanea esuat\n");
		*cap_linii_coloane = 1;

	} else if (nr_mat > *cap_linii_coloane - 1) {
		// Daca e nevoie sa fie realocati, se dubleaza capacitatea.
		// In cazul in care nu se pot realoca, se afiseaza mesajul de eroare si
		// se iese din functie.
		*cap_linii_coloane *= 2;

		verif1 = realloc(*lin, *cap_linii_coloane * sizeof(int));
		DIE(!verif1, "Realocarea vectorului linii a esuat\n");
		*lin = verif1;

		verif2 = (int *)realloc(*col, *cap_linii_coloane * sizeof(int));
			DIE(!verif2, "Realocarea vectorului coloane a esuat\n");
		*col = verif2;
	}
}

void eliberare(int m, int **mat)
{
	// Functia elibereaza memoria alocata dinamic pentru o matrice.
	// Se elibereaza liniile, apoi matricea.
	int i;
	for (i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
}

void realoc(int ****mat, int nr_mat, int *cap)
{
	// Functia realoca matricea.
	// Daca nu se poate face realocarea, se afiseaza mesajul de eroare si se
	// iese din functie.
	int ***verif;
	if (*cap == 0) {
		*cap = 1;
		verif = (int ***)malloc(1 * sizeof(int **));
	} else {
		while (nr_mat > *cap - 1)
			*cap *= 2;
		verif = (int ***)realloc((*mat), *cap * sizeof(int **));
	}
	if (!verif) {
		printf("Realocarea matricei a esuat\n");
		*mat = NULL;
		return;
	}
	*mat = verif;
}

void aloc_mat(int ***mat, int m, int n)
{
	// Functia aloca matricea fara sa o bage in vectorul de matrice.
	int i, j;
	(*mat) = malloc(m * sizeof(int *));
	if (!(*mat)) {
		free(*mat);
		*mat = NULL;
		return;
	}

	// Daca se poate aloca matricea, se aloca fiecare linie in parte.
	// Daca o linie nu se poate aloca, se elibereaza toate cele deja alocate.
	for (i = 0; i < m; i++) {
		(*mat)[i] = malloc(n * sizeof(int));

		if (!(*mat)[i]) {
			for (j = 0; j < i - 1; j++)
				free((*mat)[j]);
			free((*mat));
			*mat = NULL;
		}
	}
}

void aloc(int n, int m, int ****mat, int nr_mat, int *cap, int *lin)
{
	int i, j;
	// Functia aloca matricea si o adauga la finalul vectorului de matrice.
	// Daca nu se poate aloca, se va afisa un mesaj si se va elibera ce a fost
	// alocat anterior.

	realoc(mat, nr_mat, cap);

	(*mat)[nr_mat] = (int **)malloc(m * sizeof(int *));
	if (!(*mat)[nr_mat]) {
		printf("Alocarea matricei a esuat\n");

		for (i = 0; i <= nr_mat; i++)
			free((*mat)[i]);
		free((*mat));

		*mat = NULL;
		return;
	}

	for (i = 0; i < m; i++) {
		(*mat)[nr_mat][i] = (int *)malloc(n * sizeof(int));
		if (!(*mat)[nr_mat][i]) {
			printf("Alocarea liniei a esuat\n");

			for (j = 0; j < i; j++)
				free((*mat)[nr_mat][j]);

			for (j = 0; j < nr_mat; j++)
				eliberare(lin[j], (*mat)[j]);
			free((*mat));

			*mat = NULL;
		}
	}
}

void citire(int n, int m, int ***mat, int nr_mat)
{
	// Functia citeste matricea.
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &mat[nr_mat][i][j]);
}

void afisare(int m, int n, int **mat)
{
	// Functia afiseaza matricea.
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

void redimensionare(int **lin, int **col, int *nr_mat, int ****mat)
{
	int index;
	scanf("%d", &index);
	int *v_lin, *v_col, nr_l, nr_c, i, **aux, j;

	// Se citeste indexul matricei ce va fi redimensionata.

	// Se citesc numarul de linii si cei n indici care vor fi salvati
	// int-un vector.

	scanf("%d", &nr_l);
	v_lin = (int *)malloc(nr_l * sizeof(int));
	for (i = 0; i < nr_l; i++)
		scanf("%d", &v_lin[i]);

	// Se citesc numarul de coloane si cei n indici care vor fi salvati
	// int-un vector.

	scanf("%d", &nr_c);
	v_col = (int *)malloc(nr_c * sizeof(int));
	for (i = 0; i < nr_c; i++)
		scanf("%d", &v_col[i]);

	// Se realizeaza intersectia acestora ce va fi salvata intr-o matrice care
	// va fi adaugata in locul celei vechi.

	if (index > *nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		aloc_mat(&aux, nr_l, nr_c);

		for (i = 0; i < nr_l; i++)
			for (j = 0; j < nr_c; j++)
				aux[i][j] = (*mat)[index][v_lin[i]][v_col[j]];

		eliberare((*lin)[index], (*mat)[index]);
		(*lin)[index] = nr_l;
		(*col)[index] = nr_c;
		(*mat)[index] = aux;
	}

	// La final se elibereaza vectorii de linii si de coloane.
	free(v_lin);
	free(v_col);
}

int t_inm(int l, int c, int n, int **mat1, int **mat2)
{
	// Functia calculeaza separat fiecare element al matricei.
	int s = 0, i;
	for (i = 0; i < n; i++) {
		s += mat1[l][i] * mat2[i][c];
		s %= 10007;
	}
	if (s < 0)
		s += 10007;

	return s;
}

void inm(int ***mat1, int ***mat2, int ***aux, int m, int n, int lin2)
{
	// Prin intermediul unei matrice auxiliare se face inmultirea matricelor
	// date. La final memoria alocata matricei auxiliare este eliberata.
	int i, j, **aux2;
	aloc_mat(&aux2, m, n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			aux2[i][j] = t_inm(i, j, lin2, *mat1, *mat2);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			(*aux)[i][j] = aux2[i][j];

	eliberare(m, aux2);
}

void inmultire(int ****mat, int *nr_mat, int *cap, int **lin, int **col,
			   int *cap_linii_coloane)
{
	int ind1, ind2; // ind = index
	scanf("%d%d", &ind1, &ind2);
	if (ind1 > *nr_mat || ind2 > *nr_mat || ind1 < 0 || ind2 < 0) {
		// Se verifica daca indexul corespunde unei matrice.
		printf("No matrix with the given index\n");
	} else if ((*col)[ind1] != (*lin)[ind2]) {
		// Se verifica daca se poate realiza inmultirea.
		printf("Cannot perform matrix multiplication\n");
	} else {
		// Daca toate conditiile sunt indeplinite, se realizeaza inmultirea,
		// iar matricea este adaugata la finalul vectorului.
		*nr_mat = *nr_mat + 1;
		aloc_lin_col(&(*lin), &(*col), *nr_mat, cap_linii_coloane);
		(*lin)[*nr_mat] = (*lin)[ind1];
		(*col)[*nr_mat] = (*col)[ind2];

		aloc((*col)[ind2], (*lin)[ind1], mat, *nr_mat, cap, *lin);
		inm(&(*mat)[ind1], &(*mat)[ind2], &(*mat)[*nr_mat], (*lin)[ind1],
			(*col)[ind2], (*lin)[ind2]);
	}
}

int suma_elem(int m, int n, int **mat)
{
	// Functia realizeaza suma elementelor unei matrice date.
	int s = 0, i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			s += mat[i][j];

	s %= 10007;
	if (s < 0)
		s += 10007;

	return s;
}

void sortare(int *lin, int *col, int nr_mat, int ****mat)
{
	// Functia ordoneaza matricele in functie de suma elementelor.
	int *sume, i, j, **aux1, aux2;
	// Se calculeaza sumele si sunt salvate intr-un vector.
	sume = (int *)malloc((nr_mat + 1) * sizeof(int));
	if (!sume)
		return;

	for (i = 0; i <= nr_mat; i++)
		sume[i] = suma_elem(lin[i], col[i], (*mat)[i]);

	for (i = 0; i < nr_mat; i++)
		for (j = 0; j < nr_mat - i; j++) {
			if (sume[j] > sume[j + 1]) {
				aux2 = sume[j];
				sume[j] = sume[j + 1];
				sume[j + 1] = aux2;

				aux1 = (*mat)[j];
				(*mat)[j] = (*mat)[j + 1];
				(*mat)[j + 1] = aux1;

				aux2 = lin[j];
				lin[j] = lin[j + 1];
				lin[j + 1] = aux2;

				aux2 = col[j];
				col[j] = col[j + 1];
				col[j + 1] = aux2;
			}
		}
	free(sume);
}

void transpunere(int *nr_mat, int ****mat, int **lin, int **col)
{
	// Functia transpune matricea data si o pune in locul celei vechi.
	int index, i, j, **aux, aux2;
	scanf("%d", &index);
	// Se verifica daca indexul citit corespunde unei matrice.
	if (index > *nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		aux2 = (*lin)[index];
		(*lin)[index] = (*col)[index];
		(*col)[index] = aux2;
		aloc_mat(&aux, (*lin)[index], (*col)[index]);

		for (i = 0; i < (*lin)[index]; i++)
			for (j = 0; j < (*col)[index]; j++)
				aux[i][j] = (*mat)[index][j][i];

		eliberare((*col)[index], (*mat)[index]);
		(*mat)[index] = aux;
	}
}

void stergere(int ****mat, int *nr_mat, int **lin, int **col, int *cap_lin_col,
			  int *cap)
{
	// Functia elibereaza memoria ocupata de matricea cu indexul dat si
	// deplaseaza restul matricelor cu o pozitie.
	int index, i;
	scanf("%d", &index);
	if (index > *nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		eliberare((*lin)[index], (*mat)[index]);

		for (i = index; i < *nr_mat; i++) {
			(*mat)[i] = (*mat)[i + 1];
			(*lin)[i] = (*lin)[i + 1];
			(*col)[i] = (*col)[i + 1];
		}
		(*nr_mat)--;

		if (*nr_mat < ((*cap) / 2)) {
			*cap /= 2;
			*cap_lin_col /= 2;
			*mat = realloc(*mat, *cap * sizeof(int **));
			*lin = realloc(*lin, *cap_lin_col * sizeof(int));
			*col = realloc(*col, *cap_lin_col * sizeof(int));
		}
	}
}

void ridicare(int ****mat, int **lin, int **col, int *nr_mat)
{
	// Functia ridica matricea la puterea data in timp logaritmic.
	int index, i, j, exp = 0;
	scanf("%d%d", &index, &exp);
	if (index > *nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else if (exp < 0) {
		printf("Power should be positive\n");
	} else if ((*col)[index] != (*lin)[index]) {
		printf("Cannot perform matrix multiplication\n");
	} else if (exp == 0) {
		// Daca exponentul este 0, matricea va deveni matricea identitate.
		for (i = 0; i < (*col)[index]; i++)
			for (j = 0; j < (*col)[index]; j++) {
				if (i == j)
					(*mat)[index][i][j] = 1;
				else
					(*mat)[index][i][j] = 0;
			}
	} else {
		int **aux;
		aloc_mat(&aux, (*col)[index], (*col)[index]);

		for (i = 0; i < (*col)[index]; i++)
			for (j = 0; j < (*col)[index]; j++)
				if (i == j)
					aux[i][j] = 1;
				else
					aux[i][j] = 0;

		while (exp > 0) {
			if (exp % 2 == 1) // Verifica daca exponentul este impar.
				inm(&aux, &(*mat)[index], &aux, (*col)[index], (*col)[index],
					(*col)[index]);

			// Daca exponentul devine 0, se iese din while. Altfel, se ridica
			// matricea la patrat.
			inm(&(*mat)[index], &(*mat)[index], &(*mat)[index], (*col)[index],
				(*col)[index], (*col)[index]);
				exp /= 2;
		}

		for (i = 0; i < (*col)[index]; i++)
			for (j = 0; j < (*col)[index]; j++)
				(*mat)[index][i][j] = aux[i][j];

		eliberare((*col)[index], aux);
	}
}

void adunare(int **mat1, int **mat2, int ***rez, int lin)
{
	// Functia aduna doua matrice.
	int i, j;
	for (i = 0; i < lin; i++)
		for (j = 0; j < lin; j++) {
			(*rez)[i][j] = mat1[i][j] + mat2[i][j];
			(*rez)[i][j] %= 10007;

			if ((*rez)[i][j] < 0)
				(*rez)[i][j] += 10007;
		}
}

void scadere(int **mat1, int **mat2, int ***rez, int lin)
{
	// Functia scade doua matrice.
	int i, j;
	for (i = 0; i < lin; i++)
		for (j = 0; j < lin; j++) {
			(*rez)[i][j] = mat1[i][j] - mat2[i][j];
			(*rez)[i][j] %= 10007;

			if ((*rez)[i][j] < 0)
				(*rez)[i][j] += 10007;
		}
}

void strassen(int **mat1, int **mat2, int ***mat3, int dim)
{	// Functia realizeaza algoritmul lui Strassen.
	if (dim == 1) {
		(*mat3)[0][0] = mat1[0][0] * mat2[0][0];
	} else {
		int dim2 = dim / 2, i, j, **D2;
		int **A11, **A12, **A21, **A22, **B11, **B12, **B21, **B22, **M1, **M2;
		int **M3, **M4, **M5, **M6, **M7, **C11, **C22, **C21, **C12, **D1;
		aloc_mat(&A11, dim2, dim2); aloc_mat(&A12, dim2, dim2);
		aloc_mat(&A21, dim2, dim2); aloc_mat(&A22, dim2, dim2);
		aloc_mat(&B11, dim2, dim2); aloc_mat(&B12, dim2, dim2);
		aloc_mat(&B21, dim2, dim2); aloc_mat(&B22, dim2, dim2);
		aloc_mat(&C11, dim2, dim2); aloc_mat(&C12, dim2, dim2);
		aloc_mat(&C21, dim2, dim2); aloc_mat(&C22, dim2, dim2);
		aloc_mat(&D1, dim2, dim2); aloc_mat(&D2, dim2, dim2);
		aloc_mat(&M1, dim2, dim2); aloc_mat(&M2, dim2, dim2);
		aloc_mat(&M3, dim2, dim2); aloc_mat(&M4, dim2, dim2);
		aloc_mat(&M5, dim2, dim2); aloc_mat(&M6, dim2, dim2);
		aloc_mat(&M7, dim2, dim2);
		for (i = 0; i < dim2; i++)
			for (j = 0; j < dim2; j++) {
				A11[i][j] = mat1[i][j];
				A12[i][j] = mat1[i][j + dim2];
				A21[i][j] = mat1[i + dim2][j];
				A22[i][j] = mat1[i + dim2][j + dim2];
				B11[i][j] = mat2[i][j];
				B12[i][j] = mat2[i][j + dim2];
				B21[i][j] = mat2[i + dim2][j];
				B22[i][j] = mat2[i + dim2][j + dim2];
			} // Matricele sunt impartite in matrice blocuri.
		adunare(A11, A22, &D1, dim2);
		adunare(B11, B22, &D2, dim2);
		strassen(D1, D2, &M1, dim2);

		adunare(A21, A22, &D1, dim2);
		strassen(D1, B11, &M2, dim2);

		scadere(B12, B22, &D2, dim2);
		strassen(A11, D2, &M3, dim2);

		scadere(B21, B11, &D2, dim2);
		strassen(A22, D2, &M4, dim2);

		adunare(A11, A12, &D1, dim2);
		strassen(D1, B22, &M5, dim2);

		scadere(A21, A11, &D1, dim2);
		adunare(B11, B12, &D2, dim2);
		strassen(D1, D2, &M6, dim2);

		scadere(A12, A22, &D1, dim2);
		adunare(B21, B22, &D2, dim2);
		strassen(D1, D2, &M7, dim2);

		adunare(M1, M4, &D1, dim2);
		scadere(D1, M5, &D2, dim2);
		adunare(D2, M7, &C11, dim2);
		adunare(M3, M5, &C12, dim2);
		adunare(M2, M4, &C21, dim2);
		scadere(M1, M2, &D1, dim2);
		adunare(M3, M6, &D2, dim2);
		adunare(D1, D2, &C22, dim2);
		for (i = 0; i < dim2; i++)
			for (j = 0; j < dim2; j++) {
				(*mat3)[i][j] = C11[i][j];
				(*mat3)[i][j + dim2] = C12[i][j];
				(*mat3)[i + dim2][j] = C21[i][j];
				(*mat3)[i + dim2][j + dim2] = C22[i][j];
			}
		eliberare(dim2, A11); eliberare(dim2, A12);
		eliberare(dim2, A21); eliberare(dim2, A22);
		eliberare(dim2, B11); eliberare(dim2, B12);
		eliberare(dim2, B21); eliberare(dim2, B22);
		eliberare(dim2, C11); eliberare(dim2, C12);
		eliberare(dim2, C21); eliberare(dim2, C22);
		eliberare(dim2, D1); eliberare(dim2, D2);
		eliberare(dim2, M1); eliberare(dim2, M2);
		eliberare(dim2, M3); eliberare(dim2, M4);
		eliberare(dim2, M5); eliberare(dim2, M6);
		eliberare(dim2, M7);
	}
}

int main(void)
{
	int ***mat, n, m, nr_mat = -1, *cap, *lin, *col, i, index;
	int *cap_linii_coloane, capacitate = 0, capacitatem = 0;
	// cap = capacitate
	// mat = vectorul in care sunt salvate matricele
	char l;

	cap_linii_coloane = &capacitate;
	cap = &capacitatem;
	scanf("%c", &l);
	while (l != 'Q') {
		if (l == 'L') {
			nr_mat++;
			scanf("%d%d", &m, &n);
			aloc_lin_col(&lin, &col, nr_mat, cap_linii_coloane);
			lin[nr_mat] = m;
			col[nr_mat] = n;
			aloc(n, m, &mat, nr_mat, cap, lin);
			citire(n, m, mat, nr_mat);
			if (!mat)
				break;
		} else if (l == 'D') {
			scanf("%d", &index);
			if (index > nr_mat || index < 0)
				printf("No matrix with the given index\n");
			else
				printf("%d %d\n", lin[index], col[index]);
		} else if (l == 'P') {
			scanf("%d", &index);
			if (index > nr_mat || index < 0)
				printf("No matrix with the given index\n");
			else
				afisare(lin[index], col[index], mat[index]);
		} else if (l == 'C') {
			redimensionare(&lin, &col, &nr_mat, &mat);
		} else if (l == 'M') {
			inmultire(&mat, &nr_mat, cap, &lin, &col, cap_linii_coloane);
		} else if (l == 'O') {
			sortare(lin, col, nr_mat, &mat);
		} else if (l == 'F') {
			stergere(&mat, &nr_mat, &lin, &col, cap_linii_coloane, cap);
		} else if (l == 'T') {
			transpunere(&nr_mat, &mat, &lin, &col);
		} else if (l == 'R') {
			ridicare(&mat, &lin, &col, &nr_mat);
		} else if (l == 'S') {
			int ind1, ind2;
			scanf("%d%d", &ind1, &ind2);
			if (ind1 > nr_mat || ind2 > nr_mat || ind1 < 0 || ind2 < 0) {
				printf("No matrix with the given index\n");
			} else if (col[ind1] != lin[ind2]) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				int dim = lin[ind2];
				nr_mat++;
				aloc_lin_col(&lin, &col, nr_mat, cap_linii_coloane);
				lin[nr_mat] = dim;
				col[nr_mat] = dim;
				aloc(dim, dim, &mat, nr_mat, cap, lin);
				strassen(mat[ind1], mat[ind2], &mat[nr_mat], dim);
			}
		} else if (l >= 'A' && l <= 'Z') {
			printf("Unrecognized command\n");
		}
		scanf("\n");
		scanf("%c", &l);
	}
	// La final se elibereaza vectorul de matrice.
	if (nr_mat >= 0) {
		for (i = 0; i <= nr_mat; i++)
			eliberare(lin[i], (mat)[i]);
		free(mat);
	}
	free(lin);
	free(col);
	return 0;
}
