#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_custmerAproducter.h"

class custmerAproducter : public QMainWindow
{
	Q_OBJECT

public:
	custmerAproducter(QWidget *parent = Q_NULLPTR);

private:
	Ui::custmerAproducterClass ui;
};
