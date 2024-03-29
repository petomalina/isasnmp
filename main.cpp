#include <iostream>
#include <getopt.h>
#include "SNMPClient.h"
#include <chrono>
#include <thread>

#ifdef __unix__
#include <signal.h>
#endif

using namespace std;

SNMPClient *client = nullptr;

void signal_int(int sig) {
	if (client != nullptr) {
		client->Stop();
	}
}

int main(int argc, char *argv[]) {

	signal(SIGINT, signal_int);

	int flag; // input flags are: -i interval, -c community_string
	opterr = 0; // clear error flag

	int interval = 100; // default interval
	string community_string, agent;

	// check arguments
	while ((flag = getopt(argc, argv, "i:c:")) != -1) {
		switch (flag) {
			case 'i':
				interval = stoi(optarg);
				break;

			case 'c':
				community_string = string{optarg};
				break;

			default:
				abort();
		}
	}

	// look for specified agent
	if (optind < argc) {
		agent = string{argv[optind]};
	} else {
		return 1;
	}

	// create client and run it
	client = new SNMPClient{agent, community_string, interval};

	int ret = static_cast<int>(client->Run());

	while (client->running()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	delete client;

	return ret;
}
