#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <windows.h>

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Declaring the prototype of the User Defines Functions.
int Counter();
void Add_student();
void Save_Database();
void Load_Database();
void Show_All_Student();
void Edit_Student(int Edit_ID,int x);
void about();

void Search_Student();
void Search_by_ID();
void Search_by_NAME();
void Search_by_GPA_U();
void Show_SearchedByGPA_Student(int found[], int n);
void Not_Found();
void Show_Searched_Student(int i);
void Search_GoBack_Main();
void Delete_Student(int Delete_id,int x);

float Grade_Point(int a);
char* Latter_Grade(int a);

void gotoxy(int x, int y);
int pattern_loop(int *c,int n);

// Permanent Input and Output Formating.
const char* FORMAT_READ = "( %d, %[^,], %[^,], %d,";
const char* FORMAT_READ_COURSE = " %[^,], %[^,], %d, %f, %[^,],";
const char* FORMAT_WRITE = "( %d, %s, %s, %d,";
const char* FORMAT_WRITE_COURSE =" %s, %s, %d, %.2f, %s,";

int count = 0;
int choice;
int chO = 0;

void Menu();
void Add_student();
void Show_All_Student();
void gotoxy(int x, int y);
int pattern_loop(int *c,int n);
void Save_Database();
void Load_Database();
int Counter();
void Search_Student();

float Grade_Point(int a);
char* Latter_Grade(int a);

FILE* database;
FILE* counter;

struct student
{
    int sl;
    int ID;
    char name[30];
    char trimester_name[20];
    float trimester_gpa;
    int course_taken;
    char course_code[30][30];
    char course_name[30][30];
    int course_marks[8];
    float course_gpa[8];
    char course_grade[30][30];

} student[50];

int main()
{
    system("title CSE 13");
    system("cls");
    system("color F0");
    Load_Database();
    hidecursor();
    choice = 0;
    Menu();
}

void Menu()
{

    // Declaring array type character [Program Name Title][Enter Choice text];
    char Program_titile[40] = " NOTRE DAME UNIVERSITY BANGLADESH ";
    char choice_text[20] = "Enter Your Choice: ";
    // Declaring Menu Items;
    char menu_items[20][40] =
    {
        "[1] Add Student.",
        "[2] Search Student.",
        "[3] Show all Student database.",
        "[4] Edit Student Details.",
        "[5] Delete Student",
        "[6] Reset Software.",
        "[7] About Developer.",
        "[8] Exit.",
    };

    // Menu Box;
    gotoxy(0,2);
    int p=22,q=22;
    printf("\t\t\t");
    for(int i=1; i<=p; i++)
    {
        for(int j=1; j<=q; j++)
        {
            if(i==p || i==1 || j==1 || j==q || i==5 && j>=1 && j<=q \
                    || i==20 && j>=1 && j<=q)
                printf("\xB1\xB1\xB1");
            else
                printf("   ");
        }
        printf("\n");
        printf("\t\t\t");
    }

    // Printing Menu items into the box;
    for(int i=0; i<=strlen(menu_items); i++)
    {
        gotoxy(45,i+8);
        printf("%s",menu_items[i]); // Menu items are getting from array of string declared up line: 53;
    }
    gotoxy(32,1); printf("FOR BETTER VIEW, MAKE THE COMPILER FULL SCREEN MOOD.");
    gotoxy(66,19);
    count = Counter(); // Calling the function to get the counter from the file. [counter.dat]
    printf("Total Students: %d",count);
    // printing title after printing the menu box, either menu box's
    // loop will replace the text;
    gotoxy(40,3);
    printf("%c",201);
    pattern_loop(205,34);
    printf("%c",187);
    gotoxy(40,4);
    printf("%c",186);
    printf("%s",Program_titile);
    printf("%c",186);
    gotoxy(40,5);
    printf("%c",200);
    pattern_loop(205,34);
    printf("%c",188);
    // Title of the program print done.

    // Printing choice text;
    gotoxy(45,22);
    printf("%s",choice_text);
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        system("cls");
        Add_student();
        break;
    case 2:
        system("cls");
        Search_Student();
        break;
    case 3:
        system("cls");
        Show_All_Student();
        break;
    case 4:
        system("cls");
        Show_All_Student();
        break;
    case 5:
        system("cls");
        Show_All_Student();
        break;
    case 6:
        system("cls");
        remove("student_cse13.dat");
        counter = fopen("counter.dat","w+");
        fseek(counter,0,SEEK_SET);
        fprintf(counter,"%d",0);
        fclose(counter);
        getch();
        main();
        break;
    case 7:
        system("cls");
        about();
        break;
    case 8:
        exit(1);
        break;
    default:
        gotoxy(40,25);
        printf("  Please choose between 1-7.");
        gotoxy(40,26);
        printf("Press any key to choose again.");
        getch();
        fflush(stdin);
        main();
    }
}

