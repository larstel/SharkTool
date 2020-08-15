#include "app.h"

app::App::App()
    : m_state(new app::AppState),
      m_graphicsPixmapItem(new QGraphicsPixmapItem){
    m_scene = new CustomScene(getAppState());
}

void app::App::onCanvasClicked(){
    Tool selectedTool = this->m_state->getSelectedTool();
        switch(selectedTool){
            case RECTANGLE: {
                // create rectangle on canvas
                CustomRectangle *rectangle = new CustomRectangle(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), 3, QBrush(m_state->getSelectedColor()), getAppState());
                this->getScene()->addItem(rectangle);
                break;}
            case CIRCLE: {
                // create circle on canvas
                CustomCircle *circle = new CustomCircle(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), 3, QBrush(m_state->getSelectedColor()), getAppState());
                this->getScene()->addItem(circle);
                break;}
            case TEXT: {
                // create text on canvas
                CustomText * text = new CustomText(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), QBrush(m_state->getSelectedColor()), getAppState(), "TEXT", m_state->getSelectedTextScale());
                this->getScene()->addItem(text);
                break;}
            case RECTANGLE_TEXT: {
                // create text rectangle on canvas
                CustomTextRectangle *textRectangle = new CustomTextRectangle(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), 3, QBrush(m_state->getSelectedColor()), getAppState(), "TEXT");
                this->getScene()->addItem(textRectangle);
                break;}
            case CIRCLE_TEXT: {
                // create text circle on canvas
                CustomTextCircle *textCircle = new CustomTextCircle(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), 3, QBrush(m_state->getSelectedColor()), getAppState(), "TEXT");
                this->getScene()->addItem(textCircle);
                break;}
            case POINT_TEXT: {
                // create text point on canvas
                CustomTextPoint *textPoint = new CustomTextPoint(m_state->getSelectedPosition()->x()-(m_state->getSelectedWidth()/2), m_state->getSelectedPosition()->y()-(m_state->getSelectedWidth()/2), m_state->getSelectedWidth(), m_state->getSelectedHeight(), 3, QBrush(m_state->getSelectedColor()), getAppState(), "TEXT");
                this->getScene()->addItem(textPoint);
                break;}
            case DELETE: {break;} // not used here
            case SELECT: {break;} // not used here
            case RESIZE: {break;} // not used here
            case MOVE: {break;} // not used here
            case PAINT: {break;} // not used here
            case RENAME: {break;} // not used here
            case BORDER_SIZE: {break;} // not used here
            default: {
                qWarning() << "onCanvasClicked() - something went wrong!";
                break;
            }
        }
}

void app::App::onSelectedItemSizeChanged(qreal size){
    foreach(QGraphicsItem *item, m_scene->items()){
        if(item->isSelected()){
            switch(item->type()){
                case 65537: { // Customrectangle
                    CustomRectangle *rectangle = static_cast<CustomRectangle*>(item);
                    rectangle->setHeight(size);
                    rectangle->setWidth(size);
                    rectangle->update();
                    break;
                }
                case 65538: { // CustomCircle
                    CustomCircle *circle = static_cast<CustomCircle*>(item);
                    circle->setHeight(size);
                    circle->setWidth(size);
                    circle->update();
                    break;
                }
                case 65539: { // CustomText
                    CustomText *text = static_cast<CustomText*>(item);
                    text->setHeight(size);
                    text->setWidth(size);
                    text->update();
                    break;
                }
                case 65540: { // CustomTextrectangle
                    CustomTextRectangle *textRectangle = static_cast<CustomTextRectangle*>(item);
                    textRectangle->setHeight(size);
                    textRectangle->setWidth(size);
                    textRectangle->update();
                    break;
                }
                case 65541: { // CustomTextCircle
                    CustomTextCircle *textCircle = static_cast<CustomTextCircle*>(item);
                    textCircle->setHeight(size);
                    textCircle->setWidth(size);
                    textCircle->update();
                    break;
                }
                case 65542: { // CustomTextPoint
                    CustomTextPoint *textPoint = static_cast<CustomTextPoint*>(item);
                    textPoint->setHeight(size);
                    textPoint->setWidth(size);
                    textPoint->update();
                    break;
                }
                default: {
                    qWarning() << "Somethin went wrong - App/onSelectedItemSizeChanged"; break;
                }
            }

        }
    }
}

