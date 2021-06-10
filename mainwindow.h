#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_FORWARD_DECLARE_CLASS(CRenderManager)
QT_FORWARD_DECLARE_CLASS(CGraphicsScene)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void _InitUi();
    void _InitMember();

private:
    CGraphicsScene * m_pScene = nullptr;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
