#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cctype>
#include <cstring>
#include <unistd.h>
#define filename "information.txt"
#define clr system("clear")
#define f float

using namespace std;

enum option
{
    Zero,
    Ones,
    Twos,
    Tres,
    Four,
    Five
};

typedef struct
{

    string name;
    string gender;
    string club;
    string event;

    int id;
    int age;
    char dob[25];
    char Rdate[45];

    f swimTime;
    f t1;
    f cycleTime;
    f t2;
    f runTime;
    f t_Time;

    string s_con;
    string t1_con;
    string c_con;
    string t2_con;
    string r_con;
    string tt_con;

} Triathlete;

Triathlete stud;
Triathlete info;

string clubs[] = {"KIDS OF STEEL",
                  "IRON KIDS", "CAST IRON KIDS"};

void GetName(string *name);
void GetIdNum(int *num);
int GetBirthDetails(int i, int b_date[]);
void assign_club(int age, string *club);
void getGender(string *gender);
void DOB(char dob[], int day, int month, int year);
f GetScores(int i, f *score, f scores[]);
Triathlete writeDetails(void);
void read_details();
string range(int clubNo, int *start, int *end);
void loop(void (*function)());
void details(void);
void GetclubNo(int *clubNo);
void capitalize(string word, string *new_word);
int convert(int i, f scores[], string strScores[]);
void menu(void);
int getLength(int clubNo);
void GoBack(void);
void search_by_id(void);
void search_by_name(void);
void club_menu(void);
void display_winner(void);
void DisplayWinner(string club);
void winner_details(string club, string name1, string name2, string name3);
void GetClubScores(int clubNo, f club_s[], f club_c[], f club_r[], f club_t[]);
void view_winner(int n, int size, f stime[], f ctime[], f rtime[], f t_time[]);

void bestTime(void);

int main(void)
{
    string request;
    menu();
    cin >> request;
    request[0] = toupper(request[Zero]);

    if (request[Zero] == 'A')
    {
        clr;
        writeDetails();
    }
    else if (request[Zero] == 'B')
    {
        clr;
        read_details();
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
    cout << "Invalid Type!!\n";
    main();
    return 0;
}

Triathlete writeDetails(void)
{
    std::ofstream file;

    int b_date[3];
    f score, scores[6];
    string name, converted[6];
    time_t now = time(NULL);
    struct tm date = *localtime(&now);

    file.open(filename, ios::app | ios::binary);
    strftime(stud.Rdate, 45, "%A %B %d, %Y @ %X %p %Z", &date);
    fflush(stdin);
    GetName(&name);
    clr;
    capitalize(name, &stud.name);
    GetIdNum(&stud.id);
    clr;
    getGender(&stud.gender);
    clr;
    cout << "\n\n\t\tPlease enter your date of birth\n\n";
    stud.age = GetBirthDetails(0, b_date);
    clr;
    if (stud.age < 6 && stud.age > 15)
    {
        cout << "Can't Finish Process. Age not Adequate!!";
        exit(0);
    }
    DOB(stud.dob, b_date[2], b_date[1], b_date[0]);
    assign_club(stud.age, &stud.club);

    cout << "\n\n\t\tPlease enter the Scores (0.00) e.g 1.09 = 1 hour 9 mins\n\n";
    scores[5] = GetScores(0, &score, scores);
    clr;
    stud.swimTime = scores[0], stud.t1 = scores[1], stud.cycleTime = scores[2];
    stud.t2 = scores[3], stud.runTime = scores[4];
    stud.t_Time = scores[5];

    convert(0, scores, converted);
    stud.s_con = converted[0], stud.t1_con = converted[1], stud.c_con = converted[2];
    stud.t2_con = converted[3], stud.r_con = converted[4];
    stud.tt_con = converted[5];

    file.write(reinterpret_cast<char *>(&stud), sizeof(Triathlete));
    file.close();
    cout << "\n\n\n\tProcessing..\n";
    sleep(1);
    clr;
    cout << "\n\tRECORDED SUCCESSFULLY\n\n";
    main();
    return stud;
}

void read_details()
{
    int start, end, clubNo;
    string current_name;

    GetclubNo(&clubNo);
    range(clubNo, &start, &end);

    std::ifstream file;
    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (info.age >= start && info.age <= end)
        {
            if (!(current_name == info.name))
            {
                details();
                current_name = info.name;
            }
        }
    }
    file.close();
    cout << "Do you want view details from another club (Y\\N): ";
    loop(read_details);
}

