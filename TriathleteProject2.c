#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <ncurses.h>
#include <math.h>
#define current_year 2022
#define clr system("clear");
#define f float

enum Num
{ /*Enumerations from 0 to 5*/
  Zero,
  Ones,
  Twos,
  Tres,
  Four,
  Five
};

typedef struct
{ /*Structure with different data types to record from a user*/
    char name[Five * Four];
    int id;
    int age;
    char gender[Five + Twos];
    char dob[Five * Tres];
    char date[Five * Four];
    char time[Five * Four];
    char event[Tres * Tres];
    char club[Tres * Five];
    char dRdate[Five * Tres * Tres];
    f swimTime;
    f t1;
    f cycleTime;
    f t2;
    f runTime;
    f t_Time;
    char s_con[Five * Five];
    char t1_con[Five * Five];
    char c_con[Five * Five];
    char t2_con[Five * Five];
    char r_con[Five * Five];
    char tt_con[Five * Five];

} Triathlete;

FILE *file;
Triathlete stud; /*Instance of struct for writing to a binary file*/
Triathlete info; /*Instance of struct for reading from binary file*/

/*Function prototypes*/
void menu(void);
void GoBack(void);
void details(void);
void bestTime(void);
void club_menu(void);
void club(int clubNo);
char *get_event(void);
void search_by_id(void);
char *get_gender(void);
void getIdNum(int *id);
char *score_time(f num);
void display_winner(void);
int get_length(int clubNo);
void loop(void (*function)());
void GetclubNo(int *clubNo);
static void search_by_name();
Triathlete writeDetails(void);
f getScores(f num, f scores[]);
void DisplayWinner(char *club);
void getName(char name[Five * Four]);
void assign_club(int age, char club[]);
int getBirthDetails(int i, int b_date[]);
void insertion_sort(f club[], int length);
void take_score(int i, f score, f scores[]);
void cwsac(char string[], char new_string[]);
char *range(int clubNo, int *start, int *end);
int convert(int i, f scores[], char strScores[][Five * Five]);
void date_of_birth(char dob[Tres * Five], int day, int month, int year);
void winner_details(char *club, char *name1, char *name2, char *name3);
void GetClubScores(int clubNo, f club_s[], f club_c[], f club_r[], f club_t[]);
void view_winner(int n, int size, f stime[], f ctime[], f rtime[], f t_time[]);

char *filename = "information.txt";
char *append = "ab";
char *s = "Please Enter The Scores (0.00) e.g 1.09 = 1 hour 9 mins";
char *idtext = "\n\n\t\tPlease enter your ID number ####: ";
char *stext = "\nThere is no match for that name in the system!!\n\n";
char *ctext = "Do you want to view details from another club (Y\\N)? ";
char *itext = "Do you want to search with your ID number instead (Y\\N)? ";
char *clubs[] = {"KIDS OF STEEL", "IRON KIDS", "CAST IRON KIDS"};
char *gender[] = {"Male", "Female"};

int main(void)
{
    char request[Five * Four];
    int cNum;
    menu();
    scanf("%s", request);
    request[0] = toupper(request[Zero]);
    if (request[Zero] == 'A')
    {
        clr;
        writeDetails();
    }
    else if (request[Zero] == 'B')
    {
        clr;
        club(cNum);
    }
    else if (request[Zero] == 'C')
    {
        clr;
        search_by_name();
    }
    else if (request[Zero] == 'D')
    {
        clr;
        display_winner();
    }
    else if (request[Zero] == 'E')
    {
        clr;
        bestTime();
    }
    else if (request[Zero] == 'X')
    {
        exit(Zero);
    }
    clr;
    puts("Invalid Type!!");
    main();
}

void getName(char name[Five * Four])
{ /*Takes the user name*/
    printf("\n\n\t\tPlease enter your name: ");
    scanf(" %[^\n]", name);
}

