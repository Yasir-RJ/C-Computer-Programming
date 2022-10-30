
// program for bank accounts
// by: Yasir Riyadh Jabbar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KONTO 1000
#define MAX_NAMN 15


struct bankkonton{ // template for BankKonton structure
    unsigned int  kontonummer;
    char agare[MAX_NAMN+1];
    int  saldo;
};
typedef struct bankkonton BANKKONTON;

//huvud funktioner
bool readFromFile(int *pAccounts,BANKKONTON BK[],char filename[]); // lasa filen
unsigned int accountManagement(void); // visa menyn
void registerAccount(int *pAccounts, BANKKONTON BK[]); // val 1
void viewAccounts(int Accounts, BANKKONTON BK[]); // val 2
void sortAccounts(int Accounts, BANKKONTON BK[]); // val 3
void searchAccounts(int Accounts, BANKKONTON BK[]); // val 4
void changeBalance(int Accounts, BANKKONTON BK[]); // val 5
void unregisterAccount(int *pAccounts, BANKKONTON BK[]); // val 6
void statistics(int Accounts, BANKKONTON BK[]); // val 7  *** Extra uppgifter for lab1***

void saveAndExit(int Accounts,bool file_exist,char* filename, BANKKONTON BK[]); // val 9

//accessoriska funktioner
void ToUpperCase(int Accounts, BANKKONTON BK[]);
void swap(int i,int j,BANKKONTON BK[]);
void SplitName(char *Name, char words[][MAX_NAMN+1]);
void SortByBalance(int Accounts, BANKKONTON BK[]);
bool SearchByName(int Accounts, BANKKONTON BK[]);
bool SearchByNumber(int Accounts, BANKKONTON BK[]);
bool SearchByBalance(int Accounts, BANKKONTON BK[]);
bool BalanceByNumber(int Accounts, BANKKONTON BK[]);
bool deleteAccount(int *pAccounts, BANKKONTON BK[]);


int main(){
    BANKKONTON bankkonton[MAX_KONTO]={0,"\0",0};
    unsigned int nrOfAccounts=0, selection;
    char filename[255]={"\0"};
    bool file_exist=false;

    system("color 0e");
    file_exist=readFromFile(&nrOfAccounts,bankkonton,filename); // lasa filen
    while(1){
        selection=accountManagement(); // visa menyn
        switch (selection){
            case 1: //Registrera nya konton
                registerAccount(&nrOfAccounts, bankkonton);
                break;
            case 2: //Skriva ut alla konton
                if(nrOfAccounts > 0) viewAccounts(nrOfAccounts, bankkonton);
                else printf("\n... Det finns inga konton att skriva ut!\n");
                break;
            case 3: //Sortera konton
                if(nrOfAccounts > 1) sortAccounts(nrOfAccounts, bankkonton);
                else printf("\n... Det finns inga tillrackligt konton for att sortera!\n");
                break;
            case 4: //Soka efter konto
                if(nrOfAccounts > 0) searchAccounts(nrOfAccounts, bankkonton);
                else printf("\n... Det finns inga konton att soka!\n");
                break;
            case 5: //Andra saldot pa ett konto
                if(nrOfAccounts > 0) changeBalance(nrOfAccounts, bankkonton);
                else printf("\n... Det finns inga konton att andra!\n");
                break;
            case 6: //Avregistrera ett konto
                if(nrOfAccounts > 0) unregisterAccount(&nrOfAccounts, bankkonton);
                else printf("\n... Det finns inga konton att avregistrera!\n");
                break;
            case 7: //Statistik
                if(nrOfAccounts > 0) statistics(nrOfAccounts, bankkonton);
                else printf("\n... Det finns inte tillrackligt konton for att tillampa statistik!\n");
                break;
            case 8: //Overforing   *** ej implementerad ***
                break;
            case 9: //Avsluta
                if(nrOfAccounts > 0) saveAndExit(nrOfAccounts,file_exist,filename,bankkonton);
                return 0;
            default:
                break;
        }
    }
    return 0;
}

bool readFromFile(int *pAccounts,BANKKONTON BK[],char filename[]){
    char Fname[MAX_NAMN+1],Lname[MAX_NAMN+1];
    unsigned int i;
    bool file_exist;
    FILE *fp;

    printf("\nAnge Informationsfilnamnet (textfil): ");
    scanf("%s%*c",filename);
    fp = fopen(filename, "r");
    if (fp != NULL){ // fil OK
        file_exist=true;
        fscanf(fp, "%d", pAccounts);
        if (*pAccounts > MAX_KONTO){
            printf("\n... Antalet konton overstiger MAX KONTO!\n");
            exit(0);
        }
        for(i=0;i<(*pAccounts);i++){
            fscanf(fp, "%d %s %s %d", &BK[i].kontonummer,Fname,Lname,&BK[i].saldo);
            strcpy(BK[i].agare,Fname);
            strcat(BK[i].agare," ");
            strcat(BK[i].agare,Lname);
            if(strlen(BK[i].agare)>MAX_NAMN){
                printf("\n... Antalet tecken i Namn overstiger MAX NAMN!\n");
                exit(0);
            }
            ToUpperCase(*pAccounts, BK);
        }
        fclose(fp);
    }
    else{
        printf("\n... Kunde inte oppna filen eller ingen sadan fil existerar!\n");
        file_exist=false;
    }
    return file_exist;
}