void GetclubNo(int *clubNo)
{
    club_menu();
    cin >> *clubNo;
    clr;
    if (*clubNo < Ones || *clubNo > Four)
    {
        clr;
        cout << "Invalid Number\\Data Type!!";
        cin.clear();
        cin.ignore(256, '\n');
        GetclubNo(clubNo);
    }
    if (*clubNo == Four)
    {
        clr;
        main();
    }
}

void details(void)
{ /*Display the student details base on the value gain from Function 'club', 'search_by_name' and 'search_by_id'*/
    cout << "\t\t\t–––––––––––––––––––––––––––––––––––––––––––––––———————\n";
    cout << "\n\t\t\t Registered " << info.Rdate << "\n\n";
    cout << "\t\t\t   + Name                –             " << info.name << endl;
    cout << "\t\t\t   + Id number           –             " << info.id << endl;
    cout << "\t\t\t   + Gender              –             " << info.gender << endl;
    cout << "\t\t\t   + DOB                 –             " << info.dob << endl;
    cout << "\t\t\t   + Age                 –             " << info.age << " Years Old\n";
    cout << "\t\t\t   + Club                –             " << info.club << endl;
    // cout << "\t\t\t   + Event               –             " << info.event << endl << endl;
    cout << "\t\t\t———————————————————————————————————————————————————————\n";
    cout << "\t\t\t    EVENT                                 TIMES\n";
    cout << "\t\t\t———————————————————————————————————————————————————————\n\n";
    cout << "\t\t\t   + Swim Time           –             " << info.s_con << endl;
    cout << "\t\t\t   + Trans 1             –             " << info.t1_con << endl;
    cout << "\t\t\t   + Cycle Time          –             " << info.c_con << endl;
    cout << "\t\t\t   + Trans 2             –             " << info.t2_con << endl;
    cout << "\t\t\t   + Run Time            –             " << info.r_con << endl
         << endl;
    cout << "\t\t\t   TRIATHLETE TIME       –            " << info.tt_con << endl
         << endl;
    cout << "\t\t\t±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\n\n\n";
}

void GetName(string *name)
{
    cout << "\n\n\t\tPlease enter your name: ";
    getline(cin, *name);
}

void GetIdNum(int *num)
{
    cout << "\n\n\t\tPlease enter your ID Number ####: ";
    cin >> *num;
    while (cin.fail())
    {
        cout << "Only numbers allowed\n";
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please enter your ID Number ####: ";
        cin >> *num;
    }
}

int GetBirthDetails(int i, int b_date[])
{
    const int current_year = 2022;
    string text[] = {"Year (0000): ", "Month (00): ", "Day (00): "};
    if (i < 3)
    {
        cout << "    \t\t" + text[i];
        cin >> b_date[i];
        while (cin.fail())
        {
            cout << "Only Numbers Allowed\n";
            cin.clear();
            cin.ignore(256, '\n');
            cout << text[i];
            cin >> b_date[i];
        }
        GetBirthDetails(i + 1, b_date);
    }
    return (current_year - b_date[0]);
}

void DOB(char dob[], int day, int month, int year)
{
    time_t now = time(NULL);
    struct tm date = *localtime(&now);
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    strftime(dob, 25, "%B %d, %Y", &date);
}

void getGender(string *gender)
{
    int i = 0;
    string genders[] = {"Male", "Female"}, gen_type;
    cout << "\n\n\t\tPlease enter your Gender Type\n\n";
    cout << "\t\t\tM. Male\n\t\t\tF. Female\n\n\t\t=> ";
    cin >> gen_type;
    gen_type[0] = toupper(gen_type[0]);
    if (gen_type[0] != 'M' && gen_type[0] != 'F')
    {
        cout << "Invalid Gender Type!!\n";
        getGender(gender);
    }
    if (!(gen_type[0] == 'M'))
    {
        *gender = genders[1];
    }
    else
        *gender = genders[0];
}

