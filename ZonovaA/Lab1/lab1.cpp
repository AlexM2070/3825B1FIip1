#include<iostream>

//Чтобы представлять дробь в несократимом виде нужен алгоритм евклида
int nod(int a, int b) { //функция для нахождения НОД, который всегда будет положительным, берем модуль чисел
	//делаем положительными
	if (a < 0) {
		a = -a;
	}
	if (b < 0) {
		b = -b;
	}
	//Алгоритм Евклида
	// Работа алгоритма: НОД(a,b) = НОД(b,a%b) и так далее, когда a%b = 0, НОД равен тому что слева.
	while (b != 0) {
		int c = b;
		b = a % b;
		a = c;
	}
	return a;
}

//создаем класс рациональных чисел
class Rational {
	//Сделав метод приватным, гарантируется, что: cокращение происходит автоматически, дробь всегда хранится в корректном виде
private:
	int chisl; //числитель
	int znam; //знаменатель
	//сокращение дроби
	void sokr() {
		if (znam == 0) {
			std::cout << "Error, try again!" << std::endl;
			return;
		}
		//ищем НОД
		int delit = nod(chisl, znam);
		//чтобы представлять дробь в сокращенном виде, надо поделить числитель и знаменатель на НОД
		chisl /= delit;
		znam /= delit;
		//чтобы не было повтора одной и той же дроби, убираем минус из знаменателя, переводим его в числитель
		if (znam < 0) {
			chisl = -chisl;
			znam = -znam;
		}
	}
public:
	//создаем конструктор без параметров, чтобы объекты создавать без параметров, инициализируем числитель и знаменатель, чтобы дробь была равна 0
	Rational () : chisl(0), znam(1) {} //тело пустое, конструктор ничего не делает
	//создаем конструктор с параметрами (числитель и знаменатель), создается дробь и сразу сокращается
	Rational(int ch, int zn) {
		if (zn == 0) {
			std::cout << "Error, try again!" << std::endl;
			chisl = 0;
			znam = 1;
			return;
		}

		chisl = ch;
		znam = zn;
		sokr(); //сокращаем дробь
	}
	//создаем конструктор для целых чисел, у которых знаменатель равен 1
	Rational(int ch) : chisl(ch), znam(1) {}

	//дружественная функция для вывода
	friend std::ostream& operator<<(std::ostream& os, const Rational& r); //та внешняя функция получает доступ к приватным (private) членам класса

	//сложение
	Rational add(const Rational& other) const { //const Rational& other - передать объект в функцию без копирования и без возможности его изменения
		int newchisl = chisl * other.znam + other.chisl * znam;
		int newznam = znam * other.znam;
		return Rational(newchisl, newznam);
	}
	//вычитание
	Rational cut(const Rational& other) const { //const Rational& other - передать объект в функцию без копирования и без возможности его изменения
		int newchisl = chisl * other.znam - other.chisl * znam;
		int newznam = znam * other.znam;
		return Rational(newchisl, newznam);
	}
	//умножение
	Rational pro(const Rational& other) const { //const Rational& other - передать объект в функцию без копирования и без возможности его изменения
		int newchisl = chisl * other.chisl;
		int newznam = znam * other.znam;
		return Rational(newchisl, newznam);
	}
	//деление
	Rational del(const Rational& other) const { //const Rational& other - передать объект в функцию без копирования и без возможности его изменения
		//проверка на ноль
		if (other.chisl == 0) {
			std::cout << "Error, try again!" << std::endl;
			return Rational(0, 1);
		}
		int newchisl = chisl * other.znam;
		int newznam = znam * other.chisl;
		return Rational(newchisl, newznam);
	}
};
//Перегрузка оператора — это когда мы берем существующий оператор (например, <<) и объясняем компилятору, как он должен работать с нашим новым типом данных (Rational).
std::ostream& operator<<(std::ostream& os, const Rational& r) {
	if (r.znam == 1) {
		os << r.chisl; //целое число
	}
	else {
		os << r.chisl << "/" << r.znam;
	}
	return os;
}
//главная функция, работа класса
int main() {
	std::cout << "Work class" << std::endl;
	std::cout << std::endl;

	//создание чисел
	std::cout << "Create number" << std::endl;
	Rational a(1, 2);
	Rational b(2, 3);
	Rational c(8, 12);
	Rational d(5);

	std::cout << "a = " << a << " (1/2)" << std::endl;
	std::cout << "b = " << b << " (2/3)" << std::endl;
	std::cout << "c = " << c << " (8/12 -> 2/3)" << std::endl;
	std::cout << "d = " << d << " (5)" << std::endl;
	std::cout << std::endl;

	//сокращения
	std::cout << "8/12 after transformation: " << c << std::endl;
	std::cout << std::endl;

	//арифметические операции
	std::cout << "Arifmetic operations:" << std::endl;

	Rational sum = a.add(b);
	std::cout << a << " + " << b << " = " << sum << std::endl;

	Rational diff = a.cut(b);
	std::cout << a << " - " << b << " = " << diff << std::endl;

	Rational prod = a.pro(b);
	std::cout << a << " * " << b << " = " << prod << std::endl;

	Rational quot = a.del(b);
	std::cout << a << " / " << b << " = " << quot << std::endl;
	std::cout << std::endl;

	//pабота с целыми числами
	std::cout << "Work integer:" << std::endl;
	std::cout << d << " + " << a << " = " << d.add(a) << std::endl;
	std::cout << d << " * " << a << " = " << d.pro(a) << std::endl;
	std::cout << std::endl;

	//проверка на отрицательные числа
	std::cout << "Work negative numbers:" << std::endl;
	Rational e(-1, 2); // -1/2
	Rational f(3, -4); // -3/4

	std::cout << "e = " << e << " (-1/2)" << std::endl;
	std::cout << "f = " << f << " (3/-4 -> -3/4)" << std::endl;
	std::cout << e << " + " << f << " = " << e.add(f) << std::endl;
	std::cout << std::endl;

	//демонстрация обработки ошибок
	std::cout << "Errors:" << std::endl;
	Rational zero(0, 1); // Ноль
	std::cout << "Delenie: " << a << " for " << zero << ": ";
	Rational bad = a.del(zero);

	return 0;
}