#include <QtGui>
#include <QLabel>
#include "dragwidget.hpp"


DragWidget::DragWidget(const QString &t, QWidget *p) : QGroupBox(t, p)
{
	resize(100, 100);
	setAcceptDrops(true);
	
   img = new QLabel(this);
   img->setScaledContents(true);
   img->setPixmap(QPixmap(":/res/plantations/cafe.jpg"));
   img->resize(61, 51);
   img->move(15, 25);
}


DragWidget::~DragWidget()
{
}


void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
	{
		if (event->source() == this)
		{
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
		else
		{
			event->acceptProposedAction();
        }
     }
	 else
	 {
         event->ignore();
     }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata"))
	{
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	else
	{
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata"))
	{
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
		newIcon->resize(61, 51);
		newIcon->setScaledContents(true);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);
		
		event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	else
	{
       event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
	QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
	
	if (!child)
	{
		return;
	}

    QPixmap childPixmap = *child->pixmap();
	QPixmap pixmap = childPixmap.scaled(61, 51, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
	
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
	
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
	
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
	{
        child->close();
	}
    else
	{
        child->show();
        child->setPixmap(pixmap);
    }
}
