#include "DeviceControl.h"
#include "QCoreApplication.h"
#ifdef _WIN32
#include <windows.h>
#endif

DeviceControl::DeviceControl(QWidget* parent) : QThread(parent)
{
	Qm = new QMutex;
	MyInstantDoCtrl = InstantDoCtrl::Create();
	MyInstantDiCtrl = InstantDiCtrl::Create();
	InputTimer = new QTimer();
	QObject::connect(InputTimer, &QTimer::timeout, this, &DeviceControl::getInputState);
}

DeviceControl::~DeviceControl()
{
	MyInstantDoCtrl->Dispose();
	MyInstantDiCtrl->Dispose();
}

void DeviceControl::preInit()
{
	DeviceInformation devInfo(deviceDescription);
	MyInstantDiCtrl->Cleanup();
	MyInstantDoCtrl->Cleanup();
	RetIn = MyInstantDoCtrl->setSelectedDevice(devInfo);
	RetOut = MyInstantDiCtrl->setSelectedDevice(devInfo);
	if (!InputTimer->isActive())
	{
		InputTimer->start(100);
	}
}

void DeviceControl::getInputState()
{
	//Qm->lock();
	if (isExsitError(RetIn))
	{
		preInit();
	}
	uint8 bufferForReading[64] = { 0 };
	RetIn = MyInstantDiCtrl->Read(StartPort, PortCount, bufferForReading);
	if (isExsitError(RetIn))
	{
		return;
	}

	if (bufferForReading[0] & 0x80) //急停信号
	{
		printf("急停触发\n");
		emit this->enableDevice(true);
		emit this->enableSaw(false);
		emit this->EmergencyStop();
	}
	else if (bufferForReading[0] & 0x01) //支地伸长信号
	{
		printf("支地伸长触发\n");
		emit this->ExtensionDevice();
	}
	else if (bufferForReading[0] & 0x02) //支地缩短信号
	{
		printf("支地缩短触发\n");
		emit this->ShortenDevice();
	}
	//Qm->unlock();
}

void DeviceControl::setOutputState()
{
	if (isExsitError(RetOut)) 
	{
		preInit();
	}
	uint8  bufferForWriting[64] = { 0 };
	bufferForWriting[0] = OutputVal;
	RetOut = MyInstantDoCtrl->Write(StartPort, PortCount, bufferForWriting);
	isExsitError(RetOut);
}

bool DeviceControl::getOutputState(uint32 &output)
{
	if (isExsitError(RetOut)) 
	{
		preInit();
	}
	BYTE bufferForReading[64] = { 0 };
	RetOut = MyInstantDoCtrl->Read(StartPort, PortCount, bufferForReading);
	if (isExsitError(RetOut))
	{
		return false;
	}
	output = bufferForReading[0];
	//printf("Now, DO port status is:  0x%X\n\n", output);
	return true;
}

bool DeviceControl::isExsitError(ErrorCode ret)
{
	if (BioFailed(ret))
	{
		//wchar_t enumString[256];
		//AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
		//printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
		//if (InputTimer->isActive())
		//{
		//	InputTimer->stop();
		//}
		return true;
	}
	else
	{
		//printf("complete success!\n");
		return false;
	}	
}

//00位控制
void DeviceControl::enableDevice(bool enable)
{
	uint32 currentOutput;
	if (!this->getOutputState(currentOutput))
	{
		return;
	}
	if (enable)
	{
		OutputVal = currentOutput | 0x01;  //关闭支地
	}
	else
	{
		OutputVal = currentOutput & (~0x01);
	}
	this->setOutputState();
}

//03位控制
void DeviceControl::enableSaw(bool enable)
{
	uint32 currentOutput;
	if (!this->getOutputState(currentOutput))
	{
		return;
	}
	if (enable)
	{
		OutputVal = currentOutput | 0x08;  //开启摆据
	}
	else
	{
		OutputVal = currentOutput & (~0x08);
	}
	this->setOutputState();
}



