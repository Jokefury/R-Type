
#pragma once

#include <deque>
#include <map>
#include "Room.h"

enum eRequest
  {
    ROOM_GET_LIST = 1101,
    ROOM_JOIN = 1102,
    ROOM_CREATE = 1103,
    ROOM_LEAVE = 1104,
    ROOM_READY = 1105,
    ROOM_LIST = 1201,
    ROOM_NOTIFY_JOIN = 1202,
    ROOM_NOTIFY_PLAYER = 1203,
    ROOM_NOTIFY_READY = 1204,
    ROOM_SEND_RESSOURCES = 1205,
    ROOM_START_GAME = 1206,
    GAME_MOVE = 2101,
    GAME_START_SHOT = 2102,
    GAME_LAUNCH_SHOT = 2103,
    GAME_LAUNCH_BONUS = 2104,
    GAME_PLAYER_SPAWN = 2201,
    GAME_PLAYR_MOVE = 2202,
    GAME_PLAYER_DESTROY = 2203,
    GAME_ENEMY_SPAWN = 2204,
    GAME_ENEMY_MOVE = 2205,
    GAME_ENEMY_DESTROY = 2206,
    GAME_BULLET_SPAWN = 2207,
    GAME_BULLET_MOVE = 2208,
    GAME_BULLET_DESTROY = 2209,
    GAME_BONUS_SPAWN = 2210,
    GAME_BONUS_PICKED = 2211
  };

class RequestManager;
typedef void (RequestManager::*requestFct)();

class RequestManager
{
  // std::deque<Room*>&    room_;
  std::map<eRequest, requestFct> requestFunctions_;
};
