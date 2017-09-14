#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <exception>
#include <string>

using namespace std;

struct InvalidCommand : public exception {
private:
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
