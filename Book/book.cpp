#include "book.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

std::unordered_map<int, Book> books;

int getNewBookId()
{
    static int id = 0;
    return ++id;
}

std::ostream &operator<<(std::ostream &out, Book book)
{
    return out << book.id << " " << book.title << " " << book.author << " " << book.isBorrowed;
}

int getTotalBooksCount()
{
    return books.size();
}

Book &getBook(int bookId)
{
    return books.at(bookId);
}

std::vector<Book> getBorrowedBooks()
{

    std::vector<Book> borrowedBooks;

    for (const auto &book : books)
    {
        if (book.second.isBorrowed)
        {
            borrowedBooks.push_back(book.second);
        }
    }
    return borrowedBooks;
}

void listBooks()
{
    for (const auto &book : books)
    {
        std::cout << book.second << '\n';
    }
    std::cout << '\n';
}

Book initiateAddBook()
{
    std::string title, author;

    std::cin.ignore();
    std::cout << '\n';
    std::cout << "Please enter the book title." << '\n';
    std::getline(std::cin, title);
    std::cout << "Please enter the book author." << '\n';
    std::getline(std::cin, author);
    std::cout << '\n';

    int id = getNewBookId();
    Book book{id, title, author, false};
    books.insert({id, book});
    return book;
}
