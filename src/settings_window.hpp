#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>

#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>

#include "Settings.hpp"


class SettingsWindow : public QMainWindow
{
  Q_OBJECT

public:
  SettingsWindow();

  void ShowMessage()
  {
    QMessageBox msgBox;
    msgBox.setText("Настройки сохранены!");
    msgBox.exec();
  }

private slots:
  void OnButtonPressed()
  {
    m_settings.SetName(m_name->text().toUtf8().constData());
    m_settings.Save();
    ShowMessage();
  }

  void OnLevelChanged()
  {
    m_settings.SetLevel(static_cast<GameLevel>(m_level->currentIndex()));
  }

private:
  Settings m_settings;
  QComboBox * m_level;
  QLineEdit * m_name;
  QFormLayout * m_layout;
  QPushButton * m_button;
};