void getIdNum(int *id)
{ /*Takes a valid Id Number from the user*/
    int id_read = Zero;
    *id = Ones;
    printf("%s", idtext);
    id_read = scanf("%d", id);
    while (id_read != Ones)
    {
        puts("Only Number allowed!!");
        scanf("%*[^\n]");
        printf("%s", idtext);
        id_read = scanf("%d", id);
    }
    fflush(stdin);
}

void date_of_birth(char dob[25], int day, int month, int year)
{ /*Return a string with the user date of birth*/
    time_t now = time(NULL);
    struct tm date = *localtime(&now);

    date.tm_year = year - 1900;
    date.tm_mon = month - Ones;
    date.tm_mday = day;

    strftime(dob, 25, "%B %d %Y", &date);
}

char *get_gender()
{ /*Return the gender of the user base on the type they enter*/
    int i = Zero;
    char genType[Five * Four];

    puts("\n\n\t\tPlease enter your Gender Type\n");
    printf("\t\t\tM. Male\n\t\t\tF. Female\n\n\t\t=> ");
    scanf("%s", genType);

    genType[Zero] = toupper(genType[Zero]);
    if (genType[Zero] != 'M' && genType[Zero] != 'F')
    {
        puts("Invalid Gender Type!!");
        return get_gender();
    }
    while (genType[Zero] != gender[i][Zero])
    {
        i++;
    }
    return (gender[i]);
}

void assign_club(int age, char club[])
{ /*Assign the user to a club base on his/her age*/
    int start = Tres * Twos, end = Four * Twos, i = Zero;
    while (true)
    {
        if (age >= start && age <= end)
        {
            cwsac(clubs[i], club);
            break;
        }
        i++;
        start = end + Ones, end = end + Tres;
        if (i == 2)
        {
            end = 15;
        }
    }
}

char *get_event(void)
{ /*Return the event type chosen by the user base the type they enter*/
    int i = 0;
    char type;
    char *events[] = {"Swimming", "Cycling", "Running"};
    puts("\n\n\t\tPlease enter your Event Type\n");
    printf("\t\t\tS. %s\n\t\t\tC. %s\n\t\t\tR. %s\n\n\t\t=> ",
           events[Zero], events[Ones], events[Twos]);
    scanf("%s", &type);
    type = toupper(type);
    if (type != 'S' && type != 'C' && type != 'R')
    {
        puts("Invalid Event Type!!");
        return get_event();
    }
    while (type != events[i][Zero])
    {
        i++;
    }
    return (events[i]);
}

int take_scores(int i, f score, f scores[])
{ /*Working together with 'getScores' to return the correct values*/
    f value = Zero;
    char *text[] = {"Swim Time: ", "1st Transition: ",
                    "Cycling Time: ", "2nd Transition: ", "Run Time: "};
    while (i != 5)
    {
        printf("\t\t\t %s", text[i]);
        value = scanf("%f", &score);
        while (value != Ones)
        {
            puts("\t\tInvalid data type!!");
            scanf("%*[^\n]");
            printf("\n\t\t\t %s", text[i]);
            value = scanf("%f", &score);
        }
        scores[i] = score;
        break;
    }
    return Zero;
}

f getScores(f num, f scores[])
{ // Working collectively with function 'take_score' to get the scores
    f score[5], total;
    take_scores(num, Ones, score);

    if (num == Zero)
    {
        scores[Zero] = score[Zero];
    }
    if (num == Ones)
    {
        scores[Ones] = score[Ones];
    }
    if (num == Twos)
    {
        scores[Twos] = score[Twos];
    }
    if (num == Tres)
    {
        scores[Tres] = score[Tres];
    }
    if (num == Four)
    {
        scores[Four] = score[Four];
    }
    if (num == 5)
    {
        total = (scores[Zero] + scores[Ones] + scores[Twos] + scores[Tres] + scores[Four]);
        scores[Five] = total;
        return Zero;
    }
    getScores(num + 1, scores);
    return Zero;
}

