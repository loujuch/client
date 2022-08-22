#ifndef GLOBE_H
#define GLOBE_H

#include "client.h"

class Globe {
	Globe();
public:
	static Client* client;
	static int id;
	static QString name;
};

#endif // GLOBE_H
