
#include        <iostream>
#include        "Core.h"
#include        "InitializeError.h"

int     main()
{
  try
    {
      Core  c;
      c.run ();
    }
  catch (InitializeError & e)
    {
      std::cerr << "Initialize fatal error : " << e.what () << std::endl;
    }
  return (0);
}
