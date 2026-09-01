#include <iostream>
#include <string>
using namespace std;

#define MAX 100
#define MAX_QUEUE 100
#define MAX_STACK 100


// ============================================================
// STUDENT STRUCTURE
// ============================================================

struct Student
{
    long long id;
    string password;

    string name;
    string branch;
    int year;
    string section;

    string skills[5];
    int skillCount;

    string projectInterest;
};


// ============================================================
// ARRAY FOR STUDENT RECORDS
// ============================================================

Student students[MAX];
int studentCount = 0;


// ============================================================
// LINKED LIST FOR COMMUNITY MEMBERS
// ============================================================

struct MemberNode
{
    long long studentID;
    MemberNode* next;
};

MemberNode* communityHead = NULL;


// ============================================================
// QUEUE FOR CONNECTION REQUESTS
// ============================================================

struct ConnectionRequest
{
    long long senderID;
    long long receiverID;
};

ConnectionRequest requestQueue[MAX_QUEUE];

int front = -1;
int rear = -1;


// ============================================================
// STACK FOR RECENT ACTIVITY
// ============================================================

struct Activity
{
    string action;
    long long studentID;
};

Activity activityStack[MAX_STACK];

int top = -1;


// ============================================================
// CLEAR INPUT
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}


// ============================================================
// FIND STUDENT BY ID
// LINEAR SEARCH
// ============================================================

int findStudent(long long id)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


// ============================================================
// ADD STUDENT
// ARRAY
// ============================================================

void addStudent()
{
    if (studentCount >= MAX)
    {
        cout << "\nStudent storage is full!\n";
        return;
    }

    Student s;

    cout << "\n===== ADD STUDENT =====\n";

    cout << "Enter Student ID: ";
    cin >> s.id;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid Student ID!\n";
        return;
    }

    // Check duplicate ID
    if (findStudent(s.id) != -1)
    {
        cout << "Student ID already exists!\n";
        return;
    }

    cin.ignore(10000, '\n');

    cout << "Create Password: ";
    getline(cin, s.password);

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Branch: ";
    getline(cin, s.branch);

    cout << "Enter Year: ";
    cin >> s.year;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid Year!\n";
        return;
    }

    cout << "Enter Section: ";
    cin >> s.section;

    cout << "Enter number of skills (maximum 5): ";
    cin >> s.skillCount;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid number of skills!\n";
        return;
    }

    if (s.skillCount < 0)
    {
        s.skillCount = 0;
    }

    if (s.skillCount > 5)
    {
        s.skillCount = 5;
    }

    for (int i = 0; i < s.skillCount; i++)
    {
        cout << "Enter Skill " << i + 1 << ": ";
        cin >> s.skills[i];
    }

    cin.ignore(10000, '\n');

    cout << "Enter Project Interest: ";
    getline(cin, s.projectInterest);

    students[studentCount] = s;

    studentCount++;

    cout << "\nStudent added successfully!\n";
}


// ============================================================
// DISPLAY STUDENT
// ============================================================

void displayStudent(const Student& s)
{
    cout << "\n--------------------------------\n";

    cout << "Student ID: " << s.id << endl;
    cout << "Name: " << s.name << endl;
    cout << "Branch: " << s.branch << endl;
    cout << "Year: " << s.year << endl;
    cout << "Section: " << s.section << endl;

    cout << "Skills: ";

    for (int i = 0; i < s.skillCount; i++)
    {
        cout << s.skills[i];

        if (i < s.skillCount - 1)
        {
            cout << ", ";
        }
    }

    cout << endl;

    cout << "Project Interest: "
         << s.projectInterest << endl;

    cout << "--------------------------------\n";
}


// ============================================================
// LOGIN
// LINEAR SEARCH
// ============================================================

void loginStudent()
{
    long long id;
    string password;

    cout << "\n===== STUDENT LOGIN =====\n";

    cout << "Enter Student ID: ";
    cin >> id;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid Student ID!\n";
        return;
    }

    cin.ignore(10000, '\n');

    cout << "Enter Password: ";
    getline(cin, password);

    int index = findStudent(id);

    if (index == -1)
    {
        cout << "\nStudent ID not found!\n";
        return;
    }

    if (students[index].password == password)
    {
        cout << "\nLogin Successful!\n";

        displayStudent(students[index]);

        // Add activity to stack
        if (top < MAX_STACK - 1)
        {
            top++;

            activityStack[top].action = "Logged in";
            activityStack[top].studentID = id;
        }
    }
    else
    {
        cout << "\nIncorrect Password!\n";
    }
}


// ============================================================
// SEARCH BY STUDENT ID
// LINEAR SEARCH
// ============================================================

void searchByID()
{
    long long id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid Student ID!\n";
        return;
    }

    int index = findStudent(id);

    if (index != -1)
    {
        cout << "\nStudent Found!\n";

        displayStudent(students[index]);

        // Add activity
        if (top < MAX_STACK - 1)
        {
            top++;

            activityStack[top].action = "Searched student";
            activityStack[top].studentID = id;
        }
    }
    else
    {
        cout << "\nStudent not found.\n";
    }
}


