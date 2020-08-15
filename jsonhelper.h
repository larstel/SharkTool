#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QTime>
#include <QBuffer>
#include <customscene.h>
#include "customcircle.h"
#include "customrectangle.h"
#include "customtext.h"
#include "customtextrectangle.h"
#include "customtextcircle.h"
#include "customtextpoint.h"
/**
 * @brief The JsonHelper class
 * @details It implements method to read and write Json files
 * @author Lars Telöken
 * @version 1.0
 * @date 2018-12-08
 */
class JsonHelper
{
public:
    /**
     * @brief createJson - write all items and their properties into a json file
     * @param filePath - the file path if the json file
     * @param scene - contains the scene to grab all items
     * @details This method is called in App::createJson
     * save all items and their propertie and the background image to a json file
     */
    static void createJson(QString filePath, CustomScene *scene);
    /**
     * @brief readJson - read all items and their properties from a json file
     * @param filePath - the file path where the file can be found
     * @param scene - the scene to load all items to it
     * @param appState - the appstate to load all standard properties from the json to the program
     * @details This method is called in App::readJson
     * read all items and their propertie and the bockground image from a json file
     */
    static void readJson(QString filePath, CustomScene *scene, app::AppState *appState);
private:
    /**
     * @brief jsonValFromPixmap
     * @param p - the pixmap
     * @return - returned the pixmap as Base64
     * @details This method is called in JsonHelper::createJson
     * It convert the image to Base64
     * this method is on the basis of https://github.com/KubaO/stackoverflown/blob/master/questions/pixmap-to-json-32376119/main.cpp
     */
    static QJsonValue jsonValFromPixmap(const QPixmap &p);
    /**
     * @brief pixmapFrom
     * @param val - the Base64 data
     * @return - returned the image back
     * @details This method is called in JsonHelper::readJson
     * It convert the Base64 back to an image
     * this method is on the basis of https://github.com/KubaO/stackoverflown/blob/master/questions/pixmap-to-json-32376119/main.cpp
     */
    static QPixmap pixmapFrom(const QJsonValue &val);
};

#endif // JSONHELPER_H
