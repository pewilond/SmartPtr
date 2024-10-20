#include <iostream>
#include "displayCharts.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QMainWindow>

void displayCharts(
        const std::vector<int>& elementCounts,
        const std::vector<double>& customTimes,
        const std::vector<double>& standardTimes
) {
    int argc = 0;
    char* argv[] = { nullptr };
    QApplication app(argc, argv);

    QChart* chart = new QChart();
    chart->setTitle("Сравнение времени выполнения");

    QLineSeries* customSeries = new QLineSeries();
    customSeries->setName("Кастомные умные указатели");

    QLineSeries* standardSeries = new QLineSeries();
    standardSeries->setName("Стандартные умные указатели");

    for (size_t i = 0; i < elementCounts.size(); ++i) {
        customSeries->append(elementCounts[i], customTimes[i]);
        standardSeries->append(elementCounts[i], standardTimes[i]);
    }

    chart->addSeries(customSeries);
    chart->addSeries(standardSeries);

    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("Количество элементов");
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    customSeries->attachAxis(axisX);
    standardSeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Время (мс)");
    chart->addAxis(axisY, Qt::AlignLeft);
    customSeries->attachAxis(axisY);
    standardSeries->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPixmap pixmap = chartView->grab();
    QString filename = "chart.png";
    if (pixmap.save(filename)) {
        std::cout << "Chart saved in: " << filename.toStdString() << "\n";
    } else {
        std::cout << "Save file failed.\n";
    }

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    app.exec();
}