void assign_club(int age, string *club)
{
    int start = 6, end = 8, i = 0;
    while (true)
    {
        if (age >= start && age <= end)
        {
            *club = clubs[i];
            break;
        }
        i++;
        start = end + 1;
        end = end + 3;
        if (i == 2)
            end = 15;
    }
}

f GetScores(int i, f *score, f scores[])
{
    string text[] = {"Swim Time: ", "Trans 1: ", "Cycle Time: ",
                     "Trans 2: ", "Run Time: "};
    if (!(i == 5))
    {
        cout << "\t\t\t" << text[i];
        cin >> scores[i];
        while (cin.fail())
        {
            cout << "\t\tInvalid Data Type!\n";
            cin.clear();
            cin.ignore(256, '\n');
            cout << "\t\t\t" << text[i];
            cin >> scores[i];
        }
        // scores[i] = *score;
        GetScores(i + 1, score, scores);
    }
    return (scores[0] + scores[1] + scores[2] + scores[3] + scores[4]);
}

void capitalize(string word, string *new_word)
{
    int i = 0, j = 0, k = 0, l = 0, len = word.size();
    char letters[len + 1];

    strcpy(letters, word.c_str());

    while (i < len)
    {
        while (!isspace(letters[i]) && !(letters[i] == '\0'))
        {
            k = i + 1;
            letters[j] = toupper(word[i]);

            while (!isspace(word[k]) && !(word[k] == '\0'))
            {
                letters[j + 1] = tolower(word[k]);
                j++;
                k++;
            }
            j += 2;
            i = k + 1;
            letters[j - 1] = ' ';
        }
        i++;
        l++;
    }
    letters[(len + 1) - l] = '\0';
    *new_word = letters;
}

int convert(int i, f scores[], string strScores[])
{
    int whole, frac;
    if (!(i == 6))
    {
        whole = (int)scores[i];
        frac = round((scores[i] - (f)whole) * 100);

        if (frac > 59)
        {
            whole++;
            frac = frac - 60;
        }
        strScores[i] = to_string(whole) + " Hrs: " + to_string(frac) + " Mins:";
        convert(i + 1, scores, strScores);
    }
    return 0;
}

void menu(void)
{ /*Option menu to choose an operation*/
    cout << "\n\t\t\t-----------                                                    -------------";
    cout << "\n\t\t\t============ JAMAICAN TRIATHLON SOCIETY (JaTSo) UPDATE SYSTEM ==============";
    cout << "\n\t\t\t-----------                                                    -------------";
    cout << "\n\t\t\t              A.     For adding Students' Data                             ";
    cout << "\n\t\t\t              B.     For viewing All Student Data                          ";
    cout << "\n\t\t\t              C.     Search for A Student Data                             ";
    cout << "\n\t\t\t              D.     View the overall Winner for each competition          ";
    cout << "\n\t\t\t              E.     View The Triathlete With The Best Time(s) For Each\n\t\
                                     Event In Each Competition\n";
    cout << "\n\t\t\t              X.     Exit.\n\t\t\t\n\n\n\t\t\t Option Type: ";
}

void club_menu(void)
{ /*Menu showing the different clubs to choose for view details*/
    cout << "\n\t\t ~~~~~~~~~~ CLUBS ~~~~~~~~~~\n\n";
    cout << "\t\t      1 -» " << clubs[Zero] << endl;
    cout << "\t\t      2 -» " << clubs[Ones] << endl;
    cout << "\t\t      3 -» " << clubs[Twos] << "\n\n";
    cout << "\t\t      4 «- GO BACK\n\n\t\t ===‡ ";
}

