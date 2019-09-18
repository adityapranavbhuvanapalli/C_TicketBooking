#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct timing
{
    int max,flag;
    int bap,bap1;
}s[3];
struct user
{
    int id;
    char name[50];
    char pwd[50];
}*u;
typedef struct user* USER;
FILE *fp;
void receipt(int n,int ticno,int dum)
{
    int i;
    FILE *fp;
    fp=fopen("receipt.txt","w");
    fprintf(fp,"Receipt Number    :\t%d\n",ticno);
    fprintf(fp,"Number of tickets :\t%d\n",n);
    fprintf(fp,"Seats             : ");
    for(i=0;i<n;i++)
    {
        fprintf(fp,"# %d\n\t\t\t\t\t",dum++);
    }
    fclose(fp);
}
void ticket_progress(struct timing s,int abc)
{
    FILE *fp;
    int n,ticno;
    int dum=s.bap+1;
    printf("\nNo. of tickets available : %d",s.max-s.bap);
    printf("\nEnter number of tickets (Maximum alloted to each person is 5)  :");
    scanf("%d",&n);
    if(n>5)
    {
        printf("Maximum alloted to a person is 5\a");
        fflush(stdin);
        getch();
        system("cls");
        ticket();
    }
    else
    {
        if(s.bap+n>s.max)
        {
            system("cls");
            printf("\n------HOUSE FULL!!!!!!!------");
            switch(abc)
            {
                case 1:fp=fopen("inc.txt","w");break;
                case 2:fp=fopen("inc1.txt","w");break;
                case 3:fp=fopen("inc2.txt","w");break;
                case 4:fp=fopen("inc3.txt","w");break;
            }
            fprintf(fp,"%d %d",0*s.bap,s.bap1++);
            fclose(fp);
            getchar();
            getchar();
            system("cls");
            program();
        }
        ticno=receiptnum();
        receipt(n,ticno,dum);
        switch(abc)
        {
            case 1:fp=fopen("inc.txt","w");break;
            case 2:fp=fopen("inc1.txt","w");break;
            case 3:fp=fopen("inc2.txt","w");break;
            case 4:fp=fopen("inc3.txt","w");break;
        }
        fprintf(fp,"%d %d",s.bap+=n,s.bap1);
        fclose(fp);
    }
}
int receiptnum()
{
    FILE *fp;
    int receipt_number;
    fp=fopen("recnum.txt","r");
    fscanf(fp,"%d",&receipt_number);
    fclose(fp);
    fp=fopen("recnum.txt","w");
    fprintf(fp,"%d",++receipt_number);
    fclose(fp);
    return receipt_number;
}
void ticket()
{
    FILE *fp;
    int st,i;
    fp=fopen("inc.txt","r");
    fscanf(fp,"%d %d",&s[0].bap,&s[0].bap1);
    fclose(fp);
    fp=fopen("inc1.txt","r");
    fscanf(fp,"%d %d",&s[1].bap,&s[1].bap1);
    fclose(fp);
    fp=fopen("inc2.txt","r");
    fscanf(fp,"%d %d",&s[2].bap,&s[2].bap1);
    fclose(fp);
    fp=fopen("inc3.txt","r");
    fscanf(fp,"%d %d",&s[3].bap,&s[3].bap1);
    fclose(fp);
    printf("\nEnter the Show Timing.\nPress\n1. 11:30 am\n2. 2:30 pm\n3. 6:30 pm\n4. 9:30 pm\n");
    scanf("%d",&st);
    switch(st)
    {
        case 1:ticket_progress(s[0],st);break;
        case 2:ticket_progress(s[1],st);break;
        case 3:ticket_progress(s[2],st);break;
        case 4:ticket_progress(s[3],st);break;
    }
}

void receipt_print()
{
    char rec[100];
    FILE *fp;
    fp=fopen("receipt.txt","r");
    while(fscanf(fp,"%s",rec)!=EOF)
    {
        printf("%s",rec);
    }
    fclose(fp);
}
void program()
{
    int log;
    s[0].flag=s[1].flag=s[2].flag=s[3].flag=0;
    s[0].max=s[1].max=s[2].max=s[3].max=10;
    ticket();
    receipt_print();
    printf("\nPress 0 to Logout else 1\n");
    scanf("%d",&log);
    system("cls");
    if(log==0)
    {
        main();
    }
    program();
}
USER login(USER s)
{
    int uid,id;
    char name[50],password[50];
    char c,passkey[50];
    int i=0;
    printf("Enter the User ID:");
    scanf("%d",&uid);
    printf("Enter Password :");
    while(c!=13)
    {
        c=getch();
        if(c!=13 && c!=8)
        {
            putch('#');
            passkey[i]=c;
            i++;
        }
    }
    passkey[i] = '\0';
    fp=fopen("user.txt","r");
    while(fscanf(fp,"%d %s %s\n",&id,password,name)!=EOF)
    {
        if(id==uid)
        {
            break;
        }
    }
    fclose(fp);
    if(strcmp(password,passkey)==0)
    {
        system("cls");
        printf("\n--------------------------------------------------------------------------------\n");
        printf("Correct Password\n                         :)");
        printf("\nPress any key to continue");
        printf("\n--------------------------------------------------------------------------------\n");
        getch();
        system("cls");
        u=(USER)malloc(sizeof(struct user));
        u->id=id;
        strcpy(name,u->name);
        strcpy(password,u->pwd);
    }
    else
    {
        system("cls");
        printf("\n--------------------------------------------------------------------------------\n");
        printf("\n\aWarning!! Incorrect Password.\n        :(\n");
        printf("\n--------------------------------------------------------------------------------\n");
        getch();
        system("cls");
        main();
    }
    return s;
}
USER signup(USER u)
{
    int i=0,id;
    char name[50],pwd[50],c,temp[50],temp1[50];
    printf("Enter your Name(A Single String) :");
    scanf("%s",name);

    printf("Enter your desired password      :");
    while(c!=13)
    {
        c=getch();
        if(c!=13 && c!=8)
        {
            putch('#');
            pwd[i]=c;
            i++;
        }
    }
    pwd[i] = '\0';
    fp=fopen("user.txt","r");
    while(fscanf(fp,"%d %s %s\n",&id,temp,temp1)!=EOF);
    fclose(fp);
    id++;
    fp=fopen("user.txt","a");
    fprintf(fp,"%d %s %s\n",id,pwd,name);
    fclose(fp);
    printf("\nYour User ID is %d",id);
    getch();
    u=(USER)malloc(sizeof(struct user));
    u->id=id;
    strcpy(name,u->name);
    strcpy(pwd,u->pwd);
    return u;
}
int main()
{
    system("cls");
    fflush(stdin);
    int ch;
    printf("Enter choice\n 1. Login\n 2. Signup\n 3. EXIT\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:u=login(u);program(u);break;
        case 2:u=signup(u);program(u);break;
        case 3:exit(0);
    }
    main();
    return 0;
}

