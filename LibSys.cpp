#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

using namespace std;

const char ADMINUSER[] = "admin";                       // Example admin username
const char ADMINPASSWORD[] = "password";                // Example admin password
const char USER[] = "student";                          // Example student username
const char USERPASSWORD[] = "123456";                   // Example student password

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
            cout << "\n Please enter your password:";
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
            cout << "\n Please enter your password:";
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
                    cout << "\n\n Enter your choice : ";
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
                        case 9:
                            break;
                        default:
                            cout << "\n\n Error: Invalid Choice. Please enter the valid one";
                            getchar();
                            getchar();
                            break;
                    }
                }

                system("cls");
            }
            else
            {
                cout << "\n\n Error: Invalid Credentials. Please check your Credentials";
                getchar();
                getchar();
            }
        }
        else if (outerChoice != 9)
        {
            cout << "\n\n Invalid choice. Press any key to continue..";
            getchar();
            getchar();
        }
        else
        {
            cout << "\n\n Thank you for browsing!! Press any key to exit";
            getchar();
            getchar();
        }
    }

    return 0;
}

void addBook()
{
    int bookid;
    char bookname[20];
    char bookauthor[20];
    int year, month, day;

    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    year = tm->tm_year + 1900;
    month = tm->tm_mon + 1;
    day = tm->tm_mday;

    system("cls");
    cout << "\n========================================== Add a new Book ==========================================";
    cout << "\n\n Please enter a 4-digit numeric id: ";
    cin >> bookid;
    cout << "\n Please enter the book name: ";
    cin.ignore(); // Ignore the newline character left in the input stream
    cin.getline(bookname, 20);
    cout << "\n Please enter the book author: ";
    cin.getline(bookauthor, 20);

    char filename[20];
    sprintf(filename, "%d%s", bookid, ".dat");
    ofstream file(filename);
    file << bookname << "\n";
    file << bookauthor << "\n";
    file << year << "\n";
    file << month << "\n";
    file << day << "\n";
    file.close();

    cout << "\n Your file has been saved successfully!";
    getchar();
    getchar();
}



void deleteBook()
{
    int bookId;
    cout << "\n========================================== Delete a Book ==========================================";
    cout << "\n\n Please enter the book ID to delete: ";
    cin >> bookId;

    char filename[20];
    sprintf(filename, "%d%s", bookId, ".dat");

    if (remove(filename) == 0)
        cout << "\n Book with ID " << bookId << " has been deleted successfully!";
    else
        cout << "\n Error: Failed to delete the book.";

    getchar();
    getchar();
}

void updateBook()
{
    int bookId;
    cout << "\n========================================== Update a Book ==========================================";
    cout << "\n\n Please enter the book ID to update: ";
    cin >> bookId;

    char filename[20];
    sprintf(filename, "%d%s", bookId, ".dat");

    ifstream file(filename);
    if (!file)
    {
        cout << "\n Error: Book with ID " << bookId << " does not exist.";
        getchar();
        getchar();
        return;
    }

    // Read the existing book information
    string bookName, bookAuthor;
    int year, month, day;
    getline(file, bookName);
    getline(file, bookAuthor);
    file >> year >> month >> day;
    file.close();

    // Display the existing information and prompt for updates
    cout << "\n Existing Book Information:";
    cout << "\n ID: " << bookId;
    cout << "\n Name: " << bookName;
    cout << "\n Author: " << bookAuthor;
    cout << "\n Date Added: " << year << "-" << month << "-" << day << endl;

    // Prompt for updated information
    string newBookName, newBookAuthor;
    cout << "\n Enter the updated book name: ";
    cin.ignore();
    getline(cin, newBookName);
    cout << "\n Enter the updated book author: ";
    getline(cin, newBookAuthor);

    // Update the book information in the file
    ofstream outFile(filename);
    outFile << newBookName << "\n";
    outFile << newBookAuthor << "\n";
    outFile << year << "\n";
    outFile << month << "\n";
    outFile << day << "\n";
    outFile.close();

    cout << "\n Book with ID " << bookId << " has been updated successfully!";
    getchar();
    getchar();
}

void listOfAllBooks()
{
    cout << "\n========================================== List of All Books ==========================================";
    ifstream file;
    for (int bookId = 0; bookId <= 9999; ++bookId)
    {
        char filename[20];
        sprintf(filename, "%d%s", bookId, ".dat");

        file.open(filename);
        if (file)
        {
            string bookName, bookAuthor;
            int year, month, day;

            getline(file, bookName);
            getline(file, bookAuthor);
            file >> year >> month >> day;
            file.close();

            cout << "\n ID: " << bookId;
            cout << "\n Name: " << bookName;
            cout << "\n Author: " << bookAuthor;
            cout << "\n Date Added: " << year << "-" << month << "-" << day << endl;
        }
    }

    cout << "\n End of Book List";
    getchar();
    getchar();
}

void borrowBook()
{
    int bookId;
    cout << "\n========================================== Borrow a Book ==========================================";
    cout << "\n\n Please enter the book ID to borrow: ";
    cin >> bookId;

    char filename[20];
    sprintf(filename, "%d%s", bookId, ".dat");

    ifstream file(filename);
    if (!file)
    {
        cout << "\n Error: Book with ID " << bookId << " does not exist.";
        getchar();
        getchar();
        return;
    }
    file.close();

    // Implement the borrowing logic here
    // For example, update the book status, record borrower details, etc.

    cout << "\n Book with ID " << bookId << " has been borrowed successfully!";
    getchar();
    getchar();
}

void returnBook()
{
    int bookId;
    cout << "\n========================================== Return a Book ==========================================";
    cout << "\n\n Please enter the book ID to return: ";
    cin >> bookId;

    char filename[20];
    sprintf(filename, "%d%s", bookId, ".dat");

    ifstream file(filename);
    if (!file)
    {
        cout << "\n Error: Book with ID " << bookId << " does not exist.";
        getchar();
        getchar();
        return;
    }
    file.close();

    // Implement the returning logic here
    // For example, update the book status, remove borrower details, etc.

    cout << "\n Book with ID " << bookId << " has been returned successfully!";
    getchar();
    getchar();
}
