#include <stdio.h>//info related to standard input output functions
#include <conio.h>//info related to console input output functions
#include <string.h>//info related to various string functions
#include <stdlib.h>//info related to various stsndard library functions

struct Room //Structures are used because it allows combining data items of diff kind in diff memory blocks 
{
    char room_no[10];
    char dept[20];
    char room_capacity[5];
    char block[5];
}R;

struct Course
{
    char course_id[10];
    char dept[20];
    char course_name[20];
    char course_capacity[10];
    char course_timing[10];
    char course_credits[5];
    char course_day[10];
}C;

struct Teacher
{
    char Teacher_id[10];
    char Teacher_name[20];
    char Teacher_course[20];
    char dept[20];
}T;

struct Schedule
{
    char course_id[10];
    char room_no[10];
    char dept[20];
    char room_capacity[10];
    char course_name[20];
    char course_capacity[10];
    char course_timing[10];
    char course_credits[5];
    char block[10];
    char course_day[10];
    char Teacher_id[10];
    char Teacher_name[20];
}S;

long si = sizeof(R);// it is used to move the file pointer according to the size of data 
long si1 = sizeof(C);
long si2 = sizeof(S);
long si3 = sizeof(T);


//Function 
void Admin_Login();
void Student_Login();

void Final_Schedule();
int Skip_Record();

void Schedule_Day_Wise();
void Schedule_Day();

void Schedule_Department_Wise();
void Schedule_Dept();

void Add_Room();
void Add_Teacher();
void Add_Course();

int Already_Existed_Room();
int Already_Existed_Course();
int Already_Existed_Teacher();

//All display function
void Display();
void Display_Room();
void Display_Course();
void Display_Teacher();
void Display_Schedule();

void Update();
void Update_room();
void Update_course();
void Update_Teacher();

void Delete();
void Delete_room();
void Delete_course();
void Delete_Teacher();

void Search();
void Search_Room();
void Search_Course();
void Search_Teacher();

void Main_Menu_Admin();
void Main_Menu_Student();

FILE *fp;//file pointer declared globally so that it can be used anywhere inside the program 

int main()
{
    int ch;
    while (1)
    {
        printf("<== LOGIN MENU ==>\n");
        printf("1.Login as Admin \n");
        printf("2.Login as Student \n");
        printf("0.Exit\n\n");
        printf("Enter Your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            Admin_Login();
            break;

        case 2:
            Student_Login();
            break;

        default:
            printf("Invalid Choice");
        }
    }
}

void Admin_Login()
{
    int u = 123, p = 123;
    //int u1 = 123, p1 = 123;
    int u1, p1;
    printf("<== Admin LOGIN ==>\n");
	printf("Enter user id \n");
    scanf("%d", &u1);
    printf("Enter password \n");
    scanf("%d", &p1);
	if (u == u1 && p == p1)
    {
        printf("login Successfully");
        Main_Menu_Admin();
    }
    else
    {
        printf("login failed");
    }
}

void Student_Login()
{
    char s_username[20],s_password[20];
    
	printf("<== Student LOGIN ==>\n");
    printf("Enter user name \n");
    fflush(stdin);
	gets(s_username);
    
	printf("Enter password \n");
	gets(s_password);

    if(strcmp(s_username,"HEALTH_SCIENCE")==0)
        {
            Schedule_Dept("HEALTH_SCIENCE");
        }
    if(strcmp(s_username,"CS")==0)
        {
            Schedule_Dept("CS");
        }    
	if(strcmp(s_username,"LAW")==0)
        {
            Schedule_Dept("LAW");
        }
	if(strcmp(s_username,"DESIGN")==0)
        {
            Schedule_Dept("DESIGN");
        }
    if(strcmp(s_username,"BUSINESS")==0)
        {
            Schedule_Dept("BUSINESS");
        }
    else
        printf("login Failed");
    }
