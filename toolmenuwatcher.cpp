#include "toolmenuwatcher.h"

ToolMenuWatcher::ToolMenuWatcher(QObject * parent) :
    QObject(parent){
}

bool ToolMenuWatcher::eventFilter(QObject *watched, QEvent *event)
{
    QPushButton *button = qobject_cast<QPushButton*>(watched);

    if (!button) {
        return false;
    }

    // hovered by mouse
    if (event->type() == QEvent::Enter) {
        button->setStyleSheet("border: 2px solid #8f8f91");
        return true;

    }
    // not hovered by mouse
    if (event->type() == QEvent::Leave){
        button->setStyleSheet("border: none");
        return true;
    }

    // pressed by mouse
    if(event->type() == QEvent::MouseButtonPress){
        auto mouseEvent = (QMouseEvent*)event;
        if (mouseEvent->button() == Qt::LeftButton){
            emit signal_toolButtonLeftClicked(watched);
            }
        }

    return false;
}
