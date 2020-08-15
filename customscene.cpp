#include "customscene.h"

CustomScene::CustomScene(app::AppState *appState){
    m_appState = appState;
}

void CustomScene::setImage(QImage image)
{
    this->m_image = image;
}

QImage CustomScene::getImage()
{
    return this->m_image;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
      if (mouseEvent->button() == Qt::LeftButton)
      {
          app::Tool selectedTool = this->m_appState->getSelectedTool();
          // emit the position of mouse clicks
          switch(selectedTool){
            case app::RECTANGLE: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::CIRCLE: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::TEXT: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::RECTANGLE_TEXT: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::CIRCLE_TEXT: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::POINT_TEXT: {QPointF *point = new QPointF(mouseEvent->scenePos()); emit mouseClicked(point); break;}
            case app::DELETE: {QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform()); removeItem(item); break;}
            case app::SELECT: {break;} // not used here
            case app::RESIZE: {break;} // not used here
            case app::MOVE: {break;} // not used here
            case app::PAINT: {break;} // not used here
            case app::RENAME: {break;} // not used here
            case app::BORDER_SIZE: {break;} // not used here
            default: {qWarning() << "Something went wrong - CustomScene/mousePressEvent"; break;}
      }
    }
      QGraphicsScene::mousePressEvent(mouseEvent);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    emit mouseReleasedOnCustomScene();

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
        emit deleteKeyPressed();
    }
    QGraphicsScene::keyPressEvent(event);
}
