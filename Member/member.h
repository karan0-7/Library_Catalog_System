#pragma once
#include <string>

struct Member
{
    int id;
    std::string name;
};

Member initiateAddMember();
void listMembers();
Member getMember(int id);