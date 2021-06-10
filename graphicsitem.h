#ifndef CGRAPHICSITEM_H
#define CGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QWidget>

class CGraphicsItem : public QGraphicsItem
{
public:
    explicit CGraphicsItem(int _iX, int _iY, Qt::GlobalColor _eColor, QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    qreal m_iX;
    qreal m_iY;
    static constexpr qreal m_siWidth = 30;
    static constexpr qreal m_siHeight = 30;
    Qt::GlobalColor m_eGlobalColor =  Qt::black;    ///< 棋子颜色
};

#endif // CGRAPHICSITEM_H