Triathlete writeDetails(void)
{ /* Write all the users input to a binary file */
    int i, day, month, year, b_date[Tres];
    char *gender, *event, name[Five * Four], club[Five * Four];
    char texts[Tres * Twos][Five * Five];
    f scores[Tres * Twos];

    time_t now = time(NULL);           /*Getting the amount seconds from 1970 midnight till now*/
    struct tm date = *localtime(&now); /*iniatializing a struct with the local time*/

    strftime(stud.dRdate, 45, "%A %B %d, %Y @ %X %p %Z", &date); /*Making a string of the current date*/
    file = fopen(filename, append);                              /*Open the file in binary append mode.*/
    getName(name);
    clr;
    cwsac(name, stud.name); /*Call the the function get name to get a name and Capitalize each word in it*/
    getIdNum(&stud.id);
    clr; /*Call the function 'getIdNum' to get the id number from the user*/

    printf("\n\n\t\tPlease enter your date of birth\n\n"); /*Display messgae*/
    stud.age = getBirthDetails(Zero, b_date);              /*assign the struct variable 'stud.age' to return value of the function 'getBirthDetails'.*/
    clr;
    if (stud.age < Tres * Twos || stud.age > Five * Tres) /*Check if the the age is a valid age which greater than 5 and less than 16*/
    {
        puts("Can't Finish Process. Age Not Adequate!!"); /*print error message*/
        main();                                           /*Call function 'main'.*/
    }
    date_of_birth(stud.dob, b_date[2], b_date[Ones], b_date[Zero]); /*takes in the important values return from the 'getBirthDetails'*/

    gender = get_gender();
    clr;
    strcpy(stud.gender, gender); /*Call the 'get_gender' function and assign the return value to gender.*/
    assign_club(stud.age, club);
    strcpy(stud.club, club); /*Assign the club base on the age that was pass to it as argument*/
    event = get_event();
    clr;
    strcpy(stud.event, event); /*Call the 'get_event' function and assign the return value to event.*/

    printf("\n\n\t\t%s\n\n", s);
    getScores(Zero, scores); /*Prompt message and call the 'getScores' function to get the scores*/
    stud.swimTime = scores[Zero];
    stud.t1 = scores[Ones]; /*Assign the each independent scores to struct variable*/
    stud.cycleTime = scores[Twos];
    stud.t2 = scores[Tres];
    stud.runTime = scores[Four];
    stud.t_Time = scores[Five];

    convert(Zero, scores, texts); /*Call the function 'convert' to convert the scores into hours and minutes.*/
    /*Copy each each independent score into a struct variable*/
    strcpy(stud.s_con, texts[Zero]);
    strcpy(stud.t1_con, texts[Ones]);
    strcpy(stud.c_con, texts[Twos]);
    strcpy(stud.t2_con, texts[Tres]);
    strcpy(stud.r_con, texts[Four]);
    strcpy(stud.tt_con, texts[Five]);

    fwrite(&stud, sizeof(Triathlete), Ones, file);
    fclose(file);
    clr;
    printf("\n\n\n\tProcessing...\n");
    sleep(1);
    clr;
    puts("\n\tRECORDED SUCCESSFULLY\n\n");
    main();
    return stud;
}

void search_by_name(void)
{ /*Takes the name of a participant and return the details*/
    int num;
    char c, name[Five * Four], new_name[Five * Four]; /*Declaration of variables to be used*/
    if ((file = fopen(filename, "rb")) == NULL)       /*Check if file exists*/
    {
        perror("ERROR MSG");
        main(); /*display error message and call the 'main' function.*/
    }
    printf("Please enter your name: "); /*Prompt message*/
    scanf(" %[^\n]", name);             /*Reads in the string enter into memory*/
    cwsac(name, new_name);              /*Capitalize each word of the string characters entered*/

    while (!feof(file)) /*loop until the end of the file*/
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (strcmp(new_name, info.name) == Zero) /*Check if 'new_name' and 'info.name' evalues to false*/
        {
            clr;
            details();
            fflush(stdin); /*Clear the console and print out the registered details*/
            GoBack();      /*Call the function 'GoBack'.*/
        }
    } /*Display prompts and loop with the function with 'search_by_id' function*/
    printf("%s", stext);
    printf("\t\t%s", itext);
    loop(search_by_id);
}

