#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class QMouseEvent;

class mylabel : public QLabel
{
    Q_OBJECT

public:
    explicit mylabel(QWidget *parent = 0);

signals:
  void label_Clicked();

protected:
      void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H
