#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct electricity{
	int year;
	double price[12];
	double average;
};

int i, j, len;
electricity records[30];

void read() {
	FILE *file;
	char line[200], *token;

	fopen_s(&file, "F:\\Downloads\\electricity.txt", "r");
	i = 0;
	while (!feof(file)) {
		fgets(line, 200, file);
		token = strtok(line, ",\n\0");
		j = 0;
		if (line[0] == '1') {
			while (token != NULL) {
				if (j == 0) records[i].year = atoi(token);
				if (j > 0) records[i].price[j - 1] = atof(token);
				token = strtok(NULL, ",\n\0");
				j++;
			}
			for (j = 0; j < 12; j++)
				records[i].average += records[i].price[j];
			records[i].average /= 12;
			i++;
		}
	}
	len = i;
	fclose(file);
}

void month() {
	int month;
	float highest[2];
	char months[12][20] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	highest[0] = 0;
	for (j = 0; j < len; j++)
		for (i = 0; i < 12; i++) {
			if (records[j].price[i] > highest[0]) {
				highest[0] = records[j].price[i];
				month = i;
				highest[1] = records[j].year;
			}
		}
	printf("\nThe highest price was %.2f in %s, %.0f\n\n", highest[0], months[month], highest[1]);
}

void year() {
	float highest[2];
	highest[0] = 0;
	for (i = 0; i < len; i++) {
		if (highest[0] < records[i].average) {
			highest[0] = records[i].average;
			highest[1] = records[i].year;
		}
	}
	printf("\nThe highest average year was %.2f in %.0f\n\n", highest[0], highest[1]);
}

int main() {
	int choice;

	read();

	do {
		printf("Enter choice:\n0 - Exit\n1 - Find the month with the highest price\n2 - Find the year with the highest average\n");
		scanf("%d", &choice);
		if (choice == 1) { month(); }
		if (choice == 2) { year(); }
	} while (choice != 0);

	return 0;
}

