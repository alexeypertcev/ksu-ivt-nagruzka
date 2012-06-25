#include "settings.h"
#include "ui_settings.h"
#include "functions.h"
#include "delegates.h"
#define DEBUG_ENABLE_MODIFY

Settings::Settings(QWidget *parent, QSqlRelationalTableModel* tm_stat) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ComboBoxDelegate *form_training = new ComboBoxDelegate("form_training",this);
    sqlmodel_speciality = new Speciality_model();
    sqlmodel_speciality->refresh();
    ui->tableView->setModel(sqlmodel_speciality);
    ui->tableView->setItemDelegateForColumn(3, form_training);

    sqlmodel_speciality->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_speciality->setHeaderData(1, Qt::Horizontal, QObject::tr("Факультет"));
    sqlmodel_speciality->setHeaderData(2, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_speciality->setHeaderData(3, Qt::Horizontal, QObject::tr("Форма обучения"));
    ui->tableView->setColumnWidth(0,0);
    ui->tableView->setColumnWidth(1,115);
    ui->tableView->setColumnWidth(2,130);
    ui->tableView->setColumnWidth(3,145);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tablemodel_stat = tm_stat;
    ui->tableView_2->setModel(tablemodel_stat);
    ui->tableView_2->update();

    tablemodel_stat->setHeaderData(0, Qt::Horizontal, QObject::tr("Должность"));
    tablemodel_stat->setHeaderData(1, Qt::Horizontal, QObject::tr("Часы"));
    ui->tableView_2->setColumnWidth(0,150);
    ui->tableView_2->setColumnWidth(1,150);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    coefficients_model = new Coefficients_model();
    coefficients_model->refresh();
    ui->tableView_3->setModel(coefficients_model);

    coefficients_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    coefficients_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Специальность"));
    coefficients_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Норма"));
    ui->tableView_3->setColumnWidth(0,0);
    ui->tableView_3->setColumnWidth(1,358);
    ui->tableView_3->setColumnWidth(2,97);
    ui->tableView_3->setColumnWidth(3,43);

    SpecialityAllDelegate *specialityAlldelegate = new SpecialityAllDelegate(this);
    ui->tableView_3->setItemDelegateForColumn(2, specialityAlldelegate);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    update_other_data();
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_pushButton_add_spec_clicked()
{
    QSqlQuery query;
    QString s = "SELECT id, faculty_name, special_name, form_training_name "
                "FROM speciality WHERE id != 0 ORDER BY faculty_name DESC, special_name DESC, form_training_name DESC ";

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (query.exec(s)){
        if (query.next()){
            s = "insert into speciality values(NULL, '" + query.value(1).toString() + "', '" + query.value(2).toString() + "', 'оч')";
        } else {
            s = "insert into speciality values(NULL, '', '', 'оч')";
        }

#ifdef DEBUG_ENABLE_MODIFY
        DEBUG_MESSAGE( s )
#endif
        if (!query.exec(s)){
            ERROR_REPORT("0x801")
        }
        sqlmodel_speciality->refresh();
    } else {
        ERROR_REPORT("0x813");
    }
}

void Settings::on_pushButton_del_spec_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString s = "DELETE FROM speciality WHERE id = '" + sqlmodel_speciality->data( sqlmodel_speciality->index(row,0),
                                                                              Qt::DisplayRole ).toString() + "';";
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x802")
    }
    sqlmodel_speciality->refresh();
}

void Settings::on_pushButton_add_dolj_clicked()
{
    QString s = "insert into status values('', 0)";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x803")
    }
    tablemodel_stat->select();
}

void Settings::on_pushButton_del_dolj_clicked()
{
    QString s = "DELETE FROM status WHERE name = '"+ ui->tableView_2->currentIndex().data(Qt::DisplayRole).toString() + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x804")
    }
    tablemodel_stat->select();
}

void Settings::set_tab(int index){
    ui->tabWidget->setCurrentIndex(index);
}

void Settings::on_lineEdit_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit->text() +"' where name = 'academic_year'";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x805")
    }
    update_other_data();
}

void Settings::on_lineEdit_2_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_2->text() +"' where name = 'name_kafedry_faculty'";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x806")
    }
    update_other_data();
}

void Settings::on_lineEdit_3_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_3->text() +"' where name = 'business_base_of_training'";
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x807")
    }
    update_other_data();
}

void Settings::on_lineEdit_4_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_4->text() +"' where name = 'vice_rector_on_education_work'";
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x808")
    }
    update_other_data();
}

void Settings::on_lineEdit_5_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_5->text() +"' where name = 'name_kafedry_smail'";
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x809")
    }
    update_other_data();
}

void Settings::update_other_data()
{
    QSqlQuery query;
    QString s = "SELECT name, value FROM other_data";

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x80A")
        return ;
    }

    while(query.next()){
        if (query.value(0).toString() == "academic_year"){
            ui->lineEdit->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "name_kafedry_faculty"){
            ui->lineEdit_2->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "business_base_of_training"){
            ui->lineEdit_3->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "vice_rector_on_education_work"){
            ui->lineEdit_4->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "name_kafedry_smail"){
            ui->lineEdit_5->setText(query.value(1).toString());
        } else {
            ERROR_REPORT("0x80B");
        }
    }
}

