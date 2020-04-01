#include "PointCloudDim.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>  
#include <QPushButton>
#include <QMenuBar>
#include <QToolBar>
#include <QSpinBox>
#include <QLabel>
#include <QTextBrowser>
#include <QFileInfo>
#include <vector>
#include <cmath>
#include <ctime>
#include "windows.h"
#include  <stdio.h>
#include  <io.h>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/search/kdtree.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/filter.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/fpfh.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>
#include "app.h"
#include "DimReader.h"
//解决中文路径问题
#include <qtextcodec.h>

using namespace std;
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题

//创建点云对象
PointCloudT::Ptr cloudSource(new PointCloudT);
//创建点云对象
PointCloudT::Ptr cloudTarget(new PointCloudT);
//已配准的点云
PointCloudT::Ptr cloudRegistered(new PointCloudT);

PointCloudDim::PointCloudDim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(u8"点云尺寸测量");

	QDir dir;
	dir.mkdir("workspace");
	file_path = QDir::currentPath();
	file_path += "/workspace";
	ui.textBrowser->append(u8"工作目录为：" + file_path);

	addSourceFlag = true;
	addTargetFlag = true;
	addRegisteredFlag = true;
	addResultFlag = true;

	/********************************************************************************************************/
	//创建QVTK窗口  1、源点云QVTK窗口
	viewerSource.reset(new pcl::visualization::PCLVisualizer("viewerSource", false));
	ui.qvtkWidgetSource->SetRenderWindow(viewerSource->getRenderWindow());
	viewerSource->setupInteractor(ui.qvtkWidgetSource->GetInteractor(), ui.qvtkWidgetSource->GetRenderWindow());
	ui.qvtkWidgetSource->update();

	//创建QVTK窗口  2、目标点云QVTK窗口
	viewerTarget.reset(new pcl::visualization::PCLVisualizer("viewerTarget", false));
	ui.qvtkWidgetTarget->SetRenderWindow(viewerTarget->getRenderWindow());
	viewerTarget->setupInteractor(ui.qvtkWidgetTarget->GetInteractor(), ui.qvtkWidgetTarget->GetRenderWindow());
	ui.qvtkWidgetTarget->update();

	//创建QVTK窗口  3、未配准点云QVTK窗口
	viewerUnRegistered.reset(new pcl::visualization::PCLVisualizer("viewerUnRegistered", false));
	ui.qvtkWidgetUnRegistered->SetRenderWindow(viewerUnRegistered->getRenderWindow());
	viewerUnRegistered->setupInteractor(ui.qvtkWidgetUnRegistered->GetInteractor(), ui.qvtkWidgetUnRegistered->GetRenderWindow());
	ui.qvtkWidgetUnRegistered->update();

	//创建QVTK窗口  4、配准点云QVTK窗口
	viewerRegistered.reset(new pcl::visualization::PCLVisualizer("viewerRegistered", false));
	ui.qvtkWidgetRegistered->SetRenderWindow(viewerRegistered->getRenderWindow());
	viewerRegistered->setupInteractor(ui.qvtkWidgetRegistered->GetInteractor(), ui.qvtkWidgetRegistered->GetRenderWindow());
	ui.qvtkWidgetRegistered->update();

	//创建QVTK窗口  5、点云尺寸QVTK窗口
	viewerDimInfo.reset(new pcl::visualization::PCLVisualizer("viewerDimInfo", false));
	ui.qvtkWidgetDimInfo->SetRenderWindow(viewerDimInfo->getRenderWindow());
	viewerDimInfo->setupInteractor(ui.qvtkWidgetDimInfo->GetInteractor(), ui.qvtkWidgetDimInfo->GetRenderWindow());
	ui.qvtkWidgetDimInfo->update();

	QWidget::setWindowState(Qt::WindowMaximized);



	/********************************************************************************************************/
	//切换工作目录
	connect(ui.action_change_dir, &QAction::triggered, [=]() {
		changeDir();
	});

	/********************************************************************************************************/
	//点击关闭按钮，关闭窗口
	connect(ui.actionClose, &QAction::triggered, this, &QWidget::close);

	/********************************************************************************************************/
	//点击帮助按钮，查看使用说明
	connect(ui.actionHelp, &QAction::triggered, [=]() {
		QMessageBox::warning(this, u8"使用说明", u8"1、点击文件菜单，导入源点云\n 2、点击文件菜单，导入目标点云\n 3、调整滤波器体素、法线半径、FPFH半径，点击计算\n 4、点击配准\n 5、调整尺寸测量的5个参数，点击尺寸测量\n 6、点击结果导出\n\n 每一步处理结束右下角均有状态显示");
	});

	/********************************************************************************************************/
	//点击窗口按钮，最大化、最小化、还原
	connect(ui.actionMaximized, &QAction::triggered, this, &QWidget::showMaximized);
	connect(ui.actionMinimized, &QAction::triggered, this, &QWidget::showMinimized);
	connect(ui.actionNormal, &QAction::triggered, this, &QWidget::showNormal);

	/********************************************************************************************************/
	//点击编辑按钮，采样、法线、FPFH、尺寸测量，结果导出
	connect(ui.actionFPFHCalculate, &QAction::triggered, ui.pushButtonFPFHCalculate, &QPushButton::clicked);
	connect(ui.actionRegister, &QAction::triggered, ui.pushButtonRegister, &QPushButton::clicked);
	connect(ui.actionDim, &QAction::triggered, ui.pushButtonDim, &QPushButton::clicked);
	connect(ui.actionOutput, &QAction::triggered, ui.pushButtonOutput, &QPushButton::clicked);

	//1、点击导入源点云按钮，选择文件
	connect(ui.actionImportSource, &QAction::triggered, [=]() {
		importSourcePointCloud();
	});

	/********************************************************************************************************/
	//2、点击导入目标点云按钮，选择文件
	connect(ui.actionImportTarget, &QAction::triggered, [=]() {
		importTargetPointCloud();
	});

	/********************************************************************************************************/
	//计算FPFH
	ui.doubleSpinBoxVoxelGrid->setValue(3);
	ui.doubleSpinBoxNormalRadius->setValue(30);
	ui.doubleSpinBoxFPFHRadius->setValue(40);

	connect(ui.pushButtonFPFHCalculate, &QPushButton::clicked, [=]() {
		calculateFPFH();
	});

	/********************************************************************************************************/
	//配准
	connect(ui.pushButtonRegister, &QPushButton::clicked, [=]() {
		registration();
	});

	/********************************************************************************************************/
	//尺寸测量
	ui.doubleSpinBoxPlane->setValue(0.1);
	ui.doubleSpinBoxCylinder->setValue(0.05);
	ui.spinBoxkSearch->setValue(10);
	ui.doubleSpinBoxNormalWeight->setValue(0.1);
	ui.spinBoxMaxIterations->setValue(10000);

	connect(ui.pushButtonDim, &QPushButton::clicked, [=]() {
		vec_cloud.clear();
		output_res_vec.clear();
		vec_name.clear();

		dimemsionCalculation();
	});

	/************************************************************************************************/
	//输出尺寸测量结果文件
	connect(ui.pushButtonOutput, &QPushButton::clicked, [=]() {
		resultOutput();
	});
}