void Add_student()
{
    count = Counter();
    ++count;
    float gpa = 0.00;
    char* latter;
    float trimester_gpa_here = 0.00;
    char name[40];
    printf("\n\n\n STUDENT %d",count);
    printf("\n\nID: ");
    scanf("%d",&student[count].ID);
    printf("\n Student Name: ");
    fflush(stdin);
    gets(name);
    char ch;
    for(int i=0; i<strlen(name); i++)
    {
        ch = name[i];
        name[i] = toupper(ch);
    }
    strcpy(student[count].name,name);
    printf("\n Trimester Name: ");
    gets(student[count].trimester_name);
    printf("\n How many Course: ");
    scanf("%d",&student[count].course_taken);

    for(int j=0; j<student[count].course_taken; j++)
    {
        fflush(stdin);
        printf("\n\n");
        pattern_loop(196,26);
        printf("[Course %d]\n",j+1);
        printf(" Course Code   : ");
        gets(student[count].course_code[j]);
        printf(" Course Name   : ");
        gets(student[count].course_name[j]);
        printf(" Course Marks  : ");
        scanf("%d",&student[count].course_marks[j]);
        gpa = Grade_Point(student[count].course_marks[j]);
        printf("\n Course GPA    : %.2f\n",gpa);
        student[count].course_gpa[j] = gpa;
        latter = Latter_Grade(student[count].course_marks[j]);
        printf(" Latter Grade  : %s\n",latter);
        strcpy(student[count].course_grade[j],latter);
        trimester_gpa_here = trimester_gpa_here + student[count].course_gpa[j];
        pattern_loop(196,34);
    }
    student[count].trimester_gpa = trimester_gpa_here/student[count].course_taken;
    printf("\n\n Trimester GPA: %.2f",student[count].trimester_gpa);

    Save_Database(); // Function to Save the Student Data.
    // Repeating Adding Students.
    printf("\n\n DO YOU WANT TO ADD ANOTHER STUDENT? 'Y' OR 'N'");
    char a = getch();
    if(a == 'Y' || a == 'y')
    {
        system("cls");
        Add_student();
    }
    else
    {
        main();
    }

    getch();
    main();
}

void Save_Database()
{
    // Saving Student Data
    database = fopen("student_cse13.dat","a");
    fprintf(database,FORMAT_WRITE,student[count].ID,student[count].name,
            student[count].trimester_name,student[count].course_taken);
    for(int j=0; j<student[count].course_taken; j++)
    {
        fprintf(database,FORMAT_WRITE_COURSE,student[count].course_code[j],student[count].course_name[j],
                student[count].course_marks[j],student[count].course_gpa[j],student[count].course_grade[j]);
    }
    fprintf(database," %.2f)\n",student[count].trimester_gpa);
    fclose(database);

    counter = fopen("counter.dat","w+");
    fseek(counter,0,SEEK_SET);
    fprintf(counter,"%d",count);
    fclose(counter);

    // Saving End Here!
}

