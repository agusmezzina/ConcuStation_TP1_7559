#ifndef SIGTERM_HANDLER_H_
#define SIGTERM_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

#include <fstream>

class SIGTERM_Handler : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;

	public:

		SIGTERM_Handler () : gracefulQuit(0) {
		}

		~SIGTERM_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGTERM );
			this->gracefulQuit = 1;
			return 0;
		}

		sig_atomic_t getGracefulQuit () const {
			return this->gracefulQuit;
		}

};

#endif /* SIGTERM_HANDLER_H_ */
