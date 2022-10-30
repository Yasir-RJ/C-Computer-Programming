// Lab2: Measurement data analysis
// by Yasir Riyadh Jabbar / KTH
#include <stdio.h>
#include <math.h>

// funktionsprototyp
void view(int D[], int NOM);
int enter(int D[], int NOM);
void compute(int NOM, int D[], int N[]);
int Max(int D[], int NOM);
int Min(int D[], int NOM);
float mean(int D[], int NOM);
void norm(int NOM, float average, int D[], int N[]);

int main() {

	char selection;
	int i, nrOfMeasurement = 0;
	int measurements[10] = { 0 }, Normalize[10] = { 0 };


	printf("\n Measurement tool 2.0\n");
	printf(" v (View) - show the stored measured values\n");
	printf(" e (Enter) - enter the measurement values\n");
	printf(" c (Compute) - compute the max, min, average and normalized measured values\n");
	printf(" r (Reset) - delete all entered measured values\n");
	printf(" q (Quit) - exit the program\n\n");

	while (1) { //loop forever
		printf(" VECRQ? ");
		scanf(" %c", &selection);
		switch (selection) {
		case 'e':
			if (nrOfMeasurement < 10) nrOfMeasurement = enter(measurements, nrOfMeasurement);
			break;
		case 'v':
			if (nrOfMeasurement == 0) printf(" No measurements!\n");
			else view(measurements, nrOfMeasurement);
			break;
		case 'c':
			if (nrOfMeasurement == 0) printf(" No measurements!\n");
			else {
				for (i = 0; i < nrOfMeasurement; i++) Normalize[i] = measurements[i];
				compute(nrOfMeasurement, measurements, Normalize);
			}
			break;
		case 'r': {
			nrOfMeasurement = 0;
			for (i = 0; i < 10; i++) {
				measurements[i] = 0;
				Normalize[i] = 0;
			}
			break;
		}
		case 'q':
			printf(" Exit Measurement tool\n");
			return 0;

		default:
			break;
		}
	}
	return 0;
}
void view(int D[], int NOM) {
	int i;
	printf(" [ ");
	for (i = 0; i < NOM; i++)
		printf("%d ", D[i]);
	printf("]\n");
}

int enter(int D[], int NOM) {
	int i, readInteger;
	char tmp;
	while (NOM < 10) {
		printf(" Enter measurement #%d (or q to quit):", NOM + 1);
		readInteger = scanf_s("%d", &D[NOM]);
		if (readInteger) NOM++;
		else {
			scanf_s(" %c", &tmp);
			if (tmp == 'q') break;
		}
	}
	return NOM;
}

void compute(int NOM, int D[], int N[]) {
	float average;
	printf(" Max value: %d\n", Max(D, NOM));
	printf(" Min value: %d\n", Min(D, NOM));
	average = mean(D, NOM);
	printf(" Avr value: %.2f\n", average);
	norm(NOM, average, D, N);
	view(N, NOM);
}

int Max(int D[], int NOM) {
	int i, maximum = D[0];
	for (i = 1; i < NOM; i++)
		if (D[i] > maximum) maximum = D[i];
	return maximum;
}

int Min(int D[], int NOM) {
	int i, minimum = D[0];
	for (i = 0; i < NOM; i++)
		if (D[i] < minimum) minimum = D[i];
	return minimum;
}

float mean(int D[], int NOM) {
	float average;
	int i, sum = 0;
	for (i = 0; i < NOM; i++)
		sum = sum + D[i];
	average = sum / (float)NOM;
	return average;
}

void norm(int NOM, float average, int D[], int N[]) {
	int i;
	for (i = 0; i < NOM; i++)
		N[i] = D[i] - round(average);
}
