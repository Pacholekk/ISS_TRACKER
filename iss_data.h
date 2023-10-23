#ifndef ISS_DATA_H
#define ISS_DATA_H

#include <QDialog>
#include <string>
#include <QWidget>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <QElapsedTimer>


#include "mainwindow.h"
namespace Ui {
class Iss_Data;
}

/*!
 * \brief Klasa reprezentująca dialog z danymi ISS.
 */
class Iss_Data : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor klasy Iss_Data.
     * \param parent Wskaźnik do obiektu rodzica.
     */
    explicit Iss_Data(QWidget *parent = nullptr);

    /*!
     * \brief Przetwarza odebrane dane.
     */
    void processData();

    /*!
     * \brief Aktualizuje prędkość.
     * \param speed Aktualna prędkość.
     */
    void updateSpeed(double speed);

    /*!
     * \brief Aktualizuje długość geograficzną.
     * \param longitude Aktualna długość geograficzna.
     */
    void updateLongitude(double longitude);

    /*!
     * \brief Aktualizuje szerokość geograficzną.
     * \param latitude Aktualna szerokość geograficzna.
     */
    void updateLatitude(double latitude);

    /*!
     * \brief Wysyła żądanie o dane.
     */
    void requestData();

    /*!
     * \brief Aktualizuje wykres wysokości w zależności od czasu.
     * \param altitude Wartość wysokości do dodania na wykresie.
     */
    void updatePlot(double altitude);

    /*!
     * \brief Destruktor klasy Iss_Data.
     */
    ~Iss_Data();

public slots:


private slots:


private:

    Ui::Iss_Data *ui;
    MainWindow *ptr;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QTimer *timer;
    QVector<double> x; // Czas trwania programu (osi X)
    QVector<double> y; // Wysokość (osi Y)
    QElapsedTimer programTimer;
    double latitude;
    double longitude;
    double speed;

};

#endif // ISS_DATA_H
