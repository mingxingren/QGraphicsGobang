#include "bggraphicsitem.h"

#include <QDebug>
#include <QGraphicsLineItem>
#include <QEvent>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "gamelogic.h"

CBgGraphicsItem::CBgGraphicsItem(int _iWidth, int _iHeight)
    : m_iHeight(_iHeight), m_iWidth(_iWidth)
{
    m_imgBackground = QImage(":/background/background.jpg");
    m_pGameLogic = std::make_shared<CGameLogic>();
    this->InitStage();
}

void CBgGraphicsItem::InitStage(QGraphicsScene * _pScene)
{
    QPen oPen;
    oPen.setColor(Qt::black);
    oPen.setWidth(3);

    int iHorizontalStartX = -m_siLineLength / 2;
    int iVerticalStartX = -m_siLineLength / 2;

    for (int i = 0; i < 15; i++)
    {
        QGraphicsLineItem *pLineItem = new QGraphicsLineItem(this);
        pLineItem->setPen(oPen);
        // item 里坐标点
        QPointF oPointStart = QPointF(-m_siLineLength / 2, iVerticalStartX + i * m_siSpaceLength);
        QPointF oPointEnd = QPointF(m_siLineLength / 2, iVerticalStartX + i * m_siSpaceLength);
        pLineItem->setLine(QLineF(oPointStart, oPointEnd));
        m_vtXLine.push_back(pLineItem);
    }

    // 画竖线
    for (int i = 0; i < 15; i++)
    {
        QGraphicsLineItem *pLineItem = new QGraphicsLineItem(this);
        pLineItem->setPen(oPen);
        QPointF oPointStart = QPointF(iHorizontalStartX + i * m_siSpaceLength, -m_siLineLength / 2);
        QPointF oPointEnd = QPointF(iHorizontalStartX + i * m_siSpaceLength, m_siLineLength / 2);
        pLineItem->setLine(QLineF(oPointStart, oPointEnd));
        m_vtYLine.push_back(pLineItem);
    }
}

QRectF CBgGraphicsItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF((-m_iWidth - penWidth) / 2, (-m_iHeight - penWidth) / 2, m_iWidth + penWidth,
                  m_iHeight + penWidth);
}

void CBgGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rectImg = QRectF(-m_iWidth / 2, -m_iHeight / 2, m_iWidth, m_iHeight);
    painter->drawImage(rectImg, m_imgBackground);
}

bool CBgGraphicsItem::sceneEvent(QEvent *event)
{
    qDebug() << "####################CBgGraphicsItem::sceneEvent" << event->type();
    switch (event->type()){
    case QEvent::GraphicsSceneMousePress : {
        QGraphicsSceneMouseEvent * pMouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        _SetCheckerboardPosition(pMouseEvent->pos());
        break;
    }
    default:
        break;
    }
    return QGraphicsItem::sceneEvent(event);
}

void CBgGraphicsItem::_SetCheckerboardPosition(const QPointF _coPoint)
{
    static int i = 0;

    QRect rectCheckerBoard = QRect(-7 * m_siSpaceLength, -7 * m_siSpaceLength,
                                   14 * m_siSpaceLength, 14 * m_siSpaceLength);
    if (rectCheckerBoard.contains(QPoint(_coPoint.x(), _coPoint.y())))
    {
        int iXStartOffset = _coPoint.x() + 7 * m_siSpaceLength;
        int iYStartOffset = _coPoint.y() + 7 * m_siSpaceLength;
        int iRowIndex = iXStartOffset % m_siSpaceLength > 19 ?
                    iXStartOffset / m_siSpaceLength + 1 : iXStartOffset / m_siSpaceLength;
        int iColumnIndex = iYStartOffset % m_siSpaceLength > 19 ?
                    iYStartOffset / m_siSpaceLength + 1 : iYStartOffset / m_siSpaceLength;
        int iStandardX = (iRowIndex - 7) * m_siSpaceLength;
        int iStandardY = (iColumnIndex - 7) * m_siSpaceLength;
        if (m_pGameLogic->IsEmptyPosition(iRowIndex, iColumnIndex))
        {
            QGraphicsItem *pItem = new CGraphicsItem(iStandardX, iStandardY, i++ % 2 ? Qt::white : Qt::black, this);
            pItem->setPos({static_cast<qreal>(iStandardX), static_cast<qreal>(iStandardY)});
            m_vtPieceItem.push_back(pItem);
            m_pGameLogic->NextStep(iRowIndex, iColumnIndex);
        }
    }
}

