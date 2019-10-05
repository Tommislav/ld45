#include "Data.h"
#include <string>
#include <vector>
using namespace std;


Entry entries[] = {

	Entry("Start", "#p4#s3They took my #cWbadge#cD#p3#n They took my #cWgun#cD#p3#n They took my #cWdignity#cD#p3#n They took my #cWdaughter#cD#p3#n #p1#n But I will take it all back#p3#n ...and I will have my #cR#s0#e1VENGEANCE#cD")
	.AddOptions(
		Option("Continue", "Second"),
		Option("Whoa", "Second")
	),

	Entry("Second", "Some moar text")
	.AddOptions(Option("Back", "Start"))
};




Entry* GetEntry(string ID) {
	int len = (sizeof(entries) / sizeof(*entries));
	for (int i = 0; i < len; i++) {
		if (entries[i].ID == ID) {
			return &entries[i];
		}
	}
	return NULL;
}