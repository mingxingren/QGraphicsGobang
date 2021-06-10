#ifndef CBGGRAPHICSITEM_H
#define CBGGRAPHICSITEM_H

#include <memory>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QImage>
#include "graphicsitem.h"

QT_FORWARD_DECLARE_CLASS(CGameLogic)

class CBgGraphicsItem : public QGraphicsItem
{
public:
    CBgGraphicsItem(int _iWidth, int _iHeight);
    void InitStage(QGraphicsScene * _pScene = nullptr);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

protected:
    virtual bool sceneEvent(QEvent *event) override;

private:
    void _SetCheckerboardPosition(const QPointF _coPoint);

private:
    constexpr static int m_siSpaceLength = 40;   ///< 格子的宽高
    constexpr static int m_siLineLength = m_siSpaceLength * 14;   ///< 网格线的长度

private:
    int m_iHeight;  ///< 背景 item 高度
    int m_iWidth;   ///< 背景 item 宽度
    QImage m_imgBackground;     ///< 背景图
    QVector<QGraphicsItem*> m_vtXLine;   ///< 水平方向item线
    QVector<QGraphicsItem*> m_vtYLine;   ///< 竖直方向item线
    QVector<QGraphicsItem*> m_vtPieceItem;  ///< 棋子项
    std::shared_ptr<CGameLogic> m_pGameLogic = nullptr;   ///< 棋子逻辑处理
};

#endif // CBGGRAPHICSITEM_H
