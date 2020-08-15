#include "customtextpoint.h"

CustomTextPoint::CustomTextPoint(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState, QString text)
{
    // set the member
    this->setColor(brush.color());
    this->setPoint(QPointF(x,y));
    this->setWidth(width);
    this->setHeight(height);
    this->setAppState(appState);
    this->setBorderSize(borderSize);

    setRect(x,y,width,height); // set the rectangle

    setBrush(brush);

    this->m_text = text;

    //create a pen to set the border size and color
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(this->getColor());
    setPen(pen);

    // handle the text item
    m_textItem = new QGraphicsTextItem(this);
    m_textItem->setPos(getPoint().x()+((boundingRect().width()+20/3)),getPoint().y()-((boundingRect().height()+20)/1.5));

    if(this->getAppState()->getSelectedText().contains("none!@#.<>!!@#", Qt::CaseInsensitive)==true || this->getAppState()->getSelectedText().isEmpty() == true){
        m_textItem->setPlainText(text);
    } else {
        m_textItem->setPlainText(this->getAppState()->getSelectedText());
    }

    m_textItem->setScale(getHeight()/30);
    m_textItem->setDefaultTextColor(this->getColor());

    m_lineItem = new QGraphicsLineItem(this);
    m_lineItem->setPen(pen);
    m_lineItem->setLine(boundingRect().topRight().x(), boundingRect().topRight().y(), boundingRect().topRight().x()+boundingRect().width()/3, boundingRect().topRight().y()-boundingRect().height()/3);

    // set the flags
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

void CustomTextPoint::setTextItem(QGraphicsTextItem *textItem)
{
    this->m_textItem = textItem;
}

QGraphicsTextItem *CustomTextPoint::getTextItem()
{
    return this->m_textItem;
}

void CustomTextPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        switch(this->getAppState()->getSelectedTool()){
            case app::RECTANGLE: {break;} // not used here
            case app::CIRCLE: {break;} // not used here
            case app::TEXT: {break;} // not used here
            case app::RECTANGLE_TEXT: {break;} // not used here
            case app::CIRCLE_TEXT: {break;} // not used here
            case app::POINT_TEXT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, false);
                break;
            }
            case app::DELETE: {break;} // not used here // deletion in customScene
            case app::SELECT: {break;}
            case app::RESIZE: {break;}
            case app::MOVE: {break;}
            case app::PAINT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);

                this->setColor(this->getAppState()->getToolPropertieSelectedColor());
                setBrush(QBrush(this->getAppState()->getToolPropertieSelectedColor()));

                this->m_textItem->setDefaultTextColor(this->getColor());
                this->m_lineItem->setPen(QPen(this->getColor(), this->getBorderSize()));

                this->update();
                break;}
            case app::RENAME: {
                if(this->getAppState()->getToolPropertieStandardtextChecked() == true && this->getAppState()->getToolPropertieSelectedText().isEmpty() == false){
                    this->m_textItem->setPlainText(this->getAppState()->getToolPropertieSelectedText());
                } else if(this->getAppState()->getToolPropertieStandardtextChecked() == true && this->getAppState()->getToolPropertieSelectedText().isEmpty() == true){
                    this->m_textItem->setPlainText(this->m_text);
                } else if(this->getAppState()->getToolPropertieStandardtextChecked() == false){
                    bool ok;
                    QWidget *widget = new QWidget();
                    QString inputText = QInputDialog::getText(widget, ("Enter text:"), ("Text:"), QLineEdit::Normal, ("Exampletext"), &ok);
                    if (ok && !inputText.isEmpty()){
                        m_textItem->setPlainText(inputText);
                    }
                }
                break;
            }
            case app::BORDER_SIZE: {break;}
            default: {
                qWarning() << "Something went wrong - CustomTextPoint/mousePressEvent";
                break;
            }
        }
    }
    CustomCircle::mousePressEvent(event);
}

void CustomTextPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && (this->getAppState()->getSelectedTool() == app::RESIZE || this->getAppState()->getSelectedTool() == app::BORDER_SIZE)){
        m_textItem->setScale(getHeight()/30);
        m_textItem->setPos(getPoint().x()+(boundingRect().width()),getPoint().y()-(boundingRect().height()));
        m_lineItem->setLine(boundingRect().topRight().x(), boundingRect().topRight().y(), boundingRect().topRight().x()+boundingRect().width()/3, boundingRect().topRight().y()-boundingRect().height()/3);
    }
    CustomCircle::mouseReleaseEvent(event);
}

int CustomTextPoint::type() const
{
    return UserType+6;
}

CustomTextPoint::~CustomTextPoint(){
    delete this->m_lineItem;
    delete this->m_textItem;
}
