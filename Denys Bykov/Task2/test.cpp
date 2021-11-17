#include "AnyType.hpp"

#include <string>
#include <iostream>

using namespace std;

static string to_string(bool val)
{
	if (val)
		return string("true");
	return string("false");
}

static bool handle_test(const char* name, bool (*fn)())
{
	string line{" ------------- "};
	cout << "\n" << line << "testing: " << name << line << "\n";
	auto res = fn();
	cout << "\n" << line << "test passed: " << to_string(res) << line << "\n";
	return res;
}

bool test_any_type_base_constr()
{
	bool res{true};
	using any_t = AnyTypeBase<int, double>;
	any_t any;
	any_t any_int(12);
	any_t any_dbl(1.12);
	try {
		auto val1 = any.To<int>();
		val1++;	// suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) != string("No value stored"))
			res &= false;
	}

	auto val2 = any_int.To<int>();
	res &= (val2 == 12);
	try {
		auto val1 = any_int.To<double>();
		val1++; // suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) !=
			string("Stored value is not of the requested type"))
			res &= false;
	}

	auto val3 = any_dbl.To<double>();
	res &= (val3 == 1.12);
	try {
		auto val1 = any_dbl.To<int>();
		val1++; // suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) !=
			string("Stored value is not of the requested type"))
			res &= false;
	}
	return res;
}

bool test_any_type_base_move()
{
	bool res{true};
	using any_t = AnyTypeBase<int, double>;
	any_t any;
	any_t any_int(12);

	any = std::move(any_int);

	auto val2 = any.To<int>();
	res &= (val2 == 12);
	try {
		auto val1 = any.To<double>();
		val1++; // suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) !=
			string("Stored value is not of the requested type"))
			res &= false;
	}

	try {
		auto val1 = any_int.To<int>();
		val1++;	// suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) != string("No value stored"))
			res &= false;
	}
	return res;
}

bool test_any_type_base_swap()
{
	bool res{true};
	using any_t = AnyTypeBase<int, double>;
	any_t any_int(12);
	any_t any_dbl(1.12);

	any_int.Swap(any_dbl);

	auto val2 = any_dbl.To<int>();
	res &= (val2 == 12);
	try {
		auto val1 = any_dbl.To<double>();
		val1++; // suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) !=
			string("Stored value is not of the requested type"))
			res &= false;
	}

	auto val3 = any_int.To<double>();
	res &= (val3 == 1.12);
	try {
		auto val1 = any_int.To<int>();
		val1++; // suppress unused variable warning
	} catch (const TypeError& ex) {
		if (string(ex.what()) !=
			string("Stored value is not of the requested type"))
			res &= false;
	}
	return res;
}

bool test_any_type_get_type()
{
	bool res{true};
	bool v1{true};
	long double v2{1.101203};

	AnyType any1{v1};
	AnyType any2{v2};

	res &= (any1.GetType() == AnyType::Type::Bool);
	res &= (any2.GetType() == AnyType::Type::LongDouble);

	any1.Swap(any2);

	res &= (any2.GetType() == AnyType::Type::Bool);
	res &= (any1.GetType() == AnyType::Type::LongDouble);

	any1.Destroy();

	res &= (any1.GetType() == AnyType::Type::NoType);

	any1.Swap(any2);

	res &= (any2.GetType() == AnyType::Type::NoType);
	res &= (any1.GetType() == AnyType::Type::Bool);
	return res;
}

int main() {
	bool res{true};
	res &= handle_test("any type base constr", test_any_type_base_constr);
	res &= handle_test("any type base move", test_any_type_base_move);
	res &= handle_test("any type base swap", test_any_type_base_swap);
	res &= handle_test("any type get type", test_any_type_get_type);
	cout << "\nAll tests passed: " << to_string(res) << "\n";
	return 0;
}