// ============================================================
// SEARCH BY SKILL
// LINEAR SEARCH
// ============================================================

void searchBySkill()
{
    string skill;
    bool found = false;

    cout << "\nEnter Skill: ";
    cin >> skill;

    cout << "\nStudents with skill: " << skill << endl;

    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].skillCount; j++)
        {
            if (students[i].skills[j] == skill)
            {
                displayStudent(students[i]);

                found = true;

                break;
            }
        }
    }

    if (!found)
    {
        cout << "\nNo students found with this skill.\n";
    }
}


// ============================================================
// SEARCH BY BRANCH
// LINEAR SEARCH
// ============================================================

void searchByBranch()
{
    string branch;

    bool found = false;

    cin.ignore(10000, '\n');

    cout << "\nEnter Branch: ";
    getline(cin, branch);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].branch == branch)
        {
            displayStudent(students[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo students found in this branch.\n";
    }
}


// ============================================================
// SEARCH BY YEAR
// LINEAR SEARCH
// ============================================================

void searchByYear()
{
    int year;

    bool found = false;

    cout << "\nEnter Year: ";
    cin >> year;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Year!\n";

        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].year == year)
        {
            displayStudent(students[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo students found in this year.\n";
    }
}


// ============================================================
// SEARCH BY PROJECT INTEREST
// LINEAR SEARCH
// ============================================================

void searchByProjectInterest()
{
    string interest;

    bool found = false;

    cin.ignore(10000, '\n');

    cout << "\nEnter Project Interest: ";
    getline(cin, interest);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].projectInterest == interest)
        {
            displayStudent(students[i]);

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo students found for this project interest.\n";
    }
}


// ============================================================
// DISPLAY ALL STUDENTS
// ARRAY TRAVERSAL
// ============================================================

void displayAllStudents()
{
    if (studentCount == 0)
    {
        cout << "\nNo students available.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        displayStudent(students[i]);
    }
}


// ============================================================
// LINKED LIST
// ADD COMMUNITY MEMBER
// ============================================================

void addCommunityMember()
{
    long long id;

    cout << "\nEnter Student ID to add to community: ";
    cin >> id;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Student ID!\n";

        return;
    }

    // Check whether student exists
    if (findStudent(id) == -1)
    {
        cout << "\nStudent does not exist.\n";
        return;
    }


    // Create new node
    MemberNode* newNode = new MemberNode;

    newNode->studentID = id;

    newNode->next = NULL;


    // First member
    if (communityHead == NULL)
    {
        communityHead = newNode;
    }
    else
    {
        MemberNode* temp = communityHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    cout << "\nStudent added to community!\n";
}


// ============================================================
// DISPLAY COMMUNITY MEMBERS
// LINKED LIST TRAVERSAL
// ============================================================

void displayCommunity()
{
    if (communityHead == NULL)
    {
        cout << "\nCommunity is empty.\n";
        return;
    }

    MemberNode* temp = communityHead;

    cout << "\n===== COMMUNITY MEMBERS =====\n";

    while (temp != NULL)
    {
        int index = findStudent(temp->studentID);

        if (index != -1)
        {
            cout << students[index].name
                 << " (" << students[index].id << ")" << endl;
        }

        temp = temp->next;
    }
}


// ============================================================
// REMOVE COMMUNITY MEMBER
// LINKED LIST
// ============================================================

void removeCommunityMember()
{
    long long id;

    cout << "\nEnter Student ID to remove: ";
    cin >> id;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Student ID!\n";

        return;
    }

    MemberNode* temp = communityHead;
    MemberNode* previous = NULL;


    while (temp != NULL)
    {
        if (temp->studentID == id)
        {
            // Removing first node
            if (previous == NULL)
            {
                communityHead = temp->next;
            }
            else
            {
                previous->next = temp->next;
            }

            delete temp;

            cout << "\nStudent removed from community.\n";

            return;
        }

        previous = temp;
        temp = temp->next;
    }

    cout << "\nStudent is not a community member.\n";
}


// ============================================================
// QUEUE
// ADD CONNECTION REQUEST
// ENQUEUE
// ============================================================

void sendConnectionRequest()
{
    long long sender;
    long long receiver;

    cout << "\nEnter your Student ID: ";
    cin >> sender;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Student ID!\n";

        return;
    }

    cout << "Enter receiver Student ID: ";
    cin >> receiver;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Student ID!\n";

        return;
    }


    // Check students exist
    if (findStudent(sender) == -1 ||
        findStudent(receiver) == -1)
    {
        cout << "\nOne or both students do not exist.\n";

        return;
    }


    // Queue full
    if (rear == MAX_QUEUE - 1)
    {
        cout << "\nConnection request queue is full.\n";

        return;
    }


    // First request
    if (front == -1)
    {
        front = 0;
    }

    rear++;

    requestQueue[rear].senderID = sender;
    requestQueue[rear].receiverID = receiver;

    cout << "\nConnection request sent!\n";
}


