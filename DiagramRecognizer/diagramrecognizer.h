#pragma once
#include "bitmap.h"
#include <QMainWindow>

namespace Ui {
    class DiagramRecognizer;
}

class DiagramRecognizer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiagramRecognizer(QWidget *parent = 0);
    ~DiagramRecognizer();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Ui::DiagramRecognizer *ui;
    QList<QList<QPoint> > mDiagram;
    Bitmap * mBitmap;
    bool mRecognized;

private slots:
    void clear();
    void recognize();
};
