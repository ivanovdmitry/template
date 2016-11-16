#include "settings_window.hpp"

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>

#include "gl_widget.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

SettingsWindow::SettingsWindow()
{
  QWidget * centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  QPushButton * button = new QPushButton("Сохранить");
  QLineEdit * name = new QLineEdit();

  QComboBox * level = new QComboBox(this);
  level->addItem("Простой", 1);
  level->addItem("Средний", 2);
  level->addItem("Сложный", 3);
  level->setCurrentIndex(1);
  connect(level, SIGNAL(activated(int)), this, SLOT( /* bind to slot */ ));


  QFormLayout * layout = new QFormLayout(centralWidget);


  layout->addRow("Твое имя: ", name);
  layout->addRow("Выбери уровень", level);
  layout->addRow("", button);


  setFocusPolicy(Qt::StrongFocus);
}
