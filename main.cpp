#include <iostream>
#include "./Book/book.h"
#include "./Member/member.h"
#include "main.h"
#include <unordered_map>
#include <csignal>
#include <unistd.h>
#include <vector>
std::unordered_map<int, int> bookMemberMapping;

std::string getMenuString(Menu item)
{

    switch (item)
    {
    case Menu::add_book:
        return "Add a new book";
    case Menu::add_member:
        return "Add a new member";
    case Menu::borrow:
        return "Borrow a book";
    case Menu::return_book:
        return "Return book";
    case Menu::search_book:
        return "Search a book";
    case Menu::list_borrowed_books:
        return "List borrowed books";
    case Menu::exit:
        return "Exit";
    default:
        return "";
    }
    return "";
}

void printActions()
{
    std::cout << '\n';
    std::cout << "Please select a valid menu number" << '\n';
    std::cout << '\n';
    std::cout << static_cast<int>(Menu::add_book) << ": " << getMenuString(Menu::add_book) << '\n';
    std::cout << static_cast<int>(Menu::add_member) << ": " << getMenuString(Menu::add_member) << '\n';
    std::cout << static_cast<int>(Menu::borrow) << ": " << getMenuString(Menu::borrow) << '\n';
    std::cout << static_cast<int>(Menu::return_book) << ": " << getMenuString(Menu::return_book) << '\n';
    std::cout << static_cast<int>(Menu::search_book) << ": " << getMenuString(Menu::search_book) << '\n';
    std::cout << static_cast<int>(Menu::list_borrowed_books) << ": " << getMenuString(Menu::list_borrowed_books) << '\n';
    std::cout << static_cast<int>(Menu::exit) << ": " << getMenuString(Menu::exit) << '\n';
    std::cout << '\n';
}

void borrowBook()
{
    int totalBooks = getTotalBooksCount();
    if (totalBooks == 0)
    {
        std::cout << "No books available. Please add a book." << '\n';
    }
    else
    {
        std::cout << "Please choose a book id: " << '\n';
        listBooks();
        int bookId;
        std::cin >> bookId;
        Book &book = getBook(bookId);

        if (book.isBorrowed)
        {
            std::cout << "This book is already borrowed. Please choose another book." << '\n';
        }
        else
        {
            std::cout << "Please choose a member id:" << '\n';
            listMembers();
            int memberId;
            std::cin >> memberId;
            Member member = getMember(memberId);

            book.isBorrowed = true;
            bookMemberMapping.insert({bookId, memberId});
            std::cout << "Book successfully borrowed to member: " << member.name << '\n';
        }
    }
}

void terminateProgram()
{
    kill(getpid(), SIGTERM);
}

void initiateBookReturn()
{
    int bookId, memberId;
    std::cout << "Please enter the book id: " << '\n';
    std::cin >> bookId;
    std::cout << "Please enter the member id: " << '\n';
    std::cin >> memberId;

    Book book = getBook(bookId);
    if (!book.isBorrowed)
    {
        std::cout << "This book is not borrowed" << '\n';
    }
    else
    {
        bool hasMemberBorrowedBook{false};
        for (const auto &mapping : bookMemberMapping)
        {
            if (mapping.first == bookId && mapping.second == memberId)
            {
                hasMemberBorrowedBook = true;
                break;
            }
        }

        if (hasMemberBorrowedBook)
        {
            book.isBorrowed = false;
            bookMemberMapping.erase(bookId);
        }

        std::cout << "Book successfully returned." << '\n';
    }
}

void searchBook()
{
    std::cout << "Please enter the book id " << '\n';
    int bookId;
    std::cin >> bookId;
    Book book = getBook(bookId);

    std::cout << '\n';
    std::cout << book;
    std::cout << '\n';
}

void listBorrowedBooks()
{
    std::vector<Book> borrowedBooks = getBorrowedBooks();

    for (const auto &book : borrowedBooks)
    {
        std::cout << book << '\n';
    }
}

void performActions(Menu item)
{
    switch (item)
    {
    case Menu::add_book:
        initiateAddBook();
        break;
    case Menu::add_member:
        initiateAddMember();
        break;
    case Menu::borrow:
        borrowBook();
        break;
    case Menu::return_book:
        initiateBookReturn();
        break;
    case Menu::search_book:
        searchBook();
        break;
    case Menu::list_borrowed_books:
        listBorrowedBooks();
        break;
    case Menu::exit:
        terminateProgram();
        break;
    default:
        break;
    }
}

int main()
{

    while (true)
    {
        printActions();
        int action{};
        std::cin >> action;
        performActions(static_cast<Menu>(action));
    }

    return 0;
}