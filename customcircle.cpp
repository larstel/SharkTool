#include "customcircle.h"

CustomCircle::CustomCircle(){
    m_isResizing = false;
}

CustomCircle::CustomCircle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState)
{
    //set the member
    this->setColor(brush.color());
    this->setPoint(QPointF(x,y));
    this->setWidth(width);
    this->setHeight(height);
    this->setBorderSize(borderSize);

    m_isResizing = false;

    //create a rectangle
    setRect(x,y,width,height);

    //create a pen for border color and border size
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(this->getColor());
    setPen(pen);
    setColor(brush.color());

    this->setAppState(appState);

    //setFlags
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

QColor CustomCircle::getColor()
{
    return this->m_color;
}

void CustomCircle::setColor(QColor color)
{
    this->m_color = color;
}

QPointF CustomCircle::getPoint()
{
    return this->m_point;
}

void CustomCircle::setPoint(QPointF point)
{
    this->m_point = point;
}

qreal CustomCircle::getWidth()
{
    return this->m_width;
}

void CustomCircle::setWidth(qreal width)
{
    this->m_width = width;
}

qreal CustomCircle::getHeight()
{
    return this->m_height;
}

void CustomCircle::setHeight(qreal height)
{
    this->m_height = height;
}

qreal CustomCircle::getBorderSize()
{
    return this->m_borderSize;
}

void CustomCircle::setBorderSize(qreal borderSize)
{
    this->m_borderSize = borderSize;
}

app::AppState *CustomCircle::getAppState()
{
    return this->m_appState;
}

void CustomCircle::setAppState(app::AppState *appState)
{
    m_appState = appState;
}

void CustomCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        switch(this->m_appState->getSelectedTool()){
            case app::RECTANGLE: {break;} // not used here
            case app::CIRCLE: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, false);
                break;
            }
            case app::TEXT: {break;} // not used here
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
                this->update();
                break;
            }
            case app::RENAME: {break;} // not used here
            case app::BORDER_SIZE: {
                setFlag(QGraphicsItem::ItemIsSelectable, true);
                setFlag(QGraphicsItem::ItemIsMovable, false);

                qreal radius = boundingRect().width() / 2.0;
                m_center = QPointF(boundingRect().topLeft().x()+pos().x()+radius, boundingRect().topLeft().y()+pos().y() + radius);
                m_isResizing = true;
                break;
            }
            default: {
                qWarning() << "Something went wrong - CustomCircle/mousePressEvent";
                break;
            }
        }
    }
    QGraphicsEllipseItem::mousePressEvent(event);
}

void CustomCircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // resize functions
    if(m_isResizing == true && this->m_appState->getSelectedTool() == app::RESIZE){
        QPointF pos = event->scenePos();
        qreal dist = sqrt(pow(m_center.x()-pos.x(),2)+pow(m_center.y()-pos.y(),2)); //calculate the distance between center and mouse
        setRect(m_center.x()-this->pos().x()-dist, m_center.y()-this->pos().y()-dist, dist*2, dist*2);
        this->setHeight(boundingRect().height());
        this->setWidth(boundingRect().width());
    } else if(m_isResizing == true && this->m_appState->getSelectedTool() == app::BORDER_SIZE){
        QPointF pos = event->scenePos();
        qreal dist = sqrt(pow(m_center.x()-pos.x(),2)+pow(m_center.y()-pos.y(),2));//calculate the distance between center and mouse
        this->setBorderSize(dist/10);
        QPen pen;
        pen.setWidth(this->getBorderSize());
        setPen(pen);
    }
    this->setPoint(boundingRect().topLeft());
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void CustomCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_isResizing){
        m_isResizing = false;
    }
    if(event->button() == Qt::LeftButton && event->modifiers() != Qt::ShiftModifier){
        QGraphicsItem::mouseReleaseEvent(event);
    }
    this->setPoint(boundingRect().topLeft());
}

void CustomCircle::update(){
    //change color
    QPen pen;
    pen.setWidth(getBorderSize());
    pen.setBrush(this->getColor());
    setPen(pen);

    //change size
    setRect(getPoint().x(), getPoint().y() , getWidth(), getHeight());

    QGraphicsEllipseItem::update();
}

int CustomCircle::type() const
{
    return UserType+2;
}
