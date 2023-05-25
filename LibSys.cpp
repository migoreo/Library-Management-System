#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

const char ADMINUSER[] = "admin";                       // Example admin username
const char ADMINPASSWORD[] = "password";                // Example admin password
const char USER[] = "student";                          // Example student username
const char USERPASSWORD[] = "pass";                   // Example student password

struct Book {
    int bookId;
    string bookName;
    string bookAuthor;
    int year, month, day;
    double lateFee;
};

void addBook();
void deleteBook();
void updateBook();
void listOfAllBooks();
void borrowBook();
void returnBook();

int main()
{
    int outerChoice = 0;

    while (outerChoice != 9)
    {
        system("cls");

        cout << "\n\n Library Management System \n\n";
        cout << "\n1. Librarian";
        cout << "\n2. Student";
        cout << "\n9. Exit";
        cout << "\n\nEnter your choice : ";
        cin >> outerChoice;

        if (outerChoice == 1)
        {
            char adminUser[10];
            char adminPassword[10];

            system("cls");
            cout << "\n========================================== TEACHER LOGIN ========================================== ";
            cout << "\n\n Please enter your username: ";
            cin >> adminUser;
            cout << "\n Please enter your password: ";
            cin >> adminPassword;

            if ((strcmp(adminUser, ADMINUSER) == 0) && (strcmp(adminPassword, ADMINPASSWORD) == 0))
            {
                getchar();
                getchar();

                system("cls");

                int innerChoice = 0;

                while (innerChoice != 9)
                {
                    cout << "\n\n Librarian login is successful!! Press any button to continue..";
                    cout << "\n1. Add new book";
                    cout << "\n2. Update any Book";
                    cout << "\n3. Delete Book";
                    cout << "\n4. List of all Books";
                    cout << "\n9. Exit";
                    cout << "\n\n Please enter your choice : ";
                    cin >> innerChoice;

                    switch (innerChoice)
                    {
                        case 1:
                            addBook();
                            break;
                        case 2:
                            updateBook();
                            break;
                        case 3:
                            deleteBook();
                            break;
                        case 4:
                            listOfAllBooks();
                            break;
                        default:
                            cout << "\n\n Invalid Choice. Please enter the valid one";
                            getchar();
                            break;
                    }

                    system("cls");
                }
            }
            else
            {
                cout << "\n\n Error: Invalid Credentials. Please check your Credentials";
                getchar();
                getchar();
            }
        }
        else if (outerChoice == 2)
        {
            char studentUser[10];
            char studentPassword[10];

            system("cls");

            cout << "\n========================================== Student Login ==========================================";
            cout << "\n\n Please enter your username: ";
            cin >> studentUser;
            cout << "\n Please enter your password: ";
            cin >> studentPassword;

            if ((strcmp(studentUser, USER) == 0) && (strcmp(studentPassword, USERPASSWORD) == 0))
            {
                int innerChoice = 0;

                while (innerChoice != 9)
                {
                    system("cls");

                    cout << "\n1. Borrow a Book";
                    cout << "\n2. Return a Book";
                    cout << "\n3. List of All Books";
                    cout << "\n9. Exit";
                    cout << "\n\n Please enter your choice : ";
                    cin >> innerChoice;

                    switch (innerChoice)
                    {
                        case 1:
                            borrowBook();
                            break;
                        case 2:
                            returnBook();
                            break;
                        case 3:
                            listOfAllBooks();
                            break;
                        default:
                            cout << "\n\n Invalid Choice. Please enter the valid one";
                            getchar();
                            break;
                    }
                }
            }
            else
            {
                cout << "\n\n Error: Invalid Credentials. Please check your Credentials";
                getchar();
                getchar();
            }
        }
    }

    return 0;
}