string range(int clubNo, int *start, int *end)
{
    if (clubNo == Ones || clubNo == Twos)
    {
        *start = (Tres * clubNo) + Tres, *end = (*start + Twos);
        return clubs[clubNo - Ones];
    }
    *start = (Tres * clubNo) + Tres, *end = (*start + Tres);
    return clubs[clubNo - Ones];
}

void loop(void (*function)())
{
    string yes;
    cin >> yes;
    yes[0] = toupper(yes[0]);
    if (yes[0] == 'Y')
    {
        clr;
        function();
    }
    else if (yes[0] == 'N')
    {
        clr;
        main();
    }
    cout << "\tInvalid type!!\n";
    cout << "Enter Y\\N: ";
    loop(function);
}

int getLength(int clubNo)
{
    int size = 0, start, end;
    string name;
    std::ifstream file;
    range(clubNo, &start, &end);
    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (info.age >= start && info.age <= end && !(name == info.name))
        {
            size++;
            name = info.name;
        }
    }
    file.close();
    return size;
}

void insertion_sort(f arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        while (arr[i - 1] > arr[i] && i > 0)
        {
            f temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;

            i--;
        }
    }
}

void search_by_name(void)
{
    string name, full_name;
    ifstream file;
    fflush(stdin);
    cout << "Enter the name: ";
    getline(cin, name);
    capitalize(name, &full_name);
    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (full_name == info.name)
        {
            clr;
            details();
            fflush(stdin);
            GoBack();
        }
    }
    cout << "\n\n\t\tThere is data for the name entered\n\n";
    cout << "Do you want to use ID # instead (Y\\N): ";
    loop(search_by_id);
}

void search_by_id(void)
{
    int id, tries = 0;
    std::ifstream file;
    file.open(filename, ios::in | ios::binary);
    while (true)
    {
        if (tries == 3)
        {
            clr;
            cout << "YOU ARE OUT OF ATTEMPT(s)";
            fflush(stdin);
            GoBack();
        }
        cout << "\n\n\t\tYou have (" << 3 - tries << " of 3) ATTEMPT(s) to use ID number\n";
        cout << "\n\t\tEnter ID NUMBER ####: ";
        cin >> id;
        while (file)
        {
            file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
            if (id == info.id)
            {
                clr;
                details();
                fflush(stdin);
                GoBack();
            }
        }
        clr;
        cout << "\n\t\tThere is no data for that ID Number!!\n\n";
        fflush(stdin);
        tries++;
    }
}

void GoBack(void)
{
    char c;
    ifstream file;
    printf("\n\nPress ENTER to return to main menu: ");
    fflush(stdin);
    if ((c = getchar()) == Five * Twos)
    {
        file.close();
        clr;
        main();
    }
    file.close();
    clr;
    main();
}

void GetClubScores(int clubNo, f club_s[], f club_c[], f club_r[], f club_t[])
{
    int i = Zero, start, end;
    string prev_name;
    ifstream file;

    range(clubNo, &start, &end);
    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (info.age >= start && info.age <= end)
        {
            if (!(prev_name == info.name))
            {
                club_s[i] = info.swimTime;
                club_c[i] = info.cycleTime;
                club_r[i] = info.runTime;
                club_t[i] = info.t_Time;
                i++;
            }
            prev_name = info.name;
        }
    }
    file.close();
}

void view_winner(int n, int size, f stime[], f ctime[], f rtime[], f t_time[])
{
    f club_s[size], club_c[size], club_r[size], club_t[size];
    GetClubScores(n, club_s, club_c, club_r, club_t);

    insertion_sort(club_s, size);
    insertion_sort(club_c, size);
    insertion_sort(club_r, size);
    insertion_sort(club_t, size);

    for (int i = Zero; i < size; i++)
    {
        stime[i] = club_s[i];
        ctime[i] = club_c[i];
        rtime[i] = club_r[i];
        t_time[i] = club_t[i];
    }
}

