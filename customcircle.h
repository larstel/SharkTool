#ifndef CUSTOMCIRCLE_H
#define CUSTOMCIRCLE_H
#include <QGraphicsSceneMouseEvent>
#include <QtCore/qmath.h>
#include <QGraphicsItem>
#include <QDebug> // for warnings in switch case
#include <QBrush>
#include <QPen>
#include "appstate.h"
/**
 * @brief The CustomCircle class
 * @details This class is a reimplementation of QGraphicsEllipseItem
 * it contains all data a circle needed
 * @author Lars Telöken
 * @version 1.0
 * @date 2019-01-27
 */
class CustomCircle : public QGraphicsEllipseItem
{
private:
    /**
     * @brief m_center - the center member
     * @details the center of an circle
     */
    QPointF m_center;
    /**
     * @brief m_isResizing - the isResizing member
     * @details if the circle have to resize it is on true else on false
     */
    bool m_isResizing;
    /**
     * @brief m_color - the color member
     * @details the color of the circle
     */
    QColor m_color;
    /**
     * @brief m_point - the point member
     * @details contains the position of the circle
     */
    QPointF m_point;
    /**
     * @brief m_width - the width member
     * @details the width of the circle
     */
    qreal m_width;
    /**
     * @brief m_height - the height member
     * @details the height of the circle
     */
    qreal m_height;
    /**
     * @brief m_borderSize - the border size member
     * @details the size of the border of the circle
     */
    qreal m_borderSize;
    /**
     * @brief m_appState - the app state member
     * @details contains the app state with all the standard parameter
     */
    app::AppState *m_appState;
public:
    /**
     * @brief CustomCircle - the constructor of the class
     */
    CustomCircle();
    /**
     * @brief CustomCircle - the constructor of the class
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
    CustomCircle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState);
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
     * This method is called in CustomTextCircle::mousePressEvent, CustomTextPoint::mousePressEvent and in the kind classes of this class
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
     * @brief update - override function
     * @details update the items properties
     * @details This method is called in the kind classes of this class
     */
    void update();
    /**
     * @brief type - get the type of the item
     * @return - returned the item index
     * @details a override function
     * This method is called in App::onSelectedItemSizeChanged
     */
    int type() const;
protected:
    // the following functions are made with the help of https://gist.github.com/csukuangfj/c2a06416062bec9ed99eddd705c21275

    /**
     * @brief mousePressEvent - a override function
     * @param event - the current event of the mouse
     * @details This method is called in CustomCircle
     * it handle the action if a circle is clicked
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseMoveEvent - a override function
     * @param event - the current event of the mouse
     * @details is handle the action if a circle is moved
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseReleaseEvent - a override function
     * @param event - the current event of the mouse
     * @details is danle the action if a circle mouse click is released
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMCIRCLE_H
