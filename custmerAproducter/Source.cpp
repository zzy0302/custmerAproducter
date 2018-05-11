#pragma once
#include "Thread.h"
#include<QWaitCondition>
#include <QMutex>
#include <QVector>
#include <QTime>

QWaitCondition numberNotFull;
QWaitCondition numberNotEmpty;
QMutex mutex;
QVector<int> vectInt;

const int NUMBER_SIZE = 3;

int generateRandomInteger(int min, int max);

ThreadConsumer::ThreadConsumer(QObject *parent)
	: QThread(parent)
{
	m_threadStatus = true;
}

ThreadConsumer::~ThreadConsumer()
{
}

void ThreadConsumer::run()
{
	while (m_threadStatus)
	{
		mutex.lock();
		if (vectInt.isEmpty())
			numberNotEmpty.wait(&mutex);
		emit sendToMainWindow(vectInt.value(0));
		vectInt.pop_front();
		mutex.unlock();
		numberNotFull.wakeAll();
	}
}

void ThreadConsumer::setThreadStatus(bool status)
{
	m_threadStatus = status;
}

bool ThreadConsumer::threadStatus()
{
	return m_threadStatus;
}

//===================================================================
//类的分界线


ThreadProducer::ThreadProducer(QObject *parent)
	: QThread(parent)
{
	m_threadStatus = true;
}

ThreadProducer::~ThreadProducer()
{
}

void ThreadProducer::run()
{
	while (m_threadStatus)
	{
		mutex.lock();
		if (vectInt.size() > NUMBER_SIZE)
			numberNotFull.wait(&mutex);
		mutex.unlock();
		int number = generateRandomInteger(0, 1000);
		mutex.lock();
		vectInt.push_back(number);
		mutex.unlock();
		numberNotEmpty.wakeAll();
		sleep(1);//避免频繁刷新界面
	}
}

void ThreadProducer::setThreadStatus(bool status)
{
	m_threadStatus = status;
}

bool ThreadProducer::threadStatus()
{
	return m_threadStatus;
}

// 生成随机数 min:随机数的最小值，max:随机数的最大值
int generateRandomInteger(int min, int max)
{
	Q_ASSERT(min < max);
	// 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
	// 每次启动程序，只添加一次种子，以做到数字真正随机。
	static bool seedStatus;
	if (!seedStatus)
	{
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
		seedStatus = true;
	}
	int nRandom = qrand() % (max - min);
	nRandom = min + nRandom;

	return nRandom;
}
