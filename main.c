#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STACK_SIZE 100

struct Soldier {
    int health;
    int strength;
};

struct Stack {
    struct Soldier items[STACK_SIZE];
    int top;
};

void initializeStack(struct Stack *stack) {
    stack->top = -1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

//stack e asker eklemek için
void push(struct Stack *stack, struct Soldier soldier) {
    if (stack->top < STACK_SIZE - 1) {
        stack->items[++stack->top] = soldier;
    } else { // stack dolduysa
        printf("Stack is full. Cannot add more soldiers.\n");
    }
}

//stackten asker çıkarmak için
struct Soldier pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    } else {
        struct Soldier emptySoldier = {0, 0};
        printf("There are no soldiers left.\n");
        return emptySoldier;
    }
}

//stackteki askeri stackin üstüne çıkarmak için
struct Soldier top(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top];
    } else {
        struct Soldier emptySoldier = {0, 0};
        return emptySoldier;
    }
}

// fight komutu işlevi
void performFight(struct Soldier attacker, struct Soldier *defender) {
    int damage = (attacker.strength - defender->strength) * 0.05 + 50;
    if (defender->health <= damage) {
        defender->health = 0;
    } else {
        defender->health -= damage;
    }
}

// kritik vuruş fonksiyonu
void performCriticalShot(struct Soldier attacker, struct Soldier *defender) {
    int damage = (attacker.strength - defender->strength) * 0.1 + 100;
    if (defender->health <= damage) {
        defender->health = 0;
    } else {
        defender->health -= damage;
    }
}

int main() {
    struct Stack side1, side2;
    initializeStack(&side1);
    initializeStack(&side2);

    srand(time(NULL));

    char input[256];
    while (1) {
        printf("Enter a command (Add = A, Fight = F, Reinforcement = R, Critical Shot = C, Quit = Q): ");
        scanf("%s", input);

        if (input[0] == 'Q' || input[0] == 'q') {
            break; // oyundan çık
        } else if (input[0] == 'A' || input[0] == 'a') {
            int side;
            printf("Enter side (1 or 2): ");
            scanf("%d", &side);

            while (1) {
                struct Soldier soldier;
                printf("Enter soldier statistics (Health,Strength): ");
                scanf("%d,%d", &soldier.health, &soldier.strength);

                if (side == 1) {
                    push(&side1, soldier);
                    printf("Soldier is added H:%d S:%d to side 1\n", soldier.health, soldier.strength);
                } else if (side == 2) {
                    push(&side2, soldier);
                    printf("Soldier is added H:%d S:%d to side 2\n", soldier.health, soldier.strength);
                }

                // askerleri tek seferde ekleyemediğim için ard arda ekleyebilmek için
                printf("Do you want to add another soldier? (Y/N): ");
                char choice;
                scanf(" %c", &choice);
                if (choice != 'Y' && choice != 'y') {
                    break;
                }
            }
        } else if (input[0] == 'R' || input[0] == 'r') {
            int side;
            printf("Enter side (1 or 2) for reinforcements: ");
            scanf("%d", &side);

            struct Soldier randomSoldier = {rand() % 101, rand() % 1000};
            if (side == 1) {
                push(&side1, randomSoldier);
                printf("Reinforcements added to side 1: H:%d S:%d\n", randomSoldier.health, randomSoldier.strength);
            } else if (side == 2) {
                push(&side2, randomSoldier);
                printf("Reinforcements added to side 2: H:%d S:%d\n", randomSoldier.health, randomSoldier.strength);
            }
        } else if (input[0] == 'F' || input[0] == 'f') {
            while (!isEmpty(&side1) && !isEmpty(&side2)) {
                struct Soldier attacker1 = top(&side1);
                struct Soldier defender2 = top(&side2);

                int damage1 = (attacker1.strength - defender2.strength) * 0.05 + 50;
                printf("Fight: 1 hit %d damage\n", damage1);

                if (defender2.health <= damage1) {
                    defender2.health = 0;
                } else {
                    defender2.health -= damage1;
                }

                if (defender2.health == 0) {
                    pop(&side2);
                    printf("Fight: 2 has a casualty\n");
                    break;
                }

                if (isEmpty(&side2)) {
                    printf("Side 1 wins!\n");
                    break;
                }

                struct Soldier attacker2 = top(&side2);
                struct Soldier defender1 = top(&side1);

                int damage2 = (attacker2.strength - defender1.strength) * 0.05 + 50;
                printf("Fight: 2 hit %d damage\n", damage2);

                if (defender1.health <= damage2) {
                    defender1.health = 0;
                } else {
                    defender1.health -= damage2;
                }

                if (defender1.health == 0) {
                    pop(&side1);
                    printf("Fight: 1 has a casualty\n");
                    break;
                }

                if (isEmpty(&side1)) {
                    printf("Side 2 wins!\n");
                    break;
                }
            }
        } else if (input[0] == 'C' || input[0] == 'c') {
            // kritik vuruş implementasyonu
            if (!isEmpty(&side1) && !isEmpty(&side2)) {
                struct Soldier attacker1 = top(&side1);
                struct Soldier defender2 = top(&side2);

                performCriticalShot(attacker1, &defender2);
                printf("Critical Shot: 1 hit a critical shot\n");

                if (defender2.health == 0) {
                    pop(&side2);
                    printf("Critical Shot: 2 has a casualty\n");
                } else {
                    printf("Critical Shot: 2 survives the critical shot\n");
                }

                if (isEmpty(&side2)) {
                    printf("Side 1 wins with a critical shot!\n");
                    break;
                }

                struct Soldier attacker2 = top(&side2);
                struct Soldier defender1 = top(&side1);

                performCriticalShot(attacker2, &defender1);
                printf("Critical Shot: 2 hit a critical shot\n");

                if (defender1.health == 0) {
                    pop(&side1);
                    printf("Critical Shot: 1 has a casualty\n");
                } else {
                    printf("Critical Shot: 1 survives the critical shot\n");
                }

                if (isEmpty(&side1)) {
                    printf("Side 2 wins with a critical shot!\n");
                    break;
                }
            } else {
                printf("No soldiers left to perform a critical shot.\n");
            }
        }
    }

    return 0;
}