void Main_Menu_Admin()
{
    int ch;
    while (1)
    {
        printf("<== Select your choice ==>\n");
        printf("1.Add Room\n");
        printf("2.Add Course\n");
        printf("3.Add Teacher\n");
        printf("4.Display\n");
        printf("5.Update\n");
        printf("6.Delete\n");
        printf("7.Search\n");
        printf("8.Schedule_Day_Wise\n");
        printf("9.Schedule_Department_Wise\n");
        printf("10.Generate\n");
        printf("0.Exit\n\n");
        printf("Enter Your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            Add_Room();
            break;

        case 2:
            Add_Course();
            break;
        case 3:
            Add_Teacher();
            break;

        case 4:
            Display();
            break;

        case 5:
            Update();
            break;

        case 6:
            Delete();
            break;

        case 7:
            Search();
            break;

		case 8:
            Schedule_Day_Wise();
            break;

        case 9:
            Schedule_Department_Wise();
            break;

        case 10:
            Final_Schedule();
            break;

        default:
            printf("Invalid Choice");
        }
    }
}

/*
void Main_Menu_Student()
{
    int ch;
    while (1)
    {
        printf("<== Select your choice ==>\n");
        printf("1.info\n");
        printf("2.Attendence\n");
        printf("3.Schedule\n");
        printf("0.Exit\n\n");
        printf("Enter Your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            student_info();
            break;

        case 2:
            student_attendence();
            break;

        case 3:
            Final_Schedule();
            break;

        default:
            printf("Invalid Choice");
        }
    }
}*/

void Add_Room()
{
    fp = fopen("Room.txt", "ab");//opening file in append mode
    fflush(stdin);//empting the string buffer
    printf("Enter room code: ");
    gets(R.room_no);
    if (!Already_Existed_Room())
    {
        printf("Enter Room Capacity: ");
        gets(R.room_capacity);
        printf("Enter department: ");
        gets(R.dept);
        printf("Enter block:");
        gets(R.block);
        fwrite(&R, sizeof(R), 1, fp);//fwrite is used to write data into file
        printf("Record Saved Successfully \n");
        fclose(fp);
        return;
    }
    Add_Room();
}

int Already_Existed_Room()//this function will helps us by preventing duplication of records
{
    struct Room Rtemp;
    FILE *fpn;
    int already = 0;
    fpn = fopen("Room.txt", "rb");//file in read mode
    while (fread(&Rtemp, sizeof(Rtemp), 1, fpn) == 1)//reading the data from the file till its end
        if (strcmp(R.room_no, Rtemp.room_no) == 0)//strcmp is used to compare two diff strings
        {
            printf("Room Already Exists\n");
            already = 1;
            break;
        }
    fclose(fpn);
    return already;
}

void Add_Course()
{
    fp = fopen("Course.txt", "ab");
    fflush(stdin);
    printf("Enter course id: ");
    gets(C.course_id);
    printf("Enter course Name:");
    gets(C.course_name);
    printf("Enter department: ");
    gets(C.dept);
    printf("Enter course day: ");
    gets(C.course_day);
    printf("Enter course timing: ");
    gets(C.course_timing);

    if (!Already_Existed_Course())
    {
        printf("Enter course Capacity: ");
        gets(C.course_capacity);
        printf("Enter course credits: ");
        gets(C.course_credits);
        fwrite(&C, sizeof(C), 1, fp);
        printf("Record Saved Successfully \n");
        fclose(fp);
        return;
    }
    Add_Course();
}

int Already_Existed_Course()
{
    struct Course Ctemp;
    int already = 0;
    FILE *fpn;
    fpn = fopen("Course.txt", "rb");
    while (fread(&Ctemp, sizeof(Ctemp), 1, fpn) == 1)
    {
        if (strcmp(C.course_id, Ctemp.course_id) == 0 && strcmp(C.dept, Ctemp.dept) == 0 && strcmp(C.course_day, Ctemp.course_day) == 0 && strcmp(C.course_timing, Ctemp.course_timing) == 0)
        {
            printf("Course Already Exists\n");
            already = 1;
            break;
        }
    }
    fclose(fpn);
    return already;
}

