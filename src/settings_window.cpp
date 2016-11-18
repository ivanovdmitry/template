#include "settings_window.hpp"

#include <QApplication>

#include "gl_widget.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

SettingsWindow::SettingsWindow()
{
  QWidget * centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  button = new QPushButton("Сохранить");
  connect(button, SIGNAL(clicked()), this, SLOT( OnButtonPressed() ));

  name = new QLineEdit();

  level = new QComboBox(this);

  level->addItem("Простой", static_cast<unsigned char>(GameLevel::Easy));
  level->addItem("Средний", static_cast<unsigned char>(GameLevel::Medium));
  level->addItem("Сложный", static_cast<unsigned char>(GameLevel::Hard));
  level->setCurrentIndex(1);
  connect(level, SIGNAL(activated(int)), this, SLOT( OnLevelChanged() ));


  layout = new QFormLayout(centralWidget);


  layout->addRow("Твое имя: ", name);
  layout->addRow("Выбери уровень", level);
  layout->addRow("", button);


  setFocusPolicy(Qt::StrongFocus);
}
