
/*

*/

#include "DBusServer.h"
#include <cstring>
#include <iostream>

int main(int argc, char **argv)
{

    DBusServer server;

    bool forever = false;
    bool badopts = false;
    if (argc > 1) {
	if (!strcmp(argv[1], "--disable-timer")) // like in packagekitd
	    forever = true;
	else
	    badopts = true;
	if (argc > 2)
	    badopts = true;
    }
    if (badopts)
	std::cerr << "Usage: " << argv[0] << " [--disable-timer]\n";

    bool connected = server.connect();

    if (connected)
    {
	server.run(forever);
	return 0;
    }

    // indicate an error
    return 1;
}
