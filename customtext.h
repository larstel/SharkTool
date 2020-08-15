#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H
#include <QGraphicsSceneMouseEvent>
#include <QDebug> // for warning in switch case
#include <QtCore/qmath.h>
#include <QBrush>
#include <QInputDialog>
#include "appstate.h"
/**
 * @brief The CustomText class
 * @details This class is a reimplementation of QGraphicsTextItem
 * it contains all data a text needed
 * @author Lars Telöken
 * @version 1.0
 * @date 2019-01-27
 */
class CustomText : public QGraphicsTextItem
{
private:
    /**
     * @brief m_center - the center member
     * @details the center of an text
     */
    QPointF m_center;
    /**
     * @brief m_isResizing - the isResizing member
     * @details if the text have to resize it is on true else on false
     */
    bool m_isResizing;
    /**
     * @brief m_color - the color member
     * @details the color of the text
     */
    QColor m_color;
    /**
     * @brief m_point - the point member
     * @details contains the position of the text
     */
    QPointF m_point;
    /**
     * @brief m_width - the width member
     * @details the width of the text
     */
    qreal m_width;
    /**
     * @brief m_height - the height member
     * @details the height of the text
     */
    qreal m_height;
    /**
     * @brief m_appState - the app state member
     * @details contains the app state with all the standard parameter
     */
    app::AppState *m_appState;
    /**
     * @brief m_text - the text member
     * @details contains the text of the item
     */
    QString m_text;
    /**
     * @brief m_textScale the text scale member
     * @details contains the text scale of the item
     */
    qreal m_textScale;
public:
    /**
     * @brief CustomText - the constructor of the class
     * @param x - the x position of the item
     * @param y - the y position of the item
     * @param width - the width of the item
     * @param height - the height of the item
     * @param brush - the brush of the item
     * @param appState - the app state of the item
     * @param text - the text of the item
     * @param textScale - the txt scale of the item
     */
    CustomText(qreal x, qreal y, qreal width, qreal height, QBrush brush, app::AppState *appState, QString text, qreal textScale);
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
     * @brief getText - getter of text
     * @return - returned the current text
     * @details get the current text
     */
    QString getText();
    /**
     * @brief setText - setter of text
     * @param text - the current text
     * @details set the current text
     * This method is called in JsonHelper::readJson
     */
    void setText(QString text);
    /**
     * @brief getTextScale - getter of text scale
     * @return - returned the current text scale
     * @details get the current text scale
     * This method is called in JsonHelper::createJson
     */
    qreal getTextScale();
    /**
     * @brief setTextScale - setter of text scale
     * @param scale - the current scale
     * @details set the current text scale
     */
    void setTextScale(qreal scale);

    int type() const;
protected:
    // the following functions are made with the help of https://gist.github.com/csukuangfj/c2a06416062bec9ed99eddd705c21275
    /**
     * @brief mousePressEvent - a override function
     * @param event - the current event of the mouse
     * @details This method is called in CustomCircle
     * it handle the action if a text is clicked
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseMoveEvent - a override function
     * @param event - the current event of the mouse
     * @details is handle the action if a text is moved
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseReleaseEvent - a override function
     * @param event - the current event of the mouse
     * @details is danle the action if a text mouse click is released
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // CUSTOMTEXT_H