void search_by_id(void)
{ /*If function 'search_by_name' fails. Then this function will try to get the detail*/
    clr;
    int id, tries = Zero;
    char c;
    while (true)
    {
        if (tries == Tres) /*If tries and 3 becomes true*/
        {
            clr;
            printf("\n\t\t\tYOU ARE OUT OF ATTEMPT(s)!!\n\n"); /*Message*/
            fflush(stdin);
            GoBack();
        }
        if ((file = fopen(filename, "rb")) == NULL) /*Check if the file exists*/
        {
            perror("ERROR MSG"); /*Display error message*/
        }
        printf("\n\n\t\tYou have (%d of 3) ATTEMPT(s) to use ID number\n\n", Tres - tries); /*Prompt the amount of tries to use id number*/
        printf("\t\t    Enter your ID number ####: ");
        scanf("%d", &id);   /*Prompt message*/
        while (!feof(file)) /*Loop until the end of the file*/
        {
            fread(&info, sizeof(Triathlete), Ones, file);
            if (id == info.id) /*Check if the 'id' and 'info.id' evaluates to true*/
            {
                clr;
                details();
                fflush(stdin);
                GoBack(); /*Clear the console and flush the buffer and call the function 'GoBack'.*/
            }
        }
        clr;
        printf("\t\tThere is no data for that ID Number!!\n");
        fflush(stdin);
        tries++; /*Flush the buffer and increment the value of tries by 1*/
    }
}

void GoBack(void)
{                                                       /*Go back to the main menu*/
    char c;                                             /*Declaration of char*/
    printf("\n\nPress ENTER to return to main menu: "); /*Prompt*/
    fflush(stdin);
    if ((c = getchar()) == Five * Twos) /*If the ascii value of character equals 10*/
    {
        fclose(file);
        clr;
        main(); /*Close the file and call the main function*/
    }
    fclose(file);
    clr;
    main(); /*Close the file and call the main function*/
}

int get_length(int clubNo)
{                                               /*Get the size of the amount of student registerd for a club*/
    int size = Zero, start, end;                /*Declaration of integers to be used*/
    char prev_name[Five * Four];                /*Declaration of char array to be used*/
    if ((file = fopen(filename, "rb")) == NULL) /*Check if the file exists*/
    {
        perror("Error msg");
        main(); /*display error message*/
    }
    range(clubNo, &start, &end);
    while (!feof(file)) /*Loop until the end of the file*/
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (info.age >= start && info.age <= end     /*check if the value of 'info.age' is greater than or equal to start and less than equal end*/
            && strcmp(info.name, prev_name) != Zero) /*Compare 'info.name' and 'prev_name' to see if evaluates to true*/
        {
            size++;                       /*Increment the value of 'size' by 1.*/
            strcpy(prev_name, info.name); /*Copy the data of 'info.name' into 'prev_name'.*/
        }
    }
    fclose(file); /*Close the file*/
    return size;  /*Return the value of the size*/
}

void GetClubScores(int clubNo, f club_s[], f club_c[], f club_r[], f club_t[])
{                                               /*Return a list of scores base on the club number that was given to it*/
    int i = Zero, start, end;                   /*Declariton of intergers to be used*/
    char prev_name[Five * Four];                /*Declaration of chars to be used*/
    if ((file = fopen(filename, "rb")) == NULL) /*Check if the file exists.*/
    {
        perror("Error msg");
        main(); /*Display error message and return the main function*/
    }
    range(clubNo, &start, &end); /*Call the range function to get the value of the start and the end*/
    while (!feof(file))          /*loop while it is not the end of the file*/
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (info.age >= start && info.age <= end) /*Check if the 'info.age' is greater or equal to 'start' and less than or equal to the 'end'*/
        {
            if (strcmp(prev_name, info.name) != Zero) /*Check if 'prev_name' and 'info.name' evaluates to True*/
            {
                club_s[i] = info.swimTime;  /*Assign the value of 'info.swimTime' to 'club_s[i]' index.*/
                club_c[i] = info.cycleTime; /*Assign the value of 'info.cycleTime' to 'club_c[i]' index.*/
                club_r[i] = info.runTime;   /*Assign the value of 'info.runTime to 'club_r[i] index.*/
                club_t[i] = info.t_Time;    /*Assign the value of 'info.t_time' to 'club_t[i] index'*/
                i++;                        /*Increment the value of i by 1.*/
            }
            strcpy(prev_name, info.name);
        } /*Copy the 'info.name' into the 'current_name'.*/
    }
    fclose(file); /*Close the file*/
}

