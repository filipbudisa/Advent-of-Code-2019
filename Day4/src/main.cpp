#include <iostream>

int main(){
	const int start = 134792, stop = 675810;

	int count1 = 0;
	int count2 = 0;

	for(int n = start; n <= stop; n++){
		std::string t;
		t.resize(7);
		sprintf(t.data(), "%d", n);

		bool fail = false;
		for(int i = 1; i < 6; i++){
			if(t[i-1] > t[i]){
				fail = true;
				break;
			}
		}
		if(fail) continue;

		fail = true;
		for(int i = 1; i < 6; i++){
			if(t[i-1] == t[i]){
				fail = false;
				break;
			}
		}
		if(fail) continue;

		count1++;

		fail = true;
		for(int i = 0; i < 5; i++){
			int same = 1;

			for(int j = i+1; j < 6; j++){
				if(t[i] == t[j]) same++;
				else break;
			}

			if(same == 2){
				fail = false;
				break;
			}else{
				i += same-1;
			}
		}
		if(fail) continue;

		count2++;
	}

	printf("Count, pt1: %d\n", count1);
	printf("Count, pt2: %d\n", count2);
}