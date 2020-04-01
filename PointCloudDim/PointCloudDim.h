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
	PointCloudDim(QWidget *parent = Q_NULLPTR);	//���캯��
	void changeDir();							//�л�����Ŀ¼
	void importSourcePointCloud();				//����Դ����
	void importTargetPointCloud();				//����Ŀ�����
	void calculateFPFH();						//����Դ������Ŀ�����FPFH
	void registration();						//��׼
	void dimemsionCalculation();				//�ߴ����
	void resultOutput();						//����ߴ���Ϣ



private:
	Ui::PointCloudDimClass ui;

	typedef pcl::PointXYZ PointT;
	typedef pcl::PointCloud<PointT> PointCloudT;

	QString file_path;	//����Ŀ¼

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerSource;		//����QVTK����  1��Դ����QVTK����
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerTarget;		//����QVTK����  2��Ŀ�����QVTK����
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerUnRegistered;//����QVTK����  3��δ��׼����QVTK����
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerRegistered;	//����QVTK����  4����׼����QVTK����
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewerDimInfo;		//����QVTK����  5�����Ƴߴ�QVTK����

	//�����Ƿ��״ε����־
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
