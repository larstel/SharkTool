#ifndef CUSTOMTEXTCIRCLE_H
#define CUSTOMTEXTCIRCLE_H
#include <QInputDialog>
#include "customcircle.h"
/**
 * @brief The CustomTextCircle class
 * @details This class is a reimplementation of CustomCircle
 * it contains all data a circle with text needed
 * @author Lars Telöken
 * @version 1.0
 * @date 2019-01-27
 */
class CustomTextCircle : public CustomCircle
{
private:
    /**
     * @brief m_textItem - the text item member
     * @details contains the text item of the textCircle
     */
    QGraphicsTextItem *m_textItem;
    /**
     * @brief m_lineItem - the line item member
     * @details contains the line item of the textCircle
     */
    QGraphicsLineItem *m_lineItem;
    /**
     * @brief m_text - the text member
     * @details contains the text of the textCircle
     */
    QString m_text;
public:
    /**
     * @brief CustomTextCircle - the constructor of the class
     * @param x - the x position of the item
     * @param y - the y position of the item
     * @param width - the width of the item
     * @param height - the heigth oft the item
     * @param borderSize - the border size of the item
     * @param brush - the brush of the item
     * @param appState - the app state of the item
     * @param text - the text of the item
     */
    CustomTextCircle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState, QString text);
    /**
     * @brief setTextItem - setter of text item
     * @param textItem - the current text item
     * @details set the current text item
     */
    void setTextItem(QGraphicsTextItem *textItem);
    /**
     * @brief getTextItem - getter of text item
     * @return  - returned the text item of the item
     * @details get the current text item
     */
    QGraphicsTextItem *getTextItem();
    /**
     * @brief type - get the type of the item
     * @return - returned the item index
     * @details a override function
     * This method is called in App::onSelectedItemSizeChanged
     */
    int type() const;
    /**
     * @brief ~CustomTextCircle - the destructor of the class
     */
    ~CustomTextCircle();
protected:
    // the following functions are made with the help of https://gist.github.com/csukuangfj/c2a06416062bec9ed99eddd705c21275
    /**
     * @brief mousePressEvent - a override function
     * @param event - the current event of the mouse
     * @details This method is called in CustomCircle
     * it handle the action if a textCircle is clicked
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseReleaseEvent - a override function
     * @param event - the current event of the mouse
     * @details is danle the action if a textCircle mouse click is released
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMTEXTCIRCLE_H
