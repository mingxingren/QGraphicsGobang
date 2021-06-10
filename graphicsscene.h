#ifndef CGRAPHICSSCENE_H
#define CGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPixmap>

QT_FORWARD_DECLARE_CLASS(CGraphicsItem)
QT_FORWARD_DECLARE_CLASS(CBgGraphicsItem)

class CGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CGraphicsScene(QObject *parent = nullptr);

    inline CBgGraphicsItem* GetBgStage()
    {
        return m_pBgItem;
    }

protected:
    virtual bool event(QEvent *event) override;

private:
    CBgGraphicsItem * m_pBgItem = nullptr;
    QVector<CGraphicsItem*> m_vtItems;
    QPixmap m_imgBackground;
};

#endif // CGRAPHICSSCENE_H
