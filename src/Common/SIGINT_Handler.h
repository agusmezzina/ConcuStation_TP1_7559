#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class SIGINT_Handler : public EventHandler {

	private:
		sig_atomic_t launchProcess;

	public:

		SIGINT_Handler () : launchProcess(0) {
		}

		~SIGINT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			this->launchProcess = 1;
			return 0;
		}

		sig_atomic_t getLaunchProcess () const {
			return this->launchProcess;
		}

};

#endif /* SIGINT_HANDLER_H_ */
