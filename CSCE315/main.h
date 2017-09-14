#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <exception>
#include <string>

using namespace std;


// struct for throwing as an exception
struct InvalidCommand : public exception {
private:
	// Allow for a dynamic reason message
	const char* reason = "";

public:
	explicit InvalidCommand(const char *given_reason) {
		reason = given_reason;
	}

	const char* what() const throw() override {
		return reason;
	}
};

#endif