// ============================================================
// QUEUE
// PROCESS CONNECTION REQUEST
// DEQUEUE
// ============================================================

void processConnectionRequest()
{
    if (front == -1 || front > rear)
    {
        cout << "\nNo pending connection requests.\n";

        return;
    }

    ConnectionRequest request = requestQueue[front];

    cout << "\n===== CONNECTION REQUEST =====\n";

    cout << "From Student ID: "
         << request.senderID << endl;

    cout << "To Student ID: "
         << request.receiverID << endl;


    char choice;

    cout << "\nAccept request? (y/n): ";
    cin >> choice;


    if (choice == 'y' || choice == 'Y')
    {
        cout << "\nConnection accepted!\n";
    }
    else
    {
        cout << "\nConnection rejected!\n";
    }


    // Remove request from queue
    front++;

    if (front > rear)
    {
        front = -1;
        rear = -1;
    }
}


// ============================================================
// DISPLAY QUEUE
// ============================================================

void displayRequests()
{
    if (front == -1 || front > rear)
    {
        cout << "\nNo pending requests.\n";

        return;
    }

    cout << "\n===== PENDING REQUESTS =====\n";

    for (int i = front; i <= rear; i++)
    {
        cout << "From: "
             << requestQueue[i].senderID;

        cout << " -> To: "
             << requestQueue[i].receiverID
             << endl;
    }
}


// ============================================================
// STACK
// PUSH ACTIVITY
// ============================================================

void addActivity()
{
    long long id;

    string action;

    cout << "\nEnter Student ID: ";
    cin >> id;

    if (cin.fail())
    {
        clearInput();

        cout << "Invalid Student ID!\n";

        return;
    }

    cin.ignore(10000, '\n');

    cout << "Enter Activity: ";
    getline(cin, action);


    if (top == MAX_STACK - 1)
    {
        cout << "\nActivity stack is full.\n";

        return;
    }


    top++;

    activityStack[top].studentID = id;

    activityStack[top].action = action;

    cout << "\nActivity added!\n";
}


// ============================================================
// STACK
// POP ACTIVITY
// ============================================================

void undoActivity()
{
    if (top == -1)
    {
        cout << "\nNo activity to undo.\n";

        return;
    }

    cout << "\nUndoing activity:\n";

    cout << activityStack[top].action
         << " by Student "
         << activityStack[top].studentID
         << endl;

    top--;
}


// ============================================================
// DISPLAY ACTIVITY STACK
// ============================================================

void displayActivities()
{
    if (top == -1)
    {
        cout << "\nNo recent activities.\n";

        return;
    }

    cout << "\n===== RECENT ACTIVITIES =====\n";

    for (int i = top; i >= 0; i--)
    {
        cout << activityStack[i].action
             << " | Student ID: "
             << activityStack[i].studentID
             << endl;
    }
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "====================================\n";
        cout << "          CAMPUS LINK\n";
        cout << "====================================\n";

        cout << "\n--- STUDENTS ---\n";

        cout << "1. Add Student\n";
        cout << "2. Student Login\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Search Students by Skill\n";
        cout << "5. Search Students by Branch\n";
        cout << "6. Search Students by Year\n";
        cout << "7. Search Students by Project Interest\n";
        cout << "8. Display All Students\n";


        cout << "\n--- COMMUNITY / LINKED LIST ---\n";

        cout << "9. Add Community Member\n";
        cout << "10. Remove Community Member\n";
        cout << "11. Display Community Members\n";


        cout << "\n--- CONNECTION REQUESTS / QUEUE ---\n";

        cout << "12. Send Connection Request\n";
        cout << "13. Process Connection Request\n";
        cout << "14. Display Pending Requests\n";


        cout << "\n--- ACTIVITY / STACK ---\n";

        cout << "15. Add Activity\n";
        cout << "16. Undo Last Activity\n";
        cout << "17. Display Recent Activities\n";


        cout << "\n18. Exit\n";


        cout << "\nEnter your choice: ";

        cin >> choice;


        if (cin.fail())
        {
            clearInput();

            cout << "\nInvalid input! Enter a number.\n";

            continue;
        }


        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                loginStudent();
                break;

            case 3:
                searchByID();
                break;

            case 4:
                searchBySkill();
                break;

            case 5:
                searchByBranch();
                break;

            case 6:
                searchByYear();
                break;

            case 7:
                searchByProjectInterest();
                break;

            case 8:
                displayAllStudents();
                break;

            case 9:
                addCommunityMember();
                break;

            case 10:
                removeCommunityMember();
                break;

            case 11:
                displayCommunity();
                break;

            case 12:
                sendConnectionRequest();
                break;

            case 13:
                processConnectionRequest();
                break;

            case 14:
                displayRequests();
                break;

            case 15:
                addActivity();
                break;

            case 16:
                undoActivity();
                break;

            case 17:
                displayActivities();
                break;

            case 18:
                cout << "\nExiting Campus Link...\n";
                break;

            default:
                cout << "\nInvalid choice! Enter 1-18.\n";
        }

    } while (choice != 18);


    return 0;
}