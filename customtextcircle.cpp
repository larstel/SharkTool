#include "customtextcircle.h"

CustomTextCircle::CustomTextCircle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState, QString text)
{
    //setting the member
    this->setColor(brush.color());
    this->setPoint(QPointF(x,y));
    this->setWidth(width);
    this->setHeight(height);
    this->setAppState(appState);
    this->setBorderSize(borderSize);

    this->m_text = text;

    setRect(x,y,width,height); // set a rectangle

    QPen pen;
    pen.setWidth(3);
    pen.setBrush(this->getColor());
    setPen(pen);

    // handle the text item
    this->m_textItem = new QGraphicsTextItem(this);
    this->m_textItem->setPos(getPoint().x()+((boundingRect().width()+20/3)),getPoint().y()-((boundingRect().height()+20)/1.5));

    if(this->getAppState()->getSelectedText().contains("none!@#.<>!!@#", Qt::CaseInsensitive)==true || this->getAppState()->getSelectedText().isEmpty() == true){
        m_textItem->setPlainText(text);
    } else {
        m_textItem->setPlainText(this->getAppState()->getSelectedText());
    }

    this->m_textItem->setScale(getHeight()/30);
    this->m_textItem->setDefaultTextColor(this->getColor());

    this->m_lineItem = new QGraphicsLineItem(this);
    this->m_lineItem->setPen(pen);
    this->m_lineItem->setLine(boundingRect().topRight().x(), boundingRect().topRight().y(), boundingRect().topRight().x()+boundingRect().width()/3, boundingRect().topRight().y()-boundingRect().height()/3);

    //  set flags
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

void CustomTextCircle::setTextItem(QGraphicsTextItem *textItem)
{
    this->m_textItem = textItem;
}

QGraphicsTextItem *CustomTextCircle::getTextItem()
{
    return this->m_textItem;
}

void CustomTextCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        switch(this->getAppState()->getSelectedTool()){
            case app::RECTANGLE: {break;} // not used here
            case app::CIRCLE: {break;} // not used here
            case app::TEXT: {break;} // not used here
            case app::RECTANGLE_TEXT: {break;} // not used here
            case app::CIRCLE_TEXT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, false);
                break;
            }
            case app::POINT_TEXT: {break;} // not used here
            case app::DELETE: {break;} // not used here // deletion in customScene
            case app::SELECT: {break;} // not used here
            case app::RESIZE: {break;} // not used here
            case app::MOVE: {break;} // not used here
            case app::PAINT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);

                this->setColor(this->getAppState()->getToolPropertieSelectedColor());
                this->m_textItem->setDefaultTextColor(this->getColor());
                this->m_lineItem->setPen(QPen(this->getColor(), this->getBorderSize()));

                this->update();
                break;
            }
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
            case app::BORDER_SIZE: {break;} // not used here
            default: {qWarning() << "Something went wrong - CustomTextCircle/mousePressEvent";
            break;
            }
        }
    }
    CustomCircle::mousePressEvent(event);
}

void CustomTextCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && (this->getAppState()->getSelectedTool() == app::RESIZE || this->getAppState()->getSelectedTool() == app::BORDER_SIZE)){
        m_textItem->setScale(getHeight()/30);
        m_textItem->setPos(getPoint().x()+(boundingRect().width()),getPoint().y()-(boundingRect().height()));
        m_lineItem->setLine(boundingRect().topRight().x(), boundingRect().topRight().y(), boundingRect().topRight().x()+boundingRect().width()/3, boundingRect().topRight().y()-boundingRect().height()/3);
    }
    CustomCircle::mouseReleaseEvent(event);
}

int CustomTextCircle::type() const
{
    return UserType+5;
}

CustomTextCircle::~CustomTextCircle(){
    delete this->m_textItem;
    delete this->m_lineItem;
}