void view_winner(int n, int size, f stime[], f ctime[], f rtime[], f t_time[])
{                                                             /*Working collectively with function 'GetClubScores' and 'insertion_sort' to get the best times*/
    f club_s[size], club_c[size], club_r[size], club_t[size]; /*Declaration of float arrays to be used*/
    GetClubScores(n, club_s, club_c, club_r, club_t);         /*Call the function 'GetClubScores' to get the all the club values*/

    insertion_sort(club_s, size);
    insertion_sort(club_c, size); /*Call insertion sort on the arrays to get them in sorted order*/
    insertion_sort(club_r, size);
    insertion_sort(club_t, size); /*Call insertion sort on the array to get then in sorted order.*/

    for (int i = Zero; i < size; i++) /*For loop to loop through the values of the array*/
    {
        stime[i] = club_s[i];
        ctime[i] = club_c[i]; /*Point a variable to the memory address of the first value of the arrays*/
        rtime[i] = club_r[i];
        t_time[i] = club_t[i]; /*Point a vairable to the memory address of the first value of the arrays.*/
    }
}

void insertion_sort(f club[], int length)
{                      /*Sorting the values in array from lowest to highest*/
    int i = Ones;      /*Initialize the value of i to 1*/
    while (i < length) /*Loop while the value of i is less than the length*/
    {
        while (club[i - Ones] > club[i] && i > Zero) /*Loop while ther first index of the array is greater than the second index*/
        {
            f temp = club[i];         /*Initialize a temporary variable and assign the value of club i to it*/
            club[i] = club[i - Ones]; /*Assignt he value of the club[i-1] to the club i*/
            club[i - Ones] = temp;
            i--; /*Assign the value of the temporary variable to club [i-1].*/
        }
        i++; /*Increment the value i by 1*/
    }
}

char *range(int clubNo, int *start, int *end)
{                                         /*Return the club and the matching age range for it*/
    if (clubNo == Ones || clubNo == Twos) /*Check if the club number pass as argument is 1 or 2.*/
    {
        *start = (Tres * clubNo) + Tres, *end = (*start + Twos); /*Assign the value of the club number * 3 + 3 to address of start*/
        return clubs[clubNo - Ones];                             /*Return the corresponding club*/
    }
    *start = (Tres * clubNo) + Tres, *end = (*start + Tres);
    return clubs[clubNo - Ones]; /*Return the corresponding club*/
}

void GetclubNo(int *clubNo)
{ /*Takes a valid club number from the user*/
    club_menu();
    scanf("%d", clubNo);                  /*Calls the club menu to see the options and reads in a number into memory*/
    if (*clubNo < Ones || *clubNo > Four) /*Check if the number entered is less than 1 or greater than 4*/
    {
        clr;
        puts("Invalid Number\\Data Type!!"); /*If not int data type then put invalid data type*/
        scanf("%*[^\n]");                    /*Read pass the value*/
        GetclubNo(clubNo);                   /*Call back the function*/
    }
    if (*clubNo == Four)
    {
        clr;
        main();
    } /*Check if the number entered is 4 then call 'main'*/
}

void loop(void (*function)())
{                             /*Call back the function that is pass to it*/
    char yes[20], detail;     /*Declaration of char to use*/
    scanf("%s", yes);         /*Reads in a string of character into memory*/
    yes[0] = toupper(yes[0]); /*Converts the first character of string to uppercase*/
    if (yes[0] == 'Y')        /*Check if the first character and 'Y' evaluates to false*/
    {
        clr;
        function(); /*Clear the console and call the function that was pass to it as the argument*/
    }
    else if (yes[0] == 'N') /*Check if the first character and 'N' evaluates to false.*/
    {
        clr;
        main(); /*if false then clear the console and call the function 'main'.*/
    }
    puts("\tInvalid type!!\n"); /*print out invalid type*/
    printf("Enter Y\\N: ");     /*prompt message*/
    loop(function);             /*call back the said function*/
}

