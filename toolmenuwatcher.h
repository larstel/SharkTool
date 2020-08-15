#ifndef TOOLMENUWATCHER_H
#define TOOLMENUWATCHER_H
#include <QObject>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
/**
 * @brief The ToolMenuWatcher class
 * @details It implements filter for the Toolmenu in the program
 * it detects button presses and mouse hover and change the behavior of the pushButtons in the menu
 * @author Lars Telöken
 * @version 1.0
 * @date 2018-12-08
 */
class ToolMenuWatcher : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ToolMenuWatcher - the constructor of the class
     * @details it sets the parent
     */
    ToolMenuWatcher();
    /**
     * @brief ToolMenuWatcher - another constructor of the class
     * @param parent - is set to nullptr if no parent is called
     */
    explicit ToolMenuWatcher(QObject * parent = Q_NULLPTR);
    /**
     * @brief eventFilter - filter for the Toolmenu in the GUI
     * @param watched - contains the object which this class is watching
     * @param event - contains which event is on the object
     * @return - returned true if an special event is taken else false
     * @details - it implements that it recognize wenn a mouse hovered on and of a button and setting a new style to the buttons
     * Additionally it recognize if a button is clicked and emit an signal to the GUI
     */
    virtual bool eventFilter(QObject * watched, QEvent * event) Q_DECL_OVERRIDE;
signals:
    /**
     * @brief signal_toolButtonLeftClicked - a signal connected with the GUI
     * @details - the signal if a menubutton was clicked
     */
    void signal_toolButtonLeftClicked(QObject*);
};


#endif // TOOLMENUWATCHER_H
