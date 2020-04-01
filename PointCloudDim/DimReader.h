#pragma once
#include <string>
#include <vector>
using namespace std;

class DimReader
{
public:
	DimReader();
	DimReader(string& fileSourceName);
	~DimReader();

public:
	struct dimension {
		int number;
		string dimSymbol;
		string dimType;
		double dimValue;
		double upperLimit;
		double lowerLimit;
		string reference;
	};

	struct central_point {
		double x;
		double y;
		double z;
	};

	struct initial_point {
		double x;
		double y;
		double z;
	};

	struct refer {
		string refer_type;
		double radius_or_length;
		double height_or_width;
		central_point centralPoint;
		initial_point initialPoint;
		double x_lower;
		double x_upper;
		double y_lower;
		double y_upper;
		double z_lower;
		double z_upper;
	};

	struct refer_dim {
		int number;
		string dimSymbol;
		string dimType;
		double dimValue;
		double upperLimit;
		double lowerLimit;

		vector<refer> refer;
	};

	vector<refer_dim> vec_refer_dim; //存储尺寸信息的数组
};