void club(int clubNo)
{ /*Display the students details from the club you want to check*/
    int start, end, result;
    char current_name[Five * Four];

    GetclubNo(&clubNo);
    clr;                                        /*Call 'GetclubNo' to get a club number*/
    range(clubNo, &start, &end);                /*Call 'range' to get from where to start and where to end*/
    if ((file = fopen(filename, "rb")) == NULL) /*Check if the we reading from existing file*/
    {
        perror("Error msg");
        main(); /*If true then print out a error message*/
    }
    while (!feof(file))
    {                                                 /*Do while not end of the file*/
        fread(&info, sizeof(Triathlete), Ones, file); /*Read in 1 size of the structure*/
        if (info.age >= start && info.age <= end)     /*Check if the age in the file is greater than or equal to start and less than or equal to end*/
        {
            if (strcmp(current_name, info.name) != Zero) /*Check if the current_name and previous name evaluates to true*/
            {
                details();                       /*Call the function details to print out the user details*/
                strcpy(current_name, info.name); /*Copy the 'info.name' into the 'current_name'.*/
            }
        }
    }
    fclose(file);
    printf("%s", ctext);
    loop(club); /*Close the file and loop with to check if the wish to something similar*/
}

int convert(int i, f scores[], char strScores[][Five * Five])
{ /*Takes the scores inputed by the user and return a string of in hours and minutes*/
    int whole, frac;
    f decimal;                                /*Declaration of int type variables to be used*/
    char hour[Five * Tres + Tres], min[Tres]; /*Declaration of char type variables to be use*/

    if (i != Five + Ones) /*Check if the current value of i is less than 5*/
    {
        whole = (int)scores[i];                            /*Convert a first whole part of a float to a integer*/
        decimal = round((scores[i] - (float)whole) * 100); /*Round the decimal part of a float to a float*/
        frac = (int)decimal;                               /*Convert the the decimal value to a integer value*/
        if (frac > Five * Four * Tres)                     /*Check if frac is greater than 60*/
        {
            whole++;
            frac -= ((Five * Four * Tres) - Ones); /*If true then increment the value of whole by 1 and take away 60 from frac*/
        }
        sprintf(hour, "%d", whole);
        sprintf(min, "%d", frac); /*Convert the int hour and min data type to chars*/
        strcat(hour, " Hrs: ");
        strcat(hour, min); /*Link the the two converted chars to together*/
        strcat(hour, " Mins:");
        strcpy(strScores[i], hour);
        /*Call back the said function with i incremented by 1*/
        convert(i + Ones, scores, strScores);
    }
    return Zero;
}

void cwsac(char string[], char new_string[])
{ /*Takes a string and capitalize each word*/
    int i = Zero, j = Zero, k = Zero, l = Zero;
    int len = strlen(string); /*Assign the length of the string to the variable len*/
    while (i < len)
    {
        while (!isspace(string[i]) && string[i] != '\0') /*Check if the current position of string is a space or a null character*/
        {
            k = i + 1; /*Assign the value of i + 1 to the variable k*/
            new_string[j] = toupper(string[i]);

            while (!isspace(string[k]) && string[k] != '\0') /*Check if the current position of string is a space or a null character*/
            {
                new_string[j + 1] = tolower(string[k]); /*Assign the value of the current string to the new string in lower casee*/
                j++;
                k++; /*Increment the value of j and k by 1*/
            }
            j += Twos;
            i = k + Ones;            /*Increment the value of j by 2 and assign the k + 1 to i*/
            new_string[j - 1] = ' '; /*Assign a space to the current position of the of the new string*/
        }
        l++;
        i++;
    }                                 /*Increment the value of i and l by 1*/
    new_string[(len + 1) - l] = '\0'; /*Assign the null character to end of the of new string*/
}

