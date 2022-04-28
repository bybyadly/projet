#include "elaawindow.h"
#include "ui_elaawindow.h"
#include <QMessageBox>

#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QtPrintSupport/QPrinter>

#include <QTextDocument>
#include <QTextStream>

#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QTextDocument>


elaawindow::elaawindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::elaawindow)
{
    ui->setupUi(this);
}

elaawindow::~elaawindow()
{
    delete ui;
}


void elaawindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_Nom->text();
    QString categorie = ui->lineEdit_2->text();
    QString adresse = ui->lineEdit_ID_4->text();
    QString email = ui->lineEdit_ID_5->text();

    fournisseur f(id, nom, categorie, email, adresse);
    bool test = f.ajouter();

    if (test){
        ui->tableView->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void elaawindow::on_pushButton_Supprimer_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();
    bool test = f.supprimer(id);

    if (test){
        ui->tableView->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void elaawindow::on_pushButton_2_clicked()
{


        int newid = ui->newid->text().toInt();
        QString newnom = ui->newnom->text();
        QString newcategorie = ui->newcategorie->text();
        QString newadresse = ui->newadresse->text();
        QString newemail = ui->newemail->text();

        fournisseur f(newid, newnom, newcategorie,newadresse, newemail);
        bool test = f.modifier();
        if (test){
            ui->tableView->setModel(f.afficher());
            QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                  QObject::tr("modification effectué"),
                                  QMessageBox::Ok
                                  );
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                                  QObject::tr("modification non effectué"),
                                  QMessageBox::Cancel
                                );
        }
}



void elaawindow::on_pushButton_3_clicked()
{
    ui->tableView->setModel(f.trier());
}

void elaawindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(f.trierNom());
}

void elaawindow::on_pushButton_chercher_clicked()

{
    QString rech_field = ui->lineEdit_nom_recherche->text();
    ui->tableView->setModel(f.chercher(rech_field));


}




void elaawindow::on_pb_image_clicked()
{
    QFileDialog dialog(this);
        dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
        dialog.setViewMode(QFileDialog::Detail);
        QString fileName =QFileDialog::getOpenFileName(this, tr("Open Images"), "C:/Users/Hp/Desktop", tr("Image Files (*.png *.jpg *.bmp)"));
    //to select and show the picture
        if (!fileName.isEmpty())
        {
            QImage image(fileName);
                ui->label_pic->setPixmap(QPixmap::fromImage(image));
        }
}

void elaawindow::on_pushButton_5_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(1);
                QSqlQueryModel * model= new QSqlQueryModel();
                model->setQuery("select * from fournisseur where id < 19999 ");
                float taille=model->rowCount();
                model->setQuery("select * from fournisseur where id  between 19999 and 29999 ");
                float taillee=model->rowCount();
                model->setQuery("select * from fournisseur where id >29999 ");
                float tailleee=model->rowCount();
                float total=taille+taillee+tailleee;
                QString a=QString("fournisseur fidele . "+QString::number((taille*100)/total,'f',2)+"%" );
                QString b=QString("fournisseur non fidele .  "+QString::number((taillee*100)/total,'f',2)+"%" );
                QString c=QString("fournisseur retsekour ."+QString::number((tailleee*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,taille);
                series->append(b,taillee);
                series->append(c,tailleee);
                if (taille!=0)
                {QPieSlice *slice = series->slices().at(0);
                    slice->setLabelVisible();
                    slice->setPen(QPen());}
                if ( taillee!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(1);
                    //slice1->setExploded();
                    slice1->setLabelVisible();
                }
                if(tailleee!=0)
                {
                    // Add labels to rest of slices
                    QPieSlice *slice2 = series->slices().at(2);
                    //slice1->setExploded();
                    slice2->setLabelVisible();
                }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("distribution fournisseur :Nombre Des fournisseur "+ QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
    }


void elaawindow::on_pushButton_6_clicked()
{
    QString strStream;

                         QTextStream out(&strStream);

                         const int rowCount = ui->tableView->model()->rowCount();
                         const int columnCount = ui->tableView->model()->columnCount();
                         QString TT = QDateTime::currentDateTime().toString();
                         out <<"<html>\n"
                               "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             << "<title>ERP - COMmANDE LIST<title>\n "
                             << "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                                "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                +"<img src=C:\\Users\\maato\\Desktop\\Nouveau%20dossier\\fahed.pdf />"
                                "<h1 style=\"text-align: center;\"><strong> ****LISTE DES  licence commerciale **** </strong></h1>"


                             "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                               "</br> </br>";
                         // headers
                         out << "<thead><tr bgcolor=#d6e5ff>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tableView->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tableView->isColumnHidden(column)) {
                                     QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                             "</body>\n"
                             "</html>\n";

                         QTextDocument *document = new QTextDocument();
                         document->setHtml(strStream);

                         QPrinter printer;

                         QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                         if (dialog->exec() == QDialog::Accepted) {
                             document->print(&printer);
                         }

                         delete document;
}

void elaawindow::on_pushButton_exportpdf_clicked()
{

    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_Nom->text();
    QString categorie = ui->lineEdit_2->text();
    QString adresse = ui->lineEdit_ID_4->text();
    QString email = ui->lineEdit_ID_5->text();
       fournisseur F(id,nom,categorie,adresse,email);
   F.printPDF_fournisseur();
}

void elaawindow::on_pushButton_checkpDf_clicked()
{
    QString link="C:/Users/Hp/Desktop/testinteg/Smart-Tech-Store-2A9/Atelier_Connexion/fournisseur.pdf";
            QDesktopServices::openUrl(QUrl(link));
}