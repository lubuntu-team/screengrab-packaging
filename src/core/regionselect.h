/***************************************************************************
 *   Copyright (C) 2009 - 2013 by Artem 'DOOMer' Galichkin                        *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef REGIONSELECT_H
#define REGIONSELECT_H

#include "config.h"

//#include <QDialog>
#include <QWidget>

#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <QPoint>

// class RegionSelect : public QDialog
class RegionSelect : public QWidget
{
    Q_OBJECT
public:
    RegionSelect(Config *mainconf, QWidget *parent = 0);
    RegionSelect(Config *mainconf, const QRect& lastRect, QWidget *parent = 0);
    virtual ~RegionSelect();
    QPixmap getSelection();
    QPoint getSelectionStartPos();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

Q_SIGNALS:
    void processDone(bool grabbed);

private:
    QRect _selectRect;
    QSize _sizeDesktop;

    QPoint _selStartPoint;
    QPoint _selEndPoint;

    bool _processSelection;

    QPixmap _desktopPixmapBkg;
    QPixmap _desktopPixmapClr;

    void sharedInit();
    void drawBackGround();
    void drawRectSelection(QPainter &painter);

    Config *_conf;

};

#endif // REGIONSELECT_H
