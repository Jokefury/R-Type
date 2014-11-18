
#pragma once

#include <string>

struct User
{

  User(int id, std::string host)
    : id_(id), host_(host), name_(""), port_(-1), curentRoom_ (-1), ready_ (false)
  {}

  int                   id_;
  std::string           host_;
  std::string           name_;
  int                   port_;
  int                   curentRoom_;
  bool                  ready_;
};
