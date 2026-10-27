#ifndef DeviceControl_H
#define DeviceControl_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <compatibility.h>
#include <bdaqctrl.h>

using namespace Automation::BDaq;
typedef unsigned char byte;

#define  deviceDescription  L"USB-5860,BID#0"


class DeviceControl : public QThread
{
	Q_OBJECT
public:
	explicit DeviceControl(QWidget* parent = nullptr);
	~DeviceControl();

	void preInit();
	void getInputState();
	void setOutputState();
	bool getOutputState(uint32& output);
	bool isExsitError(ErrorCode ret);

	void enableDevice(bool enable);
	void enableSaw(bool enable);

	

signals:
	void EmergencyStop();
	void ExtensionDevice();
	void ShortenDevice();

private:
	QMutex* Qm;
	QTimer* InputTimer;
	InstantDoCtrl* MyInstantDoCtrl;
	InstantDiCtrl* MyInstantDiCtrl;
	uint32 OutputVal = 0x00;
	int32 StartPort = 0;
	int32 PortCount = 1;
	ErrorCode RetIn = Success;
	ErrorCode RetOut = Success;
	bool isEmergencyStop = false;
	//const wchar_t* profilePath = L"../resources/device/DemoDevice.xml";
};

#endif // ONTOVEGA_H
