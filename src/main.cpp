#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"
#include "settings_window.hpp"

int main(int argc, char ** argv)
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow mw;
  SettingsWindow sw;
  mw.show();
  sw.show();
  return a.exec();
}
