#include "appstate.h"

app::AppState::AppState()
    : m_selectedTool(RECTANGLE), m_selectedColor(Qt::GlobalColor::black), m_selectedWidth(50), m_selectedHeight(50), m_selectedPosition(nullptr), m_SelectedTextScale(2){
}

app::Tool app::AppState::getSelectedTool()
{
    return this->m_selectedTool;
}

void app::AppState::setSelectedTextScale(qreal textScale)
{
    this->m_SelectedTextScale = textScale;
    emit signal_textScaleChanged(textScale);
}

void app::AppState::setSelectedText(QString text)
{
    this->m_selectedText = text;
}

void app::AppState::setToolPropertieSelectedText(QString text)
{
    this->m_toolPropertieSelectedText = text;
}

void app::AppState::setToolPropertieStandardtextChecked(bool isChecked)
{
    this->m_isToolPropertieStandardTextChecked = isChecked;
}

void app::AppState::setToolPropertieSelectedBorder(qreal border)
{
    this->m_toolPropertieSelectedBorder = border;
}

void app::AppState::setSelectedTool(Tool tool){
    if(tool != this->m_selectedTool){
        this->m_selectedTool = tool;
        emit toolChanged(tool);
    }
}

void app::AppState::setSelectedTool(qint8 tool){
    if(tool != this->m_selectedTool){
        this->m_selectedTool = static_cast<Tool>(tool);
        emit toolChanged(tool);
    }
}

QColor app::AppState::getSelectedColor(){
    return this->m_selectedColor;
}

QColor app::AppState::getToolPropertieSelectedColor()
{
    return this->m_toolPropertieSelectedColor;
}

void app::AppState::setSelectedColor(QColor color){
    this->m_selectedColor = color;
}

void app::AppState::setToolPropertieSelectedColor(QColor color)
{
    this->m_toolPropertieSelectedColor = color;
}

qreal app::AppState::getSelectedWidth(){
    return this->m_selectedWidth;
}

qreal app::AppState::getToolPropertieSelectedWidth()
{
    return this->m_toolPropertieSeletedWidth;
}

void app::AppState::setSelectedWidth(qreal width){
    if(width != this->m_selectedWidth){
        this->m_selectedWidth = width;
        emit widthChanged(width);
    }
}

void app::AppState::setToolPropertieSelectedWidth(qreal width)
{
    this->m_toolPropertieSeletedWidth = width;
}

qreal app::AppState::getSelectedHeight()
{
    return this->m_selectedHeight;
}

qreal app::AppState::getToolPropertieSelectedHeight()
{
    return this->m_toolPropertieSelectedHeight;
}

void app::AppState::setSelectedHeight(qreal height)
{
    if(height != this->m_selectedHeight){
        this->m_selectedHeight = height;
        emit heightChanged(height);
    }
}

void app::AppState::setToolPropertieSelectedHeight(qreal height)
{
    this->m_toolPropertieSelectedHeight = height;
}

QPointF *app::AppState::getSelectedPosition()
{
    return this->m_selectedPosition;
}


void app::AppState::setSelectedPosition(QPointF *selectedPosition)
{
    this->m_selectedPosition = selectedPosition;
}

qreal app::AppState::getSelectedTextScale()
{
    return this->m_SelectedTextScale;
}

QString app::AppState::getSelectedText()
{
    return this->m_selectedText;
}

QString app::AppState::getToolPropertieSelectedText()
{
    return this->m_toolPropertieSelectedText;
}

bool app::AppState::getToolPropertieStandardtextChecked()
{
    return this->m_isToolPropertieStandardTextChecked;
}

app::AppState::~AppState()
{
    delete this->m_selectedPosition;
}
