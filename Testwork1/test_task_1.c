#include "vector.h"
#include <stdio.h>

int main()
{
    int dim = 0;
    printf("Enter the dimension of the space: ");
    scanf("%i", &dim);
    printf("Enter coordinates of the first vector: ");
    Vector* v1 = makeNewVector();
    Vector* v2 = makeNewVector();
    int temp = 0;
    for (int i = 0; i < dim; ++i) {
        scanf("%i", &temp);
        addElement(v1, temp);
    }
    printf("Enter coordinates of the second vector: ");
    for (int i = 0; i < dim; ++i) {
        scanf("%i", &temp);
        addElement(v2, temp);
    }
    if (v1->dim != dim || v2->dim != dim) {
        printf("ERROR! The dimensions of the vectors do not correspond to the dimensions of the space! ");
        return 0;
    }

    Vector* sumVector = sum(v1, v2);
    Vector* diffVector = difference(v1, v2);

    printf("Squire of length v1 = %f\n", length(v1));
    printf("Squire of length v2 = %f\n", length(v2));
    printf("v1 + v2 = ");
    printVector(sumVector);
    printf("v1 - v2 = ");
    printVector(diffVector);
    printf("v1 * v2 = %i", product(v1, v2));

    deleteVector(v1);
    deleteVector(v2);
    deleteVector(sumVector);
    deleteVector(diffVector);
    return 0;
}