void menu(void)
{ /*Option menu to choose an operation*/
    printf("\n\t\t\t-----------                                                    -------------");
    printf("\n\t\t\t============ JAMAICAN TRIATHLON SOCIETY (JaTSo) UPDATE SYSTEM ==============");
    printf("\n\t\t\t-----------                                                    -------------");
    printf("\n\t\t\t              A.     For adding Students' Data                             ");
    printf("\n\t\t\t              B.     For viewing All Student Data                          ");
    printf("\n\t\t\t              C.     Search for A Student Data                             ");
    printf("\n\t\t\t              D.     View the overall Winner for each competition          ");
    printf("\n\t\t\t              E.     View The Triathlete With The Best Time(s) For Each\n\t\
                                     Event In Each Competition\n");
    printf("\n\t\t\t              X.     Exit.\n\t\t\t\n\n\n\t\t\t Option Type: ");
}

void details(void)
{ /*Display the student details base on the value gain from Function 'club', 'search_by_name' and 'search_by_id'*/
    printf("\t\t\t–––––––––––––––––––––––––––––––––––––––––––––––———————");
    printf("\n\t\t\t Registered %s \n\n", info.dRdate);
    printf("\t\t\t   + Name                –             %s\n", info.name);
    printf("\t\t\t   + Id number           –             %d\n", info.id);
    printf("\t\t\t   + Gender              –             %s\n", info.gender);
    printf("\t\t\t   + DOB                 –             %s\n", info.dob);
    printf("\t\t\t   + Age                 –             %d Years Old\n", info.age);
    printf("\t\t\t   + Club                –             %s\n", info.club);
    printf("\t\t\t   + Event               –             %s\n\n", info.event);
    printf("\t\t\t———————————————————————————————————————————————————————\n");
    printf("\t\t\t    EVENT                                 TIMES\n");
    printf("\t\t\t———————————————————————————————————————————————————————\n\n");
    printf("\t\t\t   + Swim Time           –             %s\n", info.s_con);
    printf("\t\t\t   + Trans 1             –             %s\n", info.t1_con);
    printf("\t\t\t   + Cycle Time          –             %s\n", info.c_con);
    printf("\t\t\t   + Trans 2             –             %s\n", info.t2_con);
    printf("\t\t\t   + Run Time            –             %s\n\n", info.r_con);
    printf("\t\t\t   TRIATHLETE TIME       –            %s\n\n", info.tt_con);
    printf("\t\t\t±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\n\n\n");
}

void club_menu(void)
{ /*Menu showing the different clubs to choose for view details*/
    printf("\n\t\t ~~~~~~~~~~ CLUBS ~~~~~~~~~~\n\n");
    printf("\t\t      1 -» %s\n", clubs[Zero]);
    printf("\t\t      2 -» %s\n", clubs[Ones]);
    printf("\t\t      3 -» %s\n\n", clubs[Twos]);
    printf("\t\t      4 «- GO BACK\n\n\t\t ===‡ ");
}

void winner_details(char *club, char *name1, char *name2, char *name3)
{ /*Display the student/stud with the best time from each event*/
    char prev_n1[Five * Four], prev_n2[Five * Four], prev_n3[Five * Four];
    printf("\n\t------------                                                    \t------------");
    printf("\n\t\t========== STUDENTS WITH BEST TIME(s) FROM %s ============", club);
    printf("\n\t------------                                                    \t------------");
    file = fopen(filename, "rb");

    while (!feof(file))
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (strcmp(name1, info.name) == false && strcmp(prev_n1, info.name) != false)
        {
            printf("\n\n\t\t\tStudent \t\t->\t\t %s\n", name1);
            printf("\t\t\tSwim Time \t\t->\t\t %s\n\n", info.s_con);
            strcpy(prev_n1, info.name);
        }
        if (strcmp(name2, info.name) == false && strcmp(prev_n2, info.name) != false)
        {
            printf("\n\t\t\tStudent \t\t->\t\t %s\n", name2);
            printf("\t\t\tCycling Time \t\t->\t\t %s\n\n", info.c_con);
            strcpy(prev_n2, info.name);
        }
        if (strcmp(name3, info.name) == false && strcmp(prev_n3, info.name) != false)
        {
            printf("\n\t\t\tStudent \t\t->\t\t %s\n", name3);
            printf("\t\t\tRun Time \t\t-> \t\t %s\n", info.r_con);
            strcpy(prev_n3, info.name);
        }
    }
    printf("\n\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\t====================================================================================\n\n\n");
    fclose(file);
}

