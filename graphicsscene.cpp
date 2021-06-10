#include "graphicsscene.h"

#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "graphicsitem.h"
#include "bggraphicsitem.h"

CGraphicsScene::CGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    m_pBgItem = new CBgGraphicsItem(640, 640);
    this->addItem(m_pBgItem);
    m_pBgItem->setPos(0, 0);
}

bool CGraphicsScene::event(QEvent *event)
{
    switch (event->type()){
    case QEvent::GraphicsSceneMousePress : {
        QGraphicsSceneMouseEvent * pMouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        qDebug() << "####################CGraphicsScene::events" << pMouseEvent->pos() << pMouseEvent->scenePos();
//        CGraphicsItem *pItem = new CGraphicsItem(pMouseEvent->scenePos().x(), pMouseEvent->scenePos().y());
//        this->addItem(pItem);
//        pItem->setPos(pMouseEvent->scenePos());
//        m_vtItems.push_back(pItem);
        break;
    }
    default:
        break;
    }
    return QGraphicsScene::event(event);
}
