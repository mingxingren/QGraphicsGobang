#include "graphicsitem.h"

#include <QDebug>
#include <QPainter>

CGraphicsItem::CGraphicsItem(int _iX, int _iY, Qt::GlobalColor _eColor,
                             QGraphicsItem *parent) : QGraphicsItem(parent)
  , m_iX(_iX), m_iY(_iY), m_eGlobalColor(_eColor)
{
    qDebug() << "##############CGraphicsItem" << m_iX << m_iY;
}

QRectF CGraphicsItem::boundingRect() const
{
    // 由 bounding rect 确定位置和边界
    qreal penWidth = 1;
    return QRectF((-m_siWidth - penWidth) / 2, (-m_siHeight - penWidth) / 2, m_siWidth + penWidth,
                  m_siHeight + penWidth);
}

void CGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);   // 反锯齿
    QPainterPath oEllipsePath;
    QRectF oEllipseRect = { -m_siWidth / 2, -m_siHeight / 2, m_siWidth, m_siHeight };
    oEllipsePath.addEllipse(oEllipseRect);
    painter->fillPath(oEllipsePath, m_eGlobalColor);
}