void display_winner(void)
{
    int clubNo, size, start, end;
    string CLUB;
    ifstream file;
    GetclubNo(&clubNo);
    size = getLength(clubNo);

    f club_s[size], club_c[size], club_r[size], club_t[size];

    CLUB = range(clubNo, &start, &end);
    view_winner(clubNo, size, club_s, club_c, club_r, club_t);

    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (info.t_Time == club_t[Zero])
        {
            clr;
            DisplayWinner(CLUB);
            file.close();
            break;
        }
    }
    cout << "Do you want view details from another club (Y\\N): ";
    loop(display_winner);
}

void DisplayWinner(string club)
{ /*Print out the winner for a specific club base on the conditions given*/
    cout << "\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>                    <<<<<<<<<<<<<<<<<<<<<";
    cout << "\n\t\t\t============ THE WINNER OF " << club << " ===================";
    cout << "\n\t\t\t>>>>>>>>>>>>>>>>>>>>                    <<<<<<<<<<<<<<<<<<<<<";
    cout << "\n\t\t\t\tRegistered " << info.Rdate << endl
         << endl;
    cout << "\t\t\t\t         Name -> " << info.name << endl;
    cout << "\n\t\t\t\t    Winning Time : " << info.tt_con << endl
         << endl;
    cout << "\t\t\t==============================================================\n";
    cout << "\t\t\t**************************************************************\n\n";
}

void bestTime(void)
{ /*Work synergistically with other functions to later display out the best times*/
    int clubNo, size, start, end;
    string CLUB, name1, name2, name3;
    ifstream file;
    GetclubNo(&clubNo);
    size = getLength(clubNo);

    f club_s[size], club_c[size], club_r[size], club_t[size];

    CLUB = range(clubNo, &start, &end);
    view_winner(clubNo, size, club_s, club_c, club_r, club_t);

    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if (info.age >= start && info.age <= end)
        {
            if (club_s[Zero] == info.swimTime)
            {
                name1 = info.name;
            }
            if (club_c[Zero] == info.cycleTime)
            {
                name2 = info.name;
            }
            if (club_r[Zero] == info.runTime)
            {
                name3 = info.name;
            }
        }
    }
    file.close();
    clr;
    winner_details(CLUB, name1, name2, name3);
    cout << "Do you want view details from another club (Y\\N): ";
    loop(bestTime);
}

void winner_details(string club, string name1, string name2, string name3)
{ /*Display the student/stud with the best time from each event*/
    string prev_n1, prev_n2, prev_n3;
    ifstream file;
    cout << "\n\t------------                                                    \t------------";
    cout << "\n\t\t========== STUDENTS WITH BEST TIME(s) FROM " << club << " ============";
    cout << "\n\t------------                                                    \t------------";
    file.open(filename, ios::in | ios::binary);
    while (file)
    {
        file.read(reinterpret_cast<char *>(&info), sizeof(Triathlete));
        if ((name1 == info.name) && !(prev_n1 == info.name))
        {
            cout << "\n\n\t\t\tStudent \t\t->\t\t " << name1 << endl;
            cout << "\t\t\tSwim Time \t\t->\t\t " << info.s_con << endl
                 << endl;
            prev_n1 = info.name;
        }
        if ((name2 == info.name) && !(prev_n2 == info.name))
        {
            cout << "\n\n\t\t\tStudent \t\t->\t\t " << name2 << endl;
            ;
            cout << "\t\t\tCycling Time \t\t->\t\t " << info.c_con << endl
                 << endl;
            prev_n2 = info.name;
        }
        if ((name3 == info.name) && !(prev_n3 == info.name))
        {
            cout << "\n\t\t\tStudent \t\t->\t\t " << name3 << endl;
            cout << "\t\t\tRun Time \t\t-> \t\t " << info.r_con << endl
                 << endl;
            prev_n3 = info.name;
        }
    }
    cout << "\n\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "\t====================================================================================\n\n\n";
    file.close();
}

string getEvent()
{
    string event_type;
    cout << "Please enter your event Type: ";
    cin >> event_type;
    event_type[0] = toupper(event_type[0]);
    if (event_type[0] == 'S')
    {
        return "Swimming";
    }
    else if (event_type[0] == 'R')
    {
        return "Running";
    }
    else if (event_type[0] == 'C')
    {
        return "Cycling";
    }
}