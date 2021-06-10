#ifndef CGRAPHICSVIEW_H
#define CGRAPHICSVIEW_H

#include <QGraphicsView>

class CGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CGraphicsView(QWidget *parent = nullptr);

protected:
    virtual bool event(QEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint m_pointDrapStart;
    bool m_bMoving = false;
};

#endif // CGRAPHICSVIEW_H
