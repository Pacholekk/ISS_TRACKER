#include "iss_data.h"
#include "ui_iss_data.h"
#include "qcustomplot.h"
#include "mainwindow.h"

/*!
 * \brief Konstruktor klasy Iss_Data.
 * \param parent Wskaźnik do obiektu nadrzędnego.
 */
Iss_Data::Iss_Data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iss_Data)
{
    ui->setupUi(this);
    setWindowTitle("ISS DATA");
    manager = new QNetworkAccessManager(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Iss_Data::requestData);

    timer->start(1000);

    programTimer.start();
}

/*!
 * \brief Funkcja wysyłająca żądanie sieciowe do API w celu pobrania danych.
 */
void Iss_Data::requestData()
{
    QUrl url("https://api.wheretheiss.at/v1/satellites/25544");
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Iss_Data::processData);
    ui->customplot->addGraph();
}

/*!
 * \brief Funkcja przetwarzająca otrzymane dane i aktualizująca interfejs użytkownika.
 */
void Iss_Data::processData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply && reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        double latitude = obj.value("latitude").toDouble();
        double longitude = obj.value("longitude").toDouble();
        double speed = obj.value("velocity").toDouble();
        double altitude = obj.value("altitude").toDouble();


        updateLatitude(latitude);
        updateLongitude(longitude);
        updateSpeed(speed);
        updatePlot(altitude);
    }

    reply->deleteLater();
}

/*!
 * \brief Funkcja aktualizująca pole tekstowe dla szerokości geograficznej.
 * \param latitude Wartość szerokości geograficznej.
 */
void Iss_Data::updateLatitude(double latitude)
{
    if (latitude < 0) {
        latitude = -latitude;
        QString latitudeStr = QString::number(latitude);
        ui->lati_edit->setText(latitudeStr + "°S");
    } else {
        QString latitudeStr = QString::number(latitude);
        ui->lati_edit->setText(latitudeStr + "°N");
    }
}

/*!
 * \brief Funkcja aktualizująca pole tekstowe dla długości geograficznej.
 * \param longitude Wartość długości geograficznej.
 */
void Iss_Data::updateLongitude(double longitude)
{
    if (longitude < 0) {
        longitude = -longitude;
        QString longitudeStr = QString::number(longitude);
        ui->long_edit->setText(longitudeStr + "°E");
    } else {
        QString longitudeStr = QString::number(longitude);
        ui->long_edit->setText(longitudeStr + "°W");
    }
}

/*!
 * \brief Funkcja aktualizująca pole tekstowe dla prędkości.
 * \param speed Wartość prędkości.
 */
void Iss_Data::updateSpeed(double speed)
{
    QString speedStr = QString::number(speed);
    ui->velo_edit->setText(speedStr + " KM/H");
}


/*!
 * \brief Aktualizuje wykres wysokości w zależności od czasu.
 * \param altitude Wartość wysokości do dodania na wykresie.
 */
void Iss_Data::updatePlot(double altitude)
{
    qint64 elapsedTime = programTimer.elapsed() / 1000.0; // Czas w sekundach od początku działania programu
    x.append(elapsedTime);
    y.append(altitude);

    ui->customplot->graph(0)->setData(x, y);
    ui->customplot->xAxis->setRange(elapsedTime - 10, elapsedTime + 10);
    ui->customplot->yAxis->setRange(405,430);// Zakres osi X ustawiony na 10 sekund wokół bieżącego czasu
    ui->customplot->xAxis->setLabel("Time [s]");
     ui->customplot->yAxis->setLabel("Altitude [km]");
    ui->customplot->replot();
}


/*!
 * \brief Destruktor klasy Iss_Data.
 */
Iss_Data::~Iss_Data()
{
    delete ui;
}






