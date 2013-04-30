/*
 * Main.cpp
 *
 *  Created on: 15 avr. 2013
 *      Author: Carl
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "client.h"

int main(){
	client client("127.0.0.1", 9999);

	return 0;
}


