/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase db;

static bool createConnection(QString path_db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    return true;
}

static bool create_all_tables(){

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("CREATE TABLE form_training ( "
                   "name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE subject ( "
                   "name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE speciality ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "faculty_name TEXT NOT NULL,"
                   "special_name TEXT NOT NULL, "
                   "form_training_name TEXT NOT NULL,"
                   "CONSTRAINT form_training_name FOREIGN KEY (form_training_name) "
                   "REFERENCES form_training (name))");
        query.exec("CREATE TABLE students ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_id INTEGER NOT NULL, "
                   "course INTEGER NOT NULL, "
                   "num_group INTEGER NOT NULL, "
                   "num_undergroup INTEGER NOT NULL, "
                   "quantity_course INTEGER NOT NULL, "
                   "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
                   "REFERENCES speciality (id))");
        query.exec("CREATE TABLE status ( "
                   "name TEXT NOT NULL, "
                   "hours INTEGER NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE teachers ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "f TEXT NOT NULL, "
                   "i TEXT NOT NULL, "
                   "o TEXT NOT NULL, "
                   "status_name TEXT NOT NULL, "
                   "rate REAL NOT NULL, "
                   "CONSTRAINT status_name FOREIGN KEY (status_name) "
                   "  REFERENCES status (name)) ");
        query.exec("CREATE TABLE curriculum ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_id INTEGER NOT NULL, "
                   "subject_name TEXT NOT NULL, "
                   "semmester INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "controlwork INTEGER NOT NULL, "
                   "KCP_hr INTEGER NOT NULL, "
                   "is_examen INTEGER NOT NULL, "
                   "is_offset INTEGER NOT NULL, "
                   "is_coursework INTEGER NOT NULL, "
                   "CONSTRAINT subject_name FOREIGN KEY (subject_name) "
                   "  REFERENCES subject (name), "
                   "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
                   "  REFERENCES speciality (id))");
        query.exec("CREATE TABLE subjects_in_semmester ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "curriculum_id INTEGER NOT NULL, "
                   "students_id INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "individ_hr REAL NOT NULL, "
                   "kontr_rab_hr REAL NOT NULL, "
                   "consultation_hr REAL NOT NULL, "
                   "offset_hr REAL NOT NULL, "
                   "examen_hr REAL NOT NULL, "
                   "coursework_hr REAL NOT NULL, "
                   "diplomwork_hr REAL NOT NULL, "
                   "praktika_hr REAL NOT NULL, "
                   "gak_hr REAL NOT NULL, "
                   "other1 REAL NOT NULL, "
                   "other2 REAL NOT NULL, "
                   "other3 REAL NOT NULL, "
                   "CONSTRAINT students_id FOREIGN KEY (students_id) "
                   "  REFERENCES students (id), "
                   "CONSTRAINT curriculum_id FOREIGN KEY (curriculum_id) "
                   "  REFERENCES curriculum (id)) ");
        query.exec("CREATE TABLE distribution ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "teachers_id INTEGER NOT NULL, "
                   "subjects_in_semmester_id INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "individ_hr REAL NOT NULL, "
                   "kontr_rab_hr REAL NOT NULL, "
                   "consultation_hr REAL NOT NULL, "
                   "offset_hr REAL NOT NULL, "
                   "examen_hr REAL NOT NULL, "
                   "coursework_hr REAL NOT NULL, "
                   "diplomwork_hr REAL NOT NULL, "
                   "praktika_hr REAL NOT NULL, "
                   "gak_hr REAL NOT NULL, "
                   "other1 REAL NOT NULL, "
                   "other2 REAL NOT NULL, "
                   "other3 REAL NOT NULL, "
                   "CONSTRAINT subjects_in_semmestre_id FOREIGN KEY (subjects_in_semmestre_id) "
                   "  REFERENCES subjects_in_semmestre (id), "
                   "CONSTRAINT teachers_id FOREIGN KEY (teachers_id) "
                   "  REFERENCES teachers (id))");

    }
    return true;
}

