#ifndef APP_H
#define APP_H
#include "appstate.h"
#include "customscene.h"
#include "jsonhelper.h"
#include "customrectangle.h"
#include "customcircle.h"
#include "customtext.h"
#include "customtextrectangle.h"
#include "customtextcircle.h"
#include "customtextpoint.h"

namespace app {
    /**
     * @brief The App class
     * @details This class contains essential program features
     * it handle the item creation and the update progress of the items and the GUI
     * @author Lars Telöken
     * @version 1.0
     * @date 2019-01-27
     */
    class App : public QObject
    {
        Q_OBJECT
    signals:
        /**
         * @brief signal_selectedItemUpdate - A signal which getting the Items properties and emit them
         * @param color - the color of an item
         * @param height - the height of an item
         * @param text - the text of an item
         * @param borderSize - the border size of an item
         * @details This method is called in app::onCanvasClicked
         * It get the items properties and emit them to the GUI
         */
        void signal_selectedItemUpdate(QColor color, qreal height, QString text, qreal borderSize);
    public slots:
        /**
         * @brief onCanvasClicked - slot which is triggered when a click on the canvas is recognized
         * @details This method is called in a connect in the MainWindow
         * It creates an Item on the clicked position on the canvas
         */
        void onCanvasClicked();
        /**
         * @brief removeSelectedItems - slot which removes selected items
         * @details This method is called in a connect in the MainWindow
         * It iterates threw a list of selectedItems and delete them
         */
        void removeSelectedItems();
        /**
         * @brief createJson - creates a Json file with all elements on the canvas
         * @param filePath - the path where the file is saved
         * @details This method is called in MainWindow::on_actionSave_triggered
         * It calls the JsonHelper class to create a json file
         */
        void createJson(QString filePath);
        /**
         * @brief readJson - read a Json file with all elements on the canvas
         * @param filePath - the path where the file is saved
         * @details This method is called in MainWindow::on_actionOpen_triggered
         * It calls the JsonHelper class to read a json file
         */
        void readJson(QString filePath);
        /**
         * @brief onSelectedItemSizeChanged - updates the items if the properties are changed in the GUI
         * @param size - the new size of an item
         * @details This method is called in a connect in the MainWindow
         * It update the size of the items if the GUI change their size
         */
        void onSelectedItemSizeChanged(qreal size);
        /**
         * @brief onSelectedItemBorderSizeChanged - updates the itmes if the properties are changed in the GUI
         * @param borderSize - the new border size of an items border
         * @details This method is called in a connect in the MainWindow
         * It update the border size of the otems if the GUI change their size
         */
        void onSelectedItemBorderSizeChanged(qreal borderSize);
        /**
         * @brief onItemSelected - update the properties in the GUI if an item is selected
         * @details This method is called in a connect in the MainWindow
         * With the help of this method you can select an item on the canvas and the spinboxes etc are changing their values to the selcted item value
         */
        void onItemSelected();
    private:
        /**
         * @brief m_scene - the scenen on which all items are added
         * @details This member is initialized in the Constructor of the App class
         */
        CustomScene *m_scene;
        /**
         * @brief m_state - contains the app states
         * @details This member contains important data about the project
         */
        AppState *m_state;
        /**
         * @brief m_graphicsPixmapItem - contains the background image of the scene
         * @details This member contains the image of the scene to get it on multiply functions
         */
        QGraphicsPixmapItem *m_graphicsPixmapItem;
    public:
        /**
         * @brief Constructor - the contructor of the class
         * @details creates objects of QGraphicsPixmapItem, CustomScene and the AppState
         */
        App();
        /**
         * @brief setGraphicsPixmapItem - setter of the graphicsPixmapItem
         * @param graphicsPixmapItem - the item
         * @details This method is called in MainWindow::on_actionImport_triggered
         */
        void setGraphicsPixmapItem(QGraphicsPixmapItem *graphicsPixmapItem);
        /**
         * @brief getGraphicsPixmapItem - getter of the graphicsPixmapItem
         * @return returned the graphicsPixmapitem
         * @details This method is called in MainWindow::resizeEvent
         */
        QGraphicsPixmapItem *getGraphicsPixmapItem();
        /**
         * @brief setScene - setter of the scene
         * @param scene - contains geometry forms
         * @details This method is called in MainWindow::initializeGuiElements
         */
        void setScene(CustomScene *scene);
        /**
         * @brief getScene - getter of the scene
         * @return returned a scene
         * @details This method is called in MainWindow::on_actionImport_triggered, MainWindow::initializeGuiElements and in connects in the MainWindow
         */
        CustomScene *getScene();
        /**
         * @brief setAppState - setter of the appState
         * @param appState - state of the program
         */
        void setAppState(AppState *appState);
        /**
         * @brief getAppState - getter of the appState
         * @return returned appState
         * @details This method is called in MainWindow::initializeGuiElements, MainWindow::onGuiEnabledChanged, MainWindow::on_pushButton_toolPropertieColor_clicked,
         * MainWindow::on_pushButton_toolPropertieColor_clicked, MainWindow::setTextToolsGuiVisible, MainWindow::on_toolButtonLeftClicked and in connects in the MainWindow
         */
        AppState *getAppState();
        /**
         * @brief Destructor - destructor of the class
         */
        ~App();
    };
}


#endif // APP_H