void app::App::onSelectedItemBorderSizeChanged(qreal borderSize){
    foreach(QGraphicsItem *item, m_scene->items()){
        if(item->isSelected()){
            switch(item->type()){
                case 65537: { // CustomRectangle
                    CustomRectangle *rectangle = static_cast<CustomRectangle*>(item);
                    rectangle->setBorderSize(borderSize);
                    rectangle->update();
                    break;
                }
                case 65538: { // CustomCircle
                    CustomCircle *circle = static_cast<CustomCircle*>(item);
                    circle->setBorderSize(borderSize);
                    circle->update();
                    break;
                }
                case 65539: {break;} // not used here
                case 65540: { // CustomTextRectangle
                    CustomTextRectangle *textRectangle = static_cast<CustomTextRectangle*>(item);
                    textRectangle->setBorderSize(borderSize);
                    textRectangle->update();
                    break;
                }
                case 65541: { // CustomTextCircle
                    CustomTextCircle *textCircle = static_cast<CustomTextCircle*>(item);
                    textCircle->setBorderSize(borderSize);
                    textCircle->update();
                    break;
                }
                case 65542: { // CustomTextPoint
                    CustomTextPoint *textPoint = static_cast<CustomTextPoint*>(item);
                    textPoint->setBorderSize(borderSize);
                    textPoint->update();
                    break;
                }
                default: {
                    qWarning() << "Somethin went wrong - App/onSelectedItemSizeChanged"; break;
                }
            }

        }
    }
}

void app::App::onItemSelected(){
    foreach(QGraphicsItem *item, m_scene->items()){
        if(item->isSelected()){
            switch(item->type()){
                case 65537: { // CustomRectangle
                    CustomRectangle *rectangle = static_cast<CustomRectangle*>(item);
                    emit signal_selectedItemUpdate(rectangle->getColor(), rectangle->getHeight(), "none!@#.<>!!@#", rectangle->getBorderSize());
                    break;
                }
                case 65538: { // CustomCircle
                    CustomCircle *circle = static_cast<CustomCircle*>(item);
                    emit signal_selectedItemUpdate(circle->getColor(), circle->getHeight(), "none!@#.<>!!@#", circle->getBorderSize());
                    break;
                }
                case 65539: { // CustomText
                    CustomText *text = static_cast<CustomText*>(item);
                    emit signal_selectedItemUpdate(text->getColor(), text->getHeight(), "none!@#.<>!!@#", 0);
                    break;
                }
                case 65540: { // CustomTextRectangle
                    CustomTextRectangle *textRectangle = static_cast<CustomTextRectangle*>(item);
                    emit signal_selectedItemUpdate(textRectangle->getColor(), textRectangle->getHeight(), "none!@#.<>!!@#", textRectangle->getBorderSize());
                    break;
                }
                case 65541: { // CustomTextCircle
                    CustomTextCircle *textCircle = static_cast<CustomTextCircle*>(item);
                    emit signal_selectedItemUpdate(textCircle->getColor(), textCircle->getHeight(), "none!@#.<>!!@#", textCircle->getBorderSize());
                    break;
                }
                case 65542: { // CustomTextpoint
                    CustomTextPoint *textPoint = static_cast<CustomTextPoint*>(item);
                    emit signal_selectedItemUpdate(textPoint->getColor(), textPoint->getHeight(), "none!@#.<>!!@#", textPoint->getBorderSize());
                    break;
                }
                default: {
                    qWarning() << "Something went wrong - App/OnItemSelected"; break;
                }
            }
        }
    }
}

/**
 * @brief app::App::removeSelectedItems
 */
void app::App::removeSelectedItems(){
    while(!getScene()->selectedItems().isEmpty()){
        getScene()->removeItem(getScene()->selectedItems().front());
    }
}

void app::App::createJson(QString filePath){
    JsonHelper::createJson(filePath, getScene());
}

void app::App::readJson(QString filePath){
    JsonHelper::readJson(filePath, getScene(), getAppState());
}

void app::App::setScene(CustomScene *scene){
    this->m_scene = scene;
}

CustomScene *app::App::getScene(){
    return this->m_scene;
}

void app::App::setAppState(app::AppState *appState){
    this->m_state = appState;
}

app::AppState *app::App::getAppState(){
    return this->m_state;
}

void app::App::setGraphicsPixmapItem(QGraphicsPixmapItem *graphicsPixmapItem){
    this->m_graphicsPixmapItem = graphicsPixmapItem;
}

QGraphicsPixmapItem *app::App::getGraphicsPixmapItem(){
    return this->m_graphicsPixmapItem;
}

app::App::~App(){
    delete this->m_scene;
    delete this->m_state;
    delete this->m_graphicsPixmapItem;
}
