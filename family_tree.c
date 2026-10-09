#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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

void read_person_info(const char *role, char *name_out, int *age_out) {
    char input[100];
    char *endptr;
    long age;
    size_t length;

    while (1) {
        printf("Enter name for %s: ", role);

        if (fgets(name_out, 50, stdin) == NULL) {
            printf("Input error.\n");
            exit(EXIT_FAILURE);
        }

        length = strlen(name_out);

        if (length > 0 && name_out[length - 1] == '\n') {
            name_out[length - 1] = '\0';
        } else {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Clear remaining input */
            }

            printf("Name is too long. Enter up to 49 characters.\n");
            continue;
        }

        if (name_out[0] == '\0') {
            printf("Name cannot be empty. Try again.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter age for %s: ", role);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error.\n");
            exit(EXIT_FAILURE);
        }

        errno = 0;
        age = strtol(input, &endptr, 10);

        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (endptr == input ||
            *endptr != '\0' ||
            errno == ERANGE ||
            age < 0 ||
            age > 150) {
            printf("Please enter a valid age between 0 and 150.\n");
            continue;
        }

        *age_out = (int)age;
        break;
    }
}

void link_parents(Person *child, Person *father, Person *mother) {
    child->father = father;
    child->mother = mother;
}

void print_family_relationships(const Person *me) {
    if (me == NULL || me->father == NULL || me->mother == NULL) {
        printf("Family relationships are incomplete.\n");
        return;
    }

    printf("\n=== FAMILY TREE RELATIONSHIPS ===\n");

    printf("\n1. YOURSELF:\n");
    printf("Name: %s | Age: %d\n", me->name, me->age);

    printf("\n2. PARENTS:\n");
    printf("Father: %s | Age: %d\n",
           me->father->name, me->father->age);
    printf("Mother: %s | Age: %d\n",
           me->mother->name, me->mother->age);

    printf("\n3. PATERNAL GRANDPARENTS (via Father's Pointers):\n");

    if (me->father->father != NULL) {
        printf("Grandfather: %s | Age: %d\n",
               me->father->father->name,
               me->father->father->age);
    } else {
        printf("Grandfather: Not recorded\n");
    }

    if (me->father->mother != NULL) {
        printf("Grandmother: %s | Age: %d\n",
               me->father->mother->name,
               me->father->mother->age);
    } else {
        printf("Grandmother: Not recorded\n");
    }

    printf("\n4. MATERNAL GRANDPARENTS (via Mother's Pointers):\n");

    if (me->mother->father != NULL) {
        printf("Grandfather: %s | Age: %d\n",
               me->mother->father->name,
               me->mother->father->age);
    } else {
        printf("Grandfather: Not recorded\n");
    }

    if (me->mother->mother != NULL) {
        printf("Grandmother: %s | Age: %d\n",
               me->mother->mother->name,
               me->mother->mother->age);
    } else {
        printf("Grandmother: Not recorded\n");
    }
}

void free_family_tree(Person *people[], int count) {
    int i;

    for (i = 0; i < count; i++) {
        free(people[i]);
    }
}

int main(void) {
    char names[7][50];
    int ages[7];

    const char *roles[7] = {
        "Paternal Grandfather",
        "Paternal Grandmother",
        "Maternal Grandfather",
        "Maternal Grandmother",
        "Father",
        "Mother",
        "Myself"
    };

    Person *people[7] = {NULL};
    Person *paternal_grandfather;
    Person *paternal_grandmother;
    Person *maternal_grandfather;
    Person *maternal_grandmother;
    Person *father;
    Person *mother;
    Person *myself;

    int i;

    printf("Enter information for all seven family members.\n\n");

    for (i = 0; i < 7; i++) {
        read_person_info(roles[i], names[i], &ages[i]);
        printf("\n");
    }

    for (i = 0; i < 7; i++) {
        people[i] = create_person(names[i], ages[i]);

        if (people[i] == NULL) {
            printf("Could not create all family members.\n");
            free_family_tree(people, 7);
            return 1;
        }
    }

    paternal_grandfather = people[0];
    paternal_grandmother = people[1];
    maternal_grandfather = people[2];
    maternal_grandmother = people[3];
    father = people[4];
    mother = people[5];
    myself = people[6];

    link_parents(father,
                 paternal_grandfather,
                 paternal_grandmother);

    link_parents(mother,
                 maternal_grandfather,
                 maternal_grandmother);

    link_parents(myself, father, mother);

    print_family_relationships(myself);

    free_family_tree(people, 7);

    printf("\nMemory released successfully.\n");

    return 0;
}