#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

/*Program do transfomracji mi�dzu uk�adami wsp�rz�dnych*/

/* Prototypy funkcji */
double obrot(int n, double k, double r[]);
double sfer2vec(double r[]);
double vec2sfer(double r[]);
double st2rad(double r[]);
double hour2rad(double r[]);
double rad2st(double k, double r[]);
double rad2hour(double k, double r[]);

/* Funkcja g��wna */

int main(void)
{
	double v[3], E[3], AG[3], DG[3], k1[3], k2[3];
	double e, ag, dg, th, t, fi;
	int u1, u2;

	E[1] = 26;
	E[2] = 21.448;
	e = st2rad(E);

	/* Wsp�rz�dne r�wnikowo r�wnonocne dla gal */

	/* Rektascencja */
	AG[0] = 12;
	AG[1] = 51;
	AG[2] = 26.27549;

	ag = hour2rad(AG);

	/* Deklinacja */
	DG[0] = 27;
	DG[1] = 7;
	DG[2] = 42.7043;

	dg = st2rad(DG);

	/* Theta */
	th = 122.93191857 * M_PI / 180.0;

	printf("Program do przeliczania układów wspórzędnych.\nNaciśnij Enter aby rozpocząć.\n");
	while ((getchar()) != 'n')
	{
		printf("Podaj układ poczatkowy 1=Równikowy równonocny 2=Równikowo godzinny 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
		scanf("%d", &u1);

		if (u1 != 1 && u1 != 2 && u1 != 3 && u1 != 4 && u1 != 5)
			printf("Źle wybrany układ!\n");

		else
		{
			printf("Podaj układ końcowy 1=Równikowy równonocny 2=Równikowo godzinny 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
			scanf("%d", &u2);

			if (u2 != 1 && u2 != 2 && u2 != 3 && u2 != 4 && u2 != 5)
				printf("Źle wybrany układ\n");

			else
			{
				if (u1 == u2)
				{
					printf("Wybrano takie same układy odniesienia, dalsze działanie jest bezcelowe.\n");
					break;
				}
				else
				{
					switch (u1)
					{
						/* Start r�wnikowo r�wnonocny */
					case 1:
						printf("Podaj rektascencje (format: h min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						v[0] = hour2rad(k1);

						if (v[0] < 0 || v[0] > 2 * M_PI)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						printf("Podaj deklinację (format: st min sec)\n");
						scanf("%lf %lf %lf", &k2[0], &k2[1], &k2[2]);
						v[1] = st2rad(k2);
						if (v[1] > M_PI / 2 || v[1] < -M_PI / 2)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						sfer2vec(v);

						switch (u2)
						{
						case 2:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("Kąt godzinny: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 3:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							printf("Podaj szerokość geograficzną obserwatora (format st min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							fi = st2rad(k1);
							obrot(2, M_PI / 2 - fi, v);
							obrot(3, -M_PI, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Azymut:%.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Wysokość: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 4:
							obrot(1, e, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Długość ekliptyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szerokość ekliptyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 5:
							obrot(3, M_PI / 2 + ag, v);
							obrot(1, M_PI / 2 - dg, v);
							obrot(3, M_PI / 2 - th, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Długość galaktyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szerokość galaktyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;
						}
						break;

						/* Start r�wnikowo godzinny*/

					case 2:
						printf("Podaj kąt godzinny (format: h min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						v[0] = hour2rad(k1);

						if (v[0] < 0 || v[0] > 2 * M_PI)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						printf("Podaj deklinację (format: st min sec)\n");
						scanf("%lf %lf %lf", &k2[0], &k2[1], &k2[2]);
						v[1] = st2rad(k2);
						if (v[1] > M_PI / 2 || v[1] < -M_PI / 2)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						sfer2vec(v);

						switch (u2)
						{
						case 1:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							v[1] = -v[1];
							obrot(3, -t, v);

							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("Rektascencja: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 3:
							printf("Podaj szeroko�� geograficzn� obserwatora (format st min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							fi = st2rad(k1);
							obrot(2, M_PI / 2 - fi, v);
							obrot(3, -M_PI, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Azymut:%.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Wysoko��: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 4:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}

							v[1] = -v[1];
							obrot(3, -t, v);
							obrot(1, e, v);

							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� ekliptyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� ekliptyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 5:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							v[1] = -v[1];
							obrot(3, -t, v);
							obrot(3, M_PI / 2 + ag, v);
							obrot(1, M_PI / 2 - dg, v);
							obrot(3, M_PI / 2 - th, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� galaktyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� galaktyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;
						}
						break;

						/* Start Horyzontalny*/

					case 3:
						printf("Podaj azymut (format: st min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						v[0] = st2rad(k1);

						if (v[0] < 0 || v[0] > 2 * M_PI)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						printf("Podaj wysoko�� (format: st min sec)\n");
						scanf("%lf %lf %lf", &k2[0], &k2[1], &k2[2]);
						v[1] = st2rad(k2);
						if (v[1] > M_PI / 2 || v[1] < -M_PI / 2)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						sfer2vec(v);
						printf("Podaj szeroko�� geograficzn� obserwatora (format st min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						fi = st2rad(k1);
						obrot(3, M_PI, v);
						obrot(2, fi - M_PI / 2, v);

						switch (u2)
						{
						case 1:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							v[1] = -v[1];
							obrot(3, -t, v);

							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("Rektascencja: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 2:
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("K�t godzinny: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 4:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							v[1] = -v[1];
							obrot(3, -t, v);

							obrot(1, e, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� ekliptyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� ekliptyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 5:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							v[1] = -v[1];
							obrot(3, -t, v);

							obrot(3, M_PI / 2 + ag, v);
							obrot(1, M_PI / 2 - dg, v);
							obrot(3, M_PI / 2 - th, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� galaktyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� galaktyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;
						}
						break;

						/* Start Ekliptyczny*/

					case 4:
						printf("Podaj d�ugo�� ekliptyczn� (format: st min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						v[0] = st2rad(k1);

						if (v[0] < 0 || v[0] > 2 * M_PI)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						printf("Podaj szeroko�� ekliptyczn� (format: st min sec)\n");
						scanf("%lf %lf %lf", &k2[0], &k2[1], &k2[2]);
						v[1] = st2rad(k2);
						if (v[1] > M_PI / 2 || v[1] < -M_PI / 2)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						sfer2vec(v);
						obrot(1, -e, v);

						switch (u2)
						{
						case 1:
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("Rektascencja: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 2:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("K�t godzinny: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 3:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							printf("Podaj szeroko�� geograficzn� obserwatora (format st min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							fi = st2rad(k1);
							obrot(2, M_PI / 2 - fi, v);
							obrot(3, -M_PI, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Azymut:%.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Wysoko��: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 5:
							obrot(3, M_PI / 2 + ag, v);
							obrot(1, M_PI / 2 - dg, v);
							obrot(3, M_PI / 2 - th, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� galaktyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� galaktyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;
						}
						break;

						/* Start galaktyczny */
					case 5:
						printf("Podaj d�ugo�� galaktyczn� (format: st min sec)\n");
						scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
						v[0] = st2rad(k1);

						if (v[0] < 0 || v[0] > 2 * M_PI)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						printf("Podaj szeroko�� szeroko�� galaktyczn� (format: st min sec)\n");
						scanf("%lf %lf %lf", &k2[0], &k2[1], &k2[2]);
						v[1] = st2rad(k2);
						if (v[1] > M_PI / 2 || v[1] < -M_PI / 2)
						{
							printf("Źle wprowadzony kąt\n");
							break;
						}
						sfer2vec(v);
						obrot(3, 3 * M_PI / 2 + th, v);
						obrot(1, 3 * M_PI / 2 + dg, v);
						obrot(3, 3 * M_PI / 2 - ag, v);

						switch (u2)
						{
						case 1:
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("Rektascencja: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 2:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							vec2sfer(v);
							rad2hour(v[0], k1);
							rad2st(v[1], k2);
							printf("K�t godzinny: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Deklinacja: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 3:
							printf("Podaj miejscowy czas gwiazdowy (format: h min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							t = hour2rad(k1);

							if (t < 0 || t > 2 * M_PI)
							{
								printf("Źle wprowadzona współrzędna\n");
								break;
							}
							obrot(3, t, v);
							v[1] = -v[1];
							printf("Podaj szeroko�� geograficzn� obserwatora (format st min sec)\n");
							scanf("%lf %lf %lf", &k1[0], &k1[1], &k1[2]);
							fi = st2rad(k1);
							obrot(2, M_PI / 2 - fi, v);
							obrot(3, -M_PI, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("Azymut:%.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Wysoko��: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;

						case 4:
							obrot(1, e, v);
							vec2sfer(v);
							rad2st(v[0], k1);
							rad2st(v[1], k2);
							printf("D�ugo�� ekliptyczna: %.0f %.0f %.6f\n", k1[0], k1[1], k1[2]);
							printf("Szeroko�� ekliptyczna: %.0f %.0f %.6f\n", k2[0], k2[1], k2[2]);
							break;
						}
						break;
					}
				}
			}
			printf("Kontynuowa� program t/n (Enter/n)\n");
		}
		getchar();
	}

	return 0;
}

/* Obrocik Pasywny */

double obrot(int n, double k, double r[])
{
	double M[3][3], work[3];
	double s, c;
	int i, j;
	for (i = 0; i <= 2; i++)
		work[i] = 0;

	s = sin(k);
	c = cos(k);

	if (n == 1)
	{
		M[0][0] = 1;
		M[0][1] = 0;
		M[0][2] = 0;
		M[1][0] = 0;
		M[1][1] = c;
		M[1][2] = s;
		M[2][0] = 0;
		M[2][1] = -s;
		M[2][2] = c;
	}
	else if (n == 2)
	{
		M[0][0] = c;
		M[0][1] = 0;
		M[0][2] = -s;
		M[1][0] = 0;
		M[1][1] = 1;
		M[1][2] = 0;
		M[2][0] = s;
		M[2][1] = 0;
		M[2][2] = c;
	}
	else if (n == 3)
	{
		M[0][0] = c;
		M[0][1] = s;
		M[0][2] = 0;
		M[1][0] = -s;
		M[1][1] = c;
		M[1][2] = 0;
		M[2][0] = 0;
		M[2][1] = 0;
		M[2][2] = 1;
	}

	for (j = 0; j <= 2; j++)
		for (i = 0; i <= 2; i++)
			work[j] = work[j] + M[j][i] * r[i];

	for (i = 0; i <= 2; i++)
		r[i] = work[i];

	return 0;
}

/* Przej�cie z wsp�rz�dnych sferycznych do postaci wektorowej */

double sfer2vec(double r[])
{
	double wynik[3], s1, c1, s2, c2;
	int i;

	s1 = sin(r[0]);
	c1 = cos(r[0]);
	s2 = sin(r[1]);
	c2 = cos(r[1]);
	wynik[0] = c1 * c2;
	wynik[1] = s1 * c2;
	wynik[2] = s2;

	for (i = 0; i <= 2; i++)
		r[i] = wynik[i];

	return 0;
}
/* Przej�cie z wektora do wsp�rz�dnych sferycznych */

double vec2sfer(double r[])
{
	double wynik[2];
	int i;
	wynik[1] = asin(r[2]);
	wynik[0] = atan2(r[1], r[0]);

	if (wynik[0] < 0)
		wynik[0] = wynik[0] + 2 * M_PI;

	for (i = 0; i <= 1; i++)
		r[i] = wynik[i];

	return 0;
}

/* Stopnie na radiany */

double st2rad(double r[])
{
	double wynik;

	if (1.0 / r[0] < 0)
	{
		r[1] = -r[1];
		r[2] = -r[2];
	}

	wynik = (r[0] + r[1] / 60.0 + r[2] / 3600.0) * M_PI / 180.0;

	return wynik;
}

/* k�t godzinny na radiany */

double hour2rad(double r[])
{
	double wynik;
	if (1.0 / r[0] < 0)
	{
		r[1] = -r[1];
		r[2] = -r[2];
	}
	wynik = (r[0] + r[1] / 60 + r[2] / 3600) * M_PI / 12.0;
	return wynik;
}

/* Radiany na stopnie */

double rad2st(double k, double r[])
{
	double wynik[3], ks, ms;
	int i;
	k = k * 180.0 / M_PI;
	if (k >= 0)
	{
		wynik[0] = floor(k);
		ks = (k - wynik[0]) * 60;
		wynik[1] = floor(ks);
		ms = ks - wynik[1];
		wynik[2] = ms * 60;
	}
	else
	{
		k = -k;
		wynik[0] = floor(k);
		ks = (k - wynik[0]) * 60;
		wynik[1] = floor(ks);
		ms = ks - wynik[1];
		wynik[2] = ms * 60;
		wynik[0] = -wynik[0];
	}

	if (wynik[2] >= 59.9999995)
	{
		wynik[2] = 0.0;
		wynik[1] = wynik[1] + 1;
	}

	if (wynik[1] == 60)
	{
		wynik[1] = 0.0;
		wynik[0] = wynik[0] + 1;
	}

	for (i = 0; i <= 2; i++)
		r[i] = wynik[i];
	return 0;
}

/* Radiany na k�t godzinny */

double rad2hour(double k, double r[])
{
	double wynik[3], ks, ms;
	int i;
	k = k * 12.0 / M_PI;
	if (k >= 0)
	{
		wynik[0] = floor(k);
		ks = (k - wynik[0]) * 60;
		wynik[1] = floor(ks);
		ms = ks - wynik[1];
		wynik[2] = ms * 60;
	}
	else
	{
		k = -k;
		wynik[0] = floor(k);
		ks = (k - wynik[0]) * 60;
		wynik[1] = floor(ks);
		ms = ks - wynik[1];
		wynik[2] = ms * 60;
		wynik[0] = -wynik[0] + 12;
	}

	if (wynik[2] >= 59.9999995)
	{
		wynik[2] = 0.0;
		wynik[1] = wynik[1] + 1;
	}

	if (wynik[1] == 60)
	{
		wynik[1] = 0.0;
		wynik[0] = wynik[0] + 1;
	}

	for (i = 0; i <= 2; i++)
		r[i] = wynik[i];
	return 0;
}