/***********************************************************
*   Speciality_model
************************************************************/

Speciality_model::Speciality_model(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags Speciality_model::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if ((index.column() >= 1)||(index.column() <= 3))
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void Speciality_model::refresh()
{
    this->setQuery("SELECT id, faculty_name, special_name, form_training_name "
                   "FROM speciality WHERE id != 0 ORDER BY faculty_name, special_name, form_training_name;");
}

QVariant Speciality_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 1)
        {
            return value.toString();
        }
        break;
    }
    return value;
}

bool Speciality_model::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if ((index.column() < 1) || (index.column() > 3))
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 1:
            field = "faculty_name";
            break;
        case 2:
            field = "special_name";
            break;
        case 3:
            field = "form_training_name";
            break;
        }

    QString s = "update speciality set "+ field +" = '"+ functions::toDataString(value.toString()) +"' where id = "+ data(primaryKeyIndex, Qt::DisplayRole).toString();
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){

        ERROR_REPORT("0x812");
        return false;
    }
    refresh();
    return true;
}

/***********************************************************
*   Coefficients_model
************************************************************/

Coefficients_model::Coefficients_model(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags Coefficients_model::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if ((index.column() == 2 )||(index.column() == 3 ))
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void Coefficients_model::refresh()
{
    this->setQuery("SELECT name, name, special_name || '(' || form_training_name || ')', value "
                   "FROM coefficients, speciality WHERE coefficients.speciality_id = speciality.id ");
}

QVariant Coefficients_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    //QString buf;
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 1)
        {
            if (value.toString() == "coefficient_lection_hr"){
                return "Для лекций, часов на лекцию";
            }
            if (value.toString() == "coefficient_labs_for_undergroup_hr"){
                return "Для лабораторных работ, часов на подгруппу";
            }
            if (value.toString() == "coefficient_practice_for_group_hr"){
                return "Для практических занятий, часов на группу";
            }
            if (value.toString() == "coefficient_individ_for_KCR_hr"){
                return "Для индивидуальных занятий, часов на КСР";
            }
            if (value.toString() == "coefficient_kontr_rab_for_quantitycourse_min"){
                return "Для контрольных работ, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_offset_for_quantitycourse_min"){
                return "Для зачетов, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_examen_for_quantitycourse_min"){
                return "Для экзаменов, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_coursework_for_quantitycourse_hr"){
                return "Для курсовых работ, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_consultation_ochnui_percent"){
                return "Для консультаций очной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_zaochnui_percent"){
                return "Для консультаций заочной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_och_zaoch_percent"){
                return "Для консультаций очно-заочной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_add_is_examen_for_group"){
                return "Дополнительно для консультаций (если экзамен), часов на группу ";
            }
            if (value.toString() == "coefficient_ruk_vo_kurs_work_hr"){
                return "Руководство курсовыми работами, часов";
            }
            if (value.toString() == "coefficient_ruk_vo_VKR_spec_hr"){
                return "Руководство ВКР специалиста, часов";
            }
            if (value.toString() == "coefficient_ruk_vo_VKR_bak_hr"){
                return "Руководство ВКР бакалавра, часов";
            }
            if (value.toString() == "coefficient_zachita_kurs_rab_na_kommis_min"){
                return "Защита курсовых работ на заседании комиссии, минут";
            }
            if (value.toString() == "coefficient_ruk_vo_VKR_mag_hr"){
                return "Руководство ВКР магистра, часов";
            }
            if (value.toString() == "coefficient_recenzir_VKR_hr"){
                return "Рецензирование ВКР, часов";
            }
            if (value.toString() == "coefficient_normokontrol_hr"){
                return "Нормоконтроль, часов";
            }
            if (value.toString() == "coefficient_ychastie_work_GAK_min"){
                return "Участие в работе ГАК, часов";
            }
            if (value.toString() == "coefficient_ruk_vo_aspirants_hr"){
                return "Руководство аспирантами, часов";
            }
            return value.toString();
        } else if (index.column() == 2){
            if (value.toString() == "(оч)"){
                return "Все";
            }
        }
        break;
    }
    return value;
}

bool Coefficients_model::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if ((index.column() < 2)||(index.column() > 3))
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);

    QString field = ";";
    switch (index.column()){
        case 2:
            field = "speciality_id";
            break;
        case 3:
            field = "value";
            break;
        }

    QString s = "UPDATE coefficients SET "+ field +" = '"+ value.toString() +"' WHERE name = '"+ data(primaryKeyIndex, Qt::DisplayRole).toString() + "';";
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){

        ERROR_REPORT("0x80C");
        return false;
    }
    refresh();
    return true;
}

void Settings::on_pushButton_clicked()
{
    // добавление дополнительного коеффициента




}