static bool insert_main_data()
{

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("insert into form_training values('оч')");
        query.exec("insert into form_training values('оч-заоч')");
        query.exec("insert into form_training values('заоч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','МОиАИС', 'оч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','МОиАИС', 'оч-заоч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','ПО', 'оч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','ИАЯ', 'оч')");
        query.exec("insert into status values('default', 0)");
        query.exec("insert into status values('профессор', 680)");
        query.exec("insert into status values('доцент', 730)");
        query.exec("insert into status values('ст. препод.', 780)");
        query.exec("insert into status values('ассистент', 830)");
        query.exec("insert into status values('декан', 500)");
        query.exec("insert into status values('зав. кафедрой', 700)");

        //from anatoly zhmakin

        query.exec("insert into subject values('Информационные системы')");
        query.exec("insert into subject values('Основы микроэлектроники')");
        query.exec("insert into subject values('Архитектура компьютера')");
        query.exec("insert into subject values('Информационные системы')");
        query.exec("insert into subject values('Компьютерные сети, интернет и мультимедиа технологии')");
        query.exec("insert into subject values('Компьютерное моделирование')");
        query.exec("insert into subject values('Информатика')");
        query.exec("insert into subject values('Программирование')");
        query.exec("insert into subject values('Введение в системное программирование')");
        query.exec("insert into subject values('Структуры и алгоритмы компьютерной обработки данных')");
        query.exec("insert into subject values('Прикладная теория цифровых автоматов')");
        query.exec("insert into subject values('Операционные системы и оболочки')");
        query.exec("insert into subject values('Элементы теории автоматического регулирования')");
        query.exec("insert into subject values('Элементы микропроцессорной техники')");
        query.exec("insert into subject values('Системы реального времени')");
        query.exec("insert into subject values('Теория формальных языков и трансляции')");
        query.exec("insert into subject values('Базы данных и СУБД')");
        query.exec("insert into subject values('Объектно-ориентированные языки и системы')");
        query.exec("insert into subject values('Архитектура вычислительных систем и компьютерных сетей')");
        query.exec("insert into subject values('Компьютерная графика')");
        query.exec("insert into subject values('Теория оптимизации в базах данных')");
        query.exec("insert into subject values('Системы искусственного интеллекта')");
        query.exec("insert into subject values('Параллельное программирование')");
        query.exec("insert into subject values('Теория вычислительных процессов и структур')");
        query.exec("insert into subject values('Основы проектирования информационных систем')");
        query.exec("insert into subject values('Компьютерные сети и системы телекоммуникаций')");
        query.exec("insert into subject values('Экспертные системы и базы знаний')");
        query.exec("insert into subject values('Компьютерное моделирование')");
        query.exec("insert into subject values('Администрирование информационных систем')");
        query.exec("insert into subject values('Технология разработки программного обеспечения')");
        query.exec("insert into subject values('Защита информации в компьютерных системах и сетях')");
        query.exec("insert into subject values('Технологическая практика (от предприятия)')");
        query.exec("insert into subject values('Технологическая практика (факультетское руководство)')");
        query.exec("insert into subject values('Метрология и качество программного обеспечения')");
        query.exec("insert into subject values('Администрирование информационных систем')");
        query.exec("insert into subject values('Преддипломная практика (от предприятия)')");
        query.exec("insert into subject values('Преддипломная практика (факультетское руководство)')");
        query.exec("insert into subject values('Руководство ВКР')");
        query.exec("insert into subject values('Нормоконтроль ВКР')");
        query.exec("insert into subject values('Защита ВКР при ГАК')");
        query.exec("insert into subject values('Участие в ГАК')");
        query.exec("insert into subject values('Компьютерная графика')");
        query.exec("insert into subject values('Базы данных и экспертные системы')");
        query.exec("insert into subject values('Параллельная обработка данных')");
        query.exec("insert into subject values('Пакеты прикладных программ')");
        query.exec("insert into subject values('Рациональные языки и коды')");
        query.exec("insert into subject values('Программно-аппаратная защита информации')");
        query.exec("insert into subject values('Программирование на С++')");
        query.exec("insert into subject values('Объектно-ориентированное программирование')");
        query.exec("insert into subject values('Компьютерное моделирование электронных устройств')");
        query.exec("insert into subject values('Системное программирование')");
        query.exec("insert into subject values('Компьютерные коммуникации и сети')");
        query.exec("insert into subject values('Базы данных и управление ими')");
        query.exec("insert into subject values('Операционные системы')");
        query.exec("insert into subject values('Защита информационных систем')");
        query.exec("insert into subject values('Компьютерные коммуникации и сети')");
        query.exec("insert into subject values('Специальное программирование')");
        query.exec("insert into subject values('Мультимедиа')");
        query.exec("insert into subject values('Базы данных и управление ими')");
        query.exec("insert into subject values('Объектно-ориентированные технологии')");
        query.exec("insert into subject values('Технологическая практика (факультетское руководство)')");
        query.exec("insert into subject values('Вычислительные системы, сети, телекоммуникации')");
        query.exec("insert into subject values('Информационная безопасность ')");
        query.exec("insert into subject values('Основы проектирования информационных систем и баз данных')");
        query.exec("insert into subject values('Информационные системы')");
        query.exec("insert into subject values('Компьютерное моделирование')");
        query.exec("insert into subject values('Основы микроэлектроники и архитектура компьютера')");
        query.exec("insert into subject values('Информационная безопасность')");
        query.exec("insert into subject values('Математическое моделирование социальных процессов')");
        query.exec("insert into subject values('Руководство аспирантами')");

        query.exec("insert into teachers values(NULL, 'Жмакин', 'Анатолий', 'Петрович', 'зав. кафедрой', 1.2 );");
        query.exec("insert into teachers values(NULL, 'Лопин', 'Вячеслав', 'Николаевич', 'профессор', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Бабкин', 'Евгений', 'Александрович', 'профессор', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Кудинов', 'Виталий', 'Алексеевич', 'профессор', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Добрица', 'Вячеслав', 'Порфирьевич', 'профессор', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Григорьев', 'Сергей', 'Григорьевич', 'профессор', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Бабкин', 'Геннадий', 'Викторович', 'доцент', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Прасолова', 'Ангелина', 'Евгеньевна', 'доцент', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Бородин', 'Сергей', 'Георгиевич', 'доцент', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Белов', 'Владимир', 'Геннадьевич', 'доцент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Белова', 'Татьяна', 'Михайловна', 'доцент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Сухотерин', 'Евгений', 'Александрович', 'доцент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Фрумкин', 'Александр', 'Михайлович', 'доцент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Цуканов', 'Михаил', 'Владимирович', 'доцент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Желанов', 'Алексей', 'Леонидович', 'ст. препод.', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Жуйков', 'Виктор', 'Викторович', 'ст. препод.', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Конников', 'Павел', 'Владимирович', 'ст. препод.', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Орлова', 'Марина', 'Сергеевна', 'ст. препод.', 0.3 );");
        query.exec("insert into teachers values(NULL, 'Бабкина', 'Ольга', 'Митрофановна', 'ст. препод.', 0.4 );");
        query.exec("insert into teachers values(NULL, 'Ураева', 'Елена', 'Евгеньевна', 'ассистент', 1.0 );");
        query.exec("insert into teachers values(NULL, 'Абрамов', 'Андрей', 'Викторович', 'ассистент', 0.5 );");
        query.exec("insert into teachers values(NULL, 'Шумакова', 'Наталья', 'Владимировна', 'ассистент', 0.5 );");

        query.exec("insert into students values(NULL, 1, 1, 1, 2, 25 );");
        query.exec("insert into students values(NULL, 1, 2, 1, 2, 22 );");
        query.exec("insert into students values(NULL, 1, 3, 2, 3, 32 );");
        query.exec("insert into students values(NULL, 1, 4, 2, 3, 28 );");
        query.exec("insert into students values(NULL, 1, 5, 1, 2, 28 );");
        query.exec("insert into students values(NULL, 2, 5, 1, 1, 6 );");
        query.exec("insert into students values(NULL, 2, 6, 1, 1, 8 );");
        //query.exec("insert into students values(NULL, 'И-зао', 2, 1, 1, 6 );");
        //query.exec("insert into students values(NULL, 'И-зао', 3, 1, 1, 10 );");
        //query.exec("insert into students values(NULL, 'И-зао', 4, 1, 2, 14 );");
        //query.exec("insert into students values(NULL, 'И-зао', 5, 1, 1, 10 );");
        query.exec("insert into students values(NULL, 4, 3, 1, 2, 15 );");
        query.exec("insert into students values(NULL, 4, 4, 1, 2, 19 );");
        query.exec("insert into students values(NULL, 4, 5, 1, 2, 21 );");
        query.exec("insert into students values(NULL, 3, 2, 1, 2, 16 );");
        query.exec("insert into students values(NULL, 3, 3, 1, 1, 13 );");
        query.exec("insert into students values(NULL, 3, 4, 1, 2, 16 );");

        query.exec("insert into curriculum values(NULL, 1, 'Информатика',1, 36, 34, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',1, 36, 30, 0, 2, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',2, 32, 30, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Введение в системное программирование',2, 20, 18, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',3, 0, 0, 16, 0, 0, 0, 1, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Структуры и алгоритмы компьютерной обработки данных',3, 36, 36, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Прикладная теория цифровых автоматов',4, 34, 20, 0, 2, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Структуры и алгоритмы компьютерной обработки данных',4, 22, 20, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Операционные системы и оболочки',4, 26, 32, 0, 3, 0, 1, 0, 0 );");;
        query.exec("insert into curriculum values(NULL, 1, 'Элементы теории автоматического регулирования',4, 18, 18, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Элементы микропроцессорной техники',5, 18, 18, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Системы реального времени',5, 18, 16, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Теория формальных языков и трансляции',5, 34, 30, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Базы данных и СУБД',6, 34, 30, 0, 2, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Объектно-ориентированные языки и системы',6, 36, 54, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Архитектура вычислительных систем и компьютерных сетей',6, 34, 34, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Компьютерная графика',6, 26, 24, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Теория оптимизации в базах данных',7, 36, 18, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Системы искусственного интеллекта',7, 30, 26, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Параллельное программирование',7, 36, 20, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Теория вычислительных процессов и структур',7, 30, 26, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Основы проектирования информационных систем',7, 36, 54, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Компьютерные сети и системы телекоммуникаций',7, 36, 46, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Экспертные системы и базы знаний',8, 32, 32, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Компьютерное моделирование',8, 32, 30, 0, 2, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Теория оптимизации в базах данных',8, 16, 22, 0, 0, 0, 0, 1, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Администрирование информационных систем',8, 32, 32, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Технология разработки программного обеспечения',8, 28, 20, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Защита информации в компьютерных системах и сетях',8, 18, 18, 0, 2, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Экспертные системы и базы знаний',9, 0, 26, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Метрология и качество программного обеспечения',9, 14, 10, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Администрирование информационных систем',9, 14, 46, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 2, 'Экспертные системы и базы знаний',9, 16, 10, 0, 0, 0, 0, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Основы проектирования информационных систем',9, 18, 0, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Защита информации в компьютерных системах и сетях',9, 10, 14, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Теория оптимизации в базах данных',9, 34, 22, 0, 0, 0, 1, 0, 1 );");
        query.exec("insert into curriculum values(NULL, 2, 'Метрология и качество программного обеспечения',9, 14, 10, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Технология разработки программного обеспечения',9, 28, 20, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Администрирование информационных систем',9, 32, 44, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Экспертные системы и базы знаний',10, 32, 32, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Основы проектирования информационных систем',10, 16, 16, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 2, 'Администрирование информационных систем',10, 14, 34, 0, 0, 0, 0, 0, 1 );");
    }
    return true;
}

static bool drop_all_tables()
{

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;
        query.exec("DROP TABLE distribution");
        query.exec("DROP TABLE subjects_in_semmester");
        query.exec("DROP TABLE curriculum");
        query.exec("DROP TABLE students");
        query.exec("DROP TABLE teachers");
        query.exec("DROP TABLE speciality");
        query.exec("DROP TABLE subject");
        query.exec("DROP TABLE status");
        query.exec("DROP TABLE form_training");
    }
    return true;
}

#endif
