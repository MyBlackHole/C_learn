#include "Brush.h"
#include <qwidget.h>
#include <QMouseEvent>
#include <iostream>

Brush::Brush(QImage* image, QColor* color)
    : m_image(image)
    , m_color(color)
{

}

void Brush::mousePressEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::mouseMoveEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::mouseReleaseEvent(QMouseEvent* event)
{
    this->paintArea(event->x(), event->y());
}

void Brush::paintArea(int x, int y)
{
    //currently painting a 3x3 box with the click in the middle. Change?
    for(int i = x-2; i <= x+2; i++)
    {
        for (int j = y-2; j < y+2; j++)
        {
            if (this->m_image->height() > y && this->m_image->width() > x && y > 0 && x > 0)
            {
                this->m_image->setPixel(i, j, this->m_color->rgba());
            }
        }
    }
}

void Brush::updateImage(QImage* image)
{
    this->m_image = image;
}

void Brush::updateColor(QColor* color)
{
    //std::cout << "Changing color..." << std::endl;
    this->m_color = color;
}
