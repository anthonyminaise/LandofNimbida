#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Anthony Minaise 6/9/14

struct node
{
    char data;
    struct node *nextptr;
};

// Prototypes
void backstory(char);
void path(char, char, int *);
void darkKnightFight(char, int *);
void house(char, char[20], int *);
void read();
void insertNode(char);
void printNodes();
void freeNodes();

typedef struct node NODE;
typedef NODE *NODEPTR;

NODEPTR start = NULL;

int main()
{
    // Random number set up
    srand(time(0));

    char character = 'd', name[20], pathChoice = '1', toRead = 'y';
    int *potion = 0, chanceP = 0;
    FILE *fp;

    // Text Adventure
    if((fp = fopen("Text Adventure.txt", "w")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    puts("Welcome to the Land of Nimbida, a text adventure where you make the decisions.\n\n");
    puts("What would you like to be:\nA) a knight\nB) a sorceror\nC) a monk\nD) a paladin\n");
    scanf("%c", &character);

    // Error Catch
    while(character != 'a' && character != 'A' && character != 'b' && character != 'B' && character != 'c' && character != 'C' && character != 'd' && character != 'D')
    {
        getchar();
        puts("\nThe answer choice you made doesn't match a valid choice, choose again.");
        puts("What would you like to be:\nA) a knight\nB) a sorceror\nC) a monk\nD) a paladin");
        scanf("%c", &character);
    }
    insertNode(character);

    // Displays backstory based on choice
    backstory(character);

    puts("What is your name? (No spaces)");
    scanf("%s", &name);

    printf("Hello %s! You are about to embark on the journey of a lifetime, but you\ndon't know it yet.\n\n", name);

    fprintf(fp,"Hello %s! You are about to embark on the journey of a lifetime, but you\ndon't know it yet.\n\n", name);
    fclose(fp);

    // Gives scenario for a fock in the road
    path(pathChoice, character, &potion);

    fp = fopen("Text Adventure.txt", "a");
    if((fp = fopen("Text Adventure.txt", "a")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    puts("*** Level Up ***");
    fprintf(fp, "*** Level Up ***\n");
    puts("Health: 35\n\n");
    fprintf(fp, "Health: 35\n\n\n");
    puts("As you keep going to the kingdom, you see a dark knight on a black horse riding toward you. You try to get his attention, but it looks like he's going in for\nthe attack! You get into a battle.\n");
    fprintf(fp, "As you keep going to the kingdom, you see a dark knight on a black horse riding toward you. You try to get his attention, but it looks like he's going in for\nthe attack! You get into a battle.\n\n");

    chanceP = rand()%10 + 1;
    if(chanceP == 1 || chanceP == 2 || chanceP == 3)
    {
        puts("Nice! You just found a potion! It heals 10 hp.");
        fprintf(fp, "Nice! You just found a potion! It heals 10 hp.\n");
        potion += 1;
    }

    // Fight between user and a dark knight
    darkKnightFight(character, &potion);

    // Situations when come across a house
    house(character, name, &potion);

    puts("As you make your way down the path once again, after a few minutes you start to see the kingdom walls and buildings! You rush to the gates and get in the\nkingdom.");
    fprintf(fp, "As you make your way down the path once again, after a few minutes you start to see the kingdom walls and buildings! You rush to the gates and get in the\nkingdom.\n");
    puts("\n********************************************************************************");
    fprintf(fp, "\n********************************************************************************\n");
    puts("Congratulations! You have completed your journey and beat the game, you're a\nsmart one!");
    fprintf(fp, "Congratulations! You have completed your journey and beat the game, you're a\nsmart one!\n");
    puts("\n********************************************************************************\n");
    fprintf(fp, "\n********************************************************************************\n");

    fclose(fp);

    puts("Would you like to read you adventure? (Y or N)");
    scanf("%c", &toRead);

    // Error Check
    while(toRead != 'y' && toRead != 'Y' && toRead != 'n' && toRead != 'N')
    {
        puts("That is an invalid entry, try again.\n");
        puts("Would you like to read you adventure? (Y or N)");
        scanf("%c", &toRead);
    }

    puts("\n\n\n");

    // Read what is stored in the file
    if(toRead == 'y' || toRead == 'Y')
        read();

    puts("Would you like to read you decisions? (Y or N)");
    scanf("%c", &toRead);

    // Error Check
    while(toRead != 'y' && toRead != 'Y' && toRead != 'n' && toRead != 'N')
    {
        puts("That is an invalid entry, try again.\n");
        puts("Would you like to read you decisions? (Y or N)");
        scanf("%c", &toRead);
    }

    puts("\n\n");

    // Read what is stored in the file
    if(toRead == 'y' || toRead == 'Y')
        printNodes();

    freeNodes();

    return 0;
}

// Backstories
void backstory(char character)
{
    if(character == 'a' || character == 'A')
    {
        puts("\nYou are a young noble knight of the kingdom of Nimbida. You started your squire training at age 14 with your knight Sir Hammerlock. Sir Hammerlock gave you a 5 year experience of being a squire until you finally achieved knighthood. You\nbecame a knight at the age 19 and you are set as a guard of the kingdom. One day, her majesty asks you to go to the kingdom next door to do a secret mission noteven you know about. This is where your jounrey begins.\n");
    }

    else if(character == 'b' || character == 'B')
    {
        puts("\nYou are an intelligent sorceror. You came from the royal family of Bayfong, not\nknowing you had magical abilities until age 13. Once you figured it out, you\nsecretly trained yourself to focus your power and made spells. You kept this a\nsecret thus far, no one knows but your brother John. You decide that you want tosee what the world is like instead of being held captive in the kingdom, so you take off with some money and leave the kingdom. This is where your journey\nbegins.\n");
    }
    else if(character == 'c' || character == 'C')
    {
        puts("\nYou are a strong monk. You joined the monestary at the age of 15. Learning the\nways of the monk, you learn how to defend yourself and harness your inner power.You spend a quick 2 years with the monestary until you found it dull and wanted more out of life then the life of a monk. You pack your things and set out to\nthe kingdom of Nimbida. This is where your journey begins.\n");
    }
    else if(character == 'd' || character == 'D')
    {
        puts("\nYou are a honorable paladin of the kingdom of Nimbida. You started to learn the ways of palidans at age 17. You seemed to have learned quickly and became a palidan at age 19. You have the power to heal people, be tanky, and be very charismatic. Yet, you find the life of a kingdom palidan dull and go solo, keeping your powers with you. This is where your journey begins.\n");
    }
    getchar();
}

// Different paths
void path(char pathChoice, char character, int *potion)
{
    int enemyHealth = 20, characterHeath = 25, charAttack = 0, enemyAttack = 0, runAway = 0, chanceP;
    char menu = 'r';
    FILE *fp;

    if((fp = fopen("Text Adventure.txt", "a")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    pathChoice = 'd';

    getchar();

    printf("You start to walk down the path to the kingdom, you see a fork in the road.\nWhich path will you take? (R or L)\n");
    fprintf(fp,"You start to walk down the path to the kingdom, you see a fork in the road.\nWhich path will you take? (R or L)\n\n");
    scanf("%c", &pathChoice);

    // Error Catch
    while(pathChoice != 'r' && pathChoice != 'R' && pathChoice != 'l' && pathChoice != 'L')
    {
        puts("That is not a valid move, try again.");
        printf("You start to walk down the path to the kingdom, you see a fork in the road. Which path will you take? (R or L)\n");
        scanf("%c", &pathChoice);
    }
    insertNode(pathChoice);
    fprintf(fp, "%c\n", pathChoice);

    // Going on the right path
    if(pathChoice == 'r' || pathChoice == 'R')
    {
        getchar();
        chanceP = rand()%10 + 1;
        if(chanceP == 1 || chanceP == 2 || chanceP == 3)
        {
            puts("Nice! You just found a potion! It heals 10 hp.");
            fprintf(fp,"Nice! You just found a potion! It heals 10 hp.\n");
            (*potion) += 1;
        }
        puts("\nAs you walk down the right path, the path goes through a shady and creepy\nforrest. You decide to go through it since it seems to be the only way through to your destination.\n");
        fprintf(fp,"\nAs you walk down the right path, the path goes through a shady and creepy\nforrest. You decide to go through it since it seems to be the only way through to your destination.\n\n");
        puts("What seems to be hours, minutes pass by was you walk through the forrest.\nSuddenly, you come across a troll warlord of a near by tribe that comes to attack you. You get into a fight with him.\n\n");
        fprintf(fp,"What seems to be hours, minutes pass by was you walk through the forrest.\nSuddenly, you come across a troll warlord of a near by tribe that comes to attack you. You get into a fight with him.\n\n\n");


        // Battle scene
        while(enemyHealth > 0 || characterHeath <= 0)
        {
            printf("\nYou have %i health. The troll warlord has %i health.\n", characterHeath, enemyHealth);
            printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
            scanf("%c", &menu);

            //Error Check
            while(menu != 'a' && menu != 'A' && menu != 'b' && menu != 'B' && menu != 'c' && menu != 'C')
            {
                puts("That is not a valid choice, try again.");
                printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
                scanf("%c", &menu);
                puts("");
            }

            if(menu == 'a' || menu == 'A')
            {
                charAttack = rand()%10 + 1;
                if(character == 'a' || character == 'A')
                    printf("\nYou swing your sword and deal %i damage.\n", charAttack);
                else if(character == 'b' || character == 'B')
                    printf("\nYou cast a spell and deal %i damage.\n", charAttack);
                else if(character == 'd' || character == 'D')
                    printf("\nYou hit the troll with your mighty hammer and deal %i damage.\n", charAttack);
                else if(character == 'c' || character == 'C')
                    printf("\nYou go in for the attack dealing %i damage.\n\n", charAttack);
                enemyAttack = rand()%10 + 1;
                printf("The troll hits you for %i damage.\n", enemyAttack);
                characterHeath = characterHeath - enemyAttack;
                enemyHealth = enemyHealth - charAttack;
                // Check if either user or enemy dies
                if(enemyHealth <= 0)
                {
                    puts("Congratulations! You have defeated the mighty troll warlord! You loot the body\nand find some troll armor, a sword, a shield, and 10 gold.\n");
                    fprintf(fp,"Congratulations! You have defeated the mighty troll warlord! You loot the body\nand find some troll armor, a sword, a shield, and 10 gold.\n\n");

                    break;
                }
                else if(characterHeath <= 0)
                {
                    puts("Oh No! You have died! Looks like this adventure is over.");
                    fprintf(fp,"Oh No! You have died! Looks like this adventure is over.");
                    exit(1);
                }
            }
            // Run away
            else if(menu == 'b' || menu == 'B')
            {
                runAway = rand()%10 + 1;
                if(runAway >= 5)
                {
                    puts("You try to run away. Your efforts succeeded and move on with your journey.");
                    fprintf(fp,"You try to run away. Your efforts succeeded and move on with your journey.\n");
                    break;
                }
                else if(runAway <= 4)
                {
                    puts("You try to run away. Looks like you're still in this fight.");
                    fprintf(fp, "You try to run away. Looks like you're still in this fight.\n");
                    menu = 'a';
                    enemyAttack = rand()%10 + 1;
                    printf("The knight hits you for %i damage.\n", enemyAttack);
                }
            }
            chanceP = rand()%10 + 1;
            if(chanceP == 1 || chanceP == 2 || chanceP == 3)
            {
                puts("Nice! You just found a potion! It heals 10 hp.");
                fprintf(fp, "Nice! You just found a potion! It heals 10 hp.\n");
                (*potion) += 1;
            }

            //Heal with Potion
            else if(menu == 'c' || menu == 'C')
            {
                if((*potion) > 0)
                {
                    (*potion)--;
                    characterHeath += 10;
                    printf("You healed yourself for 10 hp, making your health %i\n", characterHeath);
                    fprintf(fp,"You healed yourself for 10 hp, making your health %i\n", characterHeath);
                }

                else if((*potion) == 0)
                {
                    puts("You don't have any potions to use! Sorry!\n");
                }
            }

            getchar();
        }

        puts("You keep going on the path and finally see an end to the forrest. You see the light again and see a tavern coming up. Also, you see that the paths merge back together. You get in the tavern and decide to take a room for the night.\n");
        fprintf(fp, "You keep going on the path and finally see an end to the forrest. You see the light again and see a tavern coming up. Also, you see that the paths merge back together. You get in the tavern and decide to take a room for the night.\n\n");
    }

    // Left path
    else if(pathChoice == 'l' || pathChoice == 'L')
    {
        getchar();
        char tavernChoice;
        puts("\n\nYou take the left path. As you take the path, you see the right path led to a\nshady forrest and are thankful you made this choice. After a while of walking\nand the sun going down, you see a tavern. You enter the tavern and");
        fprintf(fp,"\n\nYou take the left path. As you take the path, you see the right path led to a\nshady forrest and are thankful you made this choice. After a while of walking\nand the sun going down, you see a tavern. You enter the tavern and\n");
        printf("A) Get a drink and keep moving\nB) Get a room and stay the night. ");
        scanf("%c", &tavernChoice);
        puts("");

        // Error check
        while(tavernChoice != 'a' && tavernChoice != 'A' && tavernChoice != 'b' && tavernChoice != 'B')
        {
            puts("That is not a valid choice, try again.");
            puts("A) Get a drink and keep moving\nB) Get a room and stay the night. ");
            scanf("%c", &tavernChoice);
            puts("");
        }

        insertNode(tavernChoice);
        fprintf(fp, "%c\n", tavernChoice);

        chanceP = rand()%10 + 1;
        if(chanceP == 1 || chanceP == 2)
        {
            puts("Nice! You just found 2 potions! It heals 10 hp each.");
            fprintf(fp, "Nice! You just found 2 potions! It heals 10 hp each.\n");
            (*potion) += 2;
        }

        // Grab a drink at tavern
        if(tavernChoice == 'a' || tavernChoice == 'A')
        {
            puts("\nYou ask for a drink. One thing leads to another, you drink to much and wake up to find yourself beaten up and lying in a pigsty covered in pig poop.");
            fprintf(fp,"\nYou ask for a drink. One thing leads to another, you drink to much and wake up to find yourself beaten up and lying in a pigsty covered in pig poop.\n");
            puts("\nAs you pull yourself together, you seem to have a hangover and a really bad headache. You suddenly realize some of your money is missing! You lost 20 gold.");
            fprintf(fp,"\nAs you pull yourself together, you seem to have a hangover and a really bad headache. You suddenly realize some of your money is missing! You lost 20 gold.\n");
            puts("\nUnfortunatly, you have to continue with your journey with these setbacks and little to no sleep.\n\n");
            fprintf(fp,"\nUnfortunatly, you have to continue with your journey with these setbacks and little to no sleep.\n\n\n");
        }

        // Get a room at tavern
        else if(tavernChoice == 'b' || tavernChoice == 'B')
        {
            puts("\nYou get a room from the tavernkeeper and stay the night in a bed for once. The next day, you wake up fresh and ready for another day.\n\n");
            fprintf(fp,"\nYou get a room from the tavernkeeper and stay the night in a bed for once. The next day, you wake up fresh and ready for another day.\n\n\n");
        }
    }
    fclose(fp);
}

void darkKnightFight(char character, int *potion)
{
    int enemyHealth = 30, characterHeath = 35, enemyAttack, charAttack, runAway;
    char menu;
    FILE *fp;

    if((fp = fopen("Text Adventure.txt", "a")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    // Battle scene
    while(enemyHealth > 0 || characterHeath <= 0)
        {
            getchar();
            printf("\nYou have %i health. The dark knight has %i health.\n", characterHeath, enemyHealth);
            printf("What do you do?\nA) Attack\nB) Run away\nC) Use Potion\n");
            scanf("%c", &menu);

             //Error Check
            while(menu != 'a' && menu != 'A' && menu != 'b' && menu != 'B' && menu != 'c' && menu != 'C')
            {
                puts("That is not a valid choice, try again.");
                printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
                scanf("%c", &menu);
                puts("");
            }

            if(menu == 'a' || menu == 'A')
            {
                charAttack = rand()%10 + 1;
                if(character == 'a' || character == 'A')
                    printf("\nYou swing your sword and deal %i damage.\n", charAttack);
                else if(character == 'b' || character == 'B')
                    printf("\nYou cast a spell and deal %i damage.\n", charAttack);
                else if(character == 'd' || character == 'D')
                    printf("\nYou hit the knight with your mighty hammer and deal %i damage.\n", charAttack);
                else if(character == 'c' || character == 'C')
                    printf("\nYou go in for the attack dealing %i damage.\n\n", charAttack);
                enemyAttack = rand()%10 + 1;
                printf("The knight hits you for %i damage.\n", enemyAttack);
                characterHeath = characterHeath - enemyAttack;
                enemyHealth = enemyHealth - charAttack;
                // Check if either user or enemy dies
                if(enemyHealth <= 0)
                {
                    puts("Congratulations! You have defeated the dark knight! You loot the body and find some black armor, a sword, 10 gold, and you take his horse.\n");
                    fprintf(fp, "Congratulations! You have defeated the dark knight! You loot the body and find some black armor, a sword, 10 gold, and you take his horse.\n\n");
                    break;
                }
                else if(characterHeath <= 0)
                {
                    puts("Oh No! You have died! Looks like this adventure is over.");
                    fprintf(fp, "Oh No! You have died! Looks like this adventure is over.\n");
                    exit(1);
                }
            }

            // Run away
            else if(menu == 'b' || menu == 'B')
            {
                runAway = rand()%10 + 1;
                if(runAway >= 6)
                {
                    puts("You try to run away. Your efforts succeeded and move on with your journey.\n");
                    fprintf(fp, "You try to run away. Your efforts succeeded and move on with your journey.\n\n");
                    break;
                }
                else if(runAway <= 5)
                {
                    puts("You try to run away. Looks like you're still in this fight.");
                    fprintf(fp, "You try to run away. Looks like you're still in this fight.\n");
                    menu = 'a';
                    enemyAttack = rand()%10 + 1;
                    printf("The knight hits you for %i damage.\n", enemyAttack);
                }
            }

            //Heal with Potion
            else if(menu == 'c' || menu == 'C')
            {
                if((*potion) > 0)
                {
                    (*potion)--;
                    characterHeath += 10;
                    printf("You healed yourself for 10 hp, making your health %i\n", characterHeath);
                    fprintf(fp, "You healed yourself for 10 hp, making your health %i\n", characterHeath);
                }

                else if((*potion) == 0)
                {
                    puts("You don't have any potions to use! Sorry!\n");
                }
            }
        }
    fclose(fp);
}

// House choices
void house(char character, char name[20], int *potion)
{
    int enemyHealth = 30, characterHeath = 35, enemyAttack, charAttack, runAway, chanceP;
    char choices, toHouse, menu;
    FILE *fp;

    if((fp = fopen("Text Adventure.txt", "a")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    chanceP = rand()%10 + 1;
    if(chanceP == 1 || chanceP == 2 || chanceP == 3)
    {
        puts("Nice! You just found a potion! It heals 10 hp.");
        fprintf(fp, "Nice! You just found a potion! It heals 10 hp.\n");
        (*potion) += 1;
    }

    getchar();
    puts("You keep walking along and don't see the kingdom anywhere yet. You see a house\nup ahead and");
    fprintf(fp, "You keep walking along and don't see the kingdom anywhere yet. You see a house\nup ahead and\n");
    puts("A) Go to the house and knock on the door\nB) Continue on, ignoring the house\nC) Try to steal from it\n");
    fprintf(fp, "A) Go to the house and knock on the door\nB) Continue on, ignoring the house\nC) Try to steal from it\n\n");
    scanf("%c", &choices);

    // Error check
    while(choices != 'a' && choices != 'A' && choices != 'b' && choices != 'B' && choices != 'c' && choices != 'C')
    {
        puts("That choice is invalid, try again.");
        puts("A) Go to the house and knock on the door\nB) Continue on, ignoring the house\nC) Try to steal from it\n");
        scanf("%c", &choices);
    }

    insertNode(choices);
    fprintf(fp, "%c\n", choices);

    // Go to house and knock
    if(choices == 'a' || choices == 'A')
    {
        puts("\nYou go up to the house and knock on the door. The person opens the door, seemingto be a lumberjack.");
        fprintf(fp, "\nYou go up to the house and knock on the door. The person opens the door, seemingto be a lumberjack.\n");
        puts("As you talk to him, you figure out his name is Joey. He used to live in the\nkingdom on Nimbida, but decided that the life inside the kingdom was to much and decided to move to the countryside.");
        fprintf(fp, "As you talk to him, you figure out his name is Joey. He used to live in the\nkingdom on Nimbida, but decided that the life inside the kingdom was to much and decided to move to the countryside.\n");
        puts("You ask how far away the kingdom is from his house and says its about a 2 hour\nwalk.");
        fprintf(fp, "You ask how far away the kingdom is from his house and says its about a 2 hour\nwalk.\n");
        puts("\nHe realizes its getting late and asks you if you would like to stay the night. You \nA) Stay with him in his house for the night\nB) Keep moving\n\n");
        fprintf(fp, "\nHe realizes its getting late and asks you if you would like to stay the night. You \nA) Stay with him in his house for the night\nB) Keep moving\n\n\n");
        getchar();
        scanf("%c", &toHouse);

        // Error check
        while(toHouse != 'a' && toHouse != 'A' && toHouse != 'b' && toHouse != 'B')
        {
            puts("That is an invalid choice, try again.");
            puts("He realizes its getting late and asks you if you would like to stay the night. You \nA) Stay with him in his house for the night\nB) Keep moving\n\n");
            scanf("%c", &toHouse);
        }
        getchar();

        // Stay inside house for night
        if(toHouse == 'a' || toHouse == 'A')
        {
            puts("You accept his offer and enter his house. He says he was making dinner and asks if you would like some. You and Joey eat dinner and then sleep the night.");
            fprintf(fp, "You accept his offer and enter his house. He says he was making dinner and asks if you would like some. You and Joey eat dinner and then sleep the night.\n");
            puts("The next day, you wake up and check your belongings. Luckily, everything is still with you. Both of you eat breakfast and you tell him that you must keep going to the kingdom. You guys say goodbye and keep moving.");
            fprintf(fp, "The next day, you wake up and check your belongings. Luckily, everything is still with you. Both of you eat breakfast and you tell him that you must keep going to the kingdom. You guys say goodbye and keep moving.\n");
            chanceP = rand()%10 + 1;
            if(chanceP == 1 || chanceP == 2 || chanceP == 3)
            {
                puts("Nice! You just found a potion! It heals 10 hp.");
                fprintf(fp, "Nice! You just found a potion! It heals 10 hp.\n");
                (*potion) += 1;
            }
        }

        // Keep moving into night
        else if(toHouse == 'b' || toHouse == 'B')
        {
            puts("You respectively decline his offer and thank him for his hospitality. As you keep moving along into the night, you can't see much since you don't have light. You feel something tugging on your leg hard. You look down and see a wolf! You get into a fight.\n");
            fprintf(fp, "You respectively decline his offer and thank him for his hospitality. As you keep moving along into the night, you can't see much since you don't have light. You feel something tugging on your leg hard. You look down and see a wolf! You get into a fight.\n\n");

            // Battle
            while(enemyHealth > 0 || characterHeath <= 0)
            {
                getchar();
                printf("\nYou have %i health. The wolf has %i health.\n", characterHeath, enemyHealth);
                printf("What do you do?\nA) Attack\nB) Run away\nC) Use Potion\n");
                scanf("%c", &menu);

                 //Error Check
                while(menu != 'a' && menu != 'A' && menu != 'b' && menu != 'B' && menu != 'c' && menu != 'C')
                {
                    puts("That is not a valid choice, try again.");
                    printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
                    scanf("%c", &menu);
                    puts("");
                }

                if(menu == 'a' || menu == 'A')
                {
                    charAttack = rand()%10 + 1;
                    if(character == 'a' || character == 'A')
                        printf("\nYou swing your sword and deal %i damage.\n", charAttack);
                    else if(character == 'b' || character == 'B')
                        printf("\nYou cast a spell and deal %i damage.\n", charAttack);
                    else if(character == 'd' || character == 'D')
                        printf("\nYou hit the wolf with your mighty hammer and deal %i damage.\n", charAttack);
                    else if(character == 'c' || character == 'C')
                        printf("\nYou go in for the attack dealing %i damage.\n\n", charAttack);
                    enemyAttack = rand()%10 + 1;
                    printf("The knight hits you for %i damage.\n", enemyAttack);
                    characterHeath = characterHeath - enemyAttack;
                    enemyHealth = enemyHealth - charAttack;
                    if(enemyHealth <= 0)
                    {
                        puts("Congratulations! You have defeated the wolf! You skin the wolf and take it's meat.\n");
                        fprintf(fp, "Congratulations! You have defeated the wolf! You skin the wolf and take it's meat.\n\n");
                        break;
                    }
                    else if(characterHeath <= 0)
                    {
                        puts("Oh No! You have died! Looks like this adventure is over.");
                        fprintf(fp, "Oh No! You have died! Looks like this adventure is over.");
                        exit(1);
                    }
                }
                else if(menu == 'b' || menu == 'B')
                {
                    runAway = rand()%10 + 1;
                    if(runAway >= 6)
                    {
                        puts("You try to run away. Your efforts succeeded and move on with your journey.");
                        fprintf(fp, "You try to run away. Your efforts succeeded and move on with your journey.\n");
                        break;
                    }
                    else if(runAway <= 5)
                    {
                        puts("You try to run away. Looks like you're still in this fight.");
                        fprintf(fp, "You try to run away. Looks like you're still in this fight.\n");
                        menu = 'a';
                        enemyAttack = rand()%10 + 1;
                        printf("The knight hits you for %i damage.\n", enemyAttack);
                    }
                }
                //Heal with Potion
                else if(menu == 'c' || menu == 'C')
                {
                    if((*potion) > 0)
                    {
                        (*potion)--;
                        characterHeath += 10;
                        printf("You healed yourself for 10 hp, making your health %i\n", characterHeath);
                        fprintf(fp, "You healed yourself for 10 hp, making your health %i\n", characterHeath);
                    }

                    else if((*potion) == 0)
                    {
                        puts("You don't have any potions to use! Sorry!\n");
                    }
                }
            }
        puts("After the fight, you rush to get to some sort of shelter to rest the night. You find a big overhanging rock and make camp. You make a fire, find something to eat, and sleep.");
        fprintf(fp, "After the fight, you rush to get to some sort of shelter to rest the night. You find a big overhanging rock and make camp. You make a fire, find something to eat, and sleep.\n");
        puts("You wake up the next day uneasy.");
        fprintf(fp, "You wake up the next day uneasy.\n");
        }
    }

    // Keep moving, skiping house
    else if(choices == 'b' || choices == 'B')
    {
        puts("You skip the house and keep moving on the path. As you keep moving along into\nthe night, you can't see much since you don't have light. You feel something\ntugging on your leg hard. You look down and see a wolf! You get into a fight.\n");
        fprintf(fp, "You skip the house and keep moving on the path. As you keep moving along into\nthe night, you can't see much since you don't have light. You feel something\ntugging on your leg hard. You look down and see a wolf! You get into a fight.\n\n");

        // Battle
        while(enemyHealth > 0 || characterHeath <= 0)
        {
            getchar();
            printf("\nYou have %i health. The wolf has %i health.\n", characterHeath, enemyHealth);
            printf("What do you do?\nA) Attack\nB) Run away\nC) Use Potion\n");
            scanf("%c", &menu);

             //Error Check
            while(menu != 'a' && menu != 'A' && menu != 'b' && menu != 'B' && menu != 'c' && menu != 'C')
            {
                puts("That is not a valid choice, try again.");
                printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
                scanf("%c", &menu);
                puts("");
            }

            if(menu == 'a' || menu == 'A')
            {
                charAttack = rand()%10 + 1;
                if(character == 'a' || character == 'A')
                    printf("\nYou swing your sword and deal %i damage.\n", charAttack);
                else if(character == 'b' || character == 'B')
                    printf("\nYou cast a spell and deal %i damage.\n", charAttack);
                else if(character == 'd' || character == 'D')
                    printf("\nYou hit the wolf with your mighty hammer and deal %i damage.\n", charAttack);
                else if(character == 'c' || character == 'C')
                    printf("\nYou go in for the attack dealing %i damage.\n\n", charAttack);
                enemyAttack = rand()%10 + 1;
                printf("The knight hits you for %i damage.\n", enemyAttack);
                characterHeath = characterHeath - enemyAttack;
                enemyHealth = enemyHealth - charAttack;
                if(enemyHealth <= 0)
                {
                    puts("Congratulations! You have defeated the wolf! You skin the wolf and take it's meat.\n");
                    fprintf(fp, "Congratulations! You have defeated the wolf! You skin the wolf and take it's meat.\n\n");
                    break;
                }
                else if(characterHeath <= 0)
                {
                    puts("Oh No! You have died! Looks like this adventure is over.");
                    fprintf(fp, "Oh No! You have died! Looks like this adventure is over.\n");
                    exit(1);
                }
            }

            // Run away
            else if(menu == 'b' || menu == 'B')
            {
                runAway = rand()%10 + 1;
                if(runAway >= 6)
                {
                    puts("You try to run away. Your efforts succeeded and move on with your journey.");
                    fprintf(fp, "You try to run away. Your efforts succeeded and move on with your journey.\n");
                    break;
                }
                else if(runAway <= 5)
                {
                    puts("You try to run away. Looks like you're still in this fight.");
                    menu = 'a';
                    enemyAttack = rand()%10 + 1;
                    printf("The knight hits you for %i damage.\n", enemyAttack);
                }
            }

            //Heal with Potion
            else if(menu == 'c' || menu == 'C')
            {
                if((*potion) > 0)
                {
                    (*potion)--;
                    characterHeath += 10;
                    printf("You healed yourself for 10 hp, making your health %i\n", characterHeath);
                    fprintf(fp, "You healed yourself for 10 hp, making your health %i\n\n", characterHeath);
                }

                else if((*potion) == 0)
                {
                    puts("You don't have any potions to use! Sorry!\n");
                }
            }
        }
        puts("After the fight, you rush to get to some sort of shelter to rest the night. You find a big overhanging rock and make camp. You make a fire, find something to\neat, and sleep.");
        fprintf(fp, "After the fight, you rush to get to some sort of shelter to rest the night. You find a big overhanging rock and make camp. You make a fire, find something to\neat, and sleep.\n");
        puts("You wake up the next day uneasy.");
        fprintf(fp, "You wake up the next day uneasy.\n");
    }

    // Rob the house
    else if(choices == 'c' || choices == 'C')
    {
        puts("You go up to the house as stealthy as you can. You see a window on the side and enter it, it seems as if you are in a bedroom. You hear the voice of a man, so you hide in the closet. Once he moves to the other room, you get out and go through his belongings. The man comes in hearing noices, but you don't notice. You get into a fight.");
        fprintf(fp, "You go up to the house as stealthy as you can. You see a window on the side and enter it, it seems as if you are in a bedroom. You hear the voice of a man, so you hide in the closet. Once he moves to the other room, you get out and go through his belongings. The man comes in hearing noices, but you don't notice. You get into a fight.\n");

        // Battle
        while(enemyHealth > 0 || characterHeath <= 0)
        {
            getchar();
            printf("\nYou have %i health. The man has %i health.\n", characterHeath, enemyHealth);
            printf("What do you do?\nA) Attack\nB) Run away\nC) Use Potion\n");
            scanf("%c", &menu);

             //Error Check
            while(menu != 'a' && menu != 'A' && menu != 'b' && menu != 'B' && menu != 'c' && menu != 'C')
            {
                puts("That is not a valid choice, try again.");
                printf("What do you do?\nA) Attack\nB) Run away\nC) Use potion\n");
                scanf("%c", &menu);
                puts("");
            }

            if(menu == 'a' || menu == 'A')
            {
                charAttack = rand()%10 + 1;
                if(character == 'a' || character == 'A')
                    printf("\nYou swing your sword and deal %i damage.\n", charAttack);
                else if(character == 'b' || character == 'B')
                    printf("\nYou cast a spell and deal %i damage.\n", charAttack);
                else if(character == 'd' || character == 'D')
                    printf("\nYou hit the man with your mighty hammer and deal %i damage.\n", charAttack);
                else if(character == 'c' || character == 'C')
                    printf("\nYou go in for the attack dealing %i damage.\n\n", charAttack);
                enemyAttack = rand()%10 + 1;
                printf("The knight hits you for %i damage.\n", enemyAttack);
                characterHeath = characterHeath - enemyAttack;
                enemyHealth = enemyHealth - charAttack;
                if(enemyHealth <= 0)
                {
                    puts("Congratulations! You have defeated the man! You loot the body and his house.\n");
                    fprintf(fp, "Congratulations! You have defeated the man! You loot the body and his house.\n\n");
                    break;
                }
                else if(characterHeath <= 0)
                {
                    puts("Oh No! You have died! Looks like this adventure is over.");
                    fprintf(fp, "Oh No! You have died! Looks like this adventure is over.\n");
                    exit(1);
                }
            }
            else if(menu == 'b' || menu == 'B')
            {
                runAway = rand()%10 + 1;
                if(runAway >= 6)
                {
                    puts("\nYou try to run away. Your efforts succeeded and move on with your journey.\n");
                    fprintf(fp, "\nYou try to run away. Your efforts succeeded and move on with your journey.\n\n");
                    break;
                }
                else if(runAway <= 5)
                {
                    puts("You try to run away. Looks like you're still in this fight.");
                    menu = 'a';
                    enemyAttack = rand()%10 + 1;
                    printf("The knight hits you for %i damage.\n", enemyAttack);
                }
            }
            //Heal with Potion
            else if(menu == 'c' || menu == 'C')
            {
                if((*potion) > 0)
                {
                    (*potion)--;
                    characterHeath += 10;
                    printf("You healed yourself for 10 hp, making your health %i\n", characterHeath);
                    fprintf(fp, "You healed yourself for 10 hp, making your health %i\n\n", characterHeath);
                }

                else if((*potion) == 0)
                {
                    puts("You don't have any potions to use! Sorry!\n");
                }
            }
        }
        puts("You sleep the night in the house. The next day, you make breakfast and keep moving.");
        fprintf(fp, "You sleep the night in the house. The next day, you make breakfast and keep moving.\n");
    }
    fclose(fp);
}

void read()
{
    FILE *fp;
    char store;

    if((fp = fopen("Text Adventure.txt", "r")) == NULL)
    {
        puts("Cannot open the file.");
        exit(1);
    }

    while((store = fgetc(fp)) != EOF)
        printf("%c", store);

    if((store = fgetc(fp)) == EOF)
        puts("End of the file.");

    fclose(fp);
}

void insertNode(char item)
{
    NODEPTR newptr, previousptr, currentptr;

    previousptr = NULL;
    currentptr = start;

    newptr = malloc(sizeof(NODE));

    if(newptr)
    {
        //load new “node” with passed information
        newptr -> data = item;
        newptr -> nextptr = NULL;

        if(start == NULL)
            start = newptr;

        while(currentptr != NULL)
        {
            previousptr = currentptr;
            currentptr = currentptr -> nextptr;
        }
        if (previousptr != NULL) //insert at tail of list
        {
            previousptr -> nextptr = newptr;
        }
    }
    else
        printf("%c not inserted. No memory available.\n", item);
}

void printNodes()
{
    NODEPTR ptr = start;
    int i = 1;

    while(ptr != NULL)
    {
        printf("Choice %i: %c\n", i, ptr -> data);
        i++;
        ptr = ptr -> nextptr;
    }
}

void freeNodes()
{
    NODEPTR ptr = start, next;

    while(ptr != NULL)
    {
        next = ptr -> nextptr;
        free(ptr);
        ptr = next;
    }
}
