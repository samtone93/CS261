#include <stdio.h>
#include <math.h>

void areaFunc();

int main (int argc, char **argv) {
	areaFunc();
	return 0;
}

void areaFunc() {
	double a;
	double b;
	double c;
	double perimeter;
	double area;

	printf("Please enter float values for 3 sides of a triangle\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	scanf("%lf", &c);

	perimeter = a + b + c;
	perimeter = perimeter / 2;
	area = perimeter * (perimeter - a)*(perimeter - b)*(perimeter - c);
	area = sqrt(area);

	printf("\n Calculated area: %lf \n", area);

}