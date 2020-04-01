#include "PointCloudDim.h"
#include <QtWidgets/QApplication>
#include "vtkoutputwindow.h"

int main(int argc, char *argv[])
{
	vtkOutputWindow::GlobalWarningDisplayOff();//关闭弹出的警告窗口
	QApplication a(argc, argv);

	PointCloudDim w;
	w.hide();
	w.setWindowFlags(Qt::WindowStaysOnTopHint);
	w.show();

	w.hide();
	w.setWindowFlags(Qt::Widget);
	w.show();

	return a.exec();
}
