#include "settings_window.hpp"

#include <QApplication>
#include <QString>

#include "gl_widget.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

SettingsWindow::SettingsWindow()
{
  m_settings.Read();
  QWidget * centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  m_button = new QPushButton("Сохранить");
  connect(m_button, SIGNAL(clicked()), this, SLOT( OnButtonPressed() ));

  m_name = new QLineEdit();
  m_name->setText(QString::fromUtf8(m_settings.GetName().c_str()));

  m_level = new QComboBox(this);

  m_level->addItem("Простой", static_cast<unsigned char>(GameLevel::Easy));
  m_level->addItem("Средний", static_cast<unsigned char>(GameLevel::Medium));
  m_level->addItem("Сложный", static_cast<unsigned char>(GameLevel::Hard));
  m_level->setCurrentIndex(static_cast<unsigned char>(m_settings.GetLevel()));
  connect(m_level, SIGNAL(activated(int)), this, SLOT( OnLevelChanged() ));


  m_layout = new QFormLayout(centralWidget);


  m_layout->addRow("Твое имя: ", m_name);
  m_layout->addRow("Выбери уровень", m_level);
  m_layout->addRow("", m_button);


  setFocusPolicy(Qt::StrongFocus);
}
