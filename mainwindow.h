#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainter>
#include <QMainWindow>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Klasa głównego okna aplikacji.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     * @param parent Wskaźnik na obiekt rodzica.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow();

public slots:
    /**
     * @brief Slot do odczytu danych satelity.
     */
    void readSateliteData();

    /**
     * @brief Slot do obsługi odpowiedzi sieciowej.
     * @param reply Odpowiedź sieciowa.
     */
    void handleNetworkResponse(QNetworkReply *reply);

    /**
     * @brief Funkcja obliczająca współrzędną x satelity na mapie.
     * @param longitude Długość geograficzna satelity.
     * @param mapWidth Szerokość mapy.
     * @return Współrzędna x satelity.
     */
    int calculateSatelliteXCoordinate(double longitude, int mapWidth);

    /**
     * @brief Funkcja obliczająca współrzędną y satelity na mapie.
     * @param latitude Szerokość geograficzna satelity.
     * @param mapHeight Wysokość mapy.
     * @param mapWidth Szerokość mapy.
     * @return Współrzędna y satelity.
     */
    int calculateSatelliteYCoordinate(double latitude, int mapHeight, int mapWidth);

private slots:
    /**
     * @brief Slot obsługujący kliknięcie przycisku.
     */
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    MainWindow *ptr;
    QNetworkRequest request;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QTimer *timer;
    double latitude;
    double longitude;
    double velocity;
};

#endif // MAINWINDOW_H

