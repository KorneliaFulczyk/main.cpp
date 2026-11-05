#include <iostream>
#include <cmath>

using namespace std;



//funkcje
void showPopulation(int day, int susceptible, int infected, int recovered);
void simulateDay(int* day, int* susceptible, int* infected, int* recovered, double infectionRate, double recoveryRate);
bool checkPopulation(int s, int i, int r);


void showPopulation(int day, int susceptible, int infected, int recovered) {
	int total = susceptible + infected + recovered;

	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << "Total: " << total << endl << endl;
}


void simulateDay(int* day, int* susceptible, int* infected, int* recovered, double infectionRate, double recoveryRate) {
	//cout << "Infection Rate: " << infectionRate << endl;
	//cout << "Recovery Rate: " << recoveryRate << endl;
	int prevInfected = *infected;


	int newInfections = floor(prevInfected * infectionRate);
	int newRecoveries = floor(prevInfected * recoveryRate);


	if (newInfections > *susceptible) { //ograniczenie
		newInfections = *susceptible;
	}


	if (newRecoveries > prevInfected) { //ograniczenie
		newRecoveries = prevInfected;
	}


	*susceptible = *susceptible - newInfections;
	*infected = *infected + newInfections - newRecoveries;
	*recovered = *recovered + newRecoveries;


	(*day)++;

}

bool checkPopulation(int s, int i, int r) {
	if (s >= 0 && i >= 0 && r >= 0 && s + r + i == 100)
		return true;

	else {
		cout << endl << "ERROR" << endl;
		return false;
	}
}
int main()
{
	int s = 80;
	int i = 10;
	int r = 10;

	int day = 0;

	double infectionRate = 0.20;
	double recoveryRate = 0.10;


	int numer = 0;

	while (1) {
		showPopulation(day, s, i, r);
		cout << endl;
		cout << endl;
		cout << "=== Epidemic Simulator ===\n1.Simulate next day.\n2.Change model parameters.\n3.Exit.\n Your choice: ";
		cin >> numer;
		cout << endl;

		if (cin.fail()) { // dzieki temu wpisanie czegos innego niz liczba nie powoduje nieskonczonej petli
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ERROR! Enter 1,2 or 3! \n" << endl;


			continue;


		}

		switch (numer) {
		case 1:
			simulateDay(&day, &s, &i, &r, infectionRate, recoveryRate);
			if (!checkPopulation(s, i, r)) {
				cout << "ERROR! \n";
			}
			break;


		case 2: {
			double temporaryInfectionRate;
			double temporaryRecoveryRate;

			cout << "Enter new infection rate [0-1]: ";
			cin >> temporaryInfectionRate;

			if (cin.fail()) { // dzieki temu wpisanie czegos innego niz liczba nie powoduje np nieskonczonej petli
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "ERROR! Invalid input format. Parameters were not changed. \n\n";


				continue;
			}

			cout << endl << "Enter new recovery rate [0-1]: ";
			cin >> temporaryRecoveryRate;
			if (cin.fail()) { // dzieki temu wpisanie czegos innego niz liczba nie powoduje np nieskonczonej petli
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "ERROR! Invalid input format. Parameters were not changed. \n\n";


				continue;
			}
			cout << endl << endl;


			if (temporaryInfectionRate >= 0.0 && temporaryInfectionRate <= 1.0 &&
				temporaryRecoveryRate >= 0.0 && temporaryRecoveryRate <= 1.0) {

				infectionRate = temporaryInfectionRate;
				recoveryRate = temporaryRecoveryRate;
				cout << "Infection rate and recovery rate have been updated." << endl;
				cout << endl;

			}

			else {
				cout << "Error: Values must be within the range [0;1]. Parameters were not changed." << endl;
			}
			cout << endl;
			break;

		}
		case 3:
			cout << "Exiting...\n";
			return 0;
			break;


		default:
			cout << "ERROR! Enter 1,2 or 3!  \n";
			cout << endl;
			break;

		}

	}
	return 0;
}