void PointCloudDim::changeDir()
{
	QString file_path_change = QFileDialog::getExistingDirectory(this, u8"首先请选择工作目录", "./");

	if (file_path_change.isEmpty())
	{
		QMessageBox::warning(this, u8"打开失败", u8"工作目录路径为空，请重新选择");
		return;
	}
	else {
		ui.textBrowser->append(u8"工作路径为：" + file_path_change);
	}

	file_path = file_path_change;
}


void PointCloudDim::importSourcePointCloud()
{
	if (addSourceFlag) {
		addSourceFlag = false;

		QString fileSourcePath = QFileDialog::getOpenFileName(this, u8"选择文件", file_path);

		if (fileSourcePath.isEmpty()) {
			QMessageBox::warning(this, u8"打开失败", u8"文件路径为空");
			return;
		}

		string fileSourceName = fileSourcePath.toStdString();

		//读取点云数据
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileSourceName, *cloudSource) == -1) //* load the file
		{
			QMessageBox::warning(this, u8"打开失败", u8"请重新选择文件");
			return;
		}

		//打印点数量信息
		QString str_source = QString::number(cloudSource->width * cloudSource->height);
		QFileInfo info_souce(fileSourcePath);
		ui.textBrowser->append("Loaded " + str_source + " data points from " + info_souce.fileName());

		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_source(cloudSource, 255, 0, 0);
		viewerSource->addPointCloud(cloudSource, cloud_source, "cloudSource");
		viewerSource->resetCamera();
		ui.qvtkWidgetSource->update();

		viewerUnRegistered->addPointCloud(cloudSource, cloud_source, "cloudSource");
		viewerUnRegistered->resetCamera();
		ui.qvtkWidgetUnRegistered->update();
	}
	else {

		QString fileSourcePath = QFileDialog::getOpenFileName(this, u8"选择文件", file_path);

		if (fileSourcePath.isEmpty()) {
			QMessageBox::warning(this, u8"打开失败", u8"文件路径为空");
			return;
		}

		string fileSourceName = fileSourcePath.toStdString();

		//读取点云数据
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileSourceName, *cloudSource) == -1) //* load the file
		{
			QMessageBox::warning(this, u8"打开失败", u8"请重新选择文件");
			return;
		}

		//打印点数量信息
		QString str_source = QString::number(cloudSource->width * cloudSource->height);
		QFileInfo info_souce(fileSourcePath);
		ui.textBrowser->append("Loaded " + str_source + " data points from " + info_souce.fileName());

		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_source(cloudSource, 255, 0, 0);
		viewerSource->updatePointCloud(cloudSource, cloud_source, "cloudSource");
		viewerSource->resetCamera();
		ui.qvtkWidgetSource->update();

		viewerUnRegistered->updatePointCloud(cloudSource, cloud_source, "cloudSource");
		viewerUnRegistered->resetCamera();
		ui.qvtkWidgetUnRegistered->update();
	}
}


void PointCloudDim::importTargetPointCloud()
{
	if (addTargetFlag) {
		addTargetFlag = false;

		QString fileTargetPath = QFileDialog::getOpenFileName(this, u8"选择文件", file_path);

		if (fileTargetPath.isEmpty()) {
			QMessageBox::warning(this, u8"打开失败", u8"文件路径为空");
			return;
		}

		string fileTargetName = fileTargetPath.toStdString();

		//读取点云数据
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileTargetName, *cloudTarget) == -1) //* load the file
		{
			QMessageBox::warning(this, u8"打开失败", u8"请重新选择文件");
			return;
		}

		//打印点数量信息
		QString str_target = QString::number(cloudTarget->width * cloudTarget->height);
		QFileInfo info_target(fileTargetPath);
		ui.textBrowser->append("Loaded " + str_target + " data points from " + info_target.fileName());

		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target(cloudTarget, 0, 255, 0);
		viewerTarget->addPointCloud(cloudTarget, cloud_target, "cloudTarget");
		viewerTarget->resetCamera();
		//viewerSource->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudSource");
		ui.qvtkWidgetTarget->update();

		viewerUnRegistered->addPointCloud(cloudTarget, cloud_target, "cloudTarget");
		viewerUnRegistered->resetCamera();
		//viewerUnRegistered->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudUnRegistered");
		ui.qvtkWidgetUnRegistered->update();
	}
	else {
		QString fileTargetPath = QFileDialog::getOpenFileName(this, u8"选择文件", file_path);

		if (fileTargetPath.isEmpty()) {
			QMessageBox::warning(this, u8"打开失败", u8"文件路径为空");
			return;
		}

		string fileTargetName = fileTargetPath.toStdString();

		//读取点云数据
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileTargetName, *cloudTarget) == -1) //* load the file
		{
			QMessageBox::warning(this, u8"打开失败", u8"请重新选择文件");
			return;
		}

		//打印点数量信息
		QString str_target = QString::number(cloudTarget->width * cloudTarget->height);
		QFileInfo info_target(fileTargetPath);
		ui.textBrowser->append("Loaded " + str_target + " data points from " + info_target.fileName());

		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target(cloudTarget, 0, 255, 0);
		viewerTarget->updatePointCloud(cloudTarget, cloud_target, "cloudTarget");
		viewerTarget->resetCamera();
		//viewerSource->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudSource");
		ui.qvtkWidgetTarget->update();

		viewerUnRegistered->updatePointCloud(cloudTarget, cloud_target, "cloudTarget");
		viewerUnRegistered->resetCamera();
		//viewerUnRegistered->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudUnRegistered");
		ui.qvtkWidgetUnRegistered->update();
	}
}


