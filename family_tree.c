#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person* create_person(const char *name, int age) {
    Person *person = malloc(sizeof(Person));

    if (person == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    strncpy(person->name, name, sizeof(person->name) - 1);
    person->name[sizeof(person->name) - 1] = '\0';

    person->age = age;
    person->father = NULL;
    person->mother = NULL;

    return person;
}

int main(void) {
    return 0;
}