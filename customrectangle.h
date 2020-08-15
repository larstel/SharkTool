#ifndef CUSTOMRECTANGLE_H
#define CUSTOMRECTANGLE_H
#include <QGraphicsSceneMouseEvent>
#include <QtCore/qmath.h>
#include <QGraphicsItem>
#include <QDebug> // for warnings in switch case
#include <QBrush>
#include <QPen>
#include "appstate.h"
/**
 * @brief The CustomRectangle class
 * @details This class is a reimplementation of QGraphicsRectItem
 * it contains all data a rectangle needed
 * @author Lars Telöken
 * @version 1.0
 * @date 2019-01-27
 */
class CustomRectangle : public QGraphicsRectItem
{

private:
    /**
     * @brief m_center - the center member
     * @details the center of an rectangle
     */
    QPointF m_center;
    /**
     * @brief m_isResizing - the isResizing member
     * @details if the rectangle have to resize it is on true else on false
     */
    bool m_isResizing;
    /**
     * @brief m_color - the color member
     * @details the color of the rectangle
     */
    QColor m_color;
    /**
     * @brief m_point - the point member
     * @details contains the position of the rectangle
     */
    QPointF m_point;
    /**
     * @brief m_width - the width member
     * @details the width of the rectangle
     */
    qreal m_width;
    /**
     * @brief m_height - the height member
     * @details the height of the rectangle
     */
    qreal m_height;
    /**
     * @brief m_borderSize - the border size member
     * @details the size of the border of the rectangle
     */
    qreal m_borderSize;
    /**
     * @brief m_appState - the app state member
     * @details contains the app state with all the standard parameter
     */
    app::AppState *m_appState;
    /**
     * @brief m_brush - the brush member
     * @details the brush of the rectangle to colorize it
     */
    QBrush m_brush;

public:
    /**
     * @brief CustomRectangle - the constructor of the class
     */
    CustomRectangle();
    /**
     * @brief CustomRectangle - the constructor of the class
     * @param x - the x position of the item
     * @param y - the y position of the item
     * @param width - the width of the item
     * @param height - the height of the item
     * @param borderSize - the border size of the item
     * @param brush - the brush of the item
     * @param appState - the app state of the item
     * @details This method is called in App::onCanvasClicked, App::onSelectedItemSizeChanged, App::onSelectedItemBorderSizeChanged,
     * App::onItemSelected, JsonHelper::createJson and Jsonhelper::readJson
     */
    CustomRectangle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState);
    /**
     * @brief getColor - getter of color
     * @return - returned the current color
     * @details get the current color of the item
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    QColor getColor();
    /**
     * @brief setColor - setter of color
     * @param color - the current color
     * @details set the current color of the item
     * This method is called in CustomTextRectangle::mousePressEvent and in the kind classes of this class
     */
    void setColor(QColor color);
    /**
     * @brief getPoint - getter of point
     * @return - returned the current point
     * @details get the current point of the item
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    QPointF getPoint();
    /**
     * @brief setPoint - setter of point
     * @param point - the current point
     * @details set the current point of the item
     * This method is called in the kind classes of this class
     */
    void setPoint(QPointF point);
    /**
     * @brief getWidth - getter of width
     * @return - returned the current width
     * @details get the current width
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    qreal getWidth();
    /**
     * @brief setWidth - setter of width
     * @param width - the current width of the item
     * @details set the current width
     * This method is called in the kind classes of this class
     */
    void setWidth(qreal width);
    /**
     * @brief getHeight - getter of height
     * @return - returned the current height of the item
     * @details get the current height
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    qreal getHeight();
    /**
     * @brief setHeight - setter of height
     * @param height - the current height of the item
     * @details set the current height of the item
     * This method is called in the kind classes of this class
     */
    void setHeight(qreal height);
    /**
     * @brief getBrush setter of brush
     * @return - returned the current brush
     * @details get the current brush
     * This method is called in the kind classes of the item
     */
    QBrush getBrush();
    /**
     * @brief setBrush - setter of brush
     * @param brush - the current brush
     * @details set the current brush
     */
    void setBrush(QBrush brush);
    /**
     * @brief getBorderSize - getter of border size
     * @return - returned the current border size of the item
     * @details get the current border size
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    qreal getBorderSize();
    /**
     * @brief setBorderSize - setter of border size
     * @param borderSize - the current border size of the item
     * @details set the current border size
     * This method is called in the kind classes of this class
     */
    void setBorderSize(qreal borderSize);
    /**
     * @brief getAppState - getter of app state
     * @return - returned the current app state of the item
     * @details get the current app state
     * This method is called in App::onItemSelected, JsonHelper::createJson
     */
    app::AppState *getAppState();
    /**
     * @brief setAppState - setter of app state
     * @param appState - the current app state of the item
     * @details set the current app state
     * This method is called in the kind classes of this class
     */
    void setAppState(app::AppState *appState);
    /**
     * @brief type - get the type of the item
     * @return - returned the item index
     * @details a override function
     * This method is called in App::onSelectedItemSizeChanged
     */
    int type() const;
    /**
     * @brief update - override function
     * @details update the items properties
     * @details This method is called in the kind classes of this class
     */
    void update();
protected:
    // the following functions are made with the help of https://gist.github.com/csukuangfj/c2a06416062bec9ed99eddd705c21275

    /**
     * @brief mousePressEvent - a override function
     * @param event - the current event of the mouse
     * @details This method is called in CustomCircle
     * it handle the action if a rectangle is clicked
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseMoveEvent - a override function
     * @param event - the current event of the mouse
     * @details is handle the action if a rectangle is moved
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseReleaseEvent - a override function
     * @param event - the current event of the mouse
     * @details is danle the action if a rectangle mouse click is released
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMRECTANGLE_H