void PointCloudDim::calculateFPFH()
{
	//判断点云是否导入
	if (cloudSource->size() == 0) {
		QMessageBox::warning(this, u8"计算失败", u8"源点云未导入或导入的点云无效\n\n 请点击文件按钮导入源点云");
		return;
	}

	if (cloudTarget->size() == 0) {
		QMessageBox::warning(this, u8"计算失败", u8"目标点云未导入或导入的点云无效\n\n 请点击文件按钮导入目标点云");
		return;
	}

	//获得设置的 采样网格大小、法线半径、FPFH半径 3个参数
	double voxelGridOfLeafSize = ui.doubleSpinBoxVoxelGrid->value();
	double normalRadiusSearch = ui.doubleSpinBoxNormalRadius->value();
	double FPFHRadiusSearch = ui.doubleSpinBoxFPFHRadius->value();

	//对参数进行合法性判断
	if (normalRadiusSearch == 0.0) {
		QMessageBox::warning(this, u8"计算失败", u8"请输入计算法线的半径参数");
		return;
	}

	if (FPFHRadiusSearch == 0.0) {
		QMessageBox::warning(this, u8"计算失败", u8"请输入计算FPFH的半径参数");
		return;
	}

	if (FPFHRadiusSearch < normalRadiusSearch) {
		QMessageBox::warning(this, u8"计算失败", u8"FPFH的半径参数需大于等于法线半径参数");
		return;
	}

	//************************1、计算源点云FPFH信息********************************************************
	//去除NAN点
	vector<int> indices_src; //保存去除的点的索引
	pcl::removeNaNFromPointCloud(*cloudSource, *cloudSource, indices_src);
	ui.textBrowser->append("remove *cloudSource nan");

	//下采样滤波
	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid_source;
	//voxel_grid.setLeafSize(0.012,0.012,0.012);
	voxel_grid_source.setLeafSize(voxelGridOfLeafSize, voxelGridOfLeafSize, voxelGridOfLeafSize);
	voxel_grid_source.setInputCloud(cloudSource);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src(new pcl::PointCloud<pcl::PointXYZ>);
	voxel_grid_source.filter(*cloud_src);
	QString cloudSource_size = QString::number(cloudSource->size());
	QString cloud_src_size = QString::number(cloud_src->size());
	ui.textBrowser->append("down sampling cloudSource from " + cloudSource_size + " to " + cloud_src_size);

	// Create the normal estimation class, and pass the input dataset to it
	pcl::NormalEstimation <pcl::PointXYZ, pcl::Normal> ne_src;
	ne_src.setInputCloud(cloud_src);

	// Create an empty kdtree representation, and pass it to the normal estimation object.
	// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree_src(new pcl::search::KdTree<pcl::PointXYZ>());
	ne_src.setSearchMethod(tree_src);

	// Output datasets
	pcl::PointCloud<pcl::Normal>::Ptr normals_src(new pcl::PointCloud<pcl::Normal>);

	// Use all neighbors in a sphere of radius 3cm
	ne_src.setRadiusSearch(normalRadiusSearch);

	// Compute the features
	ne_src.compute(*normals_src);

	QString normals_src_size = QString::number(normals_src->points.size());
	ui.textBrowser->append("the size of normals_src is " + normals_src_size);
	// cloud_normals->points.size () should have the same size as the input cloud->points.size ()*

	//创建FPFH估计对象fpfh，并把输入数据集cloud和法线normals传递给它。

	pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_src;

	fpfh_src.setInputCloud(cloud_src);
	fpfh_src.setInputNormals(normals_src);

	//如果点云类型为PointNormal，则执行fpfh.setInputNormals (cloud);

	//创建一个空的kd树对象tree，并把它传递给FPFH估计对象。

	//基于已知的输入数据集，建立kdtree

	pcl::search::KdTree<pcl::PointXYZ>::Ptr fpfhs_tree_src(new pcl::search::KdTree<pcl::PointXYZ>());

	fpfh_src.setSearchMethod(fpfhs_tree_src);

	//输出数据集

	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs_src(new pcl::PointCloud<pcl::FPFHSignature33>());

	//使用所有半径在5厘米范围内的邻元素

	//注意：此处使用的半径必须要大于估计表面法线时使用的半径!!!

	fpfh_src.setRadiusSearch(FPFHRadiusSearch);

	//计算获取特征向量

	fpfh_src.compute(*fpfhs_src);

	QString fpfhs_src_size = QString::number(fpfhs_src->points.size());
	ui.textBrowser->append("the size of fpfhs_src is " + fpfhs_src_size);
	// fpfhs_src->points.size ()应该和input cloudSource->points.size ()有相同的大小，即每个点有一个特征向量

	QByteArray ba_src = (file_path + "/fpfhs_src.bin").toLatin1();
	const char *fpfhs_src_filename = ba_src.data();

	FILE* fid_src = fopen(fpfhs_src_filename, "wb");
	int nV_src = cloud_src->size(), nDim_src = 33;
	fwrite(&nV_src, sizeof(int), 1, fid_src);
	fwrite(&nDim_src, sizeof(int), 1, fid_src);

	for (int v = 0; v < nV_src; v++) {
		const pcl::PointXYZ &pt_src = cloud_src->points[v];
		float xyz_src[3] = { pt_src.x, pt_src.y, pt_src.z };
		fwrite(xyz_src, sizeof(float), 3, fid_src);
		const pcl::FPFHSignature33 &feature_src = fpfhs_src->points[v];
		fwrite(feature_src.histogram, sizeof(float), 33, fid_src);
	}
	fclose(fid_src);


	//************************2、计算目标点云FPFH信息********************************************************
	//去除NAN点
	vector<int> indices_tgt; //保存去除的点的索引
	pcl::removeNaNFromPointCloud(*cloudTarget, *cloudTarget, indices_tgt);
	ui.textBrowser->append("remove *cloudTarget nan");

	//下采样滤波
	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid_target;
	//voxel_grid.setLeafSize(0.012,0.012,0.012);
	voxel_grid_target.setLeafSize(voxelGridOfLeafSize, voxelGridOfLeafSize, voxelGridOfLeafSize);
	voxel_grid_target.setInputCloud(cloudTarget);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tgt(new pcl::PointCloud<pcl::PointXYZ>);
	voxel_grid_target.filter(*cloud_tgt);
	QString cloudTarget_size = QString::number(cloudTarget->size());
	QString cloud_tgt_size = QString::number(cloud_tgt->size());
	ui.textBrowser->append("down sampling cloudTarget from " + cloudTarget_size + " to " + cloud_tgt_size);

	// Create the normal estimation class, and pass the input dataset to it
	pcl::NormalEstimation <pcl::PointXYZ, pcl::Normal> ne_tgt;
	ne_tgt.setInputCloud(cloud_tgt);

	// Create an empty kdtree representation, and pass it to the normal estimation object.
	// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree_tgt(new pcl::search::KdTree<pcl::PointXYZ>());
	ne_tgt.setSearchMethod(tree_tgt);

	// Output datasets
	pcl::PointCloud<pcl::Normal>::Ptr normals_tgt(new pcl::PointCloud<pcl::Normal>);

	// Use all neighbors in a sphere of radius 3cm
	ne_tgt.setRadiusSearch(normalRadiusSearch);

	// Compute the features
	ne_tgt.compute(*normals_tgt);

	QString normals_tgt_size = QString::number(normals_tgt->points.size());
	ui.textBrowser->append("the size of normals_tgt is " + normals_tgt_size);
	// cloud_normals->points.size () should have the same size as the input cloud->points.size ()*

	//创建FPFH估计对象fpfh，并把输入数据集cloud和法线normals传递给它。

	pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_tgt;

	fpfh_tgt.setInputCloud(cloud_tgt);
	fpfh_tgt.setInputNormals(normals_tgt);

	//如果点云类型为PointNormal，则执行fpfh.setInputNormals (cloud);

	//创建一个空的kd树对象tree，并把它传递给FPFH估计对象。

	//基于已知的输入数据集，建立kdtree

	pcl::search::KdTree<pcl::PointXYZ>::Ptr fpfhs_tree_tgt(new pcl::search::KdTree<pcl::PointXYZ>());

	fpfh_src.setSearchMethod(fpfhs_tree_tgt);

	//输出数据集

	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs_tgt(new pcl::PointCloud<pcl::FPFHSignature33>());

	//使用所有半径在5厘米范围内的邻元素

	//注意：此处使用的半径必须要大于估计表面法线时使用的半径!!!

	fpfh_tgt.setRadiusSearch(FPFHRadiusSearch);

	//计算获取特征向量

	fpfh_tgt.compute(*fpfhs_tgt);

	QString fpfhs_tgt_size = QString::number(fpfhs_tgt->points.size());
	ui.textBrowser->append("the size of fpfhs_tgt is " + fpfhs_tgt_size);
	// fpfhs_src->points.size ()应该和input cloudSource->points.size ()有相同的大小，即每个点有一个特征向量


	/*
		size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
		-- buffer:指向数据块的指针
		-- size:每个数据的大小，单位为Byte(例如：sizeof(int)就是4)
		-- count:数据个数
		-- stream:文件指针
	*/

	QByteArray ba_tgt = (file_path + "/fpfhs_tgt.bin").toLatin1();
	const char *fpfhs_tgt_filename = ba_tgt.data();

	FILE* fid_tgt = fopen(fpfhs_tgt_filename, "wb");
	int nV_tgt = cloud_tgt->size(), nDim_tgt = 33;
	fwrite(&nV_tgt, sizeof(int), 1, fid_tgt);
	fwrite(&nDim_tgt, sizeof(int), 1, fid_tgt);

	for (int v = 0; v < nV_tgt; v++) {
		const pcl::PointXYZ &pt_tgt = cloud_tgt->points[v];
		float xyz_tgt[3] = { pt_tgt.x, pt_tgt.y, pt_tgt.z };
		fwrite(xyz_tgt, sizeof(float), 3, fid_tgt);
		const pcl::FPFHSignature33 &feature_tgt = fpfhs_tgt->points[v];
		fwrite(feature_tgt.histogram, sizeof(float), 33, fid_tgt);
	}
	fclose(fid_tgt);


	//输出计算完成提示信息
	ui.textBrowser->append("*****************************************");
	ui.textBrowser->append(u8"快速点特征直方图FPFH计算完成");
	ui.textBrowser->append("*****************************************");
}


