#pragma once

#include <string>

class BulletInfos
{
private:
  std::string name_;
  int angle_;
  int idOwner_;
  int speed_;
  int type_;

private:
    BulletInfos();

public:
  BulletInfos(std::string const& name, int type, int idLauncher, int angle, int speed);
  ~BulletInfos(void);

  std::string const&   getName() const;
  int getAngle() const;
  int   getIdOwner() const;
  int	getSpeed() const;
  int	getType() const;
};