void Show_All_Student()
{
    system("cls");
    hidecursor();
    Load_Database();
    int x = 7;
    printf("\n\n");
    printf("      Total Students : %d",count);
    printf("\n\n");
    printf("    \xC9");
    pattern_loop(205,150);
    printf("\xBB");
    printf("\n    \xBA SL \xBA ID NUMBER  \xBA  STUDENT NAME        \xBA TRIMESTER    \xBA COURSE CODE \xBA "
           "COURSE NAME                \xBA POINT  \xBA GPA  \xBA LATTER GRADE  \xBA TRIMISTER GPA");
    printf("     \xBA\n");
    printf("    \xC8");
    pattern_loop(205,150);
    printf("\xB9");
    for(int i=1; i<=count; i++)
    {
        gotoxy(6,x);
        printf("%d",i);
        gotoxy(11,x);
        printf("%d",student[i].ID);
        gotoxy(24,x);
        printf("%s",student[i].name);
        gotoxy(47,x);
        printf("%s",student[i].trimester_name);
        int k = 0;
        for(int j=1; j<=student[i].course_taken; j++)
        {
            gotoxy(62,x+k);
            printf("%s",student[i].course_code[j]);
            gotoxy(76,x+k);
            printf("%s",student[i].course_name[j]);
            gotoxy(106,x+k);
            printf("%3d",student[i].course_marks[j]);
            gotoxy(114,x+k);
            printf("%.2f",student[i].course_gpa[j]);
            gotoxy(125,x+k);
            printf("%s",student[i].course_grade[j]);
            k++;
        }
        gotoxy(140,x);
        printf("%.2f",student[i].trimester_gpa);
        gotoxy(5,x+k);
        pattern_loop(196,150);
        x += student[i].course_taken + 1;
    }
    // For the Lines
    for(int l=6; l<x; l++)
    {
        gotoxy(4,l);
        printf("\xBA");
        gotoxy(9,l);
        printf("\xBA");
        gotoxy(22,l);
        printf("\xBA");
        gotoxy(45,l);
        printf("\xBA");
        gotoxy(60,l);
        printf("\xBA");
        gotoxy(74,l);
        printf("\xBA");
        gotoxy(103,l);
        printf("\xBA");
        gotoxy(112,l);
        printf("\xBA");
        gotoxy(119,l);
        printf("\xBA");
        gotoxy(135,l);
        printf("\xBA");
        gotoxy(155,l);
        printf("\xBA");
    }

    // Section Delete - Choice 5
    if(choice == 4)
    {
        int Edit_ID;
        gotoxy(8,x);
        pattern_loop(220,50);
        gotoxy(10,x+2);
        printf("ENTER STUDENT ID TO EDIT : ");
        gotoxy(8,x+4);
        pattern_loop(223,50);
        gotoxy(40,x+2);
        scanf("%d",&Edit_ID);
        Edit_Student(Edit_ID,x);
    }
    if(choice == 5)
    {
        int Delete_ID;
        gotoxy(8,x);
        pattern_loop(220,50);
        gotoxy(10,x+2);
        printf("TO DELETE, ENTER STUDENT ID: ");
        gotoxy(8,x+4);
        pattern_loop(223,50);
        gotoxy(40,x+2);
        scanf("%d",&Delete_ID);
        Delete_Student(Delete_ID,x);
    }
    if(choice == 3)
    {
        getch();
        main();
    }
}

