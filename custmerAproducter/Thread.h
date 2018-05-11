#pragma once


#include <QThread>

class ThreadConsumer : public QThread
{
	Q_OBJECT

public:
	ThreadConsumer(QObject *parent);
	~ThreadConsumer();
	void run() Q_DECL_OVERRIDE;
	bool threadStatus();
	void setThreadStatus(bool status);
signals:
	void sendToMainWindow(const int);
private:
	bool m_threadStatus;
};

class ThreadProducer : public QThread
{
	Q_OBJECT

public:
	ThreadProducer(QObject *parent);
	~ThreadProducer();
	void run() Q_DECL_OVERRIDE;
	bool threadStatus();
	void setThreadStatus(bool status);
private:
	bool m_threadStatus;
};