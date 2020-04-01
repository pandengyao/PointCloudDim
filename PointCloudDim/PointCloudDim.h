#pragma once
#include <iostream>
#include <QtWidgets/QMainWindow>
#include "ui_PointCloudDim.h"
#include "Point.h"
#include "PlaneEquation.h"
#include "DimCalculate.h"
#include "DimReader.h"
#include <vector>
#include <string>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
using namespace std;

class PointCloudDim : public QMainWindow
{
	Q_OBJECT

public:
	PointCloudDim(QWidget *parent = Q_NULLPTR);	//构造函数
	void changeDir();							//切换工作目录
	void importSourcePointCloud();				//导入源点云
	void importTargetPointCloud();				//导入目标点云
	void calculateFPFH();						//计算源点云与目标点云FPFH
	void registration();						//配准
	void dimemsionCalculation();				//尺寸计算
	void resultOutput();						//保存尺寸信息



private:
	Ui::PointCloudDimClass ui;

	typedef pcl::PointXYZ PointT;
	typedef pcl::PointCloud<PointT> PointCloudT;

	QString file_path;	//工作目录

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerSource;		//创建QVTK窗口  1、源点云QVTK窗口
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerTarget;		//创建QVTK窗口  2、目标点云QVTK窗口
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerUnRegistered;//创建QVTK窗口  3、未配准点云QVTK窗口
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerRegistered;	//创建QVTK窗口  4、配准点云QVTK窗口
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerDimInfo;		//创建QVTK窗口  5、点云尺寸QVTK窗口

	//点云是否首次导入标志
	bool addSourceFlag;
	bool addTargetFlag;
	bool addRegisteredFlag;
	bool addResultFlag;

	struct output_res {
		string dim_symbol;
		double theoretical_value;
		double measured_value;
		double error;
	};
	vector<output_res> output_res_vec;

	vector<pcl::PointCloud<PointT>::Ptr> vec_cloud;
	vector<string> vec_name;
};
