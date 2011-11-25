#include <QtXml>
#include <QtCore/QFile>

#include <iostream>
using namespace std;
bool xml_work(QString path);


bool xml_work(QString path){/*
    QSqlQuery query;
    query.exec("SELECT speciality_id FROM students;");
    query.last();
    query.value(0).toString();*/


    QDomDocument opt;

    QFile iFile(path);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    QDomElement docElement = opt.documentElement(); // получаю корень
    QDomNode node;

            node = docElement.firstChild(); /*для тренировки пытаюсь хотябы какой-нибудь элемент   изменить, т.е. первый */
            qDebug() << node.toElement().text(); // элемент правильно извлекается

            node.childNodes().item(0).setNodeValue( "wefe" ); // такая вот интересная конструкция !
            //node.toElement().setNodeValue("wefe");                   // но здесь
            qDebug() << node.toElement().text();   // он не устанавливается !!!

     iFile.close();

     QFile oFile(path);
     oFile.open(QFile::ReadWrite);

            QTextStream out(&oFile);
            out.setCodec( QTextCodec::codecForName("UTF-8") );
            //out << &optFile; --- ТРЕШ не надо это здесь!!!!!!!!!!
            opt.save(out, 5, QDomNode::EncodingFromTextStream);
            oFile.close();


    qDebug() << path;
    return true;
}
