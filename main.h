#pragma once

enum class Menu{
    add_book,
    add_member,
    borrow,
    return_book,
    search_book,
    list_borrowed_books,
    exit
};

std::string getMenuString(Menu item);