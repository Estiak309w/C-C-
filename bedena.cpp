#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char email[100]; // global declaration

int nextid( ) {
    static int last = 0;
    return ++last;
}

void validEmail() {
    char p[] = "Email must contain @ and .";
    while(1) {
        printf("Enter the email: ");
        memset(email, '\0', sizeof email); // all array value will be NULL
        scanf("%s", email);
        int l = strlen(email);
        if(l<=7) {
            printf("%s\n",p);
            continue;
        }
        int flag = 0, f = 0;
        for(int i = 0; i<l; i++) {
            if(email[i]=='@') {
                flag = 1;
            }
            if(email[i]=='.') {
                f = 1;
            }
        }
        if(!flag || !f) {
            printf("%s\n",p);
            continue;
        } else {
            break;
        }
    }
}

void file() {
    FILE *fptr;

    char name[20];
    int result;

    result=nextid();

    fptr = fopen("name_email.txt", "a");

    if (fptr == NULL) {
        printf("File does not exists \n");
        return;
    }

    fprintf(fptr, "ID   = %d\n", result);
    printf("Enter the name : ");
    scanf("%s", name);

    fprintf(fptr, "Name   = %s\n", name);
    validEmail();
    fprintf(fptr, "Email   = %s\n", email);
    fclose(fptr);
}

void addScore(int score) {
    FILE *fptr;
    fptr = fopen("name_email.txt", "a");
    fprintf(fptr, "Score   = %d\n\n\n", score);
    fclose(fptr);

}
int chekTer() {
    while(1) {
        printf("Start the nw game(Y/N) : ");
        char ch;
        fflush(stdin); // flush the input buffer file
        scanf("%c", &ch);
        if(ch=='Y' ||ch=='y') {
            return 1;
        } else if(ch=='N' || ch=='n') {
            return 0;
        } else {
            printf("Invalid Input\n");
        }
    }
}
int main() {
    char play='y';
    int p;
    file();
    int x, i, j, n, c = 0;

    FILE *fp = fopen("test.txt","r"); // open file as read
    char guess[10];
    char secret[10];
    char name[20][20];
    char hints[20][20];

    i = 0;
    while(!feof(fp)) {  // load all name from the file in the "name" variable
        fscanf(fp, "%s", name[i++]);
    }

    FILE *hn = fopen("hints.txt","r"); // open hints file as read
    int h = 0;
    while(!feof(hn)) {  // load all name from the file in the "name" variable
        fscanf(hn, "%s", hints[h++]);
    }

    while(1) {
        int r = rand() % h;
        printf("\n\nPlease guess the word (hints: %s): ", hints[r]);

        scanf("%s",guess);
        if(strcmp(guess, "no")==0) {
            printf("Score:%d\n",c);
            addScore(c); // score will be added end of the file
            int r = chekTer();
            if(r==0) {  // for terminate
                return 0;
            }
            file();
            c = 0;
            continue;
        }
        bool flag = 0;
        for(int i =0 ; i < 2; i++) {
            if(strcmp(name[i], guess)==0) {
                c++;
                flag= 1;
            }
        }
        if(!flag) {
            c--;
        }
        printf("Score: %d", c);
    }
    return 0;
}

//rokimoulik@gmail.com