void PointCloudDim::registration()
{
	//判断点云是否导入
	if (cloudSource->size() == 0) {
		QMessageBox::warning(this, u8"计算失败", u8"源点云未导入或导入的点云无效\n\n 请点击文件按钮导入源点云");
		return;
	}

	if (cloudTarget->size() == 0) {
		QMessageBox::warning(this, u8"计算失败", u8"目标点云未导入或导入的点云无效\n\n 请点击文件按钮导入目标点云");
		return;
	}

	fgr::CApp app;

	QByteArray ba_tgt = (file_path + "/fpfhs_tgt.bin").toLatin1();
	const char *fpfhs_tgt_filename = ba_tgt.data();
	//判断fpfhs_tgt文件是否存在
	if (_access(fpfhs_tgt_filename, 0) == -1)
	{
		QMessageBox::warning(this, u8"配准失败", u8"请先计算FPFH");
		return;
	}
	app.ReadFeature(fpfhs_tgt_filename);

	QByteArray ba_src = (file_path + "/fpfhs_src.bin").toLatin1();
	const char *fpfhs_src_filename = ba_src.data();
	//判断fpfhs_src文件是否存在
	if (_access(fpfhs_src_filename, 0) == -1)
	{
		QMessageBox::warning(this, u8"配准失败", u8"请先计算FPFH");
		return;
	}
	app.ReadFeature(fpfhs_src_filename);

	app.NormalizePoints();
	app.AdvancedMatching();
	app.OptimizePairwise(true);
	QByteArray ba_transformMatrix = (file_path + "/FGR_transformMatrix.txt").toLatin1();
	const char *transformMatrix_filename = ba_transformMatrix.data();
	app.WriteTrans(transformMatrix_filename);

	//打印旋转平移矩阵
	ui.textBrowser->append(u8"FGR算法配准后旋转平移矩阵为：");
	ifstream infile;
	infile.open(transformMatrix_filename, ifstream::in);

	string line; //按行读取
	Eigen::Matrix4f transformMatrix;

	getline(infile, line); //跳过第一行
	int row = 0;
	while (getline(infile, line))
	{
		ui.textBrowser->append(QString::fromStdString(line));
		istringstream is(line);
		string s;
		int column = 0;
		while (is >> s)
		{
			transformMatrix(row, column) = stod(s);
			++column;
		}
		++row;
	}

	//icp配准
	PointCloudT::Ptr icp_result(new PointCloudT);
	pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	icp.setInputSource(cloudSource);
	icp.setInputTarget(cloudTarget);
	//Set the max correspondence distance to 4cm 
	//(e.g., correspondences with higher distances will be ignored)
	icp.setMaxCorrespondenceDistance(6);
	// 最大迭代次数
	icp.setMaximumIterations(1000000);
	// 两次变化矩阵之间的差值
	icp.setTransformationEpsilon(1e-20);
	// 均方误差
	icp.setEuclideanFitnessEpsilon(0.01);

	icp.align(*icp_result, transformMatrix);


	Eigen::Matrix4f icp_trans;
	icp_trans = icp.getFinalTransformation();

	//使用创建的变换对未过滤的输入点云进行变换
	pcl::transformPointCloud(*cloudSource, *cloudRegistered, icp_trans);
	//保存转换的输入点云
	QByteArray ba_transformed = (file_path + "/transformed.pcd").toLatin1();
	const char* transformed_filename = ba_transformed.data();
	pcl::io::savePCDFileASCII(transformed_filename, *cloudRegistered);

	QByteArray icp_ba_transformMatrix = (file_path + "/icp_transformMatrix.txt").toLatin1();
	const char *icp_transformMatrix_filename = icp_ba_transformMatrix.data();

	//打开要输入的文件
	ofstream oFile;
	oFile.open(icp_transformMatrix_filename);
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			oFile << icp_trans(r, c) << " ";
		}
		oFile << endl;
	}

	oFile.close();


	//打印旋转平移矩阵
	ui.textBrowser->append(u8"ICP算法配准后旋转平移矩阵为：");
	ifstream icp_infile;
	icp_infile.open(icp_transformMatrix_filename, ifstream::in);

	string icp_line; //按行读取
	Eigen::Matrix4f icp_transformMatrix;

	row = 0;
	while (getline(icp_infile, icp_line))
	{
		ui.textBrowser->append(QString::fromStdString(icp_line));
		istringstream is(icp_line);
		string s;
		int column = 0;
		while (is >> s)
		{
			icp_transformMatrix(row, column) = stod(s);
			++column;
		}
		++row;
	}

	//点云显示
	if (addRegisteredFlag) {
		addRegisteredFlag = false;
		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target(cloudTarget, 0, 255, 0);
		viewerRegistered->addPointCloud(cloudTarget, cloud_target, "cloudTarget");
		//viewerSource->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudSource");

		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_registered(cloudRegistered, 255, 0, 0);
		viewerRegistered->addPointCloud(cloudRegistered, cloud_registered, "cloudRegistered");
		viewerRegistered->resetCamera();
		//viewerUnRegistered->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudUnRegistered");
		ui.qvtkWidgetRegistered->update();
	}
	else {
		//点云显示
		//设置颜色
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target(cloudTarget, 0, 255, 0);
		viewerRegistered->updatePointCloud(cloudTarget, cloud_target, "cloudTarget");
		//viewerSource->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudSource");

		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_registered(cloudRegistered, 255, 0, 0);
		viewerRegistered->updatePointCloud(cloudRegistered, cloud_registered, "cloudRegistered");
		viewerRegistered->resetCamera();
		//viewerUnRegistered->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloudUnRegistered");
		ui.qvtkWidgetRegistered->update();
	}

	//输出配准完成提示信息
	ui.textBrowser->append("*****************************************");
	ui.textBrowser->append(u8"点云配准完成");
	ui.textBrowser->append("*****************************************");
}


