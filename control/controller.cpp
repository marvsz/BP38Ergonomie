#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    dbHandler = new DBHandler();

    viewCon = new ViewController();
    viewCon->show();

    connect(viewCon, SIGNAL(updateMetaData()), this, SLOT(updateMetaData()));
    connect(viewCon, SIGNAL(saveMetaData()), this, SLOT(saveMetaData()));
    analyst_ID = 0;
}


void Controller::updateMetaData(){
    if(analyst_ID <= 0){
        viewCon->setAnalyst("","","","");
    }
    else {
        dbHandler->select(DB_TABLES::ANALYST, QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(QString::number(analyst_ID)));
        QSqlRecord record = dbHandler->record(DB_TABLES::ANALYST, 0);
        viewCon->setAnalyst(record.value(DBConstants::COL_ANALYST_LASTNAME).toString(),
                            record.value(DBConstants::COL_ANALYST_FIRSTNAME).toString(),
                            record.value(DBConstants::COL_ANALYST_EMPLOYER).toString(),
                            record.value(DBConstants::COL_ANALYST_EXPERIENCE).toString());
    }
}

void Controller::saveMetaData(){
    analyst_ID = getAnalystID();
}


int Controller::getAnalystID(){
    QString filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_ANALYST_LASTNAME).arg(viewCon->getAnalystLastName()).arg(DBConstants::COL_ANALYST_FIRSTNAME).arg(viewCon->getAnalystFirstName());
    dbHandler->select(DB_TABLES::ANALYST, filter);
    if(dbHandler->rowCount(DB_TABLES::ANALYST) == 0){
        QSqlRecord record;
        int id = dbHandler->getNextID(DB_TABLES::ANALYST, DBConstants::COL_ANALYST_ID);
        record.append(QSqlField(DBConstants::COL_ANALYST_ID, QVariant::Int));
        record.append(QSqlField(DBConstants::COL_ANALYST_LASTNAME, QVariant::String));
        record.append(QSqlField(DBConstants::COL_ANALYST_FIRSTNAME, QVariant::String));
        record.append(QSqlField(DBConstants::COL_ANALYST_EMPLOYER, QVariant::Int));
        record.append(QSqlField(DBConstants::COL_ANALYST_EXPERIENCE, QVariant::String));
        record.append(QSqlField(DBConstants::COL_ANALYST_CORPORATION, QVariant::Int));

        record.setValue(DBConstants::COL_ANALYST_ID, id);
        record.setValue(DBConstants::COL_ANALYST_LASTNAME, viewCon->getAnalystLastName());
        record.setValue(DBConstants::COL_ANALYST_FIRSTNAME, viewCon->getAnalystFirstName());
        record.setValue(DBConstants::COL_ANALYST_EMPLOYER, 1);
        record.setValue(DBConstants::COL_ANALYST_EXPERIENCE, viewCon->getAnalystExperience());
        record.setNull(DBConstants::COL_ANALYST_CORPORATION);
        dbHandler->insertRow(DB_TABLES::ANALYST, record);
        return id;
    }
    else {
        QSqlRecord record = dbHandler->record(DB_TABLES::ANALYST, 0);
        return record.value(DBConstants::COL_ANALYST_ID).toInt();
    }

}
