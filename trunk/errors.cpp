#include "errors.h"

Error_report::Error_report()
{
    map.clear();
    map.insert("0x000", "неизвестная ошибка");
    map.insert("0x001", "не удалось соединиться с базой данных");
    map.insert("0x002", "не удалось создать файл для создания резервной копии");
    map.insert("0x003", "в таблице coefficients присутствуют неопознанные коеффициенты");
    map.insert("0x004", "не все нормы часов были найдены");
    map.insert("0x100", "не удалось выполнить запрос при переименовании предмета");
    map.insert("0x101", "не удалось выполнить запрос при добавлении предмета");
    map.insert("0x102", "не удалось выполнить запрос при удалении предмета, предмет используется в базе данных");
    map.insert("0x200", "не удалось выполнить запрос при изменении преподавателя");
    map.insert("0x201", "не удалось выполнить запрос при добавлении преподавателя");
    map.insert("0x202", "не удалось выполнить запрос при удалении преподавателя");
    map.insert("0x203", "не удалось выполнить запрос при добавлении ранее удаленного преподавателя");
    map.insert("0x300", "не удалось выполнить запрос при изменении записи в таблице студенты");
    map.insert("0x301", "ошибка добавления записи в таблицу студенты(Возможно таблица специальности пуста)");
    map.insert("0x302", "не удалось выполнить запрос при добавлении записи в таблице студенты");
    map.insert("0x303", "не удалось выполнить запрос при удалении записи в таблице студенты");
    map.insert("0x304", "не удалось выполнить SELECT запрос при добавлении записи в таблице студенты");
    map.insert("0x305", "не удалось выполнить SELECT запрос при добавлении записи в таблице студенты");
    map.insert("0x400", "не удалось получить доступ для чтения таблицы 'subjects_in_semmester'");
    map.insert("0x401", "найдено более одной записи для учебного плана в таблице предметы в семместре");
    map.insert("0x402", "не удалось получит доступ на удаление записи из 'distribution', при удалении записи из учебного плана");
    map.insert("0x403", "не удалось получит доступ на удаление записи из 'subjects_in_semmester', при удалении записи из учебного плана");
    map.insert("0x404", "не удалось получит доступ на удаление записи из 'curriculum', при удалении записи из учебного плана");
    map.insert("0x405", "не удалось выполнить SELECT запрос при добавлении новой записи в 'Учебный план'");
    map.insert("0x406", "не удалось выполнить SELECT запрос при добавлении новой записи в 'Учебный план'");
    map.insert("0x407", "ошибка при добавлении новой записи в 'Учебный план', возможно таблица специальностей пуста");
    map.insert("0x408", "не удалось выполнить SELECT запрос при добавлении новой записи в 'Учебный план'");
    map.insert("0x409", "ошибка при добавлении новой записи в 'Учебный план', возможно таблица предметов пуста");
    map.insert("0x500", "ошибка при выполнении UPDATE запроса к таблице subjects_in_semmester");
    map.insert("0x501", "ошибка при выполнении SELECT запроса при получении суммы часов");
    map.insert("0x502", "ошибка при попытке удалть запись из distribution");
    map.insert("0x503", "ошибка при попытке удалть запись из subjects_in_semmester");
    map.insert("0x504", "ошибка при выполнении SELECT запроса при получении кол-ва строк");
    map.insert("0x505", "ошибка при выполнении запроса на удаление всех данных из distribution");
    map.insert("0x506", "ошибка при выполнении запроса на удаление всех данных из subjects_in_semmester");
    map.insert("0x507", "ошибка при выполнении SELECT запроса при получении кол-ва строк");
    map.insert("0x600", "ошибка при выполнении запроса на удаление всех данных из distribution");
    map.insert("0x601", "не удалось выполнить SELECT запрос в методе check_entry()");
    map.insert("0x602", "не удалось выполнить SELECT запрос в методе check_entry()");
    map.insert("0x603", "не удалось вставить фиктивного преподавателя в таблицу распределение в методе check_entry()");
    map.insert("0x604", "не удалось вставить нового фиктивного преподавателя");
    map.insert("0x605", "не удалось удалить запись из таблицы распределение");
    map.insert("0x606", "не удалось выполнить SELECT запрос при обновлении вкладки Распределение");
    map.insert("0x607", "не удалось выполнить SELECT запрос при обновлении вкладки Распределение");
    map.insert("0x608", "не удалось выполнить запрос на обновление записи таблицы Распределение");
    map.insert("0x609", "не удалось выполнить SELECT запрос в методе rowCountDB()");
    map.insert("0x60A", "не удалось выполнить SELECT запрос в методе sum_field()");
    map.insert("0x701", "сокращенное название кафедры не было найдено в базе данных (отсутствует запись 'name_kafedry_smail' в таблице 'other_data')");
    map.insert("0x702", "учебный год не был найден в базе данных (отсутствует запись 'academic_year' в таблице 'other_data')");
    map.insert("0x703", "не удалось выполнить SELECT запрос при обновлении названия отчета");
    map.insert("0x704", "не удалось выполнить SELECT запрос при обновлении названия отчета");
    map.insert("0x801", "не удалось выполнить запрос на добавление новой специальности");
    map.insert("0x802", "не удалось выполнить запрос на удаление специальности, возможно она используется в 'Учебный план' или 'Студенты' или 'Нормы часов'");
    map.insert("0x803", "не удалось выполнить запрос на добавление новой должности");
    map.insert("0x804", "не удалось выполнить запрос на удаление должности");
    map.insert("0x805", "не удалось выполнить запрос на обновление записи Учебный год в окне Настройки");
    map.insert("0x806", "не удалось выполнить запрос на обновление записи Название кафедры в окне Настройки");
    map.insert("0x807", "не удалось выполнить запрос на обновление записи Основа обучения в окне Настройки");
    map.insert("0x808", "не удалось выполнить запрос на обновление записи Проректор по учебной работе в окне Настройки");
    map.insert("0x809", "не удалось выполнить запрос на обновление записи Название кафедры(сокращенно) в окне Настройки");
    map.insert("0x80A", "не удалось выполнить SELECT запрос при обновлении окна Настройки");
    map.insert("0x80B", "в таблице 'other_data' присутствуют неопознанные записи");
    map.insert("0x80C", "не удалось выполнить запрос на обновление коеффициента в окне 'Настройки'");
    map.insert("0x80D", "не удалось выполнить SELECT запрос при обновлении окна Преподаватели и учебные часы");
    map.insert("0x80E", "не удалось выполнить SELECT запрос при обновлении окна Преподаватели и учебные часы");
    map.insert("0x80F", "не удалось выполнить SELECT запрос при обновлении окна Преподаватели и учебные часы");
    map.insert("0x810", "не удалось выполнить SELECT запрос при обновлении окна Преподаватели и учебные часы");
    map.insert("0x811", "не удалось выполнить SELECT запрос при обновлении окна Преподаватели и учебные часы");
    map.insert("0x812", "не удалось выполнить запрос на изменение специальности");
    map.insert("0x813", "не удалось выполнить SELECT запрос при добавлении новой специальности");
}

void Error_report::show_mesage_error(QString s_err)
{
    QMessageBox msgBox;
    msgBox.setText(s_err);
    msgBox.setInformativeText(map.value(s_err));
    msgBox.setGeometry(500,300,300,200);
    msgBox.exec();
}

