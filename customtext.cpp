#include "customtext.h"

CustomText::CustomText(qreal x, qreal y, qreal width, qreal height, QBrush brush, app::AppState *appState, QString text, qreal textScale)
{
    // set the member of this class
    this->setColor(brush.color());
    this->setPoint(QPointF(x,y));
    this->setWidth(width);
    this->setHeight(height);
    this->m_appState = appState;

    this->m_isResizing = false;
    this->m_text = text;

    this->m_textScale = textScale;

    // set the flags
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);


    setWidth(this->getWidth());
    setHeight(this->getHeight());
    setColor(brush.color());
    setPos(getPoint());

    setDefaultTextColor(this->m_color);

    // handle the plain text
    if(this->m_appState->getSelectedText().contains("none!@#.<>!!@#", Qt::CaseInsensitive)==true || this->m_appState->getSelectedText().isEmpty() == true){
        setPlainText(this->m_text);
    } else if(this->m_appState->getSelectedText().isEmpty() == false){
        setPlainText(this->m_appState->getSelectedText());
    }
    setScale(textScale);
}

QColor CustomText::getColor()
{
    return this->m_color;
}

void CustomText::setColor(QColor color)
{
    this->m_color = color;
}

QPointF CustomText::getPoint()
{
    return this->m_point;
}

void CustomText::setPoint(QPointF point)
{
    this->m_point = point;
}

qreal CustomText::getWidth()
{
    return this->m_width;
}

void CustomText::setWidth(qreal width)
{
    this->m_width = width;
}

qreal CustomText::getHeight()
{
    return this->m_height;
}

void CustomText::setHeight(qreal height)
{
    this->m_height = height;
}

QString CustomText::getText()
{
    return this->m_text;
}

void CustomText::setText(QString text)
{
    this->m_text = text;
    setPlainText(text);
}

qreal CustomText::getTextScale()
{
    return this->m_textScale;
}

void CustomText::setTextScale(qreal scale)
{
    this->m_textScale = scale;
}

void CustomText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        switch(this->m_appState->getSelectedTool()){
            case app::RECTANGLE: {break;} // not used here
            case app::CIRCLE: {break;} // not used here
            case app::TEXT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, false);
                break;
            }
            case app::RECTANGLE_TEXT: {break;} // not used here
            case app::CIRCLE_TEXT: {break;} // not used here
            case app::POINT_TEXT: {break;} // not used here
            case app::DELETE: {break;} // not used here // deletion in customScene
            case app::SELECT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, true);
                setSelected(true);
                break;
            }
            case app::RESIZE: {
                setFlag(QGraphicsItem::ItemIsSelectable, true);

                qreal radius = boundingRect().width() / 2.0;
                m_center = QPointF(boundingRect().topLeft().x()+pos().x()+radius, boundingRect().topLeft().y()+pos().y() + radius);
                m_isResizing = true;
                break;
            }
            case app::MOVE: {
                setFlag(QGraphicsItem::ItemIsMovable, true);
                break;
            }
            case app::PAINT: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                this->m_color = this->m_appState->getToolPropertieSelectedColor();
                setDefaultTextColor(this->m_color);
                this->update();
                break;
            }
            case app::RENAME: {
                if(this->m_appState->getToolPropertieStandardtextChecked() == true && this->m_appState->getToolPropertieSelectedText().isEmpty() == false){
                    this->setPlainText(this->m_appState->getToolPropertieSelectedText());
                } else if(this->m_appState->getToolPropertieStandardtextChecked() == true && this->m_appState->getToolPropertieSelectedText().isEmpty() == true){
                    this->setPlainText(this->m_text);
                } else if(this->m_appState->getToolPropertieStandardtextChecked() == false){
                    bool ok;
                    QWidget *widget = new QWidget();
                    QString inputText = QInputDialog::getText(widget, ("Enter text:"), ("Text:"), QLineEdit::Normal, ("Exampletext"), &ok);
                    if (ok && !inputText.isEmpty()){
                        this->setPlainText(inputText);
                    }
                }
                break;
            }
            case app::BORDER_SIZE: {break;}
            default: {
                qWarning() << "Something went wrong - CustomText/mousePressEvent";
                break;
            }
        }
    }

    QGraphicsTextItem::mousePressEvent(event);
}

void CustomText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isResizing == true){        
        QPointF pos = event->scenePos();
        qreal dist = sqrt(pow(m_center.x()-pos.x(),2)+pow(m_center.y()-pos.y(),2));//calculate the distance between center and mouse
        qreal x = m_center.x()-this->pos().x()-dist;
        qreal y = m_center.y()-this->pos().y()-dist;
        this->setHeight(x);
        this->setWidth(y);
        setTextScale(getHeight());
        setScale(getHeight());
    }
    this->setPoint(boundingRect().topLeft());
    QGraphicsTextItem::mouseMoveEvent(event);
}

void CustomText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton && m_isResizing){
        m_isResizing = false;
    }
    if(event->button() == Qt::LeftButton && event->modifiers() != Qt::ShiftModifier){ // select multiple items with shift key
        QGraphicsTextItem::mouseReleaseEvent(event);
    }
    this->setPoint(boundingRect().topLeft());
}

int CustomText::type() const
{
    return UserType+3;
}
