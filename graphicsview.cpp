#include "graphicsview.h"

#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>

CGraphicsView::CGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

bool CGraphicsView::event(QEvent *event)
{
    switch (event->type()){
    case QEvent::MouseButtonPress : {
        QMouseEvent * pMouseEvent = dynamic_cast<QMouseEvent*>(event);
        break;
    }
    default:
        break;
    }
    return QGraphicsView::event(event);
}

void CGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPoint point = event->angleDelta();
    qreal dZoomInStep = 0.5;
    qreal dZoomOutStep = 2;
    qreal dZoom = point.y() > 0 ? dZoomInStep : dZoomOutStep;
    qreal dFactor = transform().scale(dZoom, dZoom).mapRect(QRectF(0, 0, 1, 1)).width();
    if (dFactor < 0.07 || dFactor > 100)
        return;

    QPoint centerPoint = event->pos();
    this->centerOn(this->mapToScene(centerPoint));  // 以鼠标中心进行放大缩小
    this->scale(dZoom, dZoom);
}

void CGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pointDrapStart = event->pos();
        m_bMoving = true;
    }
}

void CGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMoving)
    {
        QPoint pointXYDifference = m_pointDrapStart - event->pos();
        int iCenter_X = (0 + this->width()) / 2;
        int iCenter_Y = (0 + this->height()) / 2;
        QPoint pointCenter = { iCenter_X, iCenter_Y };
        qDebug() << "############################mouseMoveEvent pointXYDifference" << pointXYDifference;
        this->centerOn(this->mapToScene(pointCenter + pointXYDifference));
    }
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_bMoving)
    {
        m_bMoving = false;
    }
}
