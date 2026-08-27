#include "member.h"
#include <string>
#include <unordered_map>
#include <iostream>

std::unordered_map<int, Member> members;

int getMemberId()
{
    static int id = 0;
    return ++id;
}

std::ostream &operator<<(std::ostream &out, Member member)
{
    return out << member.id << " " << member.name << '\n';
}

void listMembers()
{
    for (const auto &member : members)
    {
        std::cout << member.second << '\n';
    }
    std::cout << '\n';
}

Member getMember(int id)
{
    return members.at(id);
}

Member initiateAddMember()
{
    std::string name;
    std::cin.ignore();

    std::cout << '\n';
    std::cout << "Please enter member name." << '\n';
    std::getline(std::cin, name);
    std::cout << '\n';

    int id = getMemberId();
    Member member{id, name};
    members.insert({id, member});
    return member;
}