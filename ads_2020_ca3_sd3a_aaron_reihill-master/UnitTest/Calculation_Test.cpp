#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2020_CA3_SD3a_Aaron_Reihill/Product.cpp"
#include "../ADS_2020_CA3_SD3a_Aaron_Reihill/Calculations.cpp"
#include "../ADS_2020_CA3_SD3a_Aaron_Reihill/ReadFile.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Calculation_Test
{
	TEST_CLASS(Calculation_Test)
	{
	
	public:

		TEST_METHOD(TestListConstructor)
		{
			list<Product> products;
			string file = "../ADS_2020_CA3_SD3a_Aaron_Reihill/sales_100.txt";
			readTextFile(file, products);
			int result = products.size();
			Assert::AreEqual(100, result);
		}

		TEST_METHOD(TestTotalValueOfSales)
		{
			list<Product> products;
			string file = "../ADS_2020_CA3_SD3a_Aaron_Reihill/sales_100.txt";
			readTextFile(file, products);
			float result = totalValueOfSales(products);
			float num = 32119;
			Assert::AreEqual(num, result, 2);
		}
		TEST_METHOD(TestTotalQuantityOfSales)
		{
			list<Product> products;
			string file = "../ADS_2020_CA3_SD3a_Aaron_Reihill/sales_100.txt";
			readTextFile(file, products);
			int result = totalQuantityOfSales(products);
			int num = 609;
			Assert::AreEqual(num, result);
		}
		TEST_METHOD(TestAverageValueOfSales)
		{
			list<Product> products;
			string file = "../ADS_2020_CA3_SD3a_Aaron_Reihill/sales_100.txt";
			readTextFile(file, products);
			float result = averageValueOfSales(products);
			float num = 52.7406;
			Assert::AreEqual(num, result, 2);
		}
	};
}
