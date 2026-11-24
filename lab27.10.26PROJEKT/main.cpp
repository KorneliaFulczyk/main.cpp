#include <iostream>
#include <cmath>

using namespace std;



//funkcje
void showPopulation(int day, int susceptible, int infected, int recovered);
void simulateDay(int* day, int* susceptible, int* infected, int* recovered, double infectionRate, double recoveryRate, int dailyNewInfections[], int dailyNewRecoveries[]);
bool checkPopulation(int s, int i, int r);


void showPopulation(int day, int susceptible, int infected, int recovered) {
	int total = susceptible + infected + recovered;

	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << "Total: " << total << endl << endl;
}


void simulateDay(int* day, int* susceptible, int* infected, int* recovered, double infectionRate, double recoveryRate, int dailyNewInfections[], int dailyNewRecoveries[]) {
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

	dailyNewInfections[*day - 1] = newInfections;
	dailyNewRecoveries[*day - 1] = newRecoveries;
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

	int tab[101] = { 0 }; // zeby nie bylo smieci

	int populationHistory[101][3];
	populationHistory[day][0] = s;
	populationHistory[day][1] = i;
	populationHistory[day][2] = r;

	int dailyNewInfections[100] = { 0 };
	int dailyNewRecoveries[100] = { 0 };

	int numer = 0;

	while (1) {
		showPopulation(day, s, i, r);
		cout << endl;
		cout << endl;
		cout << "=== Epidemic Simulator ===\n1.Simulate next day.\n2.Change model parameters.\n3.Show population history.\n4.Exit.\n Your choice: ";
		cin >> numer;
		cout << endl;

		if (cin.fail()) { // dzieki temu wpisanie czegos innego niz liczba nie powoduje nieskonczonej petli
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ERROR! Enter 1, 2, 3 or 4! \n" << endl;


			continue;


		}

		switch (numer) {
		case 1:
			if (tab[100] == 0) {
				simulateDay(&day, &s, &i, &r, infectionRate, recoveryRate,dailyNewInfections, dailyNewRecoveries);
				if (!checkPopulation(s, i, r)) {
					cout << "ERROR! \n";
				}

				tab[day] = day;
				populationHistory[day][0] = s;
				populationHistory[day][1] = i;
				populationHistory[day][2] = r;
			}

			else {
				cout << "ERROR!\nCannot simulate another day.\nSimulation limit has been reached." << endl << endl;
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
		case 3: {
			cout << "Showing population history and new daily infections and recoveries: \n" <<endl;
			
			for (int d = 0; d <= day; d++) {
				
				cout <<"  Statistics for day " << d << ": " << endl << endl;
				cout <<"    Susceptible: "<< populationHistory[d][0] << endl;
				cout <<"    Infected: " << populationHistory[d][1] << endl;
				cout <<"    Recovered: "<< populationHistory[d][2] << endl << endl;

				if (d > 0) {
					cout <<"    New infections: "<< dailyNewInfections[d - 1] << endl;
					cout <<"    New recoveries: "<<dailyNewRecoveries[d- 1] << endl << endl << endl;
				}
				
			}
			cout << "--------------------" << endl;
			break;
		}
		case 4:
			cout << "Exiting...\n";
			return 0;
			break;


		default:
			cout << "ERROR! Enter 1, 2, 3 or 4!  \n";
			cout << endl;
			break;

		}

	}
	return 0;
}