void gotoxy(int x, int y)
{
    // gotoxy(space,lines);
    COORD coord;
    coord.X = x, coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int pattern_loop(int *c,int n)
{
    for(int i=1; i<=n; i++)
        printf("%c",c);
}

float Grade_Point(int a)
{
    if(a < 40)
    {
        return 0.00;
    }
    else if(a >= 40 && a <= 40)
    {
        return 2.00;
    }
    else if(a >= 45 && a <= 49)
    {
        return 2.25;
    }
    else if(a >= 50 && a <= 54)
    {
        return 2.50;
    }
    else if(a >= 55 && a <= 59)
    {
        return 2.75;
    }
    else if(a >= 60 && a <= 64)
    {
        return 3.00;
    }
    else if(a >= 65 && a <= 69)
    {
        return 3.25;
    }
    else if(a >= 70 && a <= 74)
    {
        return 3.50;
    }
    else if(a >= 75 && a <= 79)
    {
        return 3.75;
    }
    else if(a >= 80 && a <= 100)
    {
        return 4.00;
    }
    else
    {
        return 0.00;
    }
}

char* Latter_Grade(int a)
{
    if(a < 40)
    {
        return "F";
    }
    else if(a >= 40 && a <= 40)
    {
        return "D";
    }
    else if(a >= 45 && a <= 49)
    {
        return "C";
    }
    else if(a >= 50 && a <= 54)
    {
        return "C+";
    }
    else if(a >= 55 && a <= 59)
    {
        return "B-";
    }
    else if(a >= 60 && a <= 64)
    {
        return "B";
    }
    else if(a >= 65 && a <= 69)
    {
        return "B+";
    }
    else if(a >= 70 && a <= 74)
    {
        return "A-";
    }
    else if(a >= 75 && a <= 79)
    {
        return "A";
    }
    else if(a >= 80 && a <= 100)
    {
        return "A+";
    }
    else
    {
        return "F";
    }
}



void Load_Database()
{
    count = Counter();
    database = fopen("student_cse13.dat","r");
    if(database == NULL)
    {
        printf("Error! Loading Database.");
    }

    for(int i=1; i<=count; i++)
    {
        fscanf(database,FORMAT_READ,&student[i].ID,student[i].name,
               student[i].trimester_name,&student[i].course_taken);
        for(int j=1; j<=student[i].course_taken; j++)
        {
            fscanf(database,FORMAT_READ_COURSE,student[i].course_code[j],student[i].course_name[j],
                   &student[i].course_marks[j],&student[i].course_gpa[j],student[i].course_grade[j]);
        }
        fscanf(database," %f)\n",&student[i].trimester_gpa);
    }
    fclose(database);
}

int Counter()
{
    counter = fopen("counter.dat","r");
    fscanf(counter,"%d",&count);
    return count;
}

void Search_Student()
{
    int l = 10;
    gotoxy(55,l);
    pattern_loop(219,50);
    gotoxy(60,l+2);
    printf("1.SEARCH BY ID [2011200**]");
    gotoxy(60,l+3);
    printf("2.SEARCH BY NAME [STUDENT'S FULL NAME]");
    gotoxy(60,l+4);
    printf("3.SEARCH BY CGPA  -Upper");
    gotoxy(60,l+5);
    printf("4.SEARCH BY CGPA  -Lower");
    gotoxy(60,l+6);
    printf("5.Back to Main Menu");
    gotoxy(55,l+8);
    pattern_loop(219,50);
    chO = getch();

    switch(chO)
    {
    case '1':
        system("cls");
        Search_by_ID();
        break;
    case '2':
        system("cls");
        Search_by_NAME();
        break;
    case '3':
        system("cls");
        Search_by_GPA_U();
        break;
    case '4':
        system("cls");
        Search_by_GPA_U();
        break;
    case '5':
        system("cls");
        main();
        break;
    default:
        system("cls");
        main();
    }

}

void Search_GoBack_Main()
{
    char ch;
    int l = 2;
    gotoxy(55,l);
    pattern_loop(177,50);
    gotoxy(60,l+2);
    printf("Enter - Search Again.");
    gotoxy(60,l+3);
    printf("S - Back to Search Menu");
    gotoxy(60,l+4);
    printf("M - Back to Main Menu");
    gotoxy(55,l+6);
    pattern_loop(177,50);
    ch = getch();
    if(ch == 's' || ch == 'S')
    {
        system("cls");
        system("color F0");
        chO = 0;
        Search_Student();
    }
    else if(ch == 'm' || ch == 'M')
    {
        system("cls");
        system("color F0");
        main();
    }
    else
    {
        system("cls");
        system("color F0");
        if(chO == '1')
        {
            Search_by_ID();
        }
        else if(chO == '2')
        {
            Search_by_NAME();
        }
        else
        {
            main();
        }
    }
}

void Search_by_ID()
{
    int id;
    int found=0;
    gotoxy(55,10);
    pattern_loop(219,50);
    gotoxy(60,12);
    printf("ENTER STUDENT ID: ");
    gotoxy(55,14);
    pattern_loop(219,50);
    gotoxy(80,12);
    scanf("%d",&id);
    for(int i=1; i<=count; i++)
    {
        if(student[i].ID == id)
        {
            found = i;
            Show_Searched_Student(i);
        }
    }
    if(found == 0)
    {
        Not_Found();
    }
}

void Search_by_NAME()
{

    char students_name[35];
    char name[35];
    int found=0;
    gotoxy(55,10);
    pattern_loop(219,50);
    gotoxy(60,12);
    printf("ENTER STUDENT's FULL NAME: ");
    fflush(stdin);
    gotoxy(55,14);
    pattern_loop(219,50);
    gotoxy(87,12);
    gets(name);
    // Transforming Letter to Capital
    for(int i=0; i<strlen(name); i++)
    {
        char ch = name[i];
        name[i] = toupper(ch);
    }
    strcpy(students_name,name);
    for(int i=1; i<=count; i++)
    {
        found = strcmp(student[i].name,students_name);
        if(found == 0)
        {
            Show_Searched_Student(i);
        }
    }
    if(found != 0)
    {
        Not_Found();
    }
}

float gpa;

void Search_by_GPA_U()
{

    int found[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 25
    gotoxy(55,10);
    pattern_loop(219,50);
    gotoxy(60,12);
    printf("ENTER GPA: ");
    gotoxy(55,14);
    pattern_loop(219,50);
    gotoxy(72,12);
    scanf("%f",&gpa);
    int j = 0 ;
    if(chO == '3')
    {
        for(int i=1; i<=count; i++)
        {
            if(student[i].trimester_gpa >= gpa)
            {
                ++j;
                found[j] = i;
            }
        }
        printf("\n\n    [%d]Students got Upper than - %.2f ",j,gpa);
    }
    else if(chO == '4')
    {
        for(int i=1; i<=count; i++)
        {
            if(student[i].trimester_gpa <= gpa)
            {
                ++j;
                found[j] = i;
            }
        }
        printf("\n\n    [%2d]Students got Less than - %.2f ",j,gpa);
    }
    Show_SearchedByGPA_Student(found,j);
    if(found[0] == 0)
    {
        Not_Found();
    }

}

void Show_SearchedByGPA_Student(int found[], int n)
{
    hidecursor();
    int x = 21;
    printf("\n\n");
    printf("    \xC9");
    pattern_loop(205,150);
    printf("\xBB");
    printf("\n    \xBA SL \xBA ID NUMBER  \xBA  STUDENT NAME        \xBA TRIMESTER    \xBA COURSE CODE \xBA "
           "COURSE NAME                \xBA POINT  \xBA GPA  \xBA LATTER GRADE  \xBA TRIMISTER GPA");
    printf("     \xBA\n");
    printf("    \xC8");
    pattern_loop(205,150);
    printf("\xB9");
    for(int i=1; i<=n; i++)
    {
        gotoxy(6,x);
        printf("%d",i);
        gotoxy(11,x);
        printf("%d",student[found[i]].ID);
        gotoxy(24,x);
        printf("%s",student[found[i]].name);
        gotoxy(47,x);
        printf("%s",student[found[i]].trimester_name);
        int k = 0;
        for(int j=1; j<=student[found[i]].course_taken; j++)
        {
            gotoxy(62,x+k);
            printf("%s",student[found[i]].course_code[j]);
            gotoxy(76,x+k);
            printf("%s",student[found[i]].course_name[j]);
            gotoxy(106,x+k);
            printf("%3d",student[found[i]].course_marks[j]);
            gotoxy(114,x+k);
            printf("%.2f",student[found[i]].course_gpa[j]);
            gotoxy(125,x+k);
            printf("%s",student[found[i]].course_grade[j]);
            k++;
        }
        gotoxy(140,x);
        printf("%.2f",student[found[i]].trimester_gpa);
        gotoxy(5,x+k);
        pattern_loop(196,150);
        x += student[found[i]].course_taken + 1;
    }
    // For the Lines
    for(int l=20; l<x; l++)
    {
        gotoxy(4,l);
        printf("\xBA");
        gotoxy(9,l);
        printf("\xBA");
        gotoxy(22,l);
        printf("\xBA");
        gotoxy(45,l);
        printf("\xBA");
        gotoxy(60,l);
        printf("\xBA");
        gotoxy(74,l);
        printf("\xBA");
        gotoxy(103,l);
        printf("\xBA");
        gotoxy(112,l);
        printf("\xBA");
        gotoxy(119,l);
        printf("\xBA");
        gotoxy(135,l);
        printf("\xBA");
        gotoxy(155,l);
        printf("\xBA");
    }
    Search_GoBack_Main();
}


void Not_Found()
{
    system("cls");
    system("color 40");
    gotoxy(55,10);
    pattern_loop(175,50);
    gotoxy(65,12);
    printf(" STUDENT NOT FOUND");
    gotoxy(55,14);
    pattern_loop(174,50);
    Search_GoBack_Main();
}

void Show_Searched_Student(int i)
{

    hidecursor();
    int x=21;
    printf("\n\n");
    printf("      Total Students : %d\n\n",count);
    printf("    \xC9");
    pattern_loop(205,150);
    printf("\xBB");
    printf("\n    \xBA SL \xBA ID NUMBER  \xBA  STUDENT NAME        \xBA TRIMESTER    \xBA COURSE CODE \xBA "
           "COURSE NAME                \xBA POINT  \xBA GPA  \xBA LATTER GRADE  \xBA TRIMISTER GPA");
    printf("     \xBA\n");
    printf("    \xC8");
    pattern_loop(205,150);
    printf("\xB9");

    gotoxy(6,x);
    printf("%d",student[i].sl);
    gotoxy(11,x);
    printf("%d",student[i].ID);
    gotoxy(24,x);
    printf("%s",student[i].name);
    gotoxy(47,x);
    printf("%s",student[i].trimester_name);
    int k = 0;
    for(int j=1; j<=student[i].course_taken; j++)
    {
        gotoxy(62,x+k);
        printf("%s",student[i].course_code[j]);
        gotoxy(76,x+k);
        printf("%s",student[i].course_name[j]);
        gotoxy(106,x+k);
        printf("%3d",student[i].course_marks[j]);
        gotoxy(114,x+k);
        printf("%.2f",student[i].course_gpa[j]);
        gotoxy(125,x+k);
        printf("%s",student[i].course_grade[j]);
        k++;
    }
    gotoxy(140,x);
    printf("%.2f",student[i].trimester_gpa);
    gotoxy(5,x+k);
    pattern_loop(196,150);
    x += student[i].course_taken + 1;
    // For the Lines
    for(int l=20; l<x; l++)
    {
        gotoxy(4,l);
        printf("\xBA");
        gotoxy(9,l);
        printf("\xBA");
        gotoxy(22,l);
        printf("\xBA");
        gotoxy(45,l);
        printf("\xBA");
        gotoxy(60,l);
        printf("\xBA");
        gotoxy(74,l);
        printf("\xBA");
        gotoxy(103,l);
        printf("\xBA");
        gotoxy(112,l);
        printf("\xBA");
        gotoxy(119,l);
        printf("\xBA");
        gotoxy(135,l);
        printf("\xBA");
        gotoxy(155,l);
        printf("\xBA");
    }
    Search_GoBack_Main();

}


void Delete_Student(int Delete_id,int x)
{
    Load_Database();
    int found = 0;
    char cat;

    for(int i=1; i<=count; i++)
    {
        if(student[i].ID == Delete_id)
        {
            found = i;
        }
    }

    if(found == 0)
    {
        gotoxy(76,x);
        pattern_loop(220,50);
        gotoxy(78,x+2);
        printf("Student Data not found in the database.");
        gotoxy(76,x+4);
        pattern_loop(223,50);
        gotoxy(40,x+2);
        getch();
        main();
    }
    gotoxy(76,x);
    pattern_loop(220,56);
    gotoxy(78,x+2);
    printf("Are you Sure?");
    gotoxy(78,x+3);
    printf("you want to Delete  -%s's Data (Y/N)",student[found].name);
    gotoxy(76,x+5);
    pattern_loop(223,56);
    cat = getch();

    if(cat == 'y' || cat == 'Y')
    {
        count = Counter();
        database = fopen("student_cse13.dat","w");

        for(int i=1; i<=count; i++)
        {
            if(student[i].ID != Delete_id)
            {
                fprintf(database,"( %d, %s, %s, %d,",student[i].ID,student[i].name,
                        student[i].trimester_name,student[i].course_taken);
                for(int j=1; j<=student[i].course_taken; j++)
                {
                    fprintf(database,FORMAT_WRITE_COURSE,student[i].course_code[j],student[i].course_name[j],
                            student[i].course_marks[j],student[i].course_gpa[j],student[i].course_grade[j]);
                }
                fprintf(database," %.2f)\n",student[i].trimester_gpa);
            }
        }
        fclose(database);
        counter = fopen("counter.dat","w+");
        fseek(counter,0,SEEK_SET);
        fprintf(counter,"%d",count-1);
        fclose(counter);
    }
    else
    {
        choice = 0;
        Show_All_Student();
    }
    choice = 3;
    Show_All_Student();
}

void Edit_Student(int Edit_ID,int x)
{
    Load_Database();
    count = Counter();
    int found = -1;

    for(int i=1; i<=count; i++)
    {
        if(student[i].ID == Edit_ID)
        {
            found = i;
        }
    }
    if(found == -1)
    {
        gotoxy(76,x);
        pattern_loop(220,50);
        gotoxy(78,x+2);
        printf("Student Data not found in the database.");
        gotoxy(76,x+4);
        pattern_loop(223,50);
        gotoxy(40,x+2);
        getch();
        main();
    }

    system("cls");
    float gpa = 0.00;
    char* latter;
    float trimester_gpa_here = 0.00;
    char ask;
    char name[40];
    printf("\n EDIT DETAILS FOR ID: %d    NAME: %s \n\n",student[found].ID,student[found].name);
    // ID
    printf("\n ID: %d \xDB Edit ID?(y/n)",student[found].ID);
    ask = toupper(getch());
    if(ask == 'Y')
    {
        printf("\n\t New ID: ");
        scanf("%d",&student[found].ID);
    }
    // Name
    printf("\n Name: %s \xDB Edit Name?(y/n)",student[found].name);
    ask = toupper(getch());
    if(ask == 'Y')
    {
        printf("\n\t New Name: ");
        fflush(stdin);
        gets(name);
        char ch;
        for(int i=0; i<strlen(name); i++)
        {
            ch = name[i];
            name[i] = toupper(ch);
        }
        strcpy(student[found].name,name);
    }
    // Trimester Name
    printf("\n Trimester: %s \xDB Edit Trimester Name?(y/n)",student[found].trimester_name);
    ask = toupper(getch());
    if(ask == 'Y')
    {
        printf("\n\t New Trimester Name: ");
        fflush(stdin);
        gets(student[found].trimester_name);
    }

    // Showing Courses
    printf("\n\n\n No. Code \t Name \t\t\t\t   Marks");
    for(int j=1; j<=student[found].course_taken; j++){
        printf("\n %d. %s \t %s \t\t %3d",j,student[found].course_code[j],student[found].course_name[j],student[found].course_marks[j]);
    }
    printf("\n\n");

    // How many Course
    printf("\n\xDB Edit Courses?(y/n)");
    ask = toupper(getch());
    if(ask == 'Y')
    {
        printf("\n How many Course: ");
        scanf("%d",&student[found].course_taken);

        for(int j=1; j<=student[found].course_taken; j++)
        {
            fflush(stdin);
            printf("\n\n");
            pattern_loop(196,26);
            printf("[Course %d]\n",j);
            printf(" Course Code   : %s \xDB Edit?(y/n)",student[found].course_code[j]);
            ask = toupper(getch());
            if(ask == 'Y'){
                printf("\n\t Course Code   : ");
                gets(student[found].course_code[j]);
            }
            printf("\n Course Name   : %s \xDB Edit?(y/n)",student[found].course_name[j]);
            ask = toupper(getch());
            if(ask == 'Y'){
                printf("\n\t New Course Name   : ");
                gets(student[found].course_name[j]);
            }
            printf("\n Course Marks  : %3d \xDB Edit?(y/n)",student[found].course_marks[j]);
            ask = toupper(getch());
            if(ask == 'Y'){
                printf("\n\t New Course Marks  : ");
                scanf("%d",&student[found].course_marks[j]);
            }
            gpa = Grade_Point(student[found].course_marks[j]);
            printf("\n Course GPA    : %.2f\n",gpa);
            student[found].course_gpa[j] = gpa;
            latter = Latter_Grade(student[found].course_marks[j]);
            printf(" Latter Grade  : %s\n",latter);
            strcpy(student[found].course_grade[j],latter);
            trimester_gpa_here = trimester_gpa_here + student[found].course_gpa[j];
            pattern_loop(196,34);
        }
    student[found].trimester_gpa = trimester_gpa_here/student[found].course_taken;
    printf("\n\n Trimester GPA: %.2f",student[found].trimester_gpa);
    }
    printf("\n\n Student Data Edited Successful");
    printf("\n\ Press Any key - Main Menu");

    // Saving All Student Details to the Database.
    database = fopen("student_cse13.dat","w");

    for(int i=1; i<=count; i++)
    {
        fprintf(database,"( %d, %s, %s, %d,",student[i].ID,student[i].name,
                student[i].trimester_name,student[i].course_taken);
        for(int j=1; j<=student[i].course_taken; j++)
        {
            fprintf(database,FORMAT_WRITE_COURSE,student[i].course_code[j],student[i].course_name[j],
                    student[i].course_marks[j],student[i].course_gpa[j],student[i].course_grade[j]);
        }
        fprintf(database," %.2f)\n",student[i].trimester_gpa);
    }

    fclose(database);

    getch();
    choice = 3;
    Show_All_Student();

}

void about(){
    hidecursor();
    system("color C0");
    printf("\n\t\t\t     \xC9");
    pattern_loop(205,54);
    printf("\xBB"); // printing the pattern using function.                              |
    printf("\n\t\t\t     \xBA      WELCOME TO NUMBER CATAGORY APPLICATION  -1.0    \xBA");
    printf("\n\t\t\t     \xCC");
    pattern_loop(205,54);
    printf("\xB9");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA Developer : Omar Fahim                               \xBA");
    printf("\n\t\t\t     \xBA Site      : https://sites.google.com/view/omarfahim  \xBA");
    printf("\n\t\t\t     \xBA email     : omarfahimofficial@gmail.com              \xBA");
    printf("\n\t\t\t     \xBA github     : https://github.com/omarfahimofficial    \xBA");
    printf("\n\t\t\t     \xBA Version   : 1.0 - 25 April, 2020 [Sunday]            \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA     This application is made with C Programming      \xBA");
    printf("\n\t\t\t     \xBA     Language. It's a Student Management System       \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA   please feel free to email me for any kind of help  \xBA");
    printf("\n\t\t\t     \xBA           and to give any kind of suggestions        \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA                     'THANK YOUR'                     \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xBA                                                      \xBA");
    printf("\n\t\t\t     \xC8");pattern_loop(205,54);printf("\xBC");
    getch();
    main();
}
