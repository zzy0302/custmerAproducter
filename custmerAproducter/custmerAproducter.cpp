

#include <QtWidgets/QMainWindow>
#include "custmerAproducter.h"

class ThreadConsumer;
class ThreadProducer;

class testApp : public QMainWindow
{
	Q_OBJECT

public:
	testApp(QWidget *parent = Q_NULLPTR);
	~testApp();

	protected slots:
	void on_btnStart_clicked();
	void handleResult(const int);

private:
	Ui::testAppClass ui;
	ThreadConsumer* thdConsumer;
	ThreadProducer* thdProducer;
};