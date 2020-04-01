#include "DimReader.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>  
using namespace std;

DimReader::DimReader() {}

DimReader::DimReader(string& fileSourceName)
{
	ifstream infile;
	infile.open(fileSourceName, ifstream::in);

	size_t index_comma1 = 0;
	size_t index_comma2 = 0;
	size_t index_comma3 = 0;
	size_t index_comma4 = 0;
	size_t index_comma5 = 0;
	size_t index_comma6 = 0;

	vector<dimension> vecDimension; //存储尺寸信息
	int i = 0;

	string line; //按行读取

	getline(infile, line); //跳过第一行
	while (getline(infile, line))
	{
		dimension dim; //尺寸结构体对象
		//number
		index_comma1 = line.find(',', 0);
		istringstream iss_number(line.substr(0, index_comma1));
		iss_number >> dim.number;

		//dimSymbol
		index_comma2 = line.find(',', index_comma1 + 1);
		dim.dimSymbol = line.substr(index_comma1 + 1, index_comma2 - index_comma1 - 1);

		//dimType
		index_comma3 = line.find(',', index_comma2 + 1);
		dim.dimType = line.substr(index_comma2 + 1, index_comma3 - index_comma2 - 1);

		//dimValue
		index_comma4 = line.find(',', index_comma3 + 1);
		istringstream iss_dimValue(line.substr(index_comma3 + 1, index_comma4 - index_comma3 - 1));
		iss_dimValue >> dim.dimValue;

		//upperLimit
		index_comma5 = line.find(',', index_comma4 + 1);
		istringstream iss_upperLimit(line.substr(index_comma4 + 1, index_comma5 - index_comma4 - 1));
		iss_upperLimit >> dim.upperLimit;

		//lowerLimit
		index_comma6 = line.find(',', index_comma5 + 1);
		istringstream iss_lowerLimit(line.substr(index_comma5 + 1, index_comma6 - index_comma5 - 1));
		iss_lowerLimit >> dim.lowerLimit;

		//reference
		dim.reference = line.substr(index_comma6 + 1);

		vecDimension.push_back(dim);
		++i;
	}

	//输出打印，辅助调试
	//ui.textBrowser->append(QString::fromStdString(vecDimension[0].dimSymbol));
	//ui.textBrowser->append(QString::fromStdString(vecDimension[1].dimSymbol));

	infile.close();

	//vector<refer_dim> vec_refer_dim;

	size_t index_symble1 = 0;
	size_t index_symble2 = 0;
	size_t index_symble3 = 0;
	size_t index_symble4 = 0;
	size_t index_symble5 = 0;
	size_t index_symble6 = 0;
	size_t index_symble7 = 0;
	size_t index_symble8 = 0;
	size_t index_symble9 = 0;
	size_t index_symble10 = 0;
	size_t index_symble11 = 0;
	size_t index_symble12 = 0;
	size_t index_symble13 = 0;
	size_t index_symble14 = 0;
	size_t index_symble15 = 0;
	size_t index_symble16 = 0;
	size_t index_symble17 = 0;
	size_t index_symble18 = 0;
	size_t index_symble19 = 0;
	size_t index_symble20 = 0;
	size_t index_symble21 = 0;

	for (auto dim : vecDimension) {

		refer_dim temp_refer_dim;
		temp_refer_dim.number = dim.number;
		temp_refer_dim.dimSymbol = dim.dimSymbol;
		temp_refer_dim.dimType = dim.dimType;
		temp_refer_dim.dimValue = dim.dimValue;
		temp_refer_dim.upperLimit = dim.upperLimit;
		temp_refer_dim.lowerLimit = dim.lowerLimit;

		refer temp_refer;
		if (dim.dimType == "DIMTYPE_RADIUS") {

			//string refer_type
			index_symble1 = dim.reference.find('{', 0);
			temp_refer.refer_type = dim.reference.substr(1, index_symble1 - 1);

			//double radius;
			index_symble2 = dim.reference.find(',', index_symble1 + 1);
			istringstream iss_radius(dim.reference.substr(index_symble1 + 1 + 6, index_symble2 - index_symble1 - 1 - 6));
			iss_radius >> temp_refer.radius_or_length;

			//	double height;
			index_symble3 = dim.reference.find(',', index_symble2 + 1);
			istringstream iss_height(dim.reference.substr(index_symble2 + 1 + 6, index_symble3 - index_symble2 - 1 - 6));
			iss_height >> temp_refer.height_or_width;

			//	central_point centralPoint.x;
			index_symble4 = dim.reference.find('(', index_symble3 + 1);
			index_symble5 = dim.reference.find(',', index_symble4 + 1);
			istringstream iss_centralPoint_x(dim.reference.substr(index_symble4 + 1, index_symble5 - index_symble4 - 1));
			iss_centralPoint_x >> temp_refer.centralPoint.x;
			//	central_point centralPoint.y;
			index_symble6 = dim.reference.find(',', index_symble5 + 1);
			istringstream iss_centralPoint_y(dim.reference.substr(index_symble5 + 1, index_symble6 - index_symble5 - 1));
			iss_centralPoint_y >> temp_refer.centralPoint.y;
			//	central_point centralPoint.z;
			index_symble7 = dim.reference.find(')', index_symble6 + 1);
			istringstream iss_centralPoint_z(dim.reference.substr(index_symble6 + 1, index_symble7 - index_symble6 - 1));
			iss_centralPoint_z >> temp_refer.centralPoint.z;

			//	central_point initialPoint.x;
			index_symble8 = dim.reference.find('(', index_symble7 + 1);
			index_symble9 = dim.reference.find(',', index_symble8 + 1);
			istringstream iss_initialPoint_x(dim.reference.substr(index_symble8 + 1, index_symble9 - index_symble8 - 1));
			iss_initialPoint_x >> temp_refer.initialPoint.x;
			//	central_point initialPoint.y;
			index_symble10 = dim.reference.find(',', index_symble9 + 1);
			istringstream iss_initialPoint_y(dim.reference.substr(index_symble9 + 1, index_symble10 - index_symble9 - 1));
			iss_initialPoint_y >> temp_refer.initialPoint.y;
			//	central_point initialPoint.z;
			index_symble11 = dim.reference.find(')', index_symble10 + 1);
			istringstream iss_initialPoint_z(dim.reference.substr(index_symble10 + 1, index_symble11 - index_symble10 - 1));
			iss_initialPoint_z >> temp_refer.initialPoint.z;

			// x_lower
			index_symble12 = dim.reference.find('[', index_symble11 + 1);
			index_symble13 = dim.reference.find(',', index_symble12 + 1);
			istringstream iss_x_lower(dim.reference.substr(index_symble12 + 1, index_symble13 - index_symble12 - 1));
			iss_x_lower >> temp_refer.x_lower;
			//x_upper
			index_symble14 = dim.reference.find(']', index_symble13 + 1);
			istringstream iss_x_upper(dim.reference.substr(index_symble13 + 1, index_symble14 - index_symble13 - 1));
			iss_x_upper >> temp_refer.x_upper;

			// y_lower
			index_symble15 = dim.reference.find('[', index_symble14 + 1);
			index_symble16 = dim.reference.find(',', index_symble15 + 1);
			istringstream iss_y_lower(dim.reference.substr(index_symble15 + 1, index_symble16 - index_symble15 - 1));
			iss_y_lower >> temp_refer.y_lower;
			// y_upper
			index_symble17 = dim.reference.find(']', index_symble16 + 1);
			istringstream iss_y_upper(dim.reference.substr(index_symble16 + 1, index_symble17 - index_symble16 - 1));
			iss_y_upper >> temp_refer.y_upper;

			// z_lower
			index_symble18 = dim.reference.find('[', index_symble17 + 1);
			index_symble19 = dim.reference.find(',', index_symble18 + 1);
			istringstream iss_z_lower(dim.reference.substr(index_symble18 + 1, index_symble19 - index_symble18 - 1));
			iss_z_lower >> temp_refer.z_lower;
			// z_upper
			index_symble20 = dim.reference.find(']', index_symble19 + 1);
			istringstream iss_z_upper(dim.reference.substr(index_symble19 + 1, index_symble20 - index_symble19 - 1));
			iss_z_upper >> temp_refer.z_upper;


			temp_refer_dim.refer.push_back(temp_refer);
		}

		else if (dim.dimType == "DIMTYPE_DIAMETER") {

			//string refer_type
			index_symble1 = dim.reference.find('{', 0);
			temp_refer.refer_type = dim.reference.substr(1, index_symble1 - 1);

			//double radius;
			index_symble2 = dim.reference.find(',', index_symble1 + 1);
			istringstream iss_radius(dim.reference.substr(index_symble1 + 1 + 6, index_symble2 - index_symble1 - 1 - 6));
			iss_radius >> temp_refer.radius_or_length;

			//	double height;
			index_symble3 = dim.reference.find(',', index_symble2 + 1);
			istringstream iss_height(dim.reference.substr(index_symble2 + 1 + 6, index_symble3 - index_symble2 - 1 - 6));
			iss_height >> temp_refer.height_or_width;

			//	central_point centralPoint.x;
			index_symble4 = dim.reference.find('(', index_symble3 + 1);
			index_symble5 = dim.reference.find(',', index_symble4 + 1);
			istringstream iss_centralPoint_x(dim.reference.substr(index_symble4 + 1, index_symble5 - index_symble4 - 1));
			iss_centralPoint_x >> temp_refer.centralPoint.x;
			//	central_point centralPoint.y;
			index_symble6 = dim.reference.find(',', index_symble5 + 1);
			istringstream iss_centralPoint_y(dim.reference.substr(index_symble5 + 1, index_symble6 - index_symble5 - 1));
			iss_centralPoint_y >> temp_refer.centralPoint.y;
			//	central_point centralPoint.z;
			index_symble7 = dim.reference.find(')', index_symble6 + 1);
			istringstream iss_centralPoint_z(dim.reference.substr(index_symble6 + 1, index_symble7 - index_symble6 - 1));
			iss_centralPoint_z >> temp_refer.centralPoint.z;

			//	central_point initialPoint.x;
			index_symble8 = dim.reference.find('(', index_symble7 + 1);
			index_symble9 = dim.reference.find(',', index_symble8 + 1);
			istringstream iss_initialPoint_x(dim.reference.substr(index_symble8 + 1, index_symble9 - index_symble8 - 1));
			iss_initialPoint_x >> temp_refer.initialPoint.x;
			//	central_point initialPoint.y;
			index_symble10 = dim.reference.find(',', index_symble9 + 1);
			istringstream iss_initialPoint_y(dim.reference.substr(index_symble9 + 1, index_symble10 - index_symble9 - 1));
			iss_initialPoint_y >> temp_refer.initialPoint.y;
			//	central_point initialPoint.z;
			index_symble11 = dim.reference.find(')', index_symble10 + 1);
			istringstream iss_initialPoint_z(dim.reference.substr(index_symble10 + 1, index_symble11 - index_symble10 - 1));
			iss_initialPoint_z >> temp_refer.initialPoint.z;

			// x_lower
			index_symble12 = dim.reference.find('[', index_symble11 + 1);
			index_symble13 = dim.reference.find(',', index_symble12 + 1);
			istringstream iss_x_lower(dim.reference.substr(index_symble12 + 1, index_symble13 - index_symble12 - 1));
			iss_x_lower >> temp_refer.x_lower;
			//x_upper
			index_symble14 = dim.reference.find(']', index_symble13 + 1);
			istringstream iss_x_upper(dim.reference.substr(index_symble13 + 1, index_symble14 - index_symble13 - 1));
			iss_x_upper >> temp_refer.x_upper;

			// y_lower
			index_symble15 = dim.reference.find('[', index_symble14 + 1);
			index_symble16 = dim.reference.find(',', index_symble15 + 1);
			istringstream iss_y_lower(dim.reference.substr(index_symble15 + 1, index_symble16 - index_symble15 - 1));
			iss_y_lower >> temp_refer.y_lower;
			// y_upper
			index_symble17 = dim.reference.find(']', index_symble16 + 1);
			istringstream iss_y_upper(dim.reference.substr(index_symble16 + 1, index_symble17 - index_symble16 - 1));
			iss_y_upper >> temp_refer.y_upper;

			// z_lower
			index_symble18 = dim.reference.find('[', index_symble17 + 1);
			index_symble19 = dim.reference.find(',', index_symble18 + 1);
			istringstream iss_z_lower(dim.reference.substr(index_symble18 + 1, index_symble19 - index_symble18 - 1));
			iss_z_lower >> temp_refer.z_lower;
			// z_upper
			index_symble20 = dim.reference.find(']', index_symble19 + 1);
			istringstream iss_z_upper(dim.reference.substr(index_symble19 + 1, index_symble20 - index_symble19 - 1));
			iss_z_upper >> temp_refer.z_upper;

			temp_refer_dim.refer.push_back(temp_refer);
		}

		else {

			string second;

			//string refer_type
			index_symble1 = dim.reference.find('{', 0);
			temp_refer.refer_type = dim.reference.substr(1, index_symble1 - 1);

			//double radius;
			index_symble2 = dim.reference.find(',', index_symble1 + 1);
			istringstream iss_radius(dim.reference.substr(index_symble1 + 1 + 6, index_symble2 - index_symble1 - 1 - 6));
			iss_radius >> temp_refer.radius_or_length;

			//	double height;
			index_symble3 = dim.reference.find(',', index_symble2 + 1);
			istringstream iss_height(dim.reference.substr(index_symble2 + 1 + 6, index_symble3 - index_symble2 - 1 - 6));
			iss_height >> temp_refer.height_or_width;

			//	central_point centralPoint.x;
			index_symble4 = dim.reference.find('(', index_symble3 + 1);
			index_symble5 = dim.reference.find(',', index_symble4 + 1);
			istringstream iss_centralPoint_x(dim.reference.substr(index_symble4 + 1, index_symble5 - index_symble4 - 1));
			iss_centralPoint_x >> temp_refer.centralPoint.x;
			//	central_point centralPoint.y;
			index_symble6 = dim.reference.find(',', index_symble5 + 1);
			istringstream iss_centralPoint_y(dim.reference.substr(index_symble5 + 1, index_symble6 - index_symble5 - 1));
			iss_centralPoint_y >> temp_refer.centralPoint.y;
			//	central_point centralPoint.z;
			index_symble7 = dim.reference.find(')', index_symble6 + 1);
			istringstream iss_centralPoint_z(dim.reference.substr(index_symble6 + 1, index_symble7 - index_symble6 - 1));
			iss_centralPoint_z >> temp_refer.centralPoint.z;

			//	central_point initialPoint.x;
			index_symble8 = dim.reference.find('(', index_symble7 + 1);
			index_symble9 = dim.reference.find(',', index_symble8 + 1);
			istringstream iss_initialPoint_x(dim.reference.substr(index_symble8 + 1, index_symble9 - index_symble8 - 1));
			iss_initialPoint_x >> temp_refer.initialPoint.x;
			//	central_point initialPoint.y;
			index_symble10 = dim.reference.find(',', index_symble9 + 1);
			istringstream iss_initialPoint_y(dim.reference.substr(index_symble9 + 1, index_symble10 - index_symble9 - 1));
			iss_initialPoint_y >> temp_refer.initialPoint.y;
			//	central_point initialPoint.z;
			index_symble11 = dim.reference.find(')', index_symble10 + 1);
			istringstream iss_initialPoint_z(dim.reference.substr(index_symble10 + 1, index_symble11 - index_symble10 - 1));
			iss_initialPoint_z >> temp_refer.initialPoint.z;

			// x_lower
			index_symble12 = dim.reference.find('[', index_symble11 + 1);
			index_symble13 = dim.reference.find(',', index_symble12 + 1);
			istringstream iss_x_lower(dim.reference.substr(index_symble12 + 1, index_symble13 - index_symble12 - 1));
			iss_x_lower >> temp_refer.x_lower;
			//x_upper
			index_symble14 = dim.reference.find(']', index_symble13 + 1);
			istringstream iss_x_upper(dim.reference.substr(index_symble13 + 1, index_symble14 - index_symble13 - 1));
			iss_x_upper >> temp_refer.x_upper;

			// y_lower
			index_symble15 = dim.reference.find('[', index_symble14 + 1);
			index_symble16 = dim.reference.find(',', index_symble15 + 1);
			istringstream iss_y_lower(dim.reference.substr(index_symble15 + 1, index_symble16 - index_symble15 - 1));
			iss_y_lower >> temp_refer.y_lower;
			// y_upper
			index_symble17 = dim.reference.find(']', index_symble16 + 1);
			istringstream iss_y_upper(dim.reference.substr(index_symble16 + 1, index_symble17 - index_symble16 - 1));
			iss_y_upper >> temp_refer.y_upper;

			// z_lower
			index_symble18 = dim.reference.find('[', index_symble17 + 1);
			index_symble19 = dim.reference.find(',', index_symble18 + 1);
			istringstream iss_z_lower(dim.reference.substr(index_symble18 + 1, index_symble19 - index_symble18 - 1));
			iss_z_lower >> temp_refer.z_lower;
			// z_upper
			index_symble20 = dim.reference.find(']', index_symble19 + 1);
			istringstream iss_z_upper(dim.reference.substr(index_symble19 + 1, index_symble20 - index_symble19 - 1));
			iss_z_upper >> temp_refer.z_upper;

			temp_refer_dim.refer.push_back(temp_refer);

			//第二个
			index_symble21 = dim.reference.find(',', index_symble20 + 1);
			second = dim.reference.substr(index_symble21);

			//string refer_type
			index_symble1 = second.find('{', 0);
			temp_refer.refer_type = second.substr(1, index_symble1 - 1);

			//double radius;
			index_symble2 = second.find(',', index_symble1 + 1);
			istringstream iss_radius2(second.substr(index_symble1 + 1 + 6, index_symble2 - index_symble1 - 1 - 6));
			iss_radius2 >> temp_refer.radius_or_length;

			//	double height;
			index_symble3 = second.find(',', index_symble2 + 1);
			istringstream iss_height2(second.substr(index_symble2 + 1 + 6, index_symble3 - index_symble2 - 1 - 6));
			iss_height2 >> temp_refer.height_or_width;

			//	central_point centralPoint.x;
			index_symble4 = second.find('(', index_symble3 + 1);
			index_symble5 = second.find(',', index_symble4 + 1);
			istringstream iss_centralPoint_x2(second.substr(index_symble4 + 1, index_symble5 - index_symble4 - 1));
			iss_centralPoint_x2 >> temp_refer.centralPoint.x;
			//	central_point centralPoint.y;
			index_symble6 = second.find(',', index_symble5 + 1);
			istringstream iss_centralPoint_y2(second.substr(index_symble5 + 1, index_symble6 - index_symble5 - 1));
			iss_centralPoint_y2 >> temp_refer.centralPoint.y;
			//	central_point centralPoint.z;
			index_symble7 = second.find(')', index_symble6 + 1);
			istringstream iss_centralPoint_z2(second.substr(index_symble6 + 1, index_symble7 - index_symble6 - 1));
			iss_centralPoint_z2 >> temp_refer.centralPoint.z;

			//	central_point initialPoint.x;
			index_symble8 = second.find('(', index_symble7 + 1);
			index_symble9 = second.find(',', index_symble8 + 1);
			istringstream iss_initialPoint_x2(second.substr(index_symble8 + 1, index_symble9 - index_symble8 - 1));
			iss_initialPoint_x2 >> temp_refer.initialPoint.x;
			//	central_point initialPoint.y;
			index_symble10 = second.find(',', index_symble9 + 1);
			istringstream iss_initialPoint_y2(second.substr(index_symble9 + 1, index_symble10 - index_symble9 - 1));
			iss_initialPoint_y2 >> temp_refer.initialPoint.y;
			//	central_point initialPoint.z;
			index_symble11 = second.find(')', index_symble10 + 1);
			istringstream iss_initialPoint_z2(second.substr(index_symble10 + 1, index_symble11 - index_symble10 - 1));
			iss_initialPoint_z2 >> temp_refer.initialPoint.z;

			// x_lower
			index_symble12 = second.find('[', index_symble11 + 1);
			index_symble13 = second.find(',', index_symble12 + 1);
			istringstream iss_x_lower2(second.substr(index_symble12 + 1, index_symble13 - index_symble12 - 1));
			iss_x_lower2 >> temp_refer.x_lower;
			//x_upper
			index_symble14 = second.find(']', index_symble13 + 1);
			istringstream iss_x_upper2(second.substr(index_symble13 + 1, index_symble14 - index_symble13 - 1));
			iss_x_upper2 >> temp_refer.x_upper;

			// y_lower
			index_symble15 = second.find('[', index_symble14 + 1);
			index_symble16 = second.find(',', index_symble15 + 1);
			istringstream iss_y_lower2(second.substr(index_symble15 + 1, index_symble16 - index_symble15 - 1));
			iss_y_lower2 >> temp_refer.y_lower;
			// y_upper
			index_symble17 = second.find(']', index_symble16 + 1);
			istringstream iss_y_upper2(second.substr(index_symble16 + 1, index_symble17 - index_symble16 - 1));
			iss_y_upper2 >> temp_refer.y_upper;

			// z_lower
			index_symble18 = second.find('[', index_symble17 + 1);
			index_symble19 = second.find(',', index_symble18 + 1);
			istringstream iss_z_lower2(second.substr(index_symble18 + 1, index_symble19 - index_symble18 - 1));
			iss_z_lower2 >> temp_refer.z_lower;
			// z_upper
			index_symble20 = second.find(']', index_symble19 + 1);
			istringstream iss_z_upper2(second.substr(index_symble19 + 1, index_symble20 - index_symble19 - 1));
			iss_z_upper2 >> temp_refer.z_upper;

			temp_refer_dim.refer.push_back(temp_refer);
		}

		vec_refer_dim.push_back(temp_refer_dim);
	}
}


DimReader::~DimReader()
{
}