void addBook()
{
    int bookid;
    string bookname;
    string bookauthor;
    int year, month, day;
    double lateFee;

    system("cls");

    cout << "\n Add Book";
    cout << "\n\n Please enter the Book ID : ";
    cin >> bookid;
    cout << "\n Please enter the Book Name : ";
    cin.ignore();
    getline(cin, bookname);
    cout << "\n Please enter the Book Author : ";
    getline(cin, bookauthor);
    cout << "\n Please enter the year of publication : ";
    cin >> year;
    cout << "\n Please enter the month of publication : ";
    cin >> month;
    cout << "\n Please enter the day of publication : ";
    cin >> day;
    cout << "\n Please enter the late fee/penalty amount : ";
    cin >> lateFee;

    ofstream file("bookdatabase.txt", ios::app);
    file << bookid << "\n";
    file << bookname << "\n";
    file << bookauthor << "\n";
    file << year << "\n";
    file << month << "\n";
    file << day << "\n";
    file << lateFee << "\n";
    file.close();

    cout << "\n\n Book Added Successfully!";
    getchar();
    getchar();
}

void deleteBook()
{
    system("cls");

    cout << "\n Delete Book";
    cout << "\n\n Please enter the Book ID : ";
    int bookid;
    cin >> bookid;

    ifstream file("bookdatabase.txt");
    ofstream tempfile("temp.txt");

    int tempbookid;
    string tempbookname;
    string tempbookauthor;
    int tempyear, tempmonth, tempday;
    double tempLateFee;

    bool found = false;

    while (file >> tempbookid && getline(file, tempbookname) && getline(file, tempbookauthor) &&
        file >> tempyear >> tempmonth >> tempday && file >> tempLateFee)
    {
        if (tempbookid != bookid)
        {
            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
        else
        {
            found = true;
        }
    }

    file.close();
    tempfile.close();

    remove("bookdatabase.txt");
    rename("temp.txt", "bookdatabase.txt");

    if (found)
    {
        cout << "\n\n Book Deleted Successfully!";
    }
    else
    {
        cout << "\n\n Book Not Found!";
    }

    getchar();
    getchar();
}

void updateBook()
{
    system("cls");

    cout << "\n Update Book";
    cout << "\n\n Please enter the Book ID : ";
    int bookid;
    cin >> bookid;

    ifstream file("bookdatabase.txt");
    ofstream tempfile("temp.txt");

    int tempbookid;
    string tempbookname;
    string tempbookauthor;
    int tempyear, tempmonth, tempday;
    double tempLateFee;

    bool found = false;

    while (file >> tempbookid && getline(file, tempbookname) && getline(file, tempbookauthor) &&
        file >> tempyear >> tempmonth >> tempday && file >> tempLateFee)
    {
        if (tempbookid != bookid)
        {
            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
        else
        {
            found = true;

            cout << "\n\n Book Found!";
            cout << "\n\n Enter New Details : \n";
            cout << "\n Please enter the new Book Name : ";
            cin.ignore();
            getline(cin, tempbookname);
            cout << "\n Please enter the new Book Author : ";
            getline(cin, tempbookauthor);
            cout << "\n Please enter the new year of publication : ";
            cin >> tempyear;
            cout << "\n Please enter the new month of publication : ";
            cin >> tempmonth;
            cout << "\n Please enter the new day of publication : ";
            cin >> tempday;
            cout << "\n Please enter the new late fee/penalty amount : ";
            cin >> tempLateFee;

            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
    }

    file.close();
    tempfile.close();

    remove("bookdatabase.txt");
    rename("temp.txt", "bookdatabase.txt");

    if (found)
    {
        cout << "\n\n Book Updated Successfully!";
    }
    else
    {
        cout << "\n\n Book Not Found!";
    }

    getchar();
    getchar();
}


void listOfAllBooks()
{
    cout << "\n========================================== List of All Books ==========================================";

    ifstream file("bookdatabase.txt");
    if (file.is_open())
    {
        int bookId;
        string bookName, bookAuthor;
        int year, month, day;
        double lateFee;

        while (file >> bookId >> ws && getline(file, bookName) && getline(file, bookAuthor) && file >> year >> month >> day >> lateFee)
        {
            cout << "\n ID: " << bookId;
            cout << "\n Name: " << bookName;
            cout << "\n Author: " << bookAuthor;
            cout << "\n Date Added: " << year << "-" << month << "-" << day;
            cout << "\n Late Fee: " << lateFee << "\n";
        }

        file.close();
    }
    else
    {
        cout << "\n\n Unable to open the database file.";
    }

    cout << "\n\n End of Book List";
    getchar();
    getchar();
}


void borrowBook()
{
    system("cls");

    cout << "\n Borrow Book";
    cout << "\n\n Please enter the Book ID : ";
    int bookid;
    cin >> bookid;

    ifstream file("bookdatabase.txt");
    ofstream tempfile("temp.txt");

    int tempbookid;
    string tempbookname;
    string tempbookauthor;
    int tempyear, tempmonth, tempday;
    double tempLateFee;

    bool found = false;

    while (file >> tempbookid && getline(file, tempbookname) && getline(file, tempbookauthor) &&
        file >> tempyear >> tempmonth >> tempday && file >> tempLateFee)
    {
        if (tempbookid == bookid)
        {
            found = true;

            cout << "\n\n Book Found!";
            cout << "\n\n Enter Borrower's Details : \n";
            cout << "\n Please enter the Borrower's Name : ";
            cin.ignore();
            getline(cin, tempbookname);
            cout << "\n Please enter the Borrower's ID : ";
            cin >> tempbookid;
            cout << "\n Please enter the year of borrowing : ";
            cin >> tempyear;
            cout << "\n Please enter the month of borrowing : ";
            cin >> tempmonth;
            cout << "\n Please enter the day of borrowing : ";
            cin >> tempday;

            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
        else
        {
            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
    }

    file.close();
    tempfile.close();

    remove("bookdatabase.txt");
    rename("temp.txt", "bookdatabase.txt");

    if (found)
    {
        cout << "\n\n Book Borrowed Successfully!";
    }
    else
    {
        cout << "\n\n Book Not Found!";
    }

    getchar();
    getchar();
}

void returnBook()
{
    system("cls");

    cout << "\n Return Book";
    cout << "\n\n Please enter the Book ID : ";
    int bookid;
    cin >> bookid;

    ifstream file("bookdatabase.txt");
    ofstream tempfile("temp.txt");

    int tempbookid;
    string tempbookname;
    string tempbookauthor;
    int tempyear, tempmonth, tempday;
    double tempLateFee;

    bool found = false;

    while (file >> tempbookid && getline(file, tempbookname) && getline(file, tempbookauthor) &&
        file >> tempyear >> tempmonth >> tempday && file >> tempLateFee)
    {
        if (tempbookid == bookid)
        {
            found = true;

            cout << "\n\n Book Found!";
            cout << "\n\n Enter Return Date : \n";
            cout << "\n Please enter the year of return : ";
            cin >> tempyear;
            cout << "\n Please enter the month of return : ";
            cin >> tempmonth;
            cout << "\n Please enter the day of return : ";
            cin >> tempday;

            // Calculate late fee/penalty
            time_t now = time(0);
            tm* ltm = localtime(&now);

            int returnYear = tempyear;
            int returnMonth = tempmonth;
            int returnDay = tempday;

            int currentYear = 1900 + ltm->tm_year;
            int currentMonth = 1 + ltm->tm_mon;
            int currentDay = ltm->tm_mday;

            double daysLate = (currentYear - returnYear) * 365 + (currentMonth - returnMonth) * 30 + (currentDay - returnDay);

            if (daysLate > 0)
            {
                tempLateFee += daysLate * 0.5; // Late fee of $0.5 per day
            }

            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
        else
        {
            tempfile << tempbookid << "\n";
            tempfile << tempbookname << "\n";
            tempfile << tempbookauthor << "\n";
            tempfile << tempyear << "\n";
            tempfile << tempmonth << "\n";
            tempfile << tempday << "\n";
            tempfile << tempLateFee << "\n";
        }
    }

    file.close();
    tempfile.close();

    remove("bookdatabase.txt");
    rename("temp.txt", "bookdatabase.txt");

    if (found)
    {
        cout << "\n\n Book Returned Successfully!";
    }
    else
    {
        cout << "\n\n Book Not Found!";
    }

    getchar();
    getchar();
}