void PointCloudDim::dimemsionCalculation()
{
	vec_cloud.clear();
	output_res_vec.clear();
	vec_name.clear();

	//获得设置的 采样平面提取gap 圆柱面提取gap 2个参数
	double disThreshold_plane = ui.doubleSpinBoxPlane->value();
	double disThreshold_radius = ui.doubleSpinBoxCylinder->value();
	int k_search = ui.spinBoxkSearch->value();
	double normal_distance_Weight = ui.doubleSpinBoxNormalWeight->value();
	int max_iterations = ui.spinBoxMaxIterations->value();

	//对参数进行合法性判断
	if (disThreshold_plane == 0.0) {
		QMessageBox::warning(this, u8"计算失败", u8"请输入平面提取gap");
		return;
	}

	if (disThreshold_radius == 0.0) {
		QMessageBox::warning(this, u8"计算失败", u8"请输入圆柱面提取gap");
		return;
	}

	//导入尺寸信息文件
	QString fileSourcePath = QFileDialog::getOpenFileName(this, u8"选择尺寸信息文件", file_path);

	if (fileSourcePath.isEmpty()) {
		QMessageBox::warning(this, u8"打开失败", u8"文件路径为空");
		return;
	}
	string fileSourceName = fileSourcePath.toStdString();

	DimReader dimReader(fileSourceName);


	/*****************************************************************************************/
	//尺寸测量部分
	for (auto dim : dimReader.vec_refer_dim) {

		output_res output_res_str;
		vec_name.push_back(dim.dimSymbol);

		//定义对象
		pcl::PCDReader reader;
		pcl::PassThrough<PointT> pass;
		pcl::NormalEstimation<PointT, pcl::Normal> ne;
		pcl::SACSegmentationFromNormals<PointT, pcl::Normal> seg;
		pcl::PCDWriter writer;
		pcl::ExtractIndices<PointT> extract;
		pcl::ExtractIndices<pcl::Normal> extract_normals;
		pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());

		// Datasets
		//定义在程序中用到的 数据对象、点类型、法线类型 的点云对象以及 模型系数 等，
		//以及存储平面上 内点的 点索引集合对象
		pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
		pcl::PointCloud<PointT>::Ptr cloud_filtered(new pcl::PointCloud<PointT>);
		pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
		pcl::PointCloud<PointT>::Ptr cloud_filtered2(new pcl::PointCloud<PointT>);
		pcl::PointCloud<pcl::Normal>::Ptr cloud_normals2(new pcl::PointCloud<pcl::Normal>);
		pcl::ModelCoefficients::Ptr coefficients_plane(new pcl::ModelCoefficients), coefficients_cylinder(new pcl::ModelCoefficients);
		pcl::PointIndices::Ptr inliers_plane(new pcl::PointIndices), inliers_cylinder(new pcl::PointIndices);
		pcl::ModelCoefficients::Ptr coefficients_plane2(new pcl::ModelCoefficients), coefficients_cylinder2(new pcl::ModelCoefficients);
		pcl::PointIndices::Ptr inliers_plane2(new pcl::PointIndices), inliers_cylinder2(new pcl::PointIndices);

		// Read in the cloud data
		//完成对点云数据的读取
		QByteArray ba_transformed = (file_path + "/transformed.pcd").toLatin1();
		const char* transformed_filename = ba_transformed.data();
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(transformed_filename, *cloud) == -1) //* load the file
		{
			QMessageBox::warning(this, u8"打开失败", u8"请先进行点云配准");
			return;
		}

		if (dim.dimType == "DIMTYPE_RADIUS") {

			//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
			pass.setInputCloud(cloud);

			pass.setFilterFieldName("x");
			pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
			pass.filter(*cloud_filtered);

			pass.setInputCloud(cloud_filtered);
			pass.setFilterFieldName("y");
			pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
			pass.filter(*cloud_filtered);

			pass.setInputCloud(cloud_filtered);
			pass.setFilterFieldName("z");
			pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
			pass.filter(*cloud_filtered);

			// Estimate point normals
			//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
			ne.setSearchMethod(tree);
			ne.setInputCloud(cloud_filtered);
			ne.setKSearch(k_search);
			//ne.setRadiusSearch(5);
			ne.compute(*cloud_normals);

			// Create the segmentation object for cylinder segmentation and set all the parameters
			//为圆柱体分割创建分割对象，并设置所有参数
			seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
			seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
			seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
			seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数0.1
			seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
			seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
														//距离阈值（离散点到模型表面距离）
			double radius = dim.refer[0].radius_or_length;
			seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
			seg.setInputCloud(cloud_filtered);
			seg.setInputNormals(cloud_normals);

			// Obtain the cylinder inliers and coefficients
			//获得圆柱体参数和处在圆柱体表面上的内点
			seg.segment(*inliers_cylinder, *coefficients_cylinder);

			// Write the cylinder inliers to disk
			//保存圆柱体表面上的内点到磁盘上
			extract.setInputCloud(cloud_filtered);
			extract.setIndices(inliers_cylinder);
			extract.setNegative(false);
			pcl::PointCloud<PointT>::Ptr cloud_cylinder(new pcl::PointCloud<PointT>());
			extract.filter(*cloud_cylinder);

			vec_cloud.push_back(cloud_cylinder);

			output_res_str.dim_symbol = dim.dimSymbol;
			output_res_str.theoretical_value = dim.refer[0].radius_or_length;
			output_res_str.measured_value = coefficients_cylinder->values[6];
			output_res_str.error = (int)(abs(dim.refer[0].radius_or_length - coefficients_cylinder->values[6])
				* 10000 + 0.5) / 10000.0;

			output_res_vec.push_back(output_res_str);
		}

		else if (dim.dimType == "DIMTYPE_DIAMETER") {

			//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
			pass.setInputCloud(cloud);

			pass.setFilterFieldName("x");
			pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
			pass.filter(*cloud_filtered);

			pass.setInputCloud(cloud_filtered);
			pass.setFilterFieldName("y");
			pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
			pass.filter(*cloud_filtered);

			pass.setInputCloud(cloud_filtered);
			pass.setFilterFieldName("z");
			pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
			pass.filter(*cloud_filtered);

			// Estimate point normals
			//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
			ne.setSearchMethod(tree);
			ne.setInputCloud(cloud_filtered);
			ne.setKSearch(k_search);
			//ne.setRadiusSearch(5);
			ne.compute(*cloud_normals);

			// Create the segmentation object for cylinder segmentation and set all the parameters
			//为圆柱体分割创建分割对象，并设置所有参数
			seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
			seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
			seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
			seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数
			seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
			seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
														//距离阈值（离散点到模型表面距离）

			double radius = dim.refer[0].radius_or_length;
			seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
			seg.setInputCloud(cloud_filtered);
			seg.setInputNormals(cloud_normals);

			// Obtain the cylinder inliers and coefficients
			//获得圆柱体参数和处在圆柱体表面上的内点
			seg.segment(*inliers_cylinder, *coefficients_cylinder);

			// Write the cylinder inliers to disk
			//保存圆柱体表面上的内点到磁盘上
			extract.setInputCloud(cloud_filtered);
			extract.setIndices(inliers_cylinder);
			extract.setNegative(false);
			pcl::PointCloud<PointT>::Ptr cloud_cylinder(new pcl::PointCloud<PointT>());
			extract.filter(*cloud_cylinder);

			vec_cloud.push_back(cloud_cylinder);

			output_res_str.dim_symbol = dim.dimSymbol;
			output_res_str.theoretical_value = dim.refer[0].radius_or_length;
			output_res_str.measured_value = coefficients_cylinder->values[6];
			output_res_str.error = (int)(abs(dim.refer[0].radius_or_length - coefficients_cylinder->values[6])
				* 10000 + 0.5) / 10000.0;

			output_res_vec.push_back(output_res_str);
		}

		else {

			if (dim.refer[0].refer_type == "SRF_PLANE" && dim.refer[1].refer_type == "SRF_PLANE") {

				//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
				pass.filter(*cloud_filtered);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered);
				ne.setKSearch(k_search);
				ne.compute(*cloud_normals);

				// Create the segmentation object for the planar model and set all the parameters
				//设置分割所用的模型类型、方法、相关参数
				seg.setOptimizeCoefficients(true);
				seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
				seg.setNormalDistanceWeight(normal_distance_Weight);
				seg.setMethodType(pcl::SAC_RANSAC);
				seg.setMaxIterations(max_iterations);
				seg.setDistanceThreshold(disThreshold_plane);
				seg.setInputCloud(cloud_filtered);
				seg.setInputNormals(cloud_normals);

				// Obtain the plane inliers and coefficients
				//根据上面的输入参数执行分割获取平面模型系数和处在平面上的内点
				seg.segment(*inliers_plane, *coefficients_plane);

				// Extract the planar inliers from the input cloud
				//从点云中抽取分割的处在平面上的点集
				extract.setInputCloud(cloud_filtered);
				extract.setIndices(inliers_plane);
				extract.setNegative(false);

				// Write the planar inliers to disk
				pcl::PointCloud<PointT>::Ptr cloud_plane(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_plane);

				///////////////////////////////////////////////////////////////////////////////////////////////

				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[1].x_lower - 3, dim.refer[1].x_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[1].y_lower - 3, dim.refer[1].y_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[1].z_lower - 3, dim.refer[1].z_upper + 3);
				pass.filter(*cloud_filtered2);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered2);
				ne.setKSearch(k_search);
				ne.compute(*cloud_normals2);

				// Create the segmentation object for the planar model and set all the parameters
				//设置分割所用的模型类型、方法、相关参数
				seg.setOptimizeCoefficients(true);
				seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
				seg.setNormalDistanceWeight(normal_distance_Weight);
				seg.setMethodType(pcl::SAC_RANSAC);
				seg.setMaxIterations(max_iterations);
				seg.setDistanceThreshold(disThreshold_plane);
				seg.setInputCloud(cloud_filtered2);
				seg.setInputNormals(cloud_normals2);

				// Obtain the plane inliers and coefficients
				//根据上面的输入参数执行分割获取平面模型系数和处在平面上的内点
				seg.segment(*inliers_plane2, *coefficients_plane2);

				// Extract the planar inliers from the input cloud
				//从点云中抽取分割的处在平面上的点集
				extract.setInputCloud(cloud_filtered2);
				extract.setIndices(inliers_plane2);
				extract.setNegative(false);

				// Write the planar inliers to disk
				pcl::PointCloud<PointT>::Ptr cloud_plane2(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_plane2);

				pcl::PointCloud<PointT>::Ptr cloud_plane1_plane2(new pcl::PointCloud<PointT>);
				*cloud_plane1_plane2 = *cloud_plane + *cloud_plane2;
				vec_cloud.push_back(cloud_plane1_plane2);

				output_res_str.dim_symbol = dim.dimSymbol;
				output_res_str.theoretical_value = dim.dimValue;
				output_res_str.measured_value = abs(coefficients_plane->values[3] - coefficients_plane2->values[3]);
				output_res_str.error = (int)(abs(dim.dimValue - abs(coefficients_plane->values[3] - coefficients_plane2->values[3]))
					* 10000 + 0.5) / 10000.0;

				output_res_vec.push_back(output_res_str);
			}

			else if (dim.refer[0].refer_type == "SRF_CYL" && dim.refer[1].refer_type == "SRF_CYL") {

				// Build a passthrough filter to remove spurious NaNs
				//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
				pass.filter(*cloud_filtered);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered);
				ne.setKSearch(k_search);
				//ne.setRadiusSearch(5);
				ne.compute(*cloud_normals);

				// Create the segmentation object for cylinder segmentation and set all the parameters
				//为圆柱体分割创建分割对象，并设置所有参数
				seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
				seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
				seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
				seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数0.1
				seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
				seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
															//距离阈值（离散点到模型表面距离）

				double radius = dim.refer[0].radius_or_length;
				seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
				seg.setInputCloud(cloud_filtered);
				seg.setInputNormals(cloud_normals);

				// Obtain the cylinder inliers and coefficients
				//获得圆柱体参数和处在圆柱体表面上的内点
				seg.segment(*inliers_cylinder, *coefficients_cylinder);

				// Write the cylinder inliers to disk
				//保存圆柱体表面上的内点到磁盘上
				extract.setInputCloud(cloud_filtered);
				extract.setIndices(inliers_cylinder);
				extract.setNegative(false);
				pcl::PointCloud<PointT>::Ptr cloud_cylinder(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_cylinder);

				///////////////////////////////////////////////////////////////////////////////////////////////

				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[1].x_lower - 3, dim.refer[1].x_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[1].y_lower - 3, dim.refer[1].y_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[1].z_lower - 3, dim.refer[1].z_upper + 3);
				pass.filter(*cloud_filtered2);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered2);
				ne.setKSearch(k_search);
				//ne.setRadiusSearch(5);
				ne.compute(*cloud_normals2);

				// Create the segmentation object for cylinder segmentation and set all the parameters
				//为圆柱体分割创建分割对象，并设置所有参数
				seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
				seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
				seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
				seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数0.1
				seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
				seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
															//距离阈值（离散点到模型表面距离）

				radius = dim.refer[1].radius_or_length;
				seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
				seg.setInputCloud(cloud_filtered2);
				seg.setInputNormals(cloud_normals2);

				// Obtain the cylinder inliers and coefficients
				//获得圆柱体参数和处在圆柱体表面上的内点
				seg.segment(*inliers_cylinder2, *coefficients_cylinder2);

				// Write the cylinder inliers to disk
				//保存圆柱体表面上的内点到磁盘上
				extract.setInputCloud(cloud_filtered2);
				extract.setIndices(inliers_cylinder2);
				extract.setNegative(false);
				pcl::PointCloud<PointT>::Ptr cloud_cylinder2(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_cylinder2);

				pcl::PointCloud<PointT>::Ptr cloud_cylinder1_cylinder2(new pcl::PointCloud<PointT>);
				*cloud_cylinder1_cylinder2 = *cloud_cylinder + *cloud_cylinder2;
				vec_cloud.push_back(cloud_cylinder1_cylinder2);

				Point pA(coefficients_cylinder->values[0], coefficients_cylinder->values[1], coefficients_cylinder->values[2]);
				Point pB(coefficients_cylinder2->values[0], coefficients_cylinder2->values[1], coefficients_cylinder2->values[2]);
				Point pC(coefficients_cylinder2->values[3], coefficients_cylinder2->values[4], coefficients_cylinder2->values[5]);

				output_res_str.dim_symbol = dim.dimSymbol;
				output_res_str.theoretical_value = dim.dimValue;
				output_res_str.measured_value = DimCalculate().dist(pA, pB, pC);
				output_res_str.error = (int)(abs(dim.dimValue - DimCalculate().dist(pA, pB, pC))
					* 10000 + 0.5) / 10000.0;

				output_res_vec.push_back(output_res_str);
			}

			else if (dim.refer[0].refer_type == "SRF_CYL" && dim.refer[1].refer_type == "SRF_PLANE") {

				//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
				pass.filter(*cloud_filtered);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered);
				ne.setKSearch(k_search);
				//ne.setRadiusSearch(5);
				ne.compute(*cloud_normals);

				// Create the segmentation object for cylinder segmentation and set all the parameters
				//为圆柱体分割创建分割对象，并设置所有参数
				seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
				seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
				seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
				seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数0.1
				seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
				seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
															//距离阈值（离散点到模型表面距离）

				double radius = dim.refer[0].radius_or_length;
				seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
				seg.setInputCloud(cloud_filtered);
				seg.setInputNormals(cloud_normals);

				// Obtain the cylinder inliers and coefficients
				//获得圆柱体参数和处在圆柱体表面上的内点
				seg.segment(*inliers_cylinder, *coefficients_cylinder);

				// Write the cylinder inliers to disk
				//保存圆柱体表面上的内点到磁盘上
				extract.setInputCloud(cloud_filtered);
				extract.setIndices(inliers_cylinder);
				extract.setNegative(false);
				pcl::PointCloud<PointT>::Ptr cloud_cylinder(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_cylinder);

				///////////////////////////////////////////////////////////////////////////////////////////

				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[1].x_lower - 3, dim.refer[1].x_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[1].y_lower - 3, dim.refer[1].y_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[1].z_lower - 3, dim.refer[1].z_upper + 3);
				pass.filter(*cloud_filtered2);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered2);
				ne.setKSearch(k_search);
				ne.compute(*cloud_normals2);

				// Create the segmentation object for the planar model and set all the parameters
				//设置分割所用的模型类型、方法、相关参数
				seg.setOptimizeCoefficients(true);
				seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
				seg.setNormalDistanceWeight(normal_distance_Weight);
				seg.setMethodType(pcl::SAC_RANSAC);
				seg.setMaxIterations(max_iterations);
				seg.setDistanceThreshold(disThreshold_plane);
				seg.setInputCloud(cloud_filtered2);
				seg.setInputNormals(cloud_normals2);

				// Obtain the plane inliers and coefficients
				//根据上面的输入参数执行分割获取平面模型系数和处在平面上的内点
				seg.segment(*inliers_plane2, *coefficients_plane2);

				// Extract the planar inliers from the input cloud
				//从点云中抽取分割的处在平面上的点集
				extract.setInputCloud(cloud_filtered2);
				extract.setIndices(inliers_plane2);
				extract.setNegative(false);

				// Write the planar inliers to disk
				pcl::PointCloud<PointT>::Ptr cloud_plane2(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_plane2);

				pcl::PointCloud<PointT>::Ptr cloud_cylinder_plane2(new pcl::PointCloud<PointT>);
				*cloud_cylinder_plane2 = *cloud_cylinder + *cloud_plane2;
				vec_cloud.push_back(cloud_cylinder_plane2);

				Point p(coefficients_cylinder->values[0], coefficients_cylinder->values[1], coefficients_cylinder->values[2]);
				PlaneEquation pe(coefficients_plane2->values[0], coefficients_plane2->values[1],
					coefficients_plane2->values[2], coefficients_plane2->values[3]);

				output_res_str.dim_symbol = dim.dimSymbol;
				output_res_str.theoretical_value = dim.dimValue;
				output_res_str.measured_value = DimCalculate().dist(p, pe);
				output_res_str.error = (int)(abs(dim.dimValue - DimCalculate().dist(p, pe))
					* 10000 + 0.5) / 10000.0;

				output_res_vec.push_back(output_res_str);
			}

			else /*if (dim.refer[0].refer_type == "SRF_PLANE" && dim.refer[1].refer_type == "SRF_CYL")*/ {

				//直通滤波，将z轴不在（0,1.5）范围内的点过滤掉，将剩余点存储在cloud_filtered对象中后续使用
				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[0].x_lower - 3, dim.refer[0].x_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[0].y_lower - 3, dim.refer[0].y_upper + 3);
				pass.filter(*cloud_filtered);

				pass.setInputCloud(cloud_filtered);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[0].z_lower - 3, dim.refer[0].z_upper + 3);
				pass.filter(*cloud_filtered);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered);
				ne.setKSearch(k_search);
				ne.compute(*cloud_normals);

				// Create the segmentation object for the planar model and set all the parameters
				//设置分割所用的模型类型、方法、相关参数
				seg.setOptimizeCoefficients(true);
				seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
				seg.setNormalDistanceWeight(normal_distance_Weight);
				seg.setMethodType(pcl::SAC_RANSAC);
				seg.setMaxIterations(max_iterations);
				seg.setDistanceThreshold(disThreshold_plane);
				seg.setInputCloud(cloud_filtered);
				seg.setInputNormals(cloud_normals);

				// Obtain the plane inliers and coefficients
				//根据上面的输入参数执行分割获取平面模型系数和处在平面上的内点
				seg.segment(*inliers_plane, *coefficients_plane);

				// Extract the planar inliers from the input cloud
				//从点云中抽取分割的处在平面上的点集
				extract.setInputCloud(cloud_filtered);
				extract.setIndices(inliers_plane);
				extract.setNegative(false);

				// Write the planar inliers to disk
				pcl::PointCloud<PointT>::Ptr cloud_plane(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_plane);

				//////////////////////////////////////////////////////////////////////////////////////////////

				pass.setInputCloud(cloud);

				pass.setFilterFieldName("x");
				pass.setFilterLimits(dim.refer[1].x_lower - 3, dim.refer[1].x_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("y");
				pass.setFilterLimits(dim.refer[1].y_lower - 3, dim.refer[1].y_upper + 3);
				pass.filter(*cloud_filtered2);

				pass.setInputCloud(cloud_filtered2);
				pass.setFilterFieldName("z");
				pass.setFilterLimits(dim.refer[1].z_lower - 3, dim.refer[1].z_upper + 3);
				pass.filter(*cloud_filtered2);

				// Estimate point normals
				//对过滤后的点云进行法线估计，为后续进行基于法线的分割准备数据
				ne.setSearchMethod(tree);
				ne.setInputCloud(cloud_filtered2);
				ne.setKSearch(k_search);
				//ne.setRadiusSearch(5);
				ne.compute(*cloud_normals2);

				// Create the segmentation object for cylinder segmentation and set all the parameters
				//为圆柱体分割创建分割对象，并设置所有参数
				seg.setOptimizeCoefficients(true);			//设置对估计的模型系数需要进行优化
				seg.setModelType(pcl::SACMODEL_CYLINDER);	//设置分割模型为圆柱体
				seg.setMethodType(pcl::SAC_RANSAC);			//设置采用RANSAC作为算法的参数估计方法
				seg.setNormalDistanceWeight(normal_distance_Weight);			//设置表面法线权重系数0.1
				seg.setMaxIterations(max_iterations);				//设置迭代的最大次数10000
				seg.setDistanceThreshold(disThreshold_radius);				//设置内点到模型的距离允许最大值
															//距离阈值（离散点到模型表面距离）
				double radius = dim.refer[1].radius_or_length;
				seg.setRadiusLimits(radius - radius * 0.1, radius + radius * 0.1);	//设置估计出的圆柱模型的半径范围
				seg.setInputCloud(cloud_filtered2);
				seg.setInputNormals(cloud_normals2);

				// Obtain the cylinder inliers and coefficients
				//获得圆柱体参数和处在圆柱体表面上的内点
				seg.segment(*inliers_cylinder2, *coefficients_cylinder2);

				// Write the cylinder inliers to disk
				//保存圆柱体表面上的内点到磁盘上
				extract.setInputCloud(cloud_filtered2);
				extract.setIndices(inliers_cylinder2);
				extract.setNegative(false);
				pcl::PointCloud<PointT>::Ptr cloud_cylinder2(new pcl::PointCloud<PointT>());
				extract.filter(*cloud_cylinder2);

				pcl::PointCloud<PointT>::Ptr cloud_plane_cylinder2(new pcl::PointCloud<PointT>);
				*cloud_plane_cylinder2 = *cloud_plane + *cloud_cylinder2;
				vec_cloud.push_back(cloud_plane_cylinder2);

				Point p(coefficients_cylinder2->values[0], coefficients_cylinder2->values[1], coefficients_cylinder2->values[2]);
				PlaneEquation pe(coefficients_plane->values[0], coefficients_plane->values[1],
					coefficients_plane->values[2], coefficients_plane->values[3]);

				output_res_str.dim_symbol = dim.dimSymbol;
				output_res_str.theoretical_value = dim.dimValue;
				output_res_str.measured_value = DimCalculate().dist(p, pe);
				output_res_str.error = (int)(abs(dim.dimValue - DimCalculate().dist(p, pe))
					* 10000 + 0.5) / 10000.0;

				output_res_vec.push_back(output_res_str);
			}
		}
	}

	//tableWeight使用
	//设置列数
	ui.tableWidget->setColumnCount(4);
	//设置水平表头
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << u8"尺寸ID" << u8"理论值" << u8"测量值" << u8"误差");
	//设置行数
	ui.tableWidget->setRowCount(output_res_vec.size());
	//设置具体内容
	int row = 0;
	for (auto e : output_res_vec) {

		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.dim_symbol)));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(e.theoretical_value, 'f', 4)));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(e.measured_value, 'f', 4)));
		ui.tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(e.error, 'f', 4)));
		row++;
	}


	//点云显示
	if (addResultFlag) {
		addResultFlag = false;

		srand(time(NULL));
		for (auto i = 0; i < vec_cloud.size(); i++) {

			int r, g, b;

			if (rand() % 255 < 50) {
				r = 0;
			}
			else if (rand() % 255 < 150) {
				r = 125;
			}
			else {
				r = 225;
			}

			if (rand() % 255 < 50) {
				g = 0;
			}
			else if (rand() % 255 < 150) {
				g = 125;
			}
			else {
				g = 225;
			}

			if (rand() % 255 < 50) {
				b = 0;
			}
			else if (rand() % 255 < 150) {
				b = 125;
			}
			else {
				b = 225;
			}

			if (r == 0 && b == 0 && g == 0) {
				r = 255;
				g = 255;
				b = 255;
			}

			pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> handler_name(vec_cloud[i], r, g, b);
			viewerDimInfo->addPointCloud(vec_cloud[i], handler_name, vec_name[i]);
		}
		//测量结果点云显示
		viewerDimInfo->resetCamera();
		ui.qvtkWidgetDimInfo->update();
	}
	else 
	{
		srand(time(NULL));
		for (auto i = 0; i < vec_cloud.size(); i++) {

			int r, g, b;

			if (rand() % 255 < 50) {
				r = 0;
			}
			else if (rand() % 255 < 150) {
				r = 125;
			}
			else {
				r = 225;
			}

			if (rand() % 255 < 50) {
				g = 0;
			}
			else if (rand() % 255 < 150) {
				g = 125;
			}
			else {
				g = 225;
			}

			if (rand() % 255 < 50) {
				b = 0;
			}
			else if (rand() % 255 < 150) {
				b = 125;
			}
			else {
				b = 225;
			}

			if (r == 0 && b == 0 && g == 0) {
				r = 255;
				g = 255;
				b = 255;
			}

			pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> handler_name(vec_cloud[i], r, g, b);
			viewerDimInfo->updatePointCloud(vec_cloud[i], handler_name, vec_name[i]);
		}
		//测量结果点云显示
		viewerDimInfo->resetCamera();
		ui.qvtkWidgetDimInfo->update();
	}


	//输出尺寸测量完成提示信息
	ui.textBrowser->append("*****************************************");
	ui.textBrowser->append(u8"点云尺寸测量完成");
	ui.textBrowser->append("*****************************************");

}

void PointCloudDim::resultOutput()
{
	ofstream oFile;

	QByteArray ba_output = (file_path + "/result.csv").toLatin1();
	const char *output_filename = ba_output.data();

	oFile.open(output_filename, ios::out | ios::trunc);    // 这样就很容易的输出一个需要的excel 文件  
	oFile << "尺寸ID" << "," << "理论值" << "," << "测量值" << "," << "误差" << endl;

	for (auto e : output_res_vec) {

		oFile << e.dim_symbol << "," << e.theoretical_value << "," << e.measured_value << "," << e.error << endl;
	}

	oFile.close();

	ui.textBrowser->append("*****************************************");
	ui.textBrowser->append(u8"尺寸结果已导出，请在工作目录中查看");
	ui.textBrowser->append("*****************************************");
}
