/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TABLETCANVAS_H
#define TABLETCANVAS_H

#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtCore/QPoint>
#include <QtGui/QTabletEvent>
#include <QtGui/QColor>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtCore/QPoint>

#include "blfunctions.h"


QT_BEGIN_NAMESPACE
class QPaintEvent;
class QString;
QT_END_NAMESPACE

//! [0]
class TabletCanvas : public QWidget
{
    Q_OBJECT

public:
    enum AlphaChannelType { AlphaPressure, AlphaTilt, NoAlpha };
    enum ColorSaturationType { SaturationVTilt, SaturationHTilt,
                               SaturationPressure, NoSaturation };
    enum LineWidthType { LineWidthPressure, LineWidthTilt, NoLineWidth };

    TabletCanvas();

    bool saveImage(const QString &file);
    bool loadImage(const QString &file);
    void erasePixmap();
    void setAlphaChannelType(AlphaChannelType type)
        { alphaChannelType = type; }
    void setColorSaturationType(ColorSaturationType type)
        { colorSaturationType = type; }
    void setLineWidthType(LineWidthType type)
        { lineWidthType = type; }
    void setColor(const QColor &color)
        { myColor = color; }
    QColor color() const
        { return myColor; }
    void setTabletDevice(QTabletEvent::TabletDevice device)
        { myTabletDevice = device; }
    int maximum(int a, int b)
        { return a > b ? a : b; }

protected:
    void tabletEvent(QTabletEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void initPixmap();
    void paintPixmap(QPainter &painter, QTabletEvent *event);
    Qt::BrushStyle brushPattern(qreal value);
    void updateBrush(QTabletEvent *event);

    AlphaChannelType alphaChannelType;
    ColorSaturationType colorSaturationType;
    LineWidthType lineWidthType;
    QTabletEvent::PointerType pointerType;
    QTabletEvent::TabletDevice myTabletDevice;
    QColor myColor;
    
public:
    QPixmap pixmap;
    QBrush myBrush;
    QPen myPen;
    bool deviceDown;
    QPoint polyLine[3];
    bool m_vacio;
};
//! [0]

#endif
