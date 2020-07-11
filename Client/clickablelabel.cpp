#include "clickablelabel.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent) {}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::setCustomPixmap(const QPixmap &p) {
  this->pixmap = p;
  ClickableLabel::update();
}
void ClickableLabel::mousePressEvent(QMouseEvent *event) { emit clicked(); }

void ClickableLabel::paintEvent(QPaintEvent *event) {
  int w = width();
  int h = height();

  QPixmap scaled = pixmap.scaled(w, h, Qt::KeepAspectRatioByExpanding,
                                 Qt::SmoothTransformation);
  QBrush brush(scaled);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setBrush(brush);
  painter.drawRoundedRect(2, 2, w - 10, h - 10, 100, 100);
  QLabel::paintEvent(event);
}

void ClickableLabel::enterEvent(QEvent *ev) { setToolTip("Upload..."); }

void ClickableLabel::leaveEvent(QEvent *ev) {}
