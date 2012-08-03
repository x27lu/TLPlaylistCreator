#include "popup.h"

using namespace std;

Popup1::Popup1(QString window_title, QString data1, QString data2, QString b1_title, QString b2_title)
{
    data1_l = new QLabel(data1);
    data1_l->setWordWrap(true);

    data2_l = new QLabel(data2);
    data2_l->setWordWrap(true);

    //data2_l->setFo
    QFont smaller_font = data1_l->font();
    smaller_font.setPointSize(smaller_font.pointSize() - 1);
    data2_l->setFont(smaller_font);

    // if this is defined in the class definition (e.g if at here it
    // is only "data2_scroll = new QScrollArea();") it will cause
    // program to crash for some reason
    QScrollArea *data2_scroll = new QScrollArea();
    data2_scroll->setWidgetResizable(true);
    data2_scroll->setWidget(data2_l);

    //data2_l->setWordWrap(true);

    b1 = new QPushButton(b1_title);
    b2 = new QPushButton(b2_title);

    QVBoxLayout *button_layout = new QVBoxLayout();
    button_layout->setAlignment(Qt::AlignBottom);
    button_layout->addWidget(b1);
    button_layout->addWidget(b2);

    QVBoxLayout *text_layout = new QVBoxLayout();
    text_layout->addWidget(data1_l);
    text_layout->addWidget(data2_scroll);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(text_layout);
    main_layout->addLayout(button_layout);

    setWindowTitle(window_title);
    setLayout(main_layout);

    connect(b1, SIGNAL(clicked()), this, SLOT(close()));
    connect(b2, SIGNAL(clicked()), this, SLOT(close()));
}

Popup1::~Popup1()
{
    delete b1;
    delete b2;
    delete data1_l;
    delete data2_l;
}

Popup2::Popup2(QString window_title, QString data, QString b1_title, QString b2_title)
{
    data_l = new QLabel(data);
    data_l->setWordWrap(true);

    b1 = new QPushButton(b1_title);
    b2 = new QPushButton(b2_title);

    QSizePolicy button_sp(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button_sp.setHorizontalStretch(0);
    b1->setSizePolicy(button_sp);
    b2->setSizePolicy(button_sp);

    QVBoxLayout *button_layout = new QVBoxLayout();
    button_layout->setAlignment(Qt::AlignBottom);
    button_layout->addWidget(b1);
    button_layout->addWidget(b2);

    //QSizePolicy text_sp(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //data_l->setSizePolicy(text_sp);

    QVBoxLayout *text_layout = new QVBoxLayout();
    text_layout->setAlignment(Qt::AlignTop);
    text_layout->addWidget(data_l);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(text_layout);
    main_layout->addLayout(button_layout);

    setWindowTitle(window_title);
    setLayout(main_layout);

    connect(b1, SIGNAL(clicked()), this, SLOT(close()));
    connect(b2, SIGNAL(clicked()), this, SLOT(close()));
}

Popup2::~Popup2()
{
    delete b1;
    delete b2;
    delete data_l;
}


/*
    This is used for showing song information
*/
Popup3::Popup3(QString window_title, QString data, QString b_title)
{
    data_l = new QLabel(data);
    data_l->setWordWrap(true);

    //data2_l->setFo
    QFont smaller_font = data_l->font();
    smaller_font.setPointSize(smaller_font.pointSize() - 1);
    data_l->setFont(smaller_font);

    QScrollArea *data_scroll = new QScrollArea();
    data_scroll->setWidgetResizable(true);
    data_scroll->setWidget(data_l);

    //data2_l->setWordWrap(true);

    b = new QPushButton(b_title);

    QVBoxLayout *button_layout = new QVBoxLayout();
    button_layout->setAlignment(Qt::AlignBottom);
    button_layout->addWidget(b);

    QVBoxLayout *text_layout = new QVBoxLayout();
    text_layout->addWidget(data_scroll);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(text_layout);
    main_layout->addLayout(button_layout);

    setWindowTitle(window_title);
    setLayout(main_layout);

    connect(b, SIGNAL(clicked()), this, SLOT(close()));
}

Popup3::~Popup3()
{
    delete b;
    delete data_l;
}

Popup4::Popup4(QString window_title,
               QString instruction,
               QString b_name,
               QStringList *status_sl,
               QStringList *lview_sl,
               int *selected_index)
    : selected_index(selected_index), status_sl(status_sl)
{   
    instruction_l = new QLabel(instruction);
    instruction_l->setWordWrap(true);

    lview_slm = new QStringListModel();
    lview_slm->setStringList(*lview_sl);

    lview = new QListView();
    lview->setEditTriggers(QListView::NoEditTriggers);
    lview->setWordWrap(true);
    //lview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //lview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lview->setModel(lview_slm);

    dir_view = new QStatusBar();


    if (*selected_index < 0) {
        lview->setCurrentIndex(lview_slm->index(0));
        dir_view->showMessage(status_sl->at(0));
    }
    else {
        lview->setCurrentIndex(lview_slm->index(*selected_index));
        dir_view->showMessage(status_sl->at(*selected_index));
    }

    b = new QPushButton(b_name);

    QVBoxLayout *text_layout = new QVBoxLayout();
    text_layout->addWidget(instruction_l);
    text_layout->addWidget(lview);

    QVBoxLayout *button_layout = new QVBoxLayout();
    button_layout->setAlignment(Qt::AlignBottom);
    button_layout->addWidget(b);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(text_layout);
    main_layout->addLayout(button_layout);

    QVBoxLayout *main_layout2 = new QVBoxLayout();
    main_layout2->addLayout(main_layout);
    main_layout2->addWidget(dir_view);

    setWindowTitle(window_title);

    setLayout(main_layout2);

    connect(b, SIGNAL(clicked()), this, SLOT(get_index_then_close()));
    connect(lview, SIGNAL(clicked(QModelIndex)), this, SLOT(show_dir()));
}

Popup4::~Popup4()
{
    delete b;
    delete instruction_l;
    delete lview_slm;
    delete lview;
    delete dir_view;
}

void Popup4::get_index_then_close()
{
    *selected_index = lview->currentIndex().row();
    close();
}

void Popup4::show_dir()
{
    int selected_index = lview->currentIndex().row();
    dir_view->showMessage(status_sl->at(selected_index));
}
