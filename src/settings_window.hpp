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

signals:
  void SaveClicked();
  void LavelClicked();

private slots:
  void OnButtonPressed()
  {
    m_settings.SetName(name->text().toUtf8().constData());
    ShowMessage();
  }

  void OnLevelChanged()
  {
    m_settings.SetLevel(static_cast<GameLevel>(level->currentIndex()));
  }

private:
  Settings m_settings;
  QComboBox * level;
  QLineEdit * name;
  QFormLayout * layout;
  QPushButton * button;
};