void Add_Teacher()
{
    fp = fopen("Teacher.txt", "ab");
    printf("Enter Teacher id: ");
    fflush(stdin);
    gets(T.Teacher_id);
    if (!Already_Existed_Teacher())
    {
        printf("Enter Teacher name: ");
        gets(T.Teacher_name);
        printf("Enter Teacher's department: ");
        gets(T.dept);
        printf("Enter Teacher's course:");
        gets(T.Teacher_course);
        fwrite(&T, sizeof(T), 1, fp);
        printf("Record Saved Successfully");
        fclose(fp);
        return;
    }
    Add_Teacher();
}

int Already_Existed_Teacher()
{

    struct Teacher Ttemp;
    int already = 0;
    FILE *fpn;
    fpn = fopen("Teacher.txt", "rb");
    while (fread(&Ttemp, sizeof(Ttemp), 1, fpn) == 1)
    {
        if (strcmp(T.Teacher_id, Ttemp.Teacher_id) == 0)
        {
            printf("Teacher Already Exists\n");
            already = 1;
            break;
        }
    }
    fclose(fpn);
    return already;
}

void Display()
{
    int ch;

    while (1)
    {
        printf("<== Display By ==>\n");
        printf("<==-------------==>\n");
        printf("1.Display Room\n");
        printf("2.Display Course\n");
        printf("3.Display Teacher\n");
        printf("4.Display Schedule\n");
        printf("0.Back To Main Menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Display_Room();
            break;

        case 2:
            Display_Course();
            break;

        case 3:
            Display_Teacher();
            break;
        
		case 4:
            Display_Schedule();
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}

void Display_Room()
{
    printf("<== Room Info ==>\n\n");
    printf("%-10s %-20s %-10s %s\n", "No", "Capacity", "dept", "block");
    fp = fopen("Room.txt", "rb");//opening roo.txt in read mode
    while (fread(&R, sizeof(R), 1, fp) == 1)//reading data till the end of room.txt
    {
        printf("%-10s %-20s %-10s %s\n", R.room_no, R.room_capacity, R.dept, R.block);
    }
    fclose(fp);
    printf("Press any key to continue... \n");
}

void Display_Course()
{
    printf("<== Course Info ==>\n\n");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %s\n", "course_id", "course_name", "capacity", "dept", "timing", "credits", "Day");
    fp = fopen("Course.txt", "rb");
    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        printf("%-10s %-11s %-11s %-9s %-10s %-10s %s\n", C.course_id, C.course_name, C.course_capacity, C.dept, C.course_timing, C.course_credits, C.course_day);
    }
    fclose(fp);
    printf("Press any key to continue... \n");
}

void Display_Teacher()
{
    printf("<== Teacher Info ==>\n\n");
    printf("%-10s %-10s %-10s %s\n", "Id", "Name", "dept", "Course");
    fp = fopen("Teacher.txt", "rb");
    while (fread(&T, sizeof(T), 1, fp) == 1)
    {
        printf("%-10s %-10s %-10s %s\n", T.Teacher_id, T.Teacher_name, T.dept, T.Teacher_course);
    }
    fclose(fp);
    printf("Press any key to continue... \n");
}

void Display_Schedule()
{
    printf("<== Schedule Info ==>\n\n");
    printf("%-8s %-10s %-10s %-10s %-7s %-6s %-7s %-10s %-10s %-10s %-10s  %s\n", "room_no", "course_id", "course_name", "r_capacity", "c_capacity", "dept", "timing", "credits", "Day", "Teacher", "T_id", "Block");
    fp = fopen("Schedule.txt", "rb");
    while (fread(&S, sizeof(S), 1, fp) == 1)
    {
        printf("%-8s %-10s %-12s %-10s %-10s %-6s %-9s %-6s %-12s %-10s %-10s  %s\n", S.room_no, S.course_id, S.course_name, S.room_capacity, S.course_capacity, S.dept, S.course_timing, S.course_credits, S.course_day, S.Teacher_name, S.Teacher_id, S.block);
    }
    fclose(fp);
    printf("Press any key to continue... \n");
}

void Update()
{
    int ch;
    while (1)
    {
        printf("<== Update ==>\n");
        printf("1.Update Room\n");
        printf("2.Update Course\n");
        printf("3.Update Teacher\n");
        printf("0.Back To Main Menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Update_room();
            break;

        case 2:
            Update_course();
            break;

        case 3:
            Update_Teacher();
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}

void Update_room()
{
    int f1 = 0;
    char roomno1[10];//creating a array of character type so that we can put room no in it 
    printf("Enter Room No To Modifiy: ");
    fflush(stdin);//empty the string buffer
    gets(roomno1);

    fp = fopen("Room.txt", "rb+");
    while (fread(&R, sizeof(R), 1, fp) == 1)
    {
        if (strcmp(roomno1, R.room_no) == 0)//compairing room no from room.txt file
        {
            f1 = 1;
            printf("Enter New room capacity: ");
            fflush(stdin);
            gets(R.room_capacity);
            printf("Enter new department: ");
            gets(R.dept);
            printf("Enter New block: ");
            gets(R.block);
            fseek(fp, -si, 1);//fseek is used to set the position of file pointer to given offset
            //-si is used to more backword in file
            fwrite(&R, sizeof(R), 1, fp);
            fclose(fp);
            break;
        }
    }
    if (f1 == 0)
        printf("Record Not Found...\n");
    else
        printf("Modified Successfully...\n");
}

void Update_course()
{
    char courseid[10];
    int f2 = 0;
    printf("Enter course id To Modifiy: ");
    fflush(stdin);
    gets(courseid);

    fp = fopen("Course.txt", "rb+");
    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        if (strcmp(courseid, C.course_id) == 0)
        {
            f2 = 1;
            printf("Enter New Course Name: ");
            fflush(stdin);
            gets(C.course_name);
            printf("Enter new course capacity: ");
            gets(C.course_capacity);
            printf("Enter New dept Name: ");
            gets(C.dept);
            printf("Enter new course timing: ");
            gets(C.course_timing);
            printf("Enter new course credits: ");
            gets(C.course_credits);
            printf("Enter new course day: ");
            gets(C.course_day);
            fseek(fp, -si1, 1);
            fwrite(&C, sizeof(C), 1, fp);
            fclose(fp);
            break;
        }
    }
    if (f2 == 0)
        printf("Record Not Found...\n");
    else
        printf("Modified Successfully...\n");
}

void Update_Teacher()
{
    int f1 = 0;
    char Tid[10];
    printf("Enter Teacher id To Modifiy: ");
    fflush(stdin);
    gets(Tid);

    fp = fopen("Teacher.txt", "rb+");
    while (fread(&T, sizeof(T), 1, fp) == 1)
    {
        if (strcmp(Tid, T.Teacher_id) == 0)
        {
            f1 = 1;
            printf("Enter new Teacher id: ");
            fflush(stdin);
            gets(T.Teacher_id);
            printf("Enter new Teacher name: ");
            gets(T.Teacher_name);
            printf("Enter new Teacher's department: ");
            gets(T.dept);
            printf("Enter new Teacher's course:");
            gets(T.Teacher_course);
            fseek(fp, -si3, 1);
            fwrite(&T, sizeof(T), 1, fp);
            fclose(fp);
            break;
        }
    }
    if (f1 == 0)
        printf("Record Not Found...\n");
    else
        printf("Modified Successfully...\n");
}

void Delete()
{
    int ch;
    while (1)
    {
        printf("<== Delete ==>\n");
        printf("1.Delete Room\n");
        printf("2.Delete Course\n");
        printf("3.Delete Teacher\n");
		printf("0.Back To Main Menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Delete_room();
            break;

        case 2:
            Delete_course();
            break;

        case 3:
            Delete_Teacher();
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}

void Delete_room()
{
    char roomno[10];
    int f = 0;
    printf("Enter room no to Delete:");
    fflush(stdin);
    gets(roomno);

    FILE *ft;
    fp = fopen("Room.txt", "rb");
    ft = fopen("temp.txt", "ab");

    while (fread(&R, sizeof(R), 1, fp) == 1)//reading data from room.txt
    {
        if (strcmp(roomno, R.room_no) == 0)
        {
            f = 1;
        }
        else
        {
            fwrite(&R, sizeof(R), 1, ft);//writting the data in temp using ft 
        }
    }
    fclose(fp);
    fclose(ft);
    remove("Room.txt");//deleting room.txt
    rename("temp.txt", "Room.txt");//rename the temp file to room

    if (f == 0)
        printf("Record Not Found... \n");
    else
        printf("Record Deleted Successfully... \n");
}

void Delete_course()
{
    char courseid1[5];
    int f1 = 0;
    printf("Enter course id to Delete: ");
    fflush(stdin);

    gets(courseid1);

    FILE *fd;
    fp = fopen("Course.txt", "rb");
    fd = fopen("temp1.txt", "ab");

    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        if (strcmp(courseid1, C.course_id) == 0)
        {
            f1 = 1;
        }
        else
        {
            fwrite(&C, sizeof(C), 1, fd);
        }
    }
    fclose(fp);
    fclose(fd);
    remove("Course.txt");
    rename("temp1.txt", "Course.txt");

    if (f1 == 0)
        printf("Record Not Found... \n");
    else
        printf("Record Deleted Successfully... \n");
}

void Delete_Teacher()
{
    char Teacherid[5];
    int f1 = 0;
    printf("Enter Teacher id to Delete: ");
    fflush(stdin);
    gets(Teacherid);
    FILE *fd;
    fp = fopen("Teacher.txt", "rb");
    fd = fopen("temp2.txt", "ab");

    while (fread(&T, sizeof(T), 1, fp) == 1)
    {
        if (strcmp(Teacherid, T.Teacher_id) == 0)
        {
            f1 = 1;
        }
        else
        {
            fwrite(&T, sizeof(T), 1, fd);
        }
    }
    fclose(fp);
    fclose(fd);
    remove("Teacher.txt");
    rename("temp2.txt", "Teacher.txt");

    if (f1 == 0)
        printf("Record Not Found... \n");
    else
        printf("Record Deleted Successfully... \n");
}

void Search()
{
    int ch;
    while (1)
    {
        printf("<== Search ==>\n");
        printf("1.Search Room\n");
        printf("2.Search Course\n");
        printf("3.Search Teacher\n");
        printf("0.Back To Main Menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Search_Room();
            break;

        case 2:
            Search_Course();
            break;

        case 3:
            Search_Teacher();
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}

void Search_Room()
{
    int found = 0;
    char rno[5];
    printf("Enter Room id to search: ");
    fflush(stdin);
	gets(rno);
    printf("%-10s %-10s %-10s %s\n", "No", "Capacity", "dept", "block");
    fp = fopen("Room.txt", "rb");
    while (fread(&R, sizeof(R), 1, fp) == 1)
    {
        if (strcmp(rno, R.room_no) == 0)
        {
            found = 1;
            printf("%-10s %-10s %-10s %s\n", R.room_no, R.room_capacity, R.dept, R.block);
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Record Not Found... \n");
    else
        printf("Record Found Successfully... \n");
}

void Search_Course()
{
    int found = 0;
    char courseid[5],courseTime[5];
    printf("Enter Course id to search: ");
    fflush(stdin);
	gets(courseid);
    
    printf("Enter Course time to search: ");
	gets(courseTime);

	fp = fopen("Course.txt", "rb");
	printf("%-30s %-20s %-10s %-10s %-10s %-10s %s\n", "course_id", "course_name", "capacity", "dept", "timing", "credits", "Day");
    while (fread(&C, sizeof(C), 1, fp) == 1)
    {
        if (strcmp(courseid,C.course_id) == 0 && strcmp(courseTime,C.course_timing) == 0)
        {
            found = 1;
            printf("%-30s %-20s %-10s %-10s %-10s %-10s %s\n", C.course_id, C.course_name, C.course_capacity, C.dept, C.course_timing, C.course_credits, C.course_day);
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Record Not Found... \n");
    else
        printf("Record Found Successfully... \n");
}

void Search_Teacher()
{
    int found = 0;
    char Tid[5];
    printf("Enter Teacher id to search: ");
    fflush(stdin);
	gets(Tid);
    printf("%-10s %-10s %-10s %s\n", "Id", "Name", "Dept", "Cousre");
    fp = fopen("Teacher.txt", "rb");
    while (fread(&T, sizeof(T), 1, fp) == 1)
    {
        if (strcmp(Tid, T.Teacher_id) == 0)
        {
            found = 1;
            printf("%-10s %-10s %-10s %s\n", T.Teacher_id, T.Teacher_name, T.dept, T.Teacher_course);
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Record Not Found...\n");
    else
        printf("Record Found Successfully...\n");
}

void Schedule_Department_Wise()//to display schedule according to there department
{
    int ch;
    while (1)
    {
        printf("<== Delete ==>\n");
        printf("1.HEALTH SCIENCE\n");
        printf("2.CS\n");
        printf("3.LAW\n");
        printf("4.DESIGN\n");
        printf("5.BUSINESS\n");
        printf("0.Back To Main menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Schedule_Dept("HEALTH_SCIENCE");
            break;

        case 2:
            Schedule_Dept("CS");
            break;

        case 3:
            Schedule_Dept("LAW");
            break;

        case 4:
            Schedule_Dept("DESIGN");
            break;

        case 5:
            Schedule_Dept("BUSINESS");
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}
void Schedule_Dept(char cdept[])
{
    printf("%s Schedule \n", cdept);
    int found = 0;
    FILE *fpn;
    fpn = fopen("Schedule.txt", "rb+");
    printf("%-8s %-10s %-10s %-10s %-7s %-6s %-7s %-10s %-10s %-10s %-10s  %s\n", "room_no", "course_id", "course_name", "r_capacity", "c_capacity", "dept", "timing", "credits", "Day", "Teacher", "T_id", "Block");
    while (fread(&S, sizeof(S), 1, fpn) == 1)
    {
        if (strcmp(cdept, S.dept) == 0)
        {
            found = 1;
            printf("%-8s %-10s %-12s %-10s %-10s %-6s %-9s %-6s %-12s %-10s %-10s  %s\n", S.room_no, S.course_id, S.course_name, S.room_capacity, S.course_capacity, S.dept, S.course_timing, S.course_credits, S.course_day, S.Teacher_name, S.Teacher_id, S.block);
        }
    }
    fclose(fpn);
    if (!found)
        printf("Record Not Found...\n");
}

void Schedule_Day_Wise()
{
    int ch;
    while (1)
    {
        printf("<== Delete ==>\n");
        printf("1.Monday\n");
        printf("2.Tuseday\n");
        printf("3.Wednesday\n");
        printf("4.Thrusday\n");
        printf("5.Friday\n");
        printf("6.Saturday\n");
        printf("7.Sunday\n");
        printf("0.Back To Main menu\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            Main_Menu_Admin();
            break;

        case 1:
            Schedule_Day("MONDAY");
            break;

        case 2:
            Schedule_Day("TUESDAY");
            break;

        case 3:
            Schedule_Day("WEDNESDAY");
            break;

        case 4:
            Schedule_Day("THRUSDAY");
            break;

        case 5:
            Schedule_Day("FRIDAY");
            break;

        case 6:
            Schedule_Day("SATURDAY");
            break;

        case 7:
            Schedule_Day("SUNDAY");
            break;

        default:
            printf("Invalid Choice \n");
        }
    }
}

void Schedule_Day(char cday[])
{
    printf("%s Schedule \n", cday);
    int found = 0;
    FILE *fpn;
    fpn = fopen("Schedule.txt", "rb+");
    printf("%-8s %-10s %-10s %-10s %-7s %-6s %-7s %-10s %-10s %-10s %-10s  %s\n", "room_no", "course_id", "course_name", "r_capacity", "c_capacity", "dept", "timing", "credits", "Day", "Teacher", "T_id", "Block");
    while (fread(&S, sizeof(S), 1, fpn) == 1)
    {
        if (strcmp(cday, S.course_day) == 0)
        {
            found = 1;
            printf("%-8s %-10s %-12s %-10s %-10s %-6s %-9s %-6s %-12s %-10s %-10s  %s\n", S.room_no, S.course_id, S.course_name, S.room_capacity, S.course_capacity, S.dept, S.course_timing, S.course_credits, S.course_day, S.Teacher_name, S.Teacher_id, S.block);
        }
    }
    fclose(fpn);
    if (!found)
        printf("Record Not Found...\n");
}

void Final_Schedule()
{
    struct Schedule Stemp;
    FILE *fpr, *fpc, *fpt, *fps;
    int found = 0;
    fflush(stdin);

    fpr = fopen("Room.txt", "rb+");
    fpc = fopen("Course.txt", "rb+");
    fpt = fopen("Teacher.txt", "rb+");

    while (fread(&R, sizeof(R), 1, fpr) == 1)
    {
        while (fread(&C, sizeof(C), 1, fpc) == 1)
        {
            while (fread(&T, sizeof(T), 1, fpt) == 1)
            {

                if (strcmp(R.room_capacity, C.course_capacity) == 0 && strcmp(R.dept, C.dept) == 0 && strcmp(R.dept, T.dept) == 0 && strcmp(C.course_name, T.Teacher_course) == 0 && !Skip_Record())
                {
                    found = 1;
                    strncpy(Stemp.course_id, C.course_id, sizeof(C.course_id));
                    strncpy(Stemp.room_no, R.room_no, sizeof(R.room_no));
                    strncpy(Stemp.dept, C.dept, sizeof(C.dept));
                    strncpy(Stemp.room_capacity, R.room_capacity, sizeof(R.room_capacity));
                    strncpy(Stemp.course_name, C.course_name, sizeof(C.course_name));
                    strncpy(Stemp.course_capacity, C.course_capacity, sizeof(C.course_capacity));
                    strncpy(Stemp.course_timing, C.course_timing, sizeof(C.course_timing));
                    strncpy(Stemp.course_credits, C.course_credits, sizeof(C.course_credits));
                    strncpy(Stemp.block, R.block, sizeof(R.block));
                    strncpy(Stemp.course_day, C.course_day, sizeof(C.course_day));
                    strncpy(Stemp.Teacher_id, T.Teacher_id, sizeof(T.Teacher_id));
                    strncpy(Stemp.Teacher_name, T.Teacher_name, sizeof(T.Teacher_name));
                    fps = fopen("Schedule.txt", "ab");
                    fwrite(&Stemp, sizeof(Stemp), 1, fps);
                    fclose(fps);
                }
            }
            rewind(fpt);
        }
        rewind(fpc);
    }
    fclose(fpc);
    fclose(fpr);
    fclose(fpt);
    if (!found)
        printf("Schedule Not Modified...\n");
    else
        printf("Schedule Written Successfully...\n");
}

int Skip_Record()
{
    struct Schedule Stemp;
    int skip = 0;
    FILE *fpn;
    fpn = fopen("Schedule.txt", "rb");
    while (fread(&Stemp, sizeof(Stemp), 1, fpn) == 1)
    {
        if (strcmp(R.room_no, Stemp.room_no) == 0 && strcmp(C.course_day, Stemp.course_day) == 0 && strcmp(C.course_timing, Stemp.course_timing) == 0)
        {
            skip = 1;
            break;
        }
    }
    fclose(fpn);
    return skip;
}

