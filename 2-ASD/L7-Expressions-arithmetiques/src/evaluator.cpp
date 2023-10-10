#include "evaluator.h"
#include <stack> // stack
#include <cctype>

using namespace std;

void calculate(stack<string>&, stack<string>&);
int computeResult(int,int,char);

int evalue(const string &contents) {

	string tabOperators("+-/*%");
	bool opError = true;

	stack<string> pileOp;
	stack<string> pileVal;

	auto it = contents.begin();
	string e;

	for (size_t i = 0; i < contents.size(); ++i) {

		e = *(it + i);

		if (e == "(") {
			continue;
		} else if (e == " ") {
			continue;
		} else if (isdigit(e[0])) {

			opError = false;
			string val;

			do {

				val += e;
				e = *(it + ++i);

			} while (isdigit(e[0]));

			--i;

			pileVal.push(val);
			//cout << endl << "val : " << val << endl;
		} else if (e == ")") {

			calculate(pileVal,pileOp);

		} else if (tabOperators.find(e) != string::npos && !opError) {
			opError = true;
			pileOp.push(e);
		}
		else {
			throw bad_expression();
		}
	}

	return stoi(pileVal.top());
}
