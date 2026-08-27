#pragma once
#include<string>
#include <vector>
struct Book
{
    int id;
    std::string title;
    std::string author;
    bool isBorrowed;
};

Book initiateAddBook();
void listBooks();
int getTotalBooksCount();
Book& getBook(int bookId);
std::ostream &operator<<(std::ostream &out, Book book);
std::vector<Book> getBorrowedBooks();