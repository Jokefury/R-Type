#include "Core.h"
#include <sstream>
#include <iostream>
#include <fstream>

static bool launch_from_file()
{
  std::ifstream ifs ( "client.config" , std::ifstream::in );
  std::string name;
  std::string host;
  std::string port;
  int ret = 0;
  if (ifs.good() && ++ret)
    std::getline(ifs, name);
  if (ifs.good() && ++ret)
    std::getline(ifs, host);
  if (ifs.good() && ++ret)
    std::getline(ifs, port);
  ifs.close();
  if (ret < 3)
    return false;
  int portV = 0;
  std::stringstream ss(port);
  ss >> portV;

  Core  core(name, host, portV);
	
  core.init();
  core.run();

  return true;
}

int     main(int ac, char **av)
{
  if (ac == 1)
    {
      if (!launch_from_file())
	{
	  std::cerr << "Error: Cannot open configuration file." << std::endl;
	  std::cerr << "Usage: ./Client <username> <host> <port>" << std::endl << "Help: Use no parameter to load config file" << std::endl;
	  return 0;
	}
	  return 0;
    }
  else	if (ac != 4)
    {
      std::cerr << "Error: Invalid arguments." << std::endl;		
      std::cerr << "Usage: ./Client <username> <host> <port>" << std::endl << "Help: Use no parameter to load config file" << std::endl;
      return 0;
    }
  int port = 0;
	std::stringstream ss(av[3]);
	ss >> port;
	Core  core(av[1], av[2], port);
  core.init();
  core.run();
  return 1;
}
