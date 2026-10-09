#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person *create_person(const char *name, int age) {
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

void read_person_info(Person *person, const char *relationship) {
    printf("Enter name of %s: ", relationship);

    if (scanf(" %49[^\n]", person->name) != 1) {
        printf("Invalid name input.\n");
        return;
    }

    printf("Enter age of %s: ", relationship);

    if (scanf("%d", &person->age) != 1) {
        printf("Invalid age input.\n");
        return;
    }
}

void link_parents(Person *child, Person *father, Person *mother) {
    child->father = father;
    child->mother = mother;
}

void print_family_relationships(Person *person, const char *relationship) {
    printf("\n%s\n", relationship);
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);

    if (person->father != NULL) {
        printf("Father: %s\n", person->father->name);
    } else {
        printf("Father: Not recorded\n");
    }

    if (person->mother != NULL) {
        printf("Mother: %s\n", person->mother->name);
    } else {
        printf("Mother: Not recorded\n");
    }
}

void free_family_tree(
    Person *paternal_grandfather,
    Person *paternal_grandmother,
    Person *maternal_grandfather,
    Person *maternal_grandmother,
    Person *father,
    Person *mother,
    Person *myself
) {
    free(paternal_grandfather);
    free(paternal_grandmother);
    free(maternal_grandfather);
    free(maternal_grandmother);
    free(father);
    free(mother);
    free(myself);
}

int main(void) {
    Person *paternal_grandfather = create_person("", 0);
    Person *paternal_grandmother = create_person("", 0);
    Person *maternal_grandfather = create_person("", 0);
    Person *maternal_grandmother = create_person("", 0);
    Person *father = create_person("", 0);
    Person *mother = create_person("", 0);
    Person *myself = create_person("", 0);

    if (paternal_grandfather == NULL ||
        paternal_grandmother == NULL ||
        maternal_grandfather == NULL ||
        maternal_grandmother == NULL ||
        father == NULL ||
        mother == NULL ||
        myself == NULL) {

        printf("Could not create all family members.\n");

        free_family_tree(
            paternal_grandfather,
            paternal_grandmother,
            maternal_grandfather,
            maternal_grandmother,
            father,
            mother,
            myself
        );

        return 1;
    }

    read_person_info(paternal_grandfather, "Paternal Grandfather");
    read_person_info(paternal_grandmother, "Paternal Grandmother");
    read_person_info(maternal_grandfather, "Maternal Grandfather");
    read_person_info(maternal_grandmother, "Maternal Grandmother");
    read_person_info(father, "Father");
    read_person_info(mother, "Mother");
    read_person_info(myself, "Myself");

    link_parents(father, paternal_grandfather, paternal_grandmother);
    link_parents(mother, maternal_grandfather, maternal_grandmother);
    link_parents(myself, father, mother);

    printf("\n========== FAMILY TREE ==========\n");

    print_family_relationships(paternal_grandfather, "Paternal Grandfather");
    print_family_relationships(paternal_grandmother, "Paternal Grandmother");
    print_family_relationships(maternal_grandfather, "Maternal Grandfather");
    print_family_relationships(maternal_grandmother, "Maternal Grandmother");
    print_family_relationships(father, "Father");
    print_family_relationships(mother, "Mother");
    print_family_relationships(myself, "Myself");

    free_family_tree(
        paternal_grandfather,
        paternal_grandmother,
        maternal_grandfather,
        maternal_grandmother,
        father,
        mother,
        myself
    );

    printf("\nMemory released successfully.\n");

    return 0;
}