void DisplayWinner(char *club)
{ /*Print out the winner for a specific club base on the conditions given*/
    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>                    <<<<<<<<<<<<<<<<<<<<<");
    printf("\n\t\t\t============ THE WINNER OF %s ===================", club);
    printf("\n\t\t\t>>>>>>>>>>>>>>>>>>>>                    <<<<<<<<<<<<<<<<<<<<<");
    printf("\n\t\t\t\tRegistered %s\n\n", info.dRdate);
    printf("\t\t\t\t         Name -> %s\n", info.name);
    printf("\n\t\t\t\t    Winning Time : %s\n\n", info.tt_con);
    printf("\t\t\t==============================================================\n");
    printf("\t\t\t**************************************************************\n\n");
}

void bestTime(void)
{ /*Work synergistically with other functions to later display out the best times*/
    int clubNo, size, start, end;
    char *CLUB, club[15], name1[20], name2[20], name3[20];

    GetclubNo(&clubNo);
    size = get_length(clubNo);

    f club_s[size], club_c[size], club_r[size], club_t[size];

    CLUB = range(clubNo, &start, &end);
    strcpy(club, CLUB);
    view_winner(clubNo, size, club_s, club_c, club_r, club_t);

    file = fopen(filename, "rb");
    while (!feof(file))
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (info.age >= start && info.age <= end)
        {
            if (club_s[Zero] == info.swimTime)
            {
                strcpy(name1, info.name);
            }
            if (club_c[Zero] == info.cycleTime)
            {
                strcpy(name2, info.name);
            }
            if (club_r[Zero] == info.runTime)
            {
                strcpy(name3, info.name);
            }
        }
    }
    fclose(file);
    clr;
    winner_details(club, name1, name2, name3);
    printf("%s", ctext);
    loop(bestTime);
    ;
}

void display_winner(void)
{ /*Work synergistically to later display the winner of each event*/
    int clubNo, size, start, end;
    char *CLUB, club[Tres * Five], yes;
    GetclubNo(&clubNo);
    size = get_length(clubNo);

    f club_s[size], club_c[size], club_r[size], club_t[size];

    CLUB = range(clubNo, &start, &end);
    strcpy(club, CLUB);
    view_winner(clubNo, size, club_s, club_c, club_r, club_t);

    file = fopen(filename, "rb");
    while (!feof(file))
    {
        fread(&info, sizeof(Triathlete), Ones, file);
        if (info.t_Time == club_t[Zero])
        {
            clr;
            DisplayWinner(club);
            fclose(file);
            break;
        }
    }
    printf("%s", ctext);
    loop(display_winner);
}

int getBirthDetails(int i, int b_date[])
{ /*Takes 0 as a argument and return pointer an array containing date of birth*/
    int values = Ones, valueRead = Zero;
    char *text[] = {"Year (0000): ", "Month (00): ",
                    "Day (00): "};
    while (i < Tres)
    {
        printf("\t\t\t%s", text[i]);
        valueRead = scanf("%d", &values);
        while (valueRead != Ones)
        {
            puts("Invalid Data type!!");
            scanf("%*[^\n]");
            printf("\n\t\t\t%s", text[i]);
            valueRead = scanf("%d", &values);
        }
        b_date[i] = values; /*Assign the values to the current index of 'b_date'.*/
        i++;                /*Increment the value of i by 1*/
    }
    return (current_year - b_date[Zero]); /*Return the age of the user*/
}