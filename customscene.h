#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug> // needed for warnings in switch case
#include "appstate.h"
/**
 * @brief The CustomScene class
 * @details This class is a reimplementation of QGraphicsScene
 * it contains all data a scene needed
 * @author Lars Telöken
 * @version 1.0
 * @date 2019-01-27
 */
class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief CustomScene - the constructor of the class
     * @param appState - the appstate
     * @details This constructor is called in the contructor of App class
     * The constructor set the app state member
     */
    CustomScene(app::AppState *appState);
    /**
     * @brief setImage - setter of the image
     * @param image - the background image of the scene
     * @details This method is called in MainWindow::on_actionImport_triggered and JsonHelper::readJson
     */
    void setImage(QImage image);
    /**
     * @brief getImage - the getter of the image
     * @return - returned the background image of a scene
     * @details This method is called in Jsonhelper::createJson
     */
    QImage getImage();
private:
    /**
     * @brief m_appState - the app state member
     * @details the app state with all standard data
     */
    app::AppState *m_appState;
    /**
     * @brief m_image - the image member
     * @details the member contains the background image of the scene
     */
    QImage m_image;
signals:
    /**
     * @brief mouseClicked - signal
     * @details emit the mouse point to the app and app state if the scene was clicked
     */
    void mouseClicked(QPointF*);
    /**
     * @brief deleteKeyPressed - signal
     * @details emit if the keyboard delte button is pressed
     * activate the selete command in the App class
     */
    void deleteKeyPressed();
    /**
     * @brief mouseReleasedOnCustomScene
     */
    void mouseReleasedOnCustomScene();
protected:
    // the following functions are made with the help of https://gist.github.com/csukuangfj/c2a06416062bec9ed99eddd705c21275

    /**
     * @brief mousePressEvent - a override function
     * @param event - the current event of the mouse
     * @details This method is called in CustomCircle
     * it handle the action if the scene is clicked
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /**
     * @brief mouseMoveEvent - a override function
     * @param event - the current event of the mouse
     * @details is handle the action if the scene is moved
     */
    void keyPressEvent(QKeyEvent *mouseEvent);
    /**
     * @brief mouseReleaseEvent - a override function
     * @param event - the current event of the mouse
     * @details is danle the action if the scene mouse click is released
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // CUSTOMSCENE_H
