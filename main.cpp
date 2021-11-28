#include <iostream>
#include <fstream>
#include <locale.h>

#define FILE_INFO_CARS   "A1.txt"
#define FILE_HIJACK_CARS "A3.txt"

using namespace std;


bool isEqStr(char* str1, char* str2) {

	bool isEq = true, isEnd = false;

	while (isEq && !isEnd) {

		isEq = *str1 == *str2;
		isEnd = !*str1 && !*str2;
		str1++;
		str2++;

	}

	return isEq;

}

struct person {

	char surname[30], name[20], patronymic[30];

};

struct car {

	person owner;
	int id;
	char brand[20];
	car* nextCar;

};

int main() {
	setlocale(LC_ALL, "RU");
	ifstream fcars(FILE_INFO_CARS);

	if (fcars) {

		car* icar;
		car cars;
		icar = &cars;
		int year;
		int length = 0;
		while (!fcars.eof()) {
			fcars >> icar->owner.surname >> icar->owner.name >> icar->owner.patronymic;
			fcars >> icar->brand >> year >> icar->id;
			icar->nextCar = new car;
			icar = icar->nextCar;
			length++;
		}

		fcars.close();



		fcars.open(FILE_HIJACK_CARS);
		if (fcars) {

			int id;
			char brand[20];


			while (!fcars.eof()) {

				fcars >> id >> brand;
				icar = &cars;

				for (int i = 0; i < length; i++) {

					if (id == icar->id) {
						if (isEqStr(brand, icar->brand)) {

							cout << "Владелец машины " << id << " - ";
							cout << icar->owner.surname << " " << icar->owner.name << " " << icar->owner.patronymic << "\n";

						}
						else {

							cout << "Ошибка: Несоответствие информации по машине (" << id << ")!!!\n";

						}
					}

					icar = icar->nextCar;

				}


			}

			fcars.close();

		}
		else {

			cout << "Ошибка: Файл с информацией об угнаных машинах не найден!!!\n";

		}


	}
	else {

		cout << "Ошибка: Файл с информацией о машинах не найден!!!\n";

	}

	

}
