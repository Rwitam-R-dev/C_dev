#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_LOGIN_ATTEMPTS 3
#define LOCKOUT_PERIOD 60
#define PASSWORD_SALT "secret"

int i, j;
int main_exit;
void display_login_box(void);
bool is_password_correct(const char *username, const char *password);
void play_welcome_sound_with_username(const char *username);
void play_successful_login_sound(void);
void display_menu(void);
void new_acc(void);
void edit(void);
void transact(void);
void see(void);
void erase(void);
void view_list(void);
void close(void);
struct date
{
    int day;
    int month;
    int year;
};

struct account
{
    char name[60];
    char acc_no[10];
    int age;
    char address[60];
    char Adhar_Number[13];
    char phone[15];
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
};

struct account add, upd, check, rem, transaction;

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}

void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

bool is_alphanumeric(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i]))
            return false;
    }
    return true;
}

bool is_numeric(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool is_valid_adhar_number(const char *adhar)
{
    if (strlen(adhar) != 12)
        return false;

    return is_numeric(adhar);
}

bool is_valid_phone_number(const char *phone)
{
    if (strlen(phone) != 12)
        return false;

    return is_numeric(phone);
}

void new_acc()
{
    int choice;
    FILE *ptr;

    ptr = fopen("record.dat", "a+");
    account_no:
    system("cls");
    printf("\t\t\t\xC2\xB2\xC2\xB2\xC2\xB2 ADD RECORD \xC2\xB2\xC2\xB2\xC2\xB2\xC2\xB2");
    printf("\n\n\nEnter today's date (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &add.deposit.day, &add.deposit.month, &add.deposit.year);
    getchar();

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    add.deposit.day = tm->tm_mday;
    add.deposit.month = tm->tm_mon + 1;
    add.deposit.year = tm->tm_year + 1900;

    printf("Enter the account number: ");
    scanf("%s", check.acc_no);
    getchar();

    while (fscanf(ptr, "%s %s %d/%d/%d %d %s %s %s %s %f %d/%d/%d\n", add.acc_no, add.name, &add.dob.day, &add.dob.month, &add.dob.year, &add.age, add.address, add.Adhar_Number, add.phone, add.acc_type, &add.amt, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF)
    {
        if (strcmp(check.acc_no, add.acc_no) == 0)
        {
            printf("Account number already in use!");
            fordelay(1000000000);
            goto account_no;
        }
    }
    strcpy(add.acc_no, check.acc_no);

    printf("Enter the name: ");
    fgets(add.name, sizeof(add.name), stdin);
    add.name[strlen(add.name) - 1] = '\0';
    getchar();

    printf("Enter the date of birth (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &add.dob.day, &add.dob.month, &add.dob.year);
    getchar();

    printf("Enter the age: ");
    scanf("%d", &add.age);
    getchar();

    printf("Enter the address: ");
    fgets(add.address, sizeof(add.address), stdin);
    add.address[strlen(add.address) - 1] = '\0';

    printf("Enter the Aadhaar Number: ");
    fgets(add.Adhar_Number, sizeof(add.Adhar_Number), stdin);
    add.Adhar_Number[strlen(add.Adhar_Number) - 1] = '\0';

    while (!is_valid_adhar_number(add.Adhar_Number))
    {
        printf("Invalid Aadhaar Number. Enter a valid 12-digit Aadhaar Number: ");
        fgets(add.Adhar_Number, sizeof(add.Adhar_Number), stdin);
        add.Adhar_Number[strlen(add.Adhar_Number) - 1] = '\0';
    }

    printf("Enter the phone number (including country code): ");
    fgets(add.phone, sizeof(add.phone), stdin);
    add.phone[strlen(add.phone) - 1] = '\0';

    while (!is_valid_phone_number(add.phone))
    {
        printf("Invalid phone number. Enter a valid phone number (including country code): ");
        fgets(add.phone, sizeof(add.phone), stdin);
        add.phone[strlen(add.phone) - 1] = '\0';
    }

    printf("Enter the amount to deposit: $");
    scanf("%f", &add.amt);
    getchar();

    printf("Type of account:\n");
    printf("\t#Saving\n");
    printf("\t#Current\n");
    printf("\t#Fixed1 (for 1 year)\n");
    printf("\t#Fixed2 (for 2 years)\n");
    printf("\t#Fixed3 (for 3 years)\n");
    printf("Enter your choice: ");
    fgets(add.acc_type, sizeof(add.acc_type), stdin);
    add.acc_type[strlen(add.acc_type) - 1] = '\0';

    fprintf(ptr, "%s %s %d-%d-%d %d %s %s %s %s %f %d-%d-%d\n", add.acc_no, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.Adhar_Number, add.phone, add.acc_type, add.amt, add.deposit.day, add.deposit.month, add.deposit.year);

    fclose(ptr);
    printf("\nAccount created successfully!");

    add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    getchar();
    system("cls");

    if (main_exit == 1)
        display_menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}


void view_list()
{
    FILE *view;
    view=fopen("record.dat","r");
    int test=0;
    system("cls");
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tPHONE\n");

    while(fscanf(view,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
       {
           printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf",add.acc_no,add.name,add.address,add.phone);
           test++;
       }

    fclose(view);
    if (test==0)
        {   system("cls");
            printf("\nNO RECORDS!!\n");}

    view_list_invalid:
     printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            display_menu();
        else if(main_exit==0)
            void close();
        else
        {
            printf("\nInvalid!\a");
            goto view_list_invalid;
        }
}
void edit(void)
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");

    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);
    while(fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.acc_no==upd.acc_no)
        {   test=1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf("%d",&choice);
            system("cls");
            if(choice==1)
                {printf("Enter the new address:");
                scanf("%s",upd.address);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }
            else if(choice==2)
                {
                    printf("Enter the new phone number:");
                scanf("%lf",&upd.phone);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,upd.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }

        }
        else
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");

if(test!=1)
        {   system("cls");
            printf("\nRecord not found!!\a\a\a");
            edit_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)

                    display_menu();
                else if (main_exit==2)
                    void close();
                else if(main_exit==0)
                    edit();
                else
                    {printf("\nInvalid!\a");
                    goto edit_invalid;}
        }
    else
        {printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            display_menu();
        else
            void close();
        }
}

void transact(void)
{   int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");

        printf("Enter the account no. of the customer:");
    scanf("%d",&transaction.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
   {

            if(add.acc_no==transaction.acc_no)
            {   test=1;
                if(strcmpi(add.acc_type,"fixed1")==0||strcmpi(add.acc_type,"fixed2")==0||strcmpi(add.acc_type,"fixed3")==0)
                {
                    printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                    fordelay(1000000000);
                    system("cls");
                    display_menu();

                }
                printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
                scanf("%d",&choice);
                if (choice==1)
                {
                    printf("Enter the amount you want to deposit:$ ");
                    scanf("%f",&transaction.amt);
                    add.amt+=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                    printf("\n\nDeposited successfully!");
                }
                else
                {
                    printf("Enter the amount you want to withdraw:$ ");
                    scanf("%f",&transaction.amt);
                    add.amt-=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                    printf("\n\nWithdrawn successfully!");
                }

            }
            else
            {
               fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
            }
   }
   fclose(old);
   fclose(newrec);
   remove("record.dat");
   rename("new.dat","record.dat");
   if(test!=1)
   {
       printf("\n\nRecord not found!!");
       transact_invalid:
      printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
      scanf("%d",&main_exit);
      system("cls");
      if (main_exit==0)
        transact();
    else if (main_exit==1)
        display_menu();
    else if (main_exit==2)
        void close();
    else
    {
        printf("\nInvalid!");
        goto transact_invalid;
    }

   }
   else
   {
       printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            display_menu();
        else
            void close();
   }

}
void erase(void)
{
    FILE *old,*newrec;
    int test=0;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d",&rem.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
   {
        if(add.acc_no!=rem.acc_no)
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

        else
            {test++;
            printf("\nRecord deleted successfully!\n");
            }
   }
   fclose(old);
   fclose(newrec);
   remove("record.dat");
   rename("new.dat","record.dat");
   if(test==0)
        {
            printf("\nRecord not found!!\a\a\a");
            erase_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);

                 if (main_exit==1)
                    display_menu();
                else if (main_exit==2)
                    void close();
                else if(main_exit==0)
                    erase();
                else
                    {printf("\nInvalid!\a");
                    goto erase_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            display_menu();
        else
            void close();
        }

}

void see(void)
{
    FILE *ptr;
    int test=0,rate;
    int choice;
    float time;
    float intrst;
    ptr=fopen("record.dat","r");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d",&choice);
    if (choice==1)
    {   printf("Enter the account number:");
        scanf("%d",&check.acc_no);

        while (fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.acc_no==check.acc_no)
            {   system("cls");
                test=1;

                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nAdhar Number:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                 else if(strcmpi(add.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }
    else if (choice==2)
    {   printf("Enter the name:");
        scanf("%s",&check.name);
        while (fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.Adhar_Number,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(strcmpi(add.name,check.name)==0)
            {   system("cls");
                test=1;
                printf("\nAccount No.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nAdhar_Number:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$%.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.Adhar_Number,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                 else if(strcmpi(add.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }


    fclose(ptr);
     if(test!=1)
        {   system("cls");
            printf("\nRecord not found!!\a\a\a");
            see_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)
                    display_menu();
                else if (main_exit==2)
                    void close();
                else if(main_exit==0)
                    see();
                else
                    {
                        system("cls");
                        printf("\nInvalid!\a");
                        goto see_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);}
        if (main_exit==1)
        {
            system("cls");
            display_menu();
        }

        else
           {

             system("cls");
            void close();
            }

}

char *hash_password(char *password)
{
    char *hashed_password = (char *)malloc(MAX_PASSWORD_LENGTH + 1);
    char salted_password[MAX_PASSWORD_LENGTH + 1];
    strcpy(salted_password, PASSWORD_SALT);
    strcat(salted_password, password);
    for (int i = 0; i < strlen(salted_password); i++)
    {
        hashed_password[i] = salted_password[i] ^ 0xFF;
    }
    hashed_password[strlen(salted_password)] = '\0';
    return hashed_password;
}

bool is_password_correct(char *username, char *password)
{
    char *correct_username = "RCCIIT";
    char *correct_password = hash_password("10020903");
    bool is_correct = strcmp(username, correct_username) == 0 && strcmp(hash_password(password), correct_password) == 0;
    free(correct_password);
    return is_correct;
}
void play_welcome_sound_with_username(const char *username)
{
    const int DELAY = 200;
    const int NOTES[] = {523, 587, 659, 587};
    const int DURATIONS[] = {250, 250, 250, 500};
    const int NUM_NOTES = sizeof(NOTES) / sizeof(NOTES[0]);

    for (int i = 0; i < NUM_NOTES; i++)
    {
        Beep(NOTES[i], DURATIONS[i]);
        Sleep(DELAY);
    }
    printf("Welcome, %s!\n", username);
}

void play_successful_login_sound()
{
    const int DELAY = 200;
    const int NOTES[] = {659, 784, 659};
    const int DURATIONS[] = {300, 600, 900};
    const int NUM_NOTES = sizeof(NOTES) / sizeof(NOTES[0]);

    for (int i = 0; i < NUM_NOTES; i++)
    {
        Beep(NOTES[i], DURATIONS[i]);
        Sleep(DELAY);
    }
    printf("Login successful!\n");
}


void display_login_box()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    

    
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    int login_attempts = 0;
    bool is_locked_out = false;
    time_t lockout_start_time = 0;

     do {
        
        system("cls");

        
        printf("\n\n\t\t\t   BANK MANAGEMENT SYSTEM");
        
        
        printf("\n\n\t\t-----------------------------------------\n");
        printf("\t\t|                                         |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\t\t|                Login                    |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\t\t|                                         |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\t|    Username:                            |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\t\t|    ");
        fgets(username, MAX_USERNAME_LENGTH + 1, stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("\t\t|                                         |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\t\t|    Password:                            |\n");
         SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\t\t|    ");
        int password_length = 0;
        while (true)
        {
            char ch = getch();
            if (ch == '\r')
            { 
                break;
            }
            else if (ch == '\b' && password_length > 0)
            { 
                password[--password_length] = '\0';
                printf("\b \b");
            }
            else if (password_length < MAX_PASSWORD_LENGTH)
            {
                password[password_length++] = ch;
                printf("*");
            }
        }
        password[password_length] = '\0';
        printf("\n\t\t|                                         |\n");
        printf("\t\t-----------------------------------------\n");

        
        if (is_locked_out)
        {
            printf("\n\n\t\tYour account has been locked out. Please try again later.\n");
            Sleep(LOCKOUT_PERIOD * 1000);
            is_locked_out = false;
        }

        if (is_password_correct(username, password))
        {
            printf("\n\n\t\tWelcome,....");
            play_welcome_sound_with_username(username);
            
            printf("\n\n\t\tLoading...");
            play_successful_login_sound();
            Sleep(2000); 
            
			display_menu();

        
            break;
        }
            else
        {
            login_attempts++;
            if (login_attempts == MAX_LOGIN_ATTEMPTS)
            {
                printf("\n\n\t\tToo many incorrect login attempts. Your account has been locked out for %d seconds.\n", LOCKOUT_PERIOD);
                is_locked_out = true;
                time_t start_time = time(NULL);
                while (difftime(time(NULL), start_time) < LOCKOUT_PERIOD)
                {
                    Sleep(1000);
                }
            }
            else
            {
                printf("\n\n\t\tIncorrect username or password. Please try again.\n");
            }
        }
    } while (true);
}
void display_menu(void)
{
    int choice;
    do {
        system("cls");
        system("color 9");
        printf("\n\n\t\t\t            BANK MANAGEMENT SYSTEM");
        printf("\n\n\n\t\t\t+--------------------------------------------+");
        printf("\n\t\t\t¦          WELCOME TO THE MAIN MENU          ¦");
        printf("\n\t\t\t+--------------------------------------------+");
        printf("\n\n\t\t1. Create New Account\n");
        printf("\t\t2. Update Information of Existing Account\n");
        printf("\t\t3. Perform Transactions\n");
        printf("\t\t4. Check Details of Existing Account\n");
        printf("\t\t5. Remove Existing Account\n");
        printf("\t\t6. View Customer's List\n");
        printf("\t\t7. Exit\n\n\n\n\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch (choice) {
            case 1:
                new_acc();
                break;
            case 2:
                edit();
                break;
            case 3:
                transact();
                break;
            case 4:
                see();
                break;
            case 5:
                erase();
                break;
            case 6:
                view_list();
                break;
             case 7:
                if (MessageBox(NULL, "Are you sure you want to exit?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    MessageBox(NULL, "Thank you for using the banking system.This Banking System is created by Rwitam And Sambhabi!", "Exit", MB_OK | MB_ICONINFORMATION);
                    exit(0);
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress any key to continue...");
        getch();
    } while (true);
}


void close(void)
{
    printf("\n\n\n\nThis Banking System is created by Rwitam And Sambhabi!");
    }

int main(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursor_info);
    system("color 3F"); 

    display_login_box();
    

    return 0;
}