unsigned int accountManagement(void){
    unsigned int sel;
    char str[10];
    do{
    printf("\n(1) Registrera nya konton");
    printf("\n(2) Skriva ut alla konton");
    printf("\n(3) Sortera konton");
    printf("\n(4) Soka efter konto");
    printf("\n(5) Andra saldot pa ett konto");
    printf("\n(6) Avregistrera ett konto");
    printf("\n(7) Statistik");
    printf("\n(8) Overforing");
    printf("\n(9) Avsluta\n\n");
    printf("Ange val:");
    fgets(str, 10, stdin);
    sel = atoi(str);
    if(sel<1 || sel>9) printf("\n... Ogiltigt val!\n");
    }while(sel==0);
    return sel;
}

void registerAccount(int *pAccounts, BANKKONTON BK[]){
	int i,readInteger;
	unsigned int ID;
	char name[255],tmp;
	bool ID_exist=false;
	printf("\nRegistrera nya konton\n");
	while (*pAccounts < MAX_KONTO) {
		printf("Ange kontonummer (q for att avsluta): ");
		readInteger = scanf("%u%*c", &ID);
		if (readInteger){
		    for(i=0;i<(*pAccounts);i++)
                if(BK[i].kontonummer==ID) ID_exist=true;
            if(ID_exist){
                printf("Kontonumret finns redan\n");
                ID_exist=false;
                continue;
            }
            BK[*pAccounts].kontonummer=ID;
            printf("Ange agare: ");
            gets(name);
            if(strlen(name)>MAX_NAMN){
                printf("\nAntalet tecken i Namn overstiger MAX NAMN!\n");
                continue;
            }
            strcpy(BK[*pAccounts].agare,name);
            BK[*pAccounts].saldo=0;
            (*pAccounts)++;
		}
		else {
			scanf(" %c%*c", &tmp);
			if (tmp == 'q') break;
		}
	}
	ToUpperCase(*pAccounts, BK);
	return ;
}

