#include "Data.h"
#include <string>
#include <vector>
using namespace std;


Entry entries[] = {

	Entry("Start", "#p4#s3They took my #cWbadge#cD#p3#n They took my #cWgun#cD#p3#n They took my #cWdignity#cD#p3#n They took my #cWdaughter#cD#p3#n #p1#n But I will take it all back#p3#n ...and I will have my #cR#s0#e1VENGEANCE#cD#p3 ")
	.AddText(
		OptionalText("#n #n I see you saw some moar text just now!").ShowIfKey(GameKey::Test2))
	.AddOptions(
		Option("Continue", "Second").HideIfKey(GameKey::Test).TriggerKey(GameKey::Test),
		Option("Whoa", "Second"),
		Option("This was hidden before", "Second").ShowIfKey(GameKey::Test),
		Option("Dependant on Test1", "Second").ShowIfKey(GameKey::Test2)

	),

	Entry("Second", "Some moar text " + to_string(2) + " lala").TriggerKey(GameKey::Test2)
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