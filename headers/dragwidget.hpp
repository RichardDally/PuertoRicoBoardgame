#ifndef DRAGWIDGET_HPP
#define DRAGWIDGET_HPP

#include <QGroupBox>

class QLabel;
class QDropEvent;
class QDragEnterEvent;

class DragWidget : public QGroupBox
{
	public:
		DragWidget(const QString &title, QWidget *parent=0);
		~DragWidget();
	
	protected:
		void dragEnterEvent(QDragEnterEvent *event);
		void dragMoveEvent(QDragMoveEvent *event);
		void dropEvent(QDropEvent *event);
		void mousePressEvent(QMouseEvent *event);
		
	private:
		QLabel *img;
};


#endif