void viewAccounts(int Accounts, BANKKONTON BK[]){
    int i;
    printf("\nAlla konton");
    printf("\nKonto-nr  Agare               Saldo (kr)");
    printf("\n________________________________________\n");
    for(i=0;i<Accounts;i++)
        printf("%06u    %-15s     %-6d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
    return;
}


void sortAccounts(int Accounts, BANKKONTON BK[]){
    unsigned int i,j,sel;
    char Lname1[MAX_NAMN+1]={"\0"},Lname2[MAX_NAMN+1]={"\0"};
    char words[2][MAX_NAMN+1];
    do{
        printf("\nVill du sortera efter konto-nr (1), agare (2) eller saldo (3):");
        scanf("%d%*c",&sel);
    }while(sel<1 || sel>3);
    switch (sel){
            case 1: // sortera efter konto-nr
                for(i=0;i<Accounts-1;i++)
                    for(j=0;j<Accounts-1-i;j++)
                        if(BK[j].kontonummer>BK[j+1].kontonummer) swap(j,j+1,BK);
                break;
            case 2:  //sortera efter agare
                for(i=0;i<Accounts-1;i++)
                    for(j=0;j<Accounts-1-i;j++){
                        SplitName(BK[j].agare, words);
                        strcpy(Lname1,words[1]);
                        SplitName(BK[j+1].agare, words);
                        strcpy(Lname2,words[1]);
                        if(strcmp(Lname1,Lname2)>0) swap(j,j+1,BK);
                    }
                break;
            case 3:  //sortera efter saldo
                SortByBalance(Accounts, BK);
                break;
            default:
                break;
        }
}

void searchAccounts(int Accounts, BANKKONTON BK[]){
    int sel=0;
    bool konExist;
    printf("\nSokning");
    while(sel!=4){
        do{
            printf("\n(1) konto-nr");
            printf("\n(2) agare");
            printf("\n(3) saldo");
            printf("\n(4) huvudmeny");
            printf("\nAnge val:");
            scanf("%d%*c",&sel);
        }while(sel<1 || sel>4);
        switch(sel){
            case 1:
                konExist=SearchByNumber(Accounts, BK);
                if(konExist==false) printf("Kontonummer saknas\n");
                break;

            case 2:
                konExist=SearchByName(Accounts, BK);
                if(konExist==false) printf("Agare saknas\n");
                break;

            case 3:
                konExist=SearchByBalance(Accounts, BK);
                if(konExist==false) printf("Saldo saknas\n");
                break;

            case 4:
                break;
        }
    }
}

void changeBalance(int Accounts, BANKKONTON BK[]){
    unsigned int i,sel=0;
    bool konExist;
    printf("\nAndra saldo");
    do{
       printf("\nVill du ange konto-nr (1) eller soka pa agare (2): ");
       scanf("%d%*c",&sel);
    }while(sel<1 || sel>2);
    switch(sel){
        case 1:
            konExist=BalanceByNumber(Accounts, BK);
            if(konExist==false) printf("Kontonummer saknas\n");
            break;

        case 2:
            konExist=SearchByName(Accounts, BK);
            if(konExist==false){
                printf("Agare saknas\n");
                break;
            }
            konExist=BalanceByNumber(Accounts, BK);
            if(konExist==false) printf("Du har inte tillrackligt med saldo for att ta ut detta belopp!\n");
            break;
    }
}

void unregisterAccount(int *pAccounts, BANKKONTON BK[]){
    unsigned int i,sel=0;
    bool konExist;
    printf("\nAvregistrera");
    do{
       printf("\nVill du ange konto-nr (1) eller soka pa agare (2): ");
       scanf("%d%*c",&sel);
    }while(sel<1 || sel>2);
    switch(sel){
        case 1:
            konExist=deleteAccount(pAccounts, BK);
            if(konExist==false) printf("Kontot kan inte tas bort eftersom saldot inte ar 0.\n");
            break;

        case 2:
            konExist=SearchByName(*pAccounts, BK);
            if(konExist==false){
                printf("Agare saknas\n");
                break;
            }
            konExist=deleteAccount(pAccounts, BK);
            if(konExist==false) printf("Kontot kan inte tas bort eftersom saldot inte ar 0.\n");
            break;
    }
}

void statistics(int Accounts, BANKKONTON BK[]){
    unsigned int i,j=0,saldo[Accounts],frequency[Accounts],maximum,index;
    int previous, count=1;
    BANKKONTON tmp,tmpArray[Accounts];
    double sum=0,median=0;

    printf("\nStatistik - saldo");

    for(i=0;i<Accounts;i++) // Hitta median
        tmpArray[i]=BK[i];
    SortByBalance(Accounts, tmpArray);
    if(Accounts % 2 == 0)
        median = (tmpArray[(Accounts-1)/2].saldo + tmpArray[Accounts/2].saldo)/2.0;
    else
        median = tmpArray[Accounts/2].saldo;
    printf("\nMedian (kr): %.2lf",(double)median);

    for(i=0;i<Accounts;i++) // Hitta medel
        sum=sum+BK[i].saldo;
    printf("\nMedel (kr): %.2lf\n",(double)(sum/Accounts));

    printf("Typvarde (kr): "); // Hitta typvarde
    previous = tmpArray[0].saldo;
    for (i = 1; i < Accounts; i++) {
        if (tmpArray[i].saldo == previous) count++;
        else{
            saldo[j]=previous;
            frequency[j]=count;
            j++;
            previous = tmpArray[i].saldo;
            count = 1;
        }
    }
    saldo[j]=previous;
    frequency[j]=count;
    maximum=frequency[0];
    index=0;
    for (i = 1; i <= j; i++){
        if(maximum<frequency[i]){
            maximum=frequency[i];
            index=i;
        }
    }
    printf("%d", saldo[index]);
    frequency[index]=0;
    for (i = 1; i <= j; i++){
        if(frequency[i]==maximum){
             printf(", %d", saldo[i]);
             frequency[i]=0;
        }
    }
    printf("\n");
}

void saveAndExit(int Accounts,bool file_exist,char* filename, BANKKONTON BK[]){
    FILE *fp;
    int i;
    char fileString[255];
    if(file_exist || (filename && filename[0])){
        if ((fp=fopen(filename, "w+")) == NULL){
            printf("\n... Kunde inte oppna eller skriva filen!");
            exit(0);
        }
    fprintf(fp,"%d\n", Accounts);
    for(i=0;i<(Accounts);i++)
            fprintf(fp,"%06d %s %d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
    fclose(fp);
    }
    else{
        printf("\n Ange namnet pa textfilen for att lagra konton:");
        scanf("%s",fileString);
        if ((fp=fopen(fileString, "w+")) == NULL){
            printf("\n... Kan inte oppna eller skriva filen!");
            exit(0);
        }
        fprintf(fp,"%d\n", Accounts);
        for(i=0;i<(Accounts);i++)
            fprintf(fp,"%06d %s %d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
        fclose(fp);
    }
    return;
}


void ToUpperCase(int Accounts, BANKKONTON BK[]){
    int i,j;
    for (i = 0; i<Accounts; i++)
        for (j = 0; (BK[i].agare[j])!='\0'; j++)
            if(BK[i].agare[j] >= 'a' && BK[i].agare[j] <= 'z')
                BK[i].agare[j] = BK[i].agare[j] - 32;
}

swap(int n,int m,BANKKONTON BK[]){
    BANKKONTON tmp;
    tmp=BK[n];
    BK[n]=BK[m];
    BK[m]=tmp;
}

void SplitName(char *Name, char words[][MAX_NAMN+1]){
    int n=0,i,j=0;
	for(i=0;true;i++){
		if(Name[i]!=' ') words[n][j++]=Name[i];
		else{
			words[n][j++]='\0';
			n++;
			j=0;
		}
		if(Name[i]=='\0') break;
	}
}

void SortByBalance(int Accounts, BANKKONTON BK[]){
    unsigned int i,j;
    BANKKONTON tmp;
    for(i=0;i<Accounts-1;i++)
        for(j=0;j<Accounts-1-i;j++)
            if(BK[j].saldo>BK[j+1].saldo) swap(j,j+1,BK);
}

bool SearchByBalance(int Accounts, BANKKONTON BK[]){
    bool konExist=false;
    int i,min,max;
    printf("Ange min:");
    scanf("%d%*c",&min);
    printf("Ange max:");
    scanf("%d%*c",&max);
    printf("\nKonto-nr  Agare               Saldo (kr)");
    printf("\n________________________________________\n");
    for(i=0;i<Accounts;i++)
        if(BK[i].saldo>=min && BK[i].saldo<=max){
            konExist=true;
            printf("%06u    %-15s     %-6d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
       }
    return konExist;
}

bool SearchByNumber(int Accounts, BANKKONTON BK[]){
    unsigned int i,konNr;
    bool konExist=false;
    printf("Ange konto-nr:");
    scanf("%u%*c",&konNr);
    for(i=0;i<Accounts;i++)
        if(BK[i].kontonummer==konNr){
            konExist=true;
            break;
        }
    if(konExist){
        printf("\nKonto-nr  Agare               Saldo (kr)");
        printf("\n________________________________________\n");
        printf("%06u    %-15s     %-6d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
    }
    return konExist;
}

bool SearchByName(int Accounts, BANKKONTON BK[]){
    int i;
    char searchStr[255];
    bool konExist=false;
    printf("Ange sokstrang:");
    scanf("%s%*c",searchStr);
    if(strlen(searchStr)>MAX_NAMN) return false;
    for(i=0;i<strlen(searchStr);i++)
        searchStr[i]=searchStr[i]-32;
        printf("\nKonto-nr  Agare               Saldo (kr)");
        printf("\n________________________________________\n");
        for(i=0;i<Accounts;i++)
            if(strstr(BK[i].agare,searchStr)){
                konExist=true;
                printf("%06u    %-15s     %-6d\n", BK[i].kontonummer,BK[i].agare,BK[i].saldo);
            }
        return konExist;
}

bool BalanceByNumber(int Accounts, BANKKONTON BK[]){
    unsigned int i,sel=0,konNr;
    int ammount;
    bool konExist=false;
    printf("\nAnge konto-nr:");
    scanf("%u%*c",&konNr);
    for(i=0;i<Accounts;i++){
        if(BK[i].kontonummer==konNr){
            konExist=true;
            break;
        }
    }
    if(konExist){
        printf("Vill du gora en insattning (1) eller ett uttag (2): ");
        scanf("%u%*c",&sel);
        printf("Ange belopp:");
        scanf("%d%*c",&ammount);
        if(sel==1) BK[i].saldo = BK[i].saldo + ammount;
        if(sel==2){
            if((BK[i].saldo - ammount) < 0) return false;
            else BK[i].saldo = BK[i].saldo - ammount;
        }
        printf("Nytt saldo: %d\n",BK[i].saldo);
    }
    return konExist;
}

bool deleteAccount(int *pAccounts, BANKKONTON BK[]){
    unsigned int i,j,konNr;
    bool konExist=false;
    printf("Ange konto-nr:");
    scanf("%u%*c",&konNr);
    for(i=0;i<(*pAccounts);i++){
        if(BK[i].kontonummer==konNr){
            konExist=true;
            break;
        }
    }
    if(konExist){
        if((BK[i].saldo)!=0) return false;
        else{
            (*pAccounts)-- ; // minska konton med 1
            for(j=i;j<(*pAccounts);j++) // skift konton upp
                BK[j]=BK[j+1];
        }
    }
    return konExist;
}


