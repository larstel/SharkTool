#include "customrectangle.h"

CustomRectangle::CustomRectangle(){
    m_isResizing = false;
}

CustomRectangle::CustomRectangle(qreal x, qreal y, qreal width, qreal height, qreal borderSize, QBrush brush, app::AppState *appState)
{
    // setting the member
    this->setColor(brush.color());
    this->setPoint(QPointF(x,y));
    this->setWidth(width);
    this->setHeight(height);
    this->setBorderSize(borderSize);
    this->setAppState(appState);

    m_isResizing = false;

    setRect(x,y,width,height); // create a rectangle

    //set the pen for border size and color
    QPen pen;
    pen.setWidth(this->getBorderSize());
    pen.setBrush(this->getColor());
    setPen(pen);
    setColor(brush.color());
    this->setBrush(brush);

    // set the flags
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

QColor CustomRectangle::getColor()
{
    return this->m_color;
}

void CustomRectangle::setColor(QColor color)
{
    this->m_color = color;
}

QPointF CustomRectangle::getPoint()
{
    return this->m_point;
}

void CustomRectangle::setPoint(QPointF point)
{
    this->m_point = point;
}

qreal CustomRectangle::getWidth()
{
    return this->m_width;
}

void CustomRectangle::setWidth(qreal width)
{
    this->m_width = width;
}

qreal CustomRectangle::getHeight()
{
    return this->m_height;
}

void CustomRectangle::setHeight(qreal height)
{
    this->m_height = height;
}

QBrush CustomRectangle::getBrush()
{
    return this->m_brush;
}

void CustomRectangle::setBrush(QBrush brush)
{
    this->m_brush = brush;
}

qreal CustomRectangle::getBorderSize()
{
    return this->m_borderSize;
}

void CustomRectangle::setBorderSize(qreal borderSize)
{
    this->m_borderSize = borderSize;
}

app::AppState *CustomRectangle::getAppState()
{
    return this->m_appState;
}

void CustomRectangle::setAppState(app::AppState *appState)
{
    this->m_appState = appState;
}

void CustomRectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        switch(this->m_appState->getSelectedTool()){
            case app::RECTANGLE: {
                setFlag(QGraphicsItem::ItemIsMovable, false);
                setFlag(QGraphicsItem::ItemIsSelectable, false);
                break;
            }
            case app::CIRCLE: {break;} // not used here
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
                break;}
            case app::MOVE: {
                setFlag(QGraphicsItem::ItemIsMovable, true);
                //setFlag(QGraphicsItem::ItemIsSelectable, false);
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
                qWarning() << "Something went wrong - CustomRectangle/mousePressEvent";
                break;
            }
        }
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void CustomRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isResizing == true && this->m_appState->getSelectedTool() == app::RESIZE){
        QPointF pos = event->scenePos();
        qreal dist = sqrt(pow(m_center.x()-pos.x(),2)+pow(m_center.y()-pos.y(),2));//calculate the distance between center and mouse
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
    QGraphicsRectItem::mouseMoveEvent(event);
}

void CustomRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_isResizing){
        m_isResizing = false;
        //setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
    if(event->button() == Qt::LeftButton && event->modifiers() != Qt::ShiftModifier){

    }
    this->setPoint(boundingRect().topLeft());
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void CustomRectangle::update(){
    //change color
    QPen pen;
    pen.setWidth(getBorderSize());
    pen.setBrush(this->getColor());
    setPen(pen);

    //change size
    setRect(getPoint().x(), getPoint().y() , getWidth(), getHeight());

    QGraphicsRectItem::update();
}

int CustomRectangle::type() const
{
    return UserType+1;
}
