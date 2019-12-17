#include <iostream>
#include <vector>
#include <algorithm>

struct money {// struct for description value
	enum struct nominal { none = 0, ft = 25, ff = 50, one = 100 };
	nominal state;
}; 
//////////////////////////////////////////////////////////////
struct buyer {
	money::nominal state= money::nominal::none;;
	std::vector<money::nominal> str;
	bool error = true;
	///////////////////////////////////////////////
	void setEnam(int& a) {
		switch (a){
		case 25:
			this->state = money::nominal::ft;
			str.push_back(state);
			break;
		case 50:
			this->state = money::nominal::ff;
			str.push_back(state);
			break;
		case 100:
			this->state = money::nominal::one;
			str.push_back(state);
			break;
		default:
			std::cout << "Error\n";
			error = false;
			break;
		} };
};
///////////////////////////////////////////////////////////////////////
struct cashBox {
	bool letGoAhead = true;
	money::nominal state= money::nominal::none;
	std::vector<money::nominal> kassa;

	void is_continou(int& a) {
		int cout_of_tf = std::count(kassa.begin(), kassa.end(), money::nominal::ft); //need for case 100
		int cout_of_ff = std::count(kassa.begin(), kassa.end(), money::nominal::ff);//need for case 100
		int temp_coun_for_tf = 0;//need for case 100
		int temp_coun_for_ff = 0;//need for case 100

		switch (a) {

		case 25:
			this->state = money::nominal::ft;
			kassa.push_back(state);
			std::cout << "Nice!Take your ticket!\n";
			break;
		/////////////////////////////////////////////////////////////////////////
		case 50:
			this->state = money::nominal::ff;
			if (kassa.empty()) {                      // or exit or let's go ahead
				std::cout << "Sorry i'v not change from 50\n";
				letGoAhead = false;
				break;
			};

			for (auto it = kassa.begin(); it < kassa.end(); it++) { //chek for possibility exchange
				if (*it == money::nominal::ft) {
					it=kassa.erase(it);
					kassa.push_back(state);
					std::cout << "This is your change from your 50!\n";
					break;
				}
				else {
					std::cout << "Sorry i'v not change from 50\n";
					letGoAhead = false;
				}
			}
			break;
		///////////////////////////////////////////////////////////////////
		case 100:
			this->state = money::nominal::one;

			if (kassa.empty()) {                      // or exit or let's go ahead
				std::cout << "Sorry i'v not change from 100\n";
				letGoAhead = false;
				break;
			};

			if (cout_of_tf >= 3) {
				for (auto it = kassa.begin(); it != kassa.end(); ) { //chek for possibility exchange
					if (*it == money::nominal::ft) {
						it=kassa.erase(it);
						std::cout << "One 25!\n";
						temp_coun_for_tf++;
						if (temp_coun_for_tf == 3) { kassa.push_back(state); std::cout << "This is you exchanga from 100! Triple 25!\n"; break; }
						//it-=1;
					}
					else { it++; }

				}
			}
			else if (cout_of_tf >= 1 && cout_of_ff >= 1) {
				for (auto it = kassa.begin(); it < kassa.end();) { //chek for possibility exchange
					if (*it == money::nominal::ft && temp_coun_for_tf != 1) {
						it = kassa.erase(it);
						std::cout << "One 25!\n";
						temp_coun_for_tf++;
					}
						else if (*it == money::nominal::ff && temp_coun_for_ff!=1) {
							it = kassa.erase(it);
							std::cout << "One 25!\n";
							temp_coun_for_ff++;
					}
						else { it++; }
				}
				kassa.push_back(state);
				std::cout << "This is you exchangange from 100!  25 and 50!\n"; break;
			}
			else { std::cout << "I can't excange you money, sorry(100)\n"; letGoAhead = false; break; }
			break;
///////////////////////////////////
		default:
			std::cout << "Error\n";
			break;
		}
	}
};



int main()
{
	cashBox kassa1;
	int count_of_client = 0;
	buyer cons[25];
	int nominal;

	while (kassa1.letGoAhead==true) {
		std::cout << "Let's imagine as you a buyer with dollar\n";
		std::cout << "How much dollars do you have?\n";

		std::cin >> nominal;
		cons[count_of_client].setEnam(nominal); //identifity of nominal

		std::cout << "Now I'll check can i give you a change?\n";

		kassa1.is_continou(nominal); //try to exchange nominal

		count_of_client++;
		std::cout << std::endl<<std::endl;
	}

	std::cout << "Number of customers served is : " << count_of_client-1;

